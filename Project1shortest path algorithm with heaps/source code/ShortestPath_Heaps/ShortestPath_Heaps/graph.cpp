#include "graph.h"

//generate graph from the input file
Graph::Graph(string filename)
{
	ifstream file;
	file.open(filename);
	char s;
	char line[20];//useless,just to skip comment

	while (file >> s ) {
		//comment
		if (s == 'c') file.getline(line, 20);

		//p sp n m
		else if (s == 'p') {
			string sp;//just for input format.useless
			file >> sp >> nodeNum >> edgeNum;
			table = new entry[nodeNum+1];
		}
	
		//a v1 v2 dist
		else if (s == 'a') {
			int i, j, dist;

			file >> i >> j >> dist;
			//link vertex j to vertex i
			node *t = new node();
			t->v = j;
			t->dist = dist;
			t->next = table[i].list;
			table[i].list = t;
		}
	}	

	file.close();

}
