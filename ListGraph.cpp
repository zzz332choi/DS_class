#include "ListGraph.h"
#include <iostream>
#include <utility>

ListGraph::ListGraph(bool type, int size) : Graph(type, size)
{
	m_List = new map<int, int> [size + 1];
}

ListGraph::~ListGraph()	
{
	delete m_List;
}

void ListGraph::getAdjacentEdges(int vertex, map<int, int>* m)	 //Definition of getAdjacentEdges(No Direction == Undirected)
{
	
}

void ListGraph::getAdjacentEdgesDirect(int vertex, map<int, int>* m)	//Definition of getAdjacentEdges(Directed graph)
{
	
}

void ListGraph::insertEdge(int from, int to, int weight) //Definition of insertEdge
{
	m_List[from].insert(to, weight);
}

bool ListGraph::printGraph(ofstream *fout)	//Definition of print Graph
{
	if(!m_List) return false;

    *fout << "========PRINT========" << endl;

    for(int i = 1; i<=getSize(); i++) {
        *fout << '[' << i << ']';

        for(auto iter = m_List[i].begin(); iter != m_List[i].end(); iter++)
            *fout << " -> (" << iter->first << ',' << iter->second << ')'; 

        *fout << endl;
    }

    *fout << "=====================" << endl << endl;

    return true;
}