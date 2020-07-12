#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
Data structure
*/
struct MyNode {
	int element;
	struct MyNode* next;
	struct MyNode* left;
	struct MyNode* right;
};
typedef struct MyNode* Node;

void check(char* Node_c, int* Node_f, char** code, int number, int length);
int pre_equal(char* c1, char* c2);
int pre_check(char** code, int length);
int calWPL(Node head, int height);
int Wpl(char** code, int length, int* Fnode);
int calWPL(Node head, int height);

int main() {
	int N;//input 2¡ÜN¡Ü63
	char* Node_c;// input c
	int* Node_f;// input f
	int count = 1;
	scanf("%d", &N);
	while (N != 0) {
		//input 2¡ÜN¡Ü63
		//exit when N==0
		Node_c = (char*)malloc(N*(sizeof(char)));
		Node_f = (int*)malloc(N*(sizeof(int)));

		int i;
		for (i = 0; i < N; i++)scanf("%s%d", &Node_c[i], &Node_f[i]);

		int Stu_N;//Total number of students
		scanf("%d", &Stu_N);//input Stu_N
		char** code = (char**)malloc(Stu_N*N*(sizeof(char*)));
		for (i = 0; i < Stu_N*N; i++)code[i] = (char*)malloc(63 * sizeof(char));
		char* Node_c1;
		Node_c1 = (char*)malloc(Stu_N*N*(sizeof(char)));
		for (i = 0; i < Stu_N*N; i++)scanf("%s%s", &Node_c1[i], code[i]);
		//printf("MyTest %d:\n", count++);
		for (i = 0; i < Stu_N; i++)check(Node_c, Node_f, code, i, N);
		scanf("%d", &N);
	}
}

/*
Check whether the input code conforms to the Huffman code
*/
void check(char* Node_c, int* Node_f, char** code, int num, int length) {
	char** p = &code[num*length];
	int a = pre_check(p, length);
	int b = Wpl(p, length, Node_f);
	if ( a == 0 && b == 1) printf("Yes\n");
	else printf("No\n");
}

/*
Check whether the two characters are equal.
*/
int pre_equal(char* c1, char* c2) {
	int l1 = strlen(c1);//length of c1
	int l2 = strlen(c2);//length of c2
	char* temp;
	//Get the same number from longer code
	if (l1 <= l2) {
		temp = (char*)malloc((l1 + 1) * sizeof(char));
		int i;
		for (i = 0; i < l1; i++)temp[i] = c2[i];
		temp[i] = '\0';
		return strcmp(c1, temp);//Return comparison result
	}
	else {
		temp = (char*)malloc((l2 + 1) * sizeof(char));
		int i;
		for (i = 0; i < l2; i++)temp[i] = c1[i];
		temp[i] = '\0';
		return strcmp(c2, temp);//Return comparison result
	}
}

/*
Check whether the code has prefix
*/
int pre_check(char** code, int length)
{
	int i;
	int j;
	int flag = 1;//The initial state assumes no prefix
	for (i = 0; i < length - 1; i++)
		for (j = i + 1; j < length; j++) {
			flag = pre_equal(code[i], code[j]);
			if (flag == 0)return 1;
		}
	return 0;
}

/*
Calculate the Wpl by recursion
*/
int calWPL(Node head, int height) {
	if (head != NULL)
		if (head->left == NULL )return height * head->element;//Leaf node's frequency value is multiplied by the depth 
		else return calWPL(head->left, height +1) + calWPL(head->right, height +1);//height+1
}



/*
1.Calculate the Wpl of input data
2.Build Huffman coding tree of the input test case
3.Check whether the code'Wpl is the minimum Wpl
*/
int Wpl(char** code, int length, int* Fnode)
{
	int* fnode = (int*)malloc(length * sizeof(int));
	int i;
	for (i = 0; i < length; i++)fnode[i] = Fnode[i];

	int wpl = 0;
	if (length > 63) wpl = -1;
	else 
		for (i = 0; i < length; i++) {
			wpl = wpl + (strlen(code[i]))*fnode[i];
			//printf("%d: wpl=%d\n",i, wpl);
	}
		
		
		//calculate wpl


	int j;
	//Sort the frequency array in ascending order 
	for (i = 0; i < length; i++)
		for (j = 0; j < length - i - 1; j++)
			if (fnode[j] > fnode[j + 1]) {
				int temp = fnode[j + 1];
				fnode[j + 1] = fnode[j];
				fnode[j] = temp;
			}

	Node head;
	Node tail;
	Node t;
	head = NULL;
	tail = head;
	//Build a linked list 
	for (i = 0; i < length; i++) {
		if (head == NULL) {
			head = (Node)malloc(sizeof(struct MyNode));
			head->element = fnode[i];
			head->left = NULL;
			head->right = NULL;
			head->next = NULL;
			tail = head;
		}
		else {
			t = (Node)malloc(sizeof(struct MyNode));
			t->element = fnode[i];
			t->left = NULL;
			t->right = NULL;
			t->next = NULL;
			tail->next = t;
			tail = t;
		}
	}
	Node h = head;
	//Build the Huffman tree
	while (h->next->next != NULL) {
		//find the smallest two elements
		if (h->element <= h->next->next->element) {
			Node t1;
			t1 = (Node)malloc(sizeof(struct MyNode));
			t1->element = h->element + h->next->element;
			t1->left = h;
			t1->right = h->next;
			t1->next = h->next->next;
			h = t1;
		}
		else {
			Node t2;
			t2 = (Node)malloc(sizeof(struct MyNode));
			t2->element = h->next->element + h->next->next->element;
			t2->left = h->next;
			t2->right = h->next->next;
			t2->next = h->next->next->next;
			h->next = t2;
		}
	}

	Node t3;
	t3 = (Node)malloc(sizeof(struct MyNode));
	t3->left = h;
	t3->right = h->next;
	t3->next = NULL;
	t3->element = 0;
	int WPL = 0;
	WPL = calWPL(t3, 0); //Calculate the Wpl of the Huffman code
	if (wpl <= WPL)return 1;//Check the two Wpl values
	else return 0;
}