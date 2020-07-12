#pragma once
#include <vector>
using namespace std;

class minNode {
public:
	int vertex; //vertex
	int dis;    //current shortest path length
};


class MinHeap {
public:
	int size;  //current size
	vector <minNode> queue;

	MinHeap();//build and initailize the min heap
	minNode deletemin(); //delete the min element ,i.e. h->queue[1] from the min heap
	void insertminNode(minNode x);  //insert minNode x into heap mh

};

