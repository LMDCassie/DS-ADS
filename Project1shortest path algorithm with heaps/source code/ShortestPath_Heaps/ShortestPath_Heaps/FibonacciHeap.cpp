#define _CRT_SECURE_NO_WARNINGS
#include "fibonacciHeap.h"
#include <iostream>

using namespace std;
//初始化
FibHeap::FibHeap() {
	maxDegree = 0;
	cons = NULL;
	min = NULL;
	tol = 0;
}

//在双向链表中把node加到root之前
void FibHeap::addnode(FibNode* root, FibNode* node) {
	if (node == NULL || root == NULL) return;

	node->right = root;
	node->left = root->left;
	root->left->right = node;
	root->left = node;

	return;
}

//在 Fibonacci heap中插入一个节点
void FibHeap::insert(FibNode* node) {
	if (min == NULL) {
		min = node;
		tol = 1;
		return;
	}

	addnode(min, node);//将node连接到根节点列表中
	if (node->key < (min)->key) min = node;//更新min
	tol++;

	return;
}

//在双向链表中删除node,返回删除后的右节点
FibNode* FibHeap::deletenode(FibNode* node) {
	if (node->right == node) return NULL;

	//连接被删除节点的左右节点
	node->right->left = node->left;
	node->left->right = node->right;

	return node->right;
}


//按fib heap 要求删除最小节点并整合
FibNode* FibHeap::deletemin() {
	FibNode* minNode = min;//最小节点
	FibNode* tmin = min;//用于寻找删除最小节点后新的最小节点
	FibNode* t;
	FibNode* t0;
	int i;
	int oldTol;//原节点数目

	if (min == NULL) return NULL;

	rbuildcon();//构建cons

				//将min的子节点放置在 Fibonacci heap根链表中
	t = min->child;
	while (min->child != NULL) {
		t = min->child;
		//更新child为下一个子节点
		if (t->right == t) min->child = NULL;
		else  min->child = t->right;
		deletenode(t);//将子节点t从min子节点链表移除		

					  //将子节点加入根节点链表中
		t->right = t;
		t->left = t;
		t->parent = NULL;
		addnode(min, t);
	}


	tmin = deletenode(min);//删除后右边第一个节点
	if (tmin == NULL) {
		min = NULL;
		return NULL;//已经没有节点
	}

	//剩余节点加入con中合并
	while (tmin->right!= tmin) {
		t0 = tmin;//当前节点
		tmin = deletenode(t0);//删除节点并返回右侧节点 
		t0->right = t0;
		t0->left = t0;
		addcon(t0);//将最小节点加入cons
	}
	tmin->right = tmin->left = tmin;
	addcon(tmin);//加入cons

	//将cons中储存的节点复制到fh中
	oldTol = tol;
	min = NULL;//初始化min为空
			   //逐个插入
	for (i = 0; i < maxDegree + 1; i++) {
		if (cons[i] != NULL) {
			insert(cons[i]);
		}
	}

	tol = oldTol - 1;//更新节点数
	return minNode;
}

//将node加入cons中
void FibHeap::addcon(FibNode* node) {
	int d = node->degree;
	FibNode* t;

	//若当前度数的树已存在，合并相同度的根节点
	while (cons[d] != NULL) {
		FibNode* x = cons[d];
		//合并相同度数的树
		if (x->key < node->key) {//保证x->key>node->key
			t = x;
			x = node;
			node = t;
		}
		attach(node, x);//将x合并到node中

		cons[d] = NULL;
		d++;
	}
	cons[d] = node;

	return;
}

//将node作为子节点连接到root的第一个子节点之前
void FibHeap::attach(FibNode* root, FibNode* node) {
	//root无子节点
	if (root->child == NULL) {
		root->child = node;
		node->right = node;
		node->left = node;
	}
	//root有子节点
	else {
		node->right = root->child;
		node->left = root->child->left;
		root->child->left->right = node;
		root->child->left = node;
		root->child = node;
	}

	node->parent = root;
	root->degree++;

	return;
}

//重新为cons分配空间
void FibHeap::rbuildcon() {
	int old = maxDegree;
	int maxd;
	maxd = log10((double)(tol)) / log10(1.5) + 1;//扩大至log(1.5)(tol)+1

												 //cout <<"**"<< old << " " << maxd << endl;
	if (old < maxd) {
		maxDegree = maxd;
		cons = (FibNode **)realloc(cons, sizeof(FibHeap *) * (maxDegree + 1));
		if (cons == NULL) cout << "realloc failure";
	}


	for (int i = 0; i < maxDegree + 1; i++) {
		cons[i] = NULL;
	}
	return;

}

//降低node节点的值为nkey并作出调整
void FibHeap::deckey(FibNode* node, int nkey) {
	//cout << "deckey" << endl;
	FibNode* parent = node->parent;
	int oldTol;//原本的节点数

	if ((min == NULL) || (node == NULL)) return;

	node->key = nkey;//更新节点key

					 //破坏了最小堆性质
	if (parent != NULL && parent->key > nkey) {
		//先删除node节点		
		node->parent = NULL;
		parent->child = deletenode(node);
		parent->degree--;//减少父节点度数
		oldTol = tol;

		//重新插入node到根链表中
		insert(node);
		tol = oldTol;

		cascade_remove(parent);//级联删除父节点
	}

	//更新最小节点
	if (nkey < min->key) min = node;

	return;
}

//级联删除
void FibHeap::cascade_remove(FibNode* node) {
	//cout << "cascade_remove" << endl;
	if (node == NULL || node->parent == NULL) return;

	FibNode* parent = node->parent;
	int oldTol;//原节点树


			   //子节点未被删除过
	if (node->marked == 0) {
		node->marked = 1;//更新标记
		return;
	}

	//父节点的子节点被删除过
	else {
		//先删除节点
		node->parent->degree--;//更新祖父节点度数
		node->parent = NULL;
		parent->child = deletenode(node);
		oldTol = tol;

		//重新插入node到根链表中
		insert(node);
		tol = oldTol;

		cascade_remove(parent); //联级删除父节点
	}

	return;
}


//初始化节点
FibNode::FibNode(int v, int key) {
	this->v = v;
	this->key = key;
	degree = 0;
	child = NULL;
	left = this;
	right = this;
	marked = 0;
	parent = NULL;
}

FibNode::FibNode() {
	degree = 0;
	child = NULL;
	left = this;
	right = this;
	marked = 0;
	parent = NULL;
}
