#define _CRT_SECURE_NO_WARNINGS
#include "minheap.h"
#include "fibonacciHeap.h"
#include "graph.h"
#include <iostream>
using namespace std;
ifstream generateQuery( int n);
double minheapPath(Graph G);//return the computing time of minHeap
double FibHeapPath(Graph G);//return the computing time of fibonacci heap


int main() {	
	double time1,time2;//the computing time
	
	Graph G=Graph("data.txt");//input graph
	
	//show graph
	/*for (int i = 1; i <= G.nodeNum; i++) {
		cout << i << ":	";
		node *t = G.table[i].list;
		while (t != NULL) {
			cout << t->v << "&" << t->dist<<"	";
			t = t->next;
		}
		cout << endl;

	}*/

    time1=minheapPath( G);//store result in "minResult.txt" and return computing time
	time2 = FibHeapPath(G);//store result in "fibResult.txt" and return computing time

	delete(G.table);
	system("pause");
	return 0;
}



//read test cases from text.txt
//if text.txt does not exist,generate $(query) query in graph with n vertex randomly, stored in test.txt
//FORMAT:
//query
//start end
//...
ifstream generateQuery(int n) {
	ifstream test("test.txt");
	int query;

	if (test.fail()) {
		test.close();
		cout << "test file does not exist!" << endl << "we will generate the test file randomly for you." << endl;
		
		//create the test file	
		cout << "how many time do you want to test?" << endl;
		cin >> query;
		ofstream testw("test.txt");
		testw << query << endl;//input the times of queries
		for (int i = 0; i < query; i++) {
			testw << rand() % n << " " << rand() % n << " " << endl;
		}
		testw.close();
		ifstream test("test.txt");

	}
	return test;
}

//input the graph and test file which contain queries
//return the computing time
double minheapPath( Graph G) {
	ifstream test;//test file which stores shortest path queries 
	int query;//number of queries
	int start, end;//the start vertex and end vertex of the shortest path
	clock_t starttime, endtime;
	MinHeap minheap;//minheap
	ofstream minResult("minResult.txt");//result of min heap
	minNode n0;//min in unknown in min heap
	node *tv;//linked node
	double time;

	test = generateQuery(G.nodeNum);//generate test file for query
	test >> query;
	cout << "minheap" << endl;
	starttime= clock();

	for (int j = 0; j < query; j++) {
		test >> start >> end;
		int count = 0;//the number of caculations
		
		//reinitialize the heap
		for (int i = 1; i <= G.nodeNum; i++) {
			minNode t;
			t.vertex = i;
			//distance
			if (i == start)  t.dis = 0;
			else t.dis = INF;
			//vertex index
			minheap.insertminNode(t);
		}

		//reinitialize the table
		for (int i = 1; i <= G.nodeNum; i++) {
			G.table[i].dist = INF;
			G.table[i].known = 0;
		}
		G.table[start].dist = 0;

		//compute the shortest path
		while (minheap.size != 0) { //while unknow is not empty
			n0 = minheap.queue[1]; //n0 is min in the unknown
			if (G.table[n0.vertex].known == 1) {
				minheap.deletemin();  //if n0 is known,drop it
				continue;
			}
			G.table[n0.vertex].known = 1; //mark that n0 is visited
			
			//count++;
			//cout << count << " min:" << n0.vertex << endl;
			tv = G.table[n0.vertex].list;//tv is the vertex that is adjacent to vertex correspond to n0
			
			//cout << n0.vertex << " " << n0.dis << endl;


			//update the len of vertex adjacent to vertex correspond to n0
			while (tv != NULL) {
				minNode n1;//temporay node n1

				n1.vertex = tv->v; n1.dis = G.table[n0.vertex].dist + tv->dist; //temporay node n1 that update
				if ((G.table[tv->v].known == 0) && (G.table[tv->v].dist>G.table[n0.vertex].dist + tv->dist)){
					minheap.insertminNode(n1); //insert the update node which is smaller
									           //so the node is updated since the origin one will be dropped when known updated
					G.table[tv->v].dist = G.table[n0.vertex].dist + tv->dist;//update len[]
				}
				tv = tv->next;
			}
			minheap.deletemin();
		}

		//cout<< j << ":" << start << " to " << end << ":" << G.table[end].dist << endl;
		minResult << j << ":" << start << " to " << end << ":" << G.table[end].dist << endl;
	}
	
	endtime = clock();
	time = (double)(endtime - starttime) * 1000 / CLK_TCK;
	cout<<time <<"ms"<<endl;
	minResult << time <<  "ms" <<endl;
	
	//close
	minResult.close();
	test.close();
	
	return time;
}

//return the computing time of fibonacci heap
double FibHeapPath( Graph G) {
	ifstream test;//test file which stores shortest path queries 
	int query;//number of queries
	int start, end;//the start vertex and end vertex of the shortest path
	clock_t starttime, endtime;
	ofstream fibResult("fibResult.txt");//result of fibHeap
	FibNode *n0;//min in unknown in fibHeap
	node *tv;//linked node
	double time;
	FibNode** f=new FibNode*[G.nodeNum];//to find FibNode according to vertex index

	test = generateQuery(G.nodeNum);//generate test file for query
	test >> query;
	cout << "fibheap" << endl;
	starttime = clock();

	for (int j = 0; j < query; j++) {
		test >> start >> end;
		//int count = 0;//the number of caculations
		FibHeap fibheap;//fibheap

		//reinitialize the table
		for (int i = 1; i <= G.nodeNum; i++) {
			G.table[i].dist = INF;
			G.table[i].known = 0;
		}
		G.table[start].dist = 0;

		//insert all nodes into the fibheap 
		for (int i = 1; i <= G.nodeNum; i++) {
			//initialize the f[MAX]
			if (i == start)  f[i] = new FibNode(i, 0);
			else  f[i] = new FibNode(i, INF);

			fibheap.insert(f[i]);//insert node into fibheap
		}

		n0 = fibheap.min;
		while (n0 != NULL) {	//fibHeap is not empty		
			G.table[n0->v].known = 1;//mark known
			
			//count++;
			//cout << count << ": " << n0->v << endl;
			
			fibheap.deletemin();//delete min node
			
			//update the distance of tv adjacent to node
			tv = G.table[n0->v].list;
			while (tv != NULL) {
				if ((G.table[tv->v].known == 0) && (G.table[n0->v].dist + tv->dist < G.table[tv->v].dist)) {
					G.table[tv->v].dist = G.table[n0->v].dist + tv->dist;
					fibheap.deckey(f[tv->v], G.table[tv->v].dist);
				}
				tv = tv->next;
			}

			n0 = fibheap.min;//update min node			
		}


		//cout << j << ":" << start << " to " << end << ":" << G.table[end].dist << endl;
		fibResult << j << ":" << start << " to " << end << ":" << G.table[end].dist << endl;
		
		//free f[MAX]
		for (int i = 1; i <= G.nodeNum; i++) {
			free(f[i]);
		}
	}

	//write time
	endtime = clock();
	time = (double)(endtime - starttime) * 1000 / CLK_TCK;
	fibResult << time <<"ms"<< endl;
	cout << time << "ms" << endl;
	
	//close
	fibResult.close();
	test.close();
	
	return time;
}