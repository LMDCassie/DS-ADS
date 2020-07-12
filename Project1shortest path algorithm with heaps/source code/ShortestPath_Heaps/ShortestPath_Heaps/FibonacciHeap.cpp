#define _CRT_SECURE_NO_WARNINGS
#include "fibonacciHeap.h"
#include <iostream>

using namespace std;
//��ʼ��
FibHeap::FibHeap() {
	maxDegree = 0;
	cons = NULL;
	min = NULL;
	tol = 0;
}

//��˫�������а�node�ӵ�root֮ǰ
void FibHeap::addnode(FibNode* root, FibNode* node) {
	if (node == NULL || root == NULL) return;

	node->right = root;
	node->left = root->left;
	root->left->right = node;
	root->left = node;

	return;
}

//�� Fibonacci heap�в���һ���ڵ�
void FibHeap::insert(FibNode* node) {
	if (min == NULL) {
		min = node;
		tol = 1;
		return;
	}

	addnode(min, node);//��node���ӵ����ڵ��б���
	if (node->key < (min)->key) min = node;//����min
	tol++;

	return;
}

//��˫��������ɾ��node,����ɾ������ҽڵ�
FibNode* FibHeap::deletenode(FibNode* node) {
	if (node->right == node) return NULL;

	//���ӱ�ɾ���ڵ�����ҽڵ�
	node->right->left = node->left;
	node->left->right = node->right;

	return node->right;
}


//��fib heap Ҫ��ɾ����С�ڵ㲢����
FibNode* FibHeap::deletemin() {
	FibNode* minNode = min;//��С�ڵ�
	FibNode* tmin = min;//����Ѱ��ɾ����С�ڵ���µ���С�ڵ�
	FibNode* t;
	FibNode* t0;
	int i;
	int oldTol;//ԭ�ڵ���Ŀ

	if (min == NULL) return NULL;

	rbuildcon();//����cons

				//��min���ӽڵ������ Fibonacci heap��������
	t = min->child;
	while (min->child != NULL) {
		t = min->child;
		//����childΪ��һ���ӽڵ�
		if (t->right == t) min->child = NULL;
		else  min->child = t->right;
		deletenode(t);//���ӽڵ�t��min�ӽڵ������Ƴ�		

					  //���ӽڵ������ڵ�������
		t->right = t;
		t->left = t;
		t->parent = NULL;
		addnode(min, t);
	}


	tmin = deletenode(min);//ɾ�����ұߵ�һ���ڵ�
	if (tmin == NULL) {
		min = NULL;
		return NULL;//�Ѿ�û�нڵ�
	}

	//ʣ��ڵ����con�кϲ�
	while (tmin->right!= tmin) {
		t0 = tmin;//��ǰ�ڵ�
		tmin = deletenode(t0);//ɾ���ڵ㲢�����Ҳ�ڵ� 
		t0->right = t0;
		t0->left = t0;
		addcon(t0);//����С�ڵ����cons
	}
	tmin->right = tmin->left = tmin;
	addcon(tmin);//����cons

	//��cons�д���Ľڵ㸴�Ƶ�fh��
	oldTol = tol;
	min = NULL;//��ʼ��minΪ��
			   //�������
	for (i = 0; i < maxDegree + 1; i++) {
		if (cons[i] != NULL) {
			insert(cons[i]);
		}
	}

	tol = oldTol - 1;//���½ڵ���
	return minNode;
}

//��node����cons��
void FibHeap::addcon(FibNode* node) {
	int d = node->degree;
	FibNode* t;

	//����ǰ���������Ѵ��ڣ��ϲ���ͬ�ȵĸ��ڵ�
	while (cons[d] != NULL) {
		FibNode* x = cons[d];
		//�ϲ���ͬ��������
		if (x->key < node->key) {//��֤x->key>node->key
			t = x;
			x = node;
			node = t;
		}
		attach(node, x);//��x�ϲ���node��

		cons[d] = NULL;
		d++;
	}
	cons[d] = node;

	return;
}

//��node��Ϊ�ӽڵ����ӵ�root�ĵ�һ���ӽڵ�֮ǰ
void FibHeap::attach(FibNode* root, FibNode* node) {
	//root���ӽڵ�
	if (root->child == NULL) {
		root->child = node;
		node->right = node;
		node->left = node;
	}
	//root���ӽڵ�
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

//����Ϊcons����ռ�
void FibHeap::rbuildcon() {
	int old = maxDegree;
	int maxd;
	maxd = log10((double)(tol)) / log10(1.5) + 1;//������log(1.5)(tol)+1

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

//����node�ڵ��ֵΪnkey����������
void FibHeap::deckey(FibNode* node, int nkey) {
	//cout << "deckey" << endl;
	FibNode* parent = node->parent;
	int oldTol;//ԭ���Ľڵ���

	if ((min == NULL) || (node == NULL)) return;

	node->key = nkey;//���½ڵ�key

					 //�ƻ�����С������
	if (parent != NULL && parent->key > nkey) {
		//��ɾ��node�ڵ�		
		node->parent = NULL;
		parent->child = deletenode(node);
		parent->degree--;//���ٸ��ڵ����
		oldTol = tol;

		//���²���node����������
		insert(node);
		tol = oldTol;

		cascade_remove(parent);//����ɾ�����ڵ�
	}

	//������С�ڵ�
	if (nkey < min->key) min = node;

	return;
}

//����ɾ��
void FibHeap::cascade_remove(FibNode* node) {
	//cout << "cascade_remove" << endl;
	if (node == NULL || node->parent == NULL) return;

	FibNode* parent = node->parent;
	int oldTol;//ԭ�ڵ���


			   //�ӽڵ�δ��ɾ����
	if (node->marked == 0) {
		node->marked = 1;//���±��
		return;
	}

	//���ڵ���ӽڵ㱻ɾ����
	else {
		//��ɾ���ڵ�
		node->parent->degree--;//�����游�ڵ����
		node->parent = NULL;
		parent->child = deletenode(node);
		oldTol = tol;

		//���²���node����������
		insert(node);
		tol = oldTol;

		cascade_remove(parent); //����ɾ�����ڵ�
	}

	return;
}


//��ʼ���ڵ�
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
