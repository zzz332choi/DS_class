//#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

#define INF 0x3f3f3f3f

// iPair ==> Integer Pair
typedef pair<int, int> iPair;

//template<typename T>
//typedef vector list;

// This class represent sa directed graph using
// adjacecy list representation

class Graph {
	int V; // No. of verteices

	// In a weighted graph, we need to store vertex
	// and weight paire for every edge
	vector <pair <int, int> >* adj;

public:
	Graph(int V); // constructor

	// fuction to add an edge to graph
	void addEdge(int u, int v, int w);

	// prints shortest path from s
	void shortestPath(int s);

};

// Allocates memory for adhacecy list
Graph::Graph(int V)
{
	this->V = V;
	adj = new vector<iPair>[V];
}

void Graph::addEdge(int u, int v, int w)
{
	adj[u].push_back(make_pair(v, w));
	adj[v].push_back(make_pair(u, w));
}

// Prints shortest paths from src to all other vertices
void Graph::shortestPath(int src)
{
	// create a priority queue to to store vertices that
	// are begin preprocessed. This is weird syntax in C++.
	priority_queue<iPair, vector <iPair>, greater<iPair> > pq;

	// Create a vector for distances and initialize all
	// disances as infinite (INF)
	vector <int> dist(V, INF);

	// insert source itself in priority queue and initialize
	// its distance as 0.
	pq.push(make_pair(0, src));
	dist[src] = 0;

	// Looping till priority queue becomes empty (or all distances are not finalized)
	while (!pq.empty()) {
		int u = pq.top().second;
		pq.pop();

		vector <pair <int, int> >::iterator i;
		for (auto i = adj[u].begin(); i != adj[u].end(); ++i) {
			int v = (*i).first;
			int weight = (*i).second;

			if (dist[v] > dist[u] + weight) {
				dist[v] = dist[u] + weight;
				pq.push(make_pair(dist[v], v));
			}
		}
	}

	printf("Vertex distance from source\n");
	for (int i = 0; i < V; i++) {
		printf("%d\t\t%d", i, dist[i]);
	}
}

