#include <iostream>
#include "graph.h"
#include <set>
#include <queue>
#include <map>
#include <algorithm>   // для работы reverse в unroll

using namespace std;

// node
// добавить соседа и вес ребра 
void Node::addNeighbour(Node *neighbour, int weight)
{
    neighbours.insert(neighbour);
    weights[neighbour] = weight;
}

// удалить соседа и апись о весе
void Node::removeNeighbour(Node *neighbour)
{
    neighbours.erase(neighbour);
    weights.erase(neighbour);
}

// получить вес ребра до указ сосед
int Node::getWeight(Node *neighbour) const
{
    auto it = weights.find(neighbour);
    if (it != weights.end())
        return it->second;
    return -1;
}


//realication graph
// добавить узел в множ узлов графа
void Graph::addNode(Node *node)
{
    nodes.insert(node);
}

// удалить узел и убрать его из соседей
void Graph::removeNode(Node *node)
{
    nodes.erase(node);
    // пройти по всем оставшимся узлам и удалить из них ссылку на удаляемый узел
    for (set<Node *>::iterator it = nodes.begin(); it != nodes.end(); ++it)
    {
        (*it)->removeNeighbour(node);
    }
}

// добавить неор ребро
void Graph::addEdge(Node *begin, Node *end, int weight)
{
    if (nodes.find(begin) == nodes.end()) return;
    if (nodes.find(end) == nodes.end())   return;
    begin->addNeighbour(end, weight);
    end->addNeighbour(begin, weight);
}

// удалить неор ребро между begin и end
void Graph::removeEdge(Node *begin, Node *end)
{
    if (nodes.find(begin) == nodes.end() || nodes.find(end) == nodes.end())
        return;
    begin->removeNeighbour(end);
    end->removeNeighbour(begin);
}


// bfs in shirinu
// проверка связности обходом в ширину
bool BFS::connected(Node *begin, Node *end)
{
    if (begin == end)
        return true;

    queue<Node *> nodes;
    nodes.push(begin);
    set<Node *> visited;

    while (!nodes.empty())
    {
        Node *next = nodes.front();
        nodes.pop();

        if (end == next)
            return true;

        // помечаем и добавляем всех непос соседей
        if (visited.find(next) == visited.end())
        {
            visited.insert(next);
            for (node_iterator it = next->nb_begin(); it != next->nb_end(); ++it)
            {
                if (visited.find(*it) == visited.end())
                    nodes.push(*it);
            }
        }
    }
    return false;
}


// dfs in glubinu
// открытый метод чистим историю и запускаем рекурсивный обход
bool DFS::connected(Node *begin, Node *end)
{
    visited.clear();
    return connected(begin, end, 0);
}

bool DFS::connected(Node *begin, Node *end, int depth)
{
    if (begin == end)
        return true;

    visited.insert(begin);

    for (node_iterator it = begin->nb_begin(); it != begin->nb_end(); ++it)
    {
        if (visited.find(*it) == visited.end())
        {
            if (connected(*it, end, depth + 1))
                return true;
        }
    }
    return false;
}


// priority qune
// линейный поиск по всем
MarkedNode PriorityQueue::pop()
{
    int minIndex = 0;
    for (size_t i = 1; i < nodes.size(); ++i)
    {
        if (nodes[i].mark < nodes[minIndex].mark)
            minIndex = i;
    }
    MarkedNode mn = nodes[minIndex];
    nodes.erase(nodes.begin() + minIndex);
    return mn;
}

// добавить новый элемент в очередь
void PriorityQueue::push(Node *node, int mark, Node *prev)
{
    nodes.push_back(MarkedNode(node, mark, prev));
}


//dijstra
// поиск кратчайшего пути между begin и end
Way Dijkstra::shortestWay(Node *begin, Node *end)
{
    if (begin == end)
    {
        Way way;
        way.nodes.push_back(begin);
        way.length = 0;
        return way;
    }

    PriorityQueue nodes;
    nodes.push(begin, 0, nullptr);
    std::map<Node *, MarkedNode> visited;  // узел -> кратчайший путь до него

    while (!nodes.empty())
    {
        MarkedNode next = nodes.pop();

        // скип если не самый короткий
        if (visited.find(next.node) != visited.end())
            continue;

        visited[next.node] = next;

        if (end == next.node)
            return unroll(visited, begin, end);

        // перебираем соседей текущего узла
        for (node_iterator it = next.node->nb_begin(); it != next.node->nb_end(); ++it)
        {
            // вес до соседа = вес текущего пути + вес ребра
            int weight = (*it)->getWeight(next.node) + next.mark;

            if (visited.find(*it) == visited.end())
            {
                nodes.push(*it, weight, next.node);
            }
        }
    }

    // ненашёлся
    return Way();
}

// razvernute put
// восстановить путь от begin до curr по visited
Way unroll(std::map<Node *, MarkedNode> visited, Node *begin, Node *curr)
{
    Way way;
    way.length = visited[curr].mark;

    while (curr != begin)
    {
        way.nodes.push_back(curr);
        curr = visited[curr].prev;
        if (curr == nullptr)  
            break;
    }
    way.nodes.push_back(begin);

    // перевернуть потому что собирали с конца
    reverse(way.nodes.begin(), way.nodes.end());

    return way;
}