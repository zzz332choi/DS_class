#include <iostream>
#include <vector>
#include "GraphMethod.h"
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <list>
#include <utility>
#include <fstream>

using namespace std;

bool BFS(Graph* graph, char option, int vertex, ofstream* fout)
{
    // The vertex you entered does not exist in the graph
    if(vertex > graph->getSize() || vertex <= 0) return false; 

    queue <int> q;
    vector <int> v;
    bool* visited = new bool [graph->getSize()];
    memset(visited, false, sizeof(bool) * graph->getSize()); // init

    map<int, int>* m = new map<int, int>[graph->getSize()];

    if (option == 'Y') { // directed
        for (int i = 1; i <= graph->getSize(); i++) {
            graph->getAdjacentEdgesDirect(i, m + (i - 1));
        }
    }
    else if (option == 'N') { // undirected
        for (int i = 1; i <= graph->getSize(); i++) {
            graph->getAdjacentEdges(i, m + (i - 1));
        }
    }

    else { // Invalid option
        delete[] m;
        delete[] visited;
        return false;
    }

    q.push(vertex);
    visited[vertex - 1] = 1;
    v.push_back(vertex);

    while (!q.empty()) {
        int num = q.front();
        q.pop();

        for (auto iter = m[num - 1].begin(); iter != m[num - 1].end(); iter++) {
            if (!visited[iter->first - 1]) { // Nodes not yet visited
                visited[iter->first - 1] = true;
                v.push_back(iter->first);
                q.push(iter->first);
            }
        }
    }

    *fout << "======== BFS ========" << endl;

    if (option == 'Y') *fout << "Directed ";
    else *fout << "Undirected ";

    *fout << "Graph BFS result" << endl;
    *fout << "startvertex: " << vertex << endl;

    for (int i = 0; i < v.size(); i++) {
        *fout << v[i];
        if (i != v.size() - 1) *fout << " -> ";
    }

    *fout << endl << "=====================" << endl << endl;

    delete[] m;
    delete[] visited;

    return true;
}

bool DFS(Graph* graph, char option, int vertex, ofstream* fout)
{
    // The vertex you entered does not exist in the graph
    if (vertex > graph->getSize() || vertex <= 0) return false;

    stack <int> sta;
    vector <int> v;
    bool* visited = new bool[graph->getSize()];
    memset(visited, false, sizeof(bool) * graph->getSize()); // init

    map<int, int>* m = new map<int, int>[graph->getSize()];

    if (option == 'Y') { // directed
        for (int i = 1; i <= graph->getSize(); i++) {
            graph->getAdjacentEdgesDirect(i, m + (i - 1));
        }
    }
    else if (option == 'N') { // undirected
        for (int i = 1; i <= graph->getSize(); i++) {
            graph->getAdjacentEdges(i, m + (i - 1));
        }
    }

    else { // Invalid option
        delete[] m;
        delete[] visited;
        return false;
    }

    sta.push(vertex);
    visited[vertex - 1] = 1;
    v.push_back(vertex);

    while (!sta.empty()) {
        int num = sta.top();
        sta.pop();

        for (auto iter = m[num - 1].begin(); iter != m[num - 1].end(); iter++) {
            if (!visited[iter->first - 1]) { // Nodes not yet visited
                visited[iter->first - 1] = true;
                sta.push(num);
                sta.push(iter->first);
                v.push_back(iter->first);
                break;
            }
        }
    }

    *fout << "======== DFS ========" << endl;

    if (option == 'Y') *fout << "Directed ";
    else *fout << "Undirected ";

    *fout << "Graph DFS result" << endl;
    *fout << "startvertex: " << vertex << endl;

    for (int i = 0; i < v.size(); i++) {
        *fout << v[i];
        if (i != v.size() - 1) *fout << " -> ";
    }

    *fout << endl << "=====================" << endl << endl;

    delete[] m;
    delete[] visited;

    return true;
 }

bool Kruskal(Graph* graph, ofstream* fout)
{
 
    int* parent = new int[graph->getSize() + 1];
    memset(parent, -1, sizeof(int) * (graph->getSize() + 1)); // initialization

    int cost = 0;

    map<int, int>* sol = new map<int, int>[graph->getSize()];

    int edges = 0;

    while (edges < graph->getSize()) {
        
    }


    delete[] parent;
    delete[] sol;

    return true;
}

bool Dijkstra(Graph* graph, char option, int vertex, ofstream* fout)
{
    return true;
}

bool Bellmanford(Graph* graph, char option, int s_vertex, int e_vertex, ofstream* fout)
{
    return true;
}

bool FLOYD(Graph* graph, char option, ofstream* fout)
{
    return true;
}



int collapsingfind(int* parent, int i)
{
    // Find the root of the tree containing element i.
    // Use the collapsing rule to collapse all nodes from i to the root.
    int r = i;
    for (; parent[r] >= 0; r = parent[r]); // find root
    while (i != r) {
        int s = parent[i];
        parent[i] = r;
        i = s;
    }
    return r;
}

void weightedunion(int* parent, int i, int j)
{
    // union sets with roots i and j, i != j, using the weighting rule
    // parent[i] = -count[i] and parent[j] = -count[j]
    int temp = parent[i] + parent[j];
    if (parent[i] > parent[j]) { // i has fewer nodes
        parent[i] = j;
        parent[j] = temp;
    }
    else { // j has fewer nodes (or i and j have the same number of nodes)
        parent[j] = i;
        parent[i] = temp;    
    }
}

bool check(int* parent)
{
    int cnt = 0;
    for (int i = 1; i <= sizeof(parent) / sizeof(int); i++) {
        if (parent[i] == -1) cnt++;
    }
    return cnt != 1;
}

bool KWANGWOON(Graph* graph, int vertex, ofstream* fout) {
    return true;
}