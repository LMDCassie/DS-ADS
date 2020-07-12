#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


class FibNode
{
public:
	int key;          // ֵ 
	int v;            // ��
	int degree;       // ����
	FibNode* left;    // ���ֵ�
	FibNode* right;   // ���ֵ�
	FibNode* child;   // ��һ�����ӽڵ�
	FibNode* parent; 
	int marked;       // �Ƿ��к��ӽڵ㱻ɾ������������ָ��1�������Ƿ�ɾ��(1��ʾɾ����0��ʾδɾ��)

	FibNode(int v,int key);
	FibNode();
};

class FibHeap {
public:
	int   tol;         // ���нڵ�����
	int   maxDegree;   // ������
	FibNode* min;     // ��С�ڵ�(���ڵ���С����С�ѵĸ��ڵ�)
	FibNode* *cons;   // ���������ڴ�������ɾ��ʱ��ʱ����

	FibHeap();
	void cascade_remove(FibNode* node); //����ɾ��
	void deckey(FibNode* node, int nkey);//����node�ڵ��ֵΪnkey����������
	void rbuildcon();//����Ϊcons����ռ�
	void attach(FibNode* root, FibNode* node);//��node��Ϊ�ӽڵ����ӵ�root�ĵ�һ���ӽڵ�֮ǰ
	void addcon(FibNode* node);//��node����cons��
	FibNode* deletemin();//��fib heap Ҫ��ɾ����С�ڵ㲢����
	void insert(FibNode* node);    //
	FibNode* deletenode(FibNode* node);//��˫��������ɾ��node,����ɾ������ҽڵ�
	void addnode(FibNode* root, FibNode* node);//��˫�������а�node�ӵ�root֮ǰ	
	
};




