#include "graph_task.h"
#include <iostream>

int main()
{
    Graph g("testgraph.txt");
    vector<set<Node *>> comp = findComponents(g);

    cout << "testgraph: component = " << comp.size() << endl;
    for (size_t i = 0; i < comp.size(); i++)
    {
        string fname = "test_component_" + to_string(i) + ".txt";
        saveComponent(comp[i], fname);
        cout << "  " << fname << " -> " << comp[i].size() << " count" << endl;
    }

    Graph g2("1000.csv");
    vector<set<Node *>> comp2 = findComponents(g2);

    cout << "\n1000.csv: component = " << comp2.size() << endl;
    for (size_t i = 0; i < comp2.size(); i++)
    {
        string fname = "csv_component_" + to_string(i) + ".txt";
        saveComponent(comp2[i], fname);
        cout << "  " << fname << " -> " << comp2[i].size() << " count" << endl;
    }

    return 0;
}
