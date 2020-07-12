#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


class FibNode
{
public:
	int key;          // 值 
	int v;            // 点
	int degree;       // 度数
	FibNode* left;    // 左兄弟
	FibNode* right;   // 右兄弟
	FibNode* child;   // 第一个孩子节点
	FibNode* parent; 
	int marked;       // 是否有孩子节点被删除。在这里是指第1个孩子是否被删除(1表示删除，0表示未删除)

	FibNode(int v,int key);
	FibNode();
};

class FibHeap {
public:
	int   tol;         // 堆中节点总数
	int   maxDegree;   // 最大度数
	FibNode* min;     // 最小节点(根节点最小的最小堆的根节点)
	FibNode* *cons;   // 最大度数的内存区域，在删除时临时保存

	FibHeap();
	void cascade_remove(FibNode* node); //级联删除
	void deckey(FibNode* node, int nkey);//降低node节点的值为nkey并作出调整
	void rbuildcon();//重新为cons分配空间
	void attach(FibNode* root, FibNode* node);//将node作为子节点连接到root的第一个子节点之前
	void addcon(FibNode* node);//将node加入cons中
	FibNode* deletemin();//按fib heap 要求删除最小节点并整合
	void insert(FibNode* node);    //
	FibNode* deletenode(FibNode* node);//在双向链表中删除node,返回删除后的右节点
	void addnode(FibNode* root, FibNode* node);//在双向链表中把node加到root之前	
	
};




