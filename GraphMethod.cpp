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
#include <cstring>
#include <algorithm>

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

    if (!graph->getSize()) return false;

    vector <W> v;

    map<int, int>* m = new map<int, int>[graph->getSize()];

    for (int i = 1; i <= graph->getSize(); i++) {
        graph->getAdjacentEdges(i, m + (i - 1));
        for (auto it = m[i - 1].begin(); it != m[i - 1].end(); it++) {
            if(it->second) v.push_back({ it->second, i, it->first });
        }
    }
    
    // sort
    quicksort(v, 0, v.size() - 1);
     
    int* parent = new int[(graph->getSize() + 1)];
    memset(parent, -1, sizeof(int) * ((graph->getSize() + 1))); // initialization

    int cost = 0;

    map<int, int>* sol = new map<int, int>[graph->getSize()];
 
    int edges = 0;// , prev_edges = 0;
    int cnt = 0;

    for (int i = 0; i < graph->getSize(); i++) {
        for (auto it = m[i].begin(); it != m[i].end(); it++) {
            if (it->second < 0) { // Negative Weight Found
                // deallocation
                delete[] parent;
                delete[] sol;
                delete[] m;
                return false;
            }
        }
    }

    while (edges < v.size()) {
        W e = v[edges];

        int S = e.s; // start
        int E = e.e; // end
        
        // find set?
        int p = collapsingfind(parent, S);
        int q = collapsingfind(parent, E);

        if (p != q) { // Cycle not formed
            weightedunion(parent, p, q); // union
            sol[S - 1].insert({ E, e.w });
            sol[E - 1].insert({ S, e.w });
            cost += e.w;
            cnt++;
        }

        edges++;

        //if (!check(parent)) break; // found mst
        //if (edges == graph->getSize()) break;
        if (cnt == graph->getSize() - 1) break;
    }

    //if (check(parent)) { // fault
    if (cnt < graph->getSize() - 1) { // fault
        delete[] parent;
        delete[] m;
        delete[] sol;

        return false;
    }

    *fout << "======= Kruskal =======" << endl;

    for (int i = 0; i < graph->getSize(); i++) {
        *fout << '[' << i + 1 << "]     ";

        for (auto it = sol[i].begin(); it != sol[i].end(); it++) {
            *fout << it->first << '(' << it->second << ')';
        }

        *fout << endl;
    }


    *fout << "cost: " << cost << endl;
    *fout << "=====================" << endl << endl;

    delete[] parent;
    delete[] m;
    delete[] sol;

    return true;
}

bool Dijkstra(Graph* graph, char option, int vertex, ofstream* fout)
{
    // The vertex you entered does not exist in the graph
    if (vertex > graph->getSize() || vertex <= 0) return false;
   
    map<int, int>* m = new map<int, int>[graph->getSize()];
    vector <int> *v = new vector<int>[graph->getSize()]; // save path
    // vector is not empty = the node visited

    int* dist = new int[graph->getSize()];

    // initialization
    // memset(dist, inf, sizeof(int) * graph->getSize()); 
    // infinite := 1,000,000,000 (1Billion)
    for (int i = 0; i < graph->getSize(); i++) dist[i] = inf;
    
    dist[vertex - 1] = 0; // self

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
        delete[] dist;
        delete[] v;
        delete[] m;
        //delete[] visited;
        return false;
    }


    for (int i = 0; i < graph->getSize(); i++) {
        for (auto it = m[i].begin(); it != m[i].end(); it++) {
            if (it->second < 0) { // Negative Weight Found
                // deallocation
                delete[] dist;
                delete[] v;
                delete[] m;
                return false;
            }
        }
    }

    // initialize
    for (auto it = m[vertex - 1].begin(); it != m[vertex - 1].end(); it++) {
        dist[it->first - 1] = it->second;
        //v[it->second - 1].push_back(vertex);
    }
    
    int* prev = new int[graph->getSize()];
    memset(prev, -1, sizeof(int) * graph->getSize());

    v[vertex - 1].push_back(vertex);

    for (int i = 0; i < graph->getSize() - 1; i++) {
        // deterine n-1 paths from vertex

        int u = -1;

        // get small node
		int min = inf;
		
		for (int j = 0; j < graph->getSize(); j++) {
			if (dist[j] < min && v[j].empty()) {
				min = dist[j];
				u = j;
			}
		}

        if (u < 0) break; // no more path


        if (prev[u] == -1) {
            prev[u] = vertex;
            v[u].push_back(vertex);
        }
        else for (int j = 0; j < v[prev[u] - 1].size(); j++) { // save the path
            v[u].push_back(v[prev[u] - 1][j]);
        }

        v[u].push_back(u + 1);

        for (int j = 0; j < graph->getSize(); j++) { // Update for non-visited nodes
            if (v[j].empty()) {
                if (m[u].find(j + 1) != m[u].end()) {
                    if (dist[u] + m[u].find(j + 1)->second < dist[j]) {
                        dist[j] = dist[u] + m[u].find(j + 1)->second;
                        prev[j] = u + 1;

                        //if (m[u].find(j + 1)->second < 0) { // Negative Weight Found
                        //    flag = true; 
                        //    break;
                        //}
                    }
                }
            }
        }
    }

    *fout << "======= Dijkstra =======" << endl;

    if (option == 'Y') *fout << "Directed ";
    else *fout << "Undirected ";

    *fout << "Graph Dijkstra result" << endl;
    *fout << "startvertex: " << vertex << endl;

    for (int i = 0; i < graph->getSize(); i++) {
        if (i == vertex - 1) continue; // exception start vertex

        *fout << '[' << i + 1 << "] ";

        if (v[i].empty()) *fout << 'x' << endl;
        else {
            for (int j = 0; j < v[i].size(); j++) {
                *fout << v[i][j];
                
                if (j != v[i].size() - 1) *fout << " -> ";
                else *fout << " (" << dist[i] << ')' << endl;
            }
        }

    }

    *fout << "=====================" << endl << endl;

    // deallocation
    delete[] prev;
    delete[] dist;
    delete[] v;
    delete[] m;
   //delete[] visited;

    return true;
}

bool Bellmanford(Graph* graph, char option, int s_vertex, int e_vertex, ofstream* fout)
{
    // The vertex you entered does not exist in the graph
    if (s_vertex > graph->getSize() || s_vertex <= 0) return false;
    else if (e_vertex > graph->getSize() || e_vertex <= 0) return false;

    map<int, int>* m = new map<int, int>[graph->getSize()];
    //vector <int>* v = new vector<int>[graph->getSize()]; // save path
    // vector is not empty = the node visited

    int* dist = new int[graph->getSize()];
    int* prev = new int[graph->getSize()];

    // initialization
    // memset(dist, inf, sizeof(int) * graph->getSize()); 
    // infinite := 1,000,000,000 (1Billion)
    for (int i = 0; i < graph->getSize(); i++) {
        dist[i] = inf;
        prev[i] = -1;
    }

    dist[s_vertex - 1] = 0; // self
    prev[s_vertex - 1] = 0;

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
        delete[] dist;
       // delete[] v;
        delete[] m;
        delete[] prev;
        //delete[] visited;
        return false;
    }

    vector <W> edges;

    // Add for all edges
    for (int i = 0; i < graph->getSize(); i++) {
        for (auto it = m[i].begin(); it != m[i].end(); it++) {
            edges.push_back({ it->second, i + 1, it->first });
        }
    }


    for (auto it = m[s_vertex - 1].begin(); it != m[s_vertex - 1].end(); it++) {
        dist[it->first - 1] = it->second;
        prev[it->first - 1] = s_vertex;
    }

   // bool flag = 0; // negative cycle

    for (int i = 0; i <= graph->getSize(); i++) {
        for (int j = 0; j < edges.size(); j++) {
            int s = edges[j].s;
            int e = edges[j].e;
            int w = edges[j].w;

            if (dist[s - 1] == inf) continue; // If there is no incoming edge
            if (dist[e - 1] > dist[s - 1] + w) {
                dist[e - 1] = dist[s - 1] + w;
                prev[e - 1] = s;
	
				// negative cycle
                if (i == graph->getSize()) {
                    delete[] dist;
                    delete[] m;
                    delete[] prev;
                    return false;
                }
            }
        }
    }

    stack <int> sta;
    sta.push(e_vertex);

    int pos = e_vertex;

    while (pos != s_vertex && pos >= 0) {
        pos = prev[pos - 1];
        sta.push(pos);
    }

    *fout << "======= Bellman-Ford =======" << endl;

    if (option == 'Y') *fout << "Directed ";
    else *fout << "Undirected ";

    *fout << "Graph Bellman-Ford result" << endl;
    if (pos < 0) *fout << "x" << endl;


    else {
        while (!sta.empty()) {
            *fout << sta.top();
            sta.pop();

            if (!sta.empty()) *fout << " -> ";
            else *fout << endl;
        }

        *fout << "cost: " << dist[e_vertex - 1] << endl;
    }
   
    *fout << "=====================" << endl << endl;

    delete[] dist;
    delete[] m;
    delete[] prev;
    return true;
}

bool FLOYD(Graph* graph, char option, ofstream* fout)
{
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

    else {
        delete[] m;
        return false;
    }

    int** table = new int* [graph->getSize()];
    for (int i = 0; i < graph->getSize(); i++) {
        table[i] = new int[graph->getSize()];
        for (int j = 0; j < graph->getSize(); j++) {
            table[i][j] = inf;
        }
        for (auto it = m[i].begin(); it != m[i].end(); it++) {
            table[i][it->first - 1] = it->second;
        }
    }

    for (int i = 0; i < graph->getSize(); i++) {
        for (int j = 0; j < graph->getSize(); j++) {
            for (int k = 0; k < graph->getSize(); k++) {
                if (table[i][k] + table[k][j] < table[i][j]) {
                    table[i][j] = table[i][k] + table[k][j];
                }
            }
        }
    }

    *fout << "======= FLOYD =======" << endl;

    if (option == 'Y') *fout << "Directed ";
    else *fout << "Undirected ";

    *fout << "Graph FLOYD result" << endl;


    *fout << "=====================" << endl << endl;


    return true;
}



int collapsingfind(int* parent, int i)
{
    // Find the root of the tree containing element i.
    // Use the collapsing rule to collapse all nodes from i to the root.
    int r = i;
    for (; parent[r] >= 0; r = parent[r]); // find root
    while (i != r) { // collapse
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

int simplefind(int* parent, int i)
{
    while (parent[i] >= 0) i = parent[i];
    return i;
}

void simpleunion(int* parent, int i, int j)
{
    parent[i] = j;
}

bool check(int* parent)
{
    int cnt = 0;
    for (int i = 1; i < sizeof(parent); i++) {
        if (parent[i] < 0) cnt++;
    }
    return cnt != 1;
}

void quicksort(vector<W>& arr, int low, int high)
{
    if (low < high) {
        if (high - low + 1 <= 6) // sement_size is 6
            insertionsort(arr, low, high);

        else {
            int i = low;
            int j = high + 1;
            W pivot = arr[low];
            do {
                do i++;  while (arr[i].w < pivot.w);
                do j--;  while (arr[j].w > pivot.w);
                if (i < j) swap(arr[i], arr[j]);
            } while (i < j);
            swap(arr[low], arr[j]);

            quicksort(arr, low, j - 1);
            quicksort(arr, j + 1, high);
        }
    }
}

void insertionsort(vector<W>& arr, int low, int high)
{
    for (int i = low + 1; i <= high; i++) {
        int j = i - 1;
        W key = arr[i];

        while (j >= low && key.w < arr[j].w) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

bool KWANGWOON(Graph* graph, int vertex, ofstream* fout) {
    return true;
}