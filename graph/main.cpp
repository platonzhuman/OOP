#include <iostream>
#include <vector>
#include "graph.h"

using namespace std;

void printPath(const Way &way)
{
    if (way.length < 0)
    {
        cout << "  No path!" << endl;
        return;
    }

    cout << "  Len: " << way.length << " | Path: ";
    for (size_t i = 0; i < way.nodes.size(); i++)
    {
        cout << way.nodes[i]->getName() << (i < way.nodes.size() - 1 ? " -> " : "");
    }
    cout << endl;
}

int main()
{
    cout << "--- Graph Testing ---" << endl;

    Graph g;
    Node *n0 = new Node("0"), *n1 = new Node("1"), *n2 = new Node("2");
    Node *n3 = new Node("3"), *n4 = new Node("4"), *n5 = new Node("5");
    Node *isolated = new Node("iso");

    g.addNode(n0);
    g.addNode(n1);
    g.addNode(n2);
    g.addNode(n3);
    g.addNode(n4);
    g.addNode(n5);
    g.addNode(isolated);

    g.addEdge(n0, n1, 10);
    g.addEdge(n1, n2, 15);
    g.addEdge(n2, n5, 30);
    g.addEdge(n0, n5, 50);
    g.addEdge(n0, n3, 20);
    g.addEdge(n3, n4, 25);
    g.addEdge(n4, n5, 15);
    g.addEdge(n1, n3, 10);
    g.addEdge(n2, n4, 5);

    BFS bfs(g);
    cout << "\n1. BFS:" << endl;
    cout << "   0-5: " << (bfs.connected(n0, n5) ? "YES" : "NO") << endl;
    cout << "   0-iso: " << (bfs.connected(n0, isolated) ? "YES" : "NO") << endl;

    DFS dfs(g);
    cout << "\n2. DFS:" << endl;
    cout << "   0-2: " << (dfs.connected(n0, n2) ? "YES" : "NO") << endl;

    Dijkstra dijkstra(g);
    cout << "\n3. Dijkstra:" << endl;
    printPath(dijkstra.shortestWay(n0, n5));
    printPath(dijkstra.shortestWay(n0, n2));
    printPath(dijkstra.shortestWay(n0, isolated));

    cout << "\n4. Remove Edge 0-1:" << endl;
    g.removeEdge(n0, n1);
    cout << "   0-1: " << (bfs.connected(n0, n1) ? "YES" : "NO") << endl;

    cout << "\n5. Remove Node 4:" << endl;
    g.removeNode(n4);
    cout << "   3-5: " << (bfs.connected(n3, n5) ? "YES" : "NO") << endl;

    cout << "\n6. Final Path 0-5:" << endl;
    printPath(dijkstra.shortestWay(n0, n5));

    delete n0;
    delete n1;
    delete n2;
    delete n3;
    delete n4;
    delete n5;
    delete isolated;
    cout << "\nDone." << endl;

    return 0;
}
