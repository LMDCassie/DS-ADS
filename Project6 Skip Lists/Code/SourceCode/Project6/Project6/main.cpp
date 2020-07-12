#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<ctime>
#include<cstdlib>
#include<iostream>
using namespace std;

int MAXLevel = 15;
int MaxKey = INT_MAX;

struct Node {
	int value;
	int key;
	Node *Next;
	Node *Down;
};//Node in SkipList

struct SkipList {
	int level;
	Node **Head;
	Node *Tail;
};//SkipList

Node *CreateNode(int level, int value, int key) {
	Node *newNode = new Node;
	newNode->value = value;
	newNode->key = key;
	return newNode;
}//Create a new Node

SkipList *CreateSkipList() {
	SkipList *newSkipList = new SkipList;
	newSkipList->level = 0;
	newSkipList->Head = new Node*[MAXLevel];
	newSkipList->Tail = new Node;
	newSkipList->Tail->Next = nullptr;
	newSkipList->Tail->Down = nullptr;
	newSkipList->Tail->key = MaxKey;
	//Initialize the SkipList 
	for (int i = 0; i < MAXLevel; i++) {
		newSkipList->Head[i] = new Node;
		newSkipList->Head[i]->key = -1;
		newSkipList->Head[i]->Next = newSkipList->Tail;
		if (i == 0) {
			newSkipList->Head[i]->Down = nullptr;
		}
		else {
			newSkipList->Head[i]->Down = newSkipList->Head[i - 1];
		}
	}
	return newSkipList;
}//Create a new SkipList

int CalRandLevel() {
	srand(static_cast<unsigned int>(time(NULL)));//Initialize the random number generator
	int L = 0;
	while (rand() % 2) {
		L++;
	}
	if (L < MAXLevel)return L;
	else return MAXLevel;
}

int InsertNode(SkipList *SL, int value, int key) {
	int L = CalRandLevel();
	Node **Update = new Node*[L + 1];
	Node *position = SL->Head[L];
	int n = L;
	while (position) {
		while (position->Next->key < key) {
			position = position->Next;
		}
		Update[n] = position;
		position = position->Down;
		n--;
	}
	for (int i = 0; i <= L; i++) {
		Node *PNode = new Node;
		PNode->value = value;
		PNode->key = key;
		PNode->Next = Update[i]->Next;
		Update[i]->Next = PNode;
		if (i == 0)PNode->Down = nullptr;
		else PNode->Down = Update[i - 1]->Next;
	}
	return 0;
}

int SearchNode(SkipList *SL, int key) {
	Node *position = SL->Head[MAXLevel - 1];
	while (true) {
		while (position->Next->key < key) {
			position = position->Next;
		}
		if (position->Down == nullptr) {
			if (position->Next->key == key) {
				return position->Next->value;
			}
			else {
				cout << "No Such Node" << endl;
				return -1;
			}
		}
		position = position->Down;
	}
}

void DeleteNode(SkipList *SL, int key) {
	Node *position = SL->Head[MAXLevel - 1];
	Node *temp = nullptr;
	while (position) {
		while (position->Next->key < key) {
			position = position->Next;
		}
		if (position->Next->key == key) {
			temp = position->Next;
			position->Next = position->Next->Next;
			delete temp;
			temp = nullptr;
			cout << "The node has been deleted" << endl;
			return;
		}
		else {
			position = position->Down;
		}
	}
	cout << "Deletion failed. The node may not exist." << endl;
}

int main() {
	SkipList *SL = CreateSkipList();
	
	// A simple test
	for (int i = 0; i < 10; i++) {
		InsertNode(SL, i * i, i);
	}
	cout << SearchNode(SL, 6) << endl;
	DeleteNode(SL, 6);
	cout << SearchNode(SL, 4) << endl;
	
	/* 

	FILE *fp = fopen("C:/Users/Cassie/Desktop/Project6/TestData/Data.out", "r"); //Get test data from .out file
	clock_t start, finish;
	double Subtime;
	double Totaltime = 0.0;

	// Insertion ,data from .out file, not for the complexity analysis
	while (!feof(fp)) {
		long key;
		long value;
		fscanf(fp, "%ld%ld\n", &key, &value);

		start = clock();

		InsertNode(SL, value, key);

		finish = clock();

		Subtime = (double)(finish - start) / CLOCKS_PER_SEC;
		Totaltime += Subtime;
	}

	cout << "Total time for the previous simple insertion test " << Totaltime << endl;
	
	*/
	

	system("pause");
	return 0;
}

