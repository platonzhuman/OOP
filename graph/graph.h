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
    set<Node *> neighbours;      // множество указателей на соседние узлы
    map<Node *, int> weights;    // отображение: сосед -> вес ребра

    // приватные методы добавления/удаления соседа (+для друзей)
    void addNeighbour(Node *neighbour, int weight = 1);
    void removeNeighbour(Node *neighbour);

public:
    // конструктор: задаёт имя узла
    Node(const string &aname) : name(aname) {}

    // получить имя узла
    const string &getName() const { return name; }

    // получить вес ребра до указанного сосед
    int getWeight(Node *neighbour) const;

    // итераторы для обхода соседей
    node_iterator nb_begin() const { return neighbours.begin(); }
    node_iterator nb_end() const   { return neighbours.end();   }

    // вружественные классы для доступа к приватным полям
    friend class Graph;
    friend class Dijkstra;
};


//этот класс озволяет добавлять/удалять неор узлы и рёбра 
class Graph
{
    set<Node *> nodes;

public:
    // добавить узел в граф
    void addNode(Node *node);

    // удалить узел из графа + все инц ребра
    void removeNode(Node *node);

    // добавить неор ребро с заданным весом 
    void addEdge(Node *begin, Node *end, int weight = 1);

    // удалить неор ребро между двумя узлами
    void removeEdge(Node *begin, Node *end);

    // итераторы для обхода всех узлов графа
    node_iterator begin() const { return nodes.begin(); }
    node_iterator end() const   { return nodes.end();   }
};

// проверяет связность двух узлов в графе поочередно (в ширигу)
class BFS
{
    const Graph &graph;

public:
    // конструктор принимает ссылку на граф далее поиск
    BFS(const Graph &agraph) : graph(agraph) {}

    // Проверить есть ли путь от begin до end
    bool connected(Node *begin, Node *end);
};


// проверяет связаность двух узлов рекурсивным обходом (в глубину)
class DFS
{
    const Graph &graph;
    set<Node *> visited;   // множество посещённых узлов

    // приватная рек реализация
    bool connected(Node *begin, Node *end, int depth);

public:
    // конструктор
    DFS(const Graph &agraph) : graph(agraph) {}

    // открытый метод очищает историю посещений и запускает поиск
    bool connected(Node *begin, Node *end);
};

// далее тут идут всп алгоритмы дейкстры

// узел с меткой и указателем на предыдущий узел в пути
struct MarkedNode
{
    Node *node;
    int mark;
    Node *prev;

    MarkedNode(Node *anode = 0, int amark = 0, Node *aprev = 0)
        : node(anode), mark(amark), prev(aprev) {}
};

// извлечение элемента с минзначением
class PriorityQueue
{
    vector<MarkedNode> nodes;

public:
    // извлечь узел с мин меткой и удалить его 
    MarkedNode pop();

    // добавить новый элемент в очередь
    void push(Node *node, int mark, Node *prev);

    // проверка на пустоту
    bool empty() const { return nodes.empty(); }
};

// последовательность узлов и сумарная длина пути
struct Way
{
    std::vector<Node *> nodes;
    int length;

    // конструктор по умол
    Way() : length(-1) {}
};

// дейкстра
class Dijkstra
{
    const Graph &graph;

public:
    // констр
    Dijkstra(const Graph &agraph) : graph(agraph) {}

    // вывод кратчайший путь от begin до end.
    Way shortestWay(Node *begin, Node *end);
};

// развернуть путь от end до begin,
Way unroll(map<Node *, MarkedNode> visited, Node *begin, Node *curr);