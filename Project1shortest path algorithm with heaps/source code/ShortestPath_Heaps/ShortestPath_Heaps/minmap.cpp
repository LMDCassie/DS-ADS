#include "minheap.h"
#include <cstdio>
using namespace std;

MinHeap::MinHeap() {
	size = 0;
	minNode t;
	t.dis = -1; t.vertex = -1;
	queue.push_back(t);
                    //queue stores the data from h->queue[1]
					//queue[0] stores the min mark  
}

void MinHeap::insertminNode(minNode x) {
	
	queue.push_back(x);

	//make sure that the parent is no more than its child in  min heap
	size++;
	int i;
	for (i = size; queue[i / 2].dis > x.dis; i = i / 2) {
		queue[i] = queue[i / 2];
	}
	queue[i] = x;

	return;


}

//delete the min element ,i.e. queue[1] from the min heap
minNode MinHeap::deletemin() {
	int i = 1;
	int child = 2;//the min child of i
	minNode min = queue[1];//min
	minNode last= queue[size];//last element

	size--;
	//percolate down the last element from root
	while (child <= size) {
		//find the min child
		if ((child <size) && (queue[child].dis >queue[child + 1].dis)) child++; //right child exist and is less
		
		//determin whether to percolate down
		if (queue[child].dis < last.dis) queue[i] = queue[child];
		else break;
		
		//update
		i = child;
		child = child * 2; //the left child of origin minNode
	}
	queue[i] = last;//put the last element

	queue.pop_back();
	return min;
}

