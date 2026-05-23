#pragma once
#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <string>
#include <queue>

using namespace std;

class Node;

// итератор для перебора соседей узла
typedef set<Node *>::const_iterator node_iterator;


class Node
{
    string name;
    set<Node *> neighbours;   // множество указателей на соседние узлы
    map<Node *, int> weights; // отображение: сосед -> вес ребра

    // приватные методы добавления/удаления соседа (только для друзей)
    void addNeighbour(Node *neighbour, int weight = 1);
    void removeNeighbour(Node *neighbour);

public:
    Node(const string &aname) : name(aname) {}

    const string &getName() const { return name; }
    int getWeight(Node *neighbour) const;

    node_iterator nb_begin() const { return neighbours.begin(); }
    node_iterator nb_end()   const { return neighbours.end(); }

    friend class Graph;
};


class Graph
{
    set<Node *> nodes;

public:
    Graph() {}

    // конструктор: строит граф из файла с парами рёбер (Source/Target)
    Graph(const char *file_name);

    // деструктор: освобождает все узлы, созданные при чтении файла
    ~Graph();

    void addNode(Node *node);
    void removeNode(Node *node);
    void addEdge(Node *begin, Node *end, int weight = 1);
    void removeEdge(Node *begin, Node *end);

    node_iterator begin() const { return nodes.begin(); }
    node_iterator end()   const { return nodes.end(); }
};


class BFS
{
    const Graph &graph;

public:
    BFS(const Graph &agraph) : graph(agraph) {}

    // проверить, есть ли путь между двумя узлами (обход в ширину)
    bool connected(Node *begin, Node *end);

    // вернуть все узлы, достижимые из start — одна связная компонента
    set<Node *> getComponent(Node *start);
};


// найти все несвязные компоненты графа с помощью BFS
vector<set<Node *>> findComponents(const Graph &g);

// сохранить одну компоненту в файл (формат как TestGraph.txt: Source\tTarget)
void saveComponent(const set<Node *> &component, const string &filename);
