#include "graph_task.h"
#include <fstream>
#include <sstream>
#include <iostream>


//  node
void Node::addNeighbour(Node *neighbour, int weight)
{
    neighbours.insert(neighbour);
    weights[neighbour] = weight;
}

void Node::removeNeighbour(Node *neighbour)
{
    neighbours.erase(neighbour);
    weights.erase(neighbour);
}

int Node::getWeight(Node *neighbour) const
{
    auto it = weights.find(neighbour);
    if (it != weights.end())
        return it->second;
    return -1;
}

//  graph

void Graph::addNode(Node *node)
{
    nodes.insert(node);
}

void Graph::removeNode(Node *node)
{
    nodes.erase(node);
    // убираем удалённый узел из списков соседей всех оставшихся узлов
    for (auto it = nodes.begin(); it != nodes.end(); ++it)
        (*it)->removeNeighbour(node);
}

void Graph::addEdge(Node *begin, Node *end, int weight)
{
    if (nodes.find(begin) == nodes.end()) return;
    if (nodes.find(end)   == nodes.end()) return;
    // неориентированный граф — добавляем ребро в обе стороны
    begin->addNeighbour(end, weight);
    end->addNeighbour(begin, weight);
}

void Graph::removeEdge(Node *begin, Node *end)
{
    if (nodes.find(begin) == nodes.end() || nodes.find(end) == nodes.end())
        return;
    begin->removeNeighbour(end);
    end->removeNeighbour(begin);
}

// конструктор: читает файл и строит граф по парам 
// поддерживает разделители пробел и табуляцию
Graph::Graph(const char *file_name)
{
    ifstream fin(file_name);
    if (!fin.is_open())
    {
        cerr << "ERROR: NOT OPEN FILE " << file_name << endl;
        return;
    }

    map<string, Node *> nodeMap; // имя вершины -> указатель на узел

    string line;
    getline(fin, line); // заголовок пропускаем

    while (getline(fin, line))
    {
        if (line.empty()) continue;

        istringstream iss(line);
        string src, tgt;
        // >> автоматически разбивает (пробел, таб)
        if (!(iss >> src >> tgt)) continue;

        // создаём узел-источник, если ещё не существует
        if (nodeMap.find(src) == nodeMap.end())
        {
            Node *n = new Node(src);
            nodeMap[src] = n;
            addNode(n);
        }

        // создаём узел-назначение, если ещё не существует
        if (nodeMap.find(tgt) == nodeMap.end())
        {
            Node *n = new Node(tgt);
            nodeMap[tgt] = n;
            addNode(n);
        }

        addEdge(nodeMap[src], nodeMap[tgt]);
    }
}

// деструктор
Graph::~Graph()
{
    for (auto it = nodes.begin(); it != nodes.end(); ++it)
        delete *it;
}


//  BFS 
bool BFS::connected(Node *begin, Node *end)
{
    if (begin == end) return true;

    queue<Node *> q;
    q.push(begin);
    set<Node *> visited;

    while (!q.empty())
    {
        Node *curr = q.front();
        q.pop();

        if (curr == end) return true;

        // если узел ещё не посещён — помечаем и добавляем его соседей в очередь
        if (visited.find(curr) == visited.end())
        {
            visited.insert(curr);
            for (node_iterator it = curr->nb_begin(); it != curr->nb_end(); ++it)
            {
                if (visited.find(*it) == visited.end())
                    q.push(*it);
            }
        }
    }
    return false;
}

// обход в ширину от стартового узла
// возвращает множество всех достижимых узлов — это и есть одна связная компонента
set<Node *> BFS::getComponent(Node *start)
{
    set<Node *> visited;
    queue<Node *> q;
    q.push(start);

    while (!q.empty())
    {
        Node *curr = q.front();
        q.pop();

        if (visited.find(curr) != visited.end())
            continue;

        visited.insert(curr);

        // добавляем в очередь всех ещё непосещённых соседей
        for (node_iterator it = curr->nb_begin(); it != curr->nb_end(); ++it)
        {
            if (visited.find(*it) == visited.end())
                q.push(*it);
        }
    }

    return visited;
}

//  поиск несвязных компонент 
vector<set<Node *>> findComponents(const Graph &g)
{
    set<Node *> allVisited;          // все уже распределённые вершины
    vector<set<Node *>> components;

    for (node_iterator it = g.begin(); it != g.end(); ++it)
    {
        // если вершина ещё не принадлежит ни одной компоненте — начинаем новый BFS
        if (allVisited.find(*it) == allVisited.end())
        {
            BFS bfs(g);
            set<Node *> comp = bfs.getComponent(*it);

            components.push_back(comp);

            // отмечаем все вершины найденной компоненты как обработанные
            allVisited.insert(comp.begin(), comp.end());
        }
    }

    return components;
}


//  сохранение компоненты в файл
void saveComponent(const set<Node *> &component, const string &filename)
{
    ofstream out(filename);
    if (!out.is_open())
    {
        cerr << "Ошибка: не удалось создать файл " << filename << endl;
        return;
    }

    out << "Source\tTarget\n";

    // запоминаем уже выведенные пары узлов
    set<pair<Node *, Node *>> printed;

    for (Node *node : component)
    {
        for (node_iterator it = node->nb_begin(); it != node->nb_end(); ++it)
        {
            Node *nb = *it;
            // выводим ребро только если обратное ещё не выведено
            if (printed.find({nb, node}) == printed.end())
            {
                out << node->getName() << "\t" << nb->getName() << "\n";
                printed.insert({node, nb});
            }
        }
    }
}
