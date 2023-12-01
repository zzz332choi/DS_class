#include <iostream>
#include <vector>
#include "GraphMethod.h"
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <list>
#include <utility>

using namespace std;

bool BFS(Graph* graph, char option, int vertex)
{
    // The vertex you entered does not exist in the graph
    if(vertex > graph->getSize()) return false; 

    queue <int> q;
    vector <int> v;
    bool* visited = new bool [graph->getSize()];
    fill(&visited[0], &visited[0] + graph->getSize(), false); // init

    if (!graph->getType()) { // list type

    }

    else { // matrix type
    
    }

   delete[] visited;
}

bool DFS(Graph* graph, char option, int vertex)
{
   
 }

bool Kruskal(Graph* graph)
{
   
}

bool Dijkstra(Graph* graph, char option, int vertex)
{
   
}

bool Bellmanford(Graph* graph, char option, int s_vertex, int e_vertex) 
{
   
}

bool FLOYD(Graph* graph, char option)
{
   
}

bool KWANGWOON(Graph* graph, int vertex) {

}