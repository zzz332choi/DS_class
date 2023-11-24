#include "MatrixGraph.h"
#include <iostream>
#include <vector>
#include <string>

MatrixGraph::MatrixGraph(bool type, int size) : Graph(type, size)
{
    *m_Mat = new int [size];

    for(int i= 0; i< size; i++) {
        m_Mat[i] = new int [size];
    }

    fill(&m_Mat[0], &m_Mat[0] + size * size, 0); // init
}

MatrixGraph::~MatrixGraph()
{
    for(int i=0; i < getSize(); i++) delete[] m_Mat[i];
    delete[] m_Mat;
}

void MatrixGraph::getAdjacentEdges(int vertex, map<int, int>* m)
{	

}

void MatrixGraph::getAdjacentEdgesDirect(int vertex, map<int, int>* m)
{
	
}

void MatrixGraph::insertEdge(int from, int to, int weight)	
{
	m_Mat[from][to] = weight;
}

bool MatrixGraph::printGraph(ofstream *fout)	
{
	if(!m_Mat) return false;

    *fout << "========PRINT========" << endl;

    *fout << '\t';

    for(int i = 1; i <= getSize(); i++) *fout << '[' << i << "] ";

    *fout << endl;

    for(int i = 1; i <= getSize(); i++) {
        *fout << '[' << i << "] " ;

        // Output in left-hand alignment
        for(int j = 0; j < getSize(); j++) {
            fout->width(4);
            *fout << ios::left << m_Mat[i-1][j];
        }

        *fout << endl;
    }

    *fout << "=====================" << endl << endl;

    return true;
}
