#ifndef _LIST_H_
#define _LIST_H_

#include "Graph.h"

class ListGraph : public Graph{	
private:
	map < int, int >* m_List = nullptr;
	vector<int>* kw_graph = nullptr;
	
public:	
	ListGraph(bool type, int size);
	~ListGraph();
		
	void getAdjacentEdges(int vertex, map<int, int>* m);	
	void getAdjacentEdgesDirect(int vertex, map<int, int>* m);
	void insertEdge(int from, int to, int weight);	
	bool printGraph(ofstream *fout);


	//my
	void RegetAdjacentEdgesDirect(int vertex, multimap<int, int>* m);
};

#endif