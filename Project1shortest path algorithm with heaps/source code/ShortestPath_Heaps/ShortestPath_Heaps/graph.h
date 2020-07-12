#pragma once
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#define INF 1e8

using namespace std;

typedef int Vertex;

//node in adjacency linked list
class node {
public:
	Vertex v;
	int dist;
	node *next;
};

//each vertex in graph
class entry {
public:	
	node* list;//adjacency list
	int known;
	int dist;//current shortest distance

	entry() {
		known = 0;
		dist = INF;
		list = NULL;
	}
};

class Graph
{	
public:
	entry *table;
	int nodeNum;//number of nodes
	int edgeNum;//number of edges
	Graph(string filename);//generate graph from the input file
};

