#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<ctime>
#include<cstdlib>
#include<iostream>
using namespace std;

int MAXLevel = 15;
int MaxKey = INT_MAX;
const int MAXN = 100000;

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
	int key[MAXN], value[MAXN];

	for (int n = 32768; n <= 65536; n *= 2) {
		int totalTime = 0;
		for (int test = 0; test < 1; test++) {
			srand(time(NULL));
			for (int i = 0; i < n; i++) key[i] = i;

			for (int i = n - 1; i > 0; i--) {
				long r = rand() % i;
				long temp = key[i];
				key[i] = key[r];
				key[r] = temp;
				value[i] = rand() % n;
			}
			value[0] = rand() % n;

			SkipList *skl = CreateSkipList();
			for (int i = 0; i < n; i++) InsertNode(skl, value[i], key[i]);

			clock_t start, finish;
			start = clock();
			for (int i = 0; i < 100; i++) {
				int currentKey = rand() % n;
				SearchNode(skl, currentKey);
			}
			finish = clock();
			totalTime += finish - start;
			delete skl;
		}
		cout << "Total time for searching " << n << " is " << totalTime << endl;
	}
}