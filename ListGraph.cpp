#include "ListGraph.h"
#include <iostream>
#include <utility>

ListGraph::ListGraph(bool type, int size) : Graph(type, size)
{
	m_List = new map<int, int> [size];
}

ListGraph::~ListGraph()	
{
	delete[] m_List;
}

void ListGraph::getAdjacentEdges(int vertex, map<int, int>* m)	 //Definition of getAdjacentEdges(No Direction == Undirected)
{
    // find in & out edge
    for (int i = 0; i < this->getSize(); i++) {
        if (i != vertex - 1) {
            if (m_List[i].find(vertex) != m_List[i].end()) { // found
                m->insert({ i+1, m_List[i].find(vertex)->second});
            }
        }
        else { // i == vertex - 1
            for (auto it = m_List[vertex - 1].begin(); it != m_List[vertex - 1].end(); it++) {
                m->insert({ it->first, it->second });
            }
        }
    }

}

void ListGraph::getAdjacentEdgesDirect(int vertex, map<int, int>* m)	//Definition of getAdjacentEdges(Directed graph)
{
    // find out edge
    for (auto it = m_List[vertex - 1].begin(); it != m_List[vertex - 1].end(); it++) {
        m->insert({ it->first, it->second });
    }
}

void ListGraph::insertEdge(int from, int to, int weight) //Definition of insertEdge
{
    m_List[from - 1].insert({ to, weight });
}

bool ListGraph::printGraph(ofstream *fout)	//Definition of print Graph
{
	if(!m_List) return false;

    *fout << "========PRINT========" << endl;

    for(int i = 0; i < getSize(); i++) {
        *fout << '[' << i + 1 << ']';

        for(auto iter = m_List[i].begin(); iter != m_List[i].end(); iter++)
            *fout << " -> (" << iter->first << ',' << iter->second << ')'; 

        *fout << endl;
    }

    *fout << "=====================" << endl << endl;

    return true;
}