#include <iostream>
#include <cstdlib>
#include <cstring>
#define BIG -1
using namespace std;

typedef struct A {
	int weight;
	char c;
	struct A* Left_Node;
	struct A* Right_Node;
	struct A* next;
}Tree_Node;

typedef struct B {
	int weight;
	char c;
}Weight_Record;

typedef struct C {
	int weight;
	char c;
	char code[70];
}Code_Record;

typedef struct D {
	char c;
	struct D* Left;
	struct D* Right;
}Tree_in;

int create_tree(int n, Weight_Record* record, int func);
int create_Hov(int n, Weight_Record* record);

int main() {
	int low_num, this_num;
	int code_sum;
	cin >> code_sum;
	Weight_Record* record;
	record = (Weight_Record *)malloc(sizeof(Weight_Record)*code_sum);

	low_num = create_Hov(code_sum, record);
	
	int ri;
	cin >> ri;
	while (ri > 0) {
		if (create_tree(code_sum, record, low_num)) cout << "Yes" << endl;
		else cout << "No" << endl;
		ri--;
	}
	
	system("pause");
	return 0;
}

int Print_Hov(Tree_Node* p_node) {
	int func = 0;
	if (p_node->Left_Node != NULL) {
		func += Print_Hov(p_node->Left_Node);
	}
	if (p_node->Right_Node != NULL) {
		func += Print_Hov(p_node->Right_Node);
	}
	if (p_node->c == NULL) {
		func += p_node->weight;
	}
	else {
		func += p_node->weight;
	}
	return func;
}

int Create(char c, char* code, Tree_in* p_code, int i) {
	if (code[i] == '0') {
		if (p_code->Left == NULL) {
			p_code->Left = (Tree_in*)malloc(sizeof(Tree_in));
			p_code->Left->c = NULL;
			p_code->Left->Left = p_code->Left->Right = NULL;
			return Create(c, code, p_code->Left, i+1);
		}
		else
		{
			if (code[i + 1] == NULL)
				return -1;
			if (p_code->Left->c == NULL)
				return Create(c, code, p_code->Left, i + 1);
			else
				return -1;
		}
	}
	else if (code[i] == '1') {
		if (p_code->Right == NULL) {
			p_code->Right = (Tree_in*)malloc(sizeof(Tree_in));
			p_code->Right->c = NULL;
			p_code->Right->Left = p_code->Right->Right = NULL;
			return Create(c, code, p_code->Right, i + 1);
		}
		else
		{
			if (code[i + 1] == NULL)
				return -1;
			if (p_code->Right->c == NULL)
				return Create(c, code, p_code->Right, i + 1);
			else
				return -1;
		}
	}
	else {
		p_code->c = c;
		return 1;
	}
}

int Find(Tree_Node* p_node) {
	Tree_Node* p1;
	Tree_Node* p2;
	Tree_Node* p3;
	Tree_Node* p_last;
	Tree_Node* p;

	p_last = p1 = p2 = p_node;
	p = p1->next;
	while (p != NULL) {
		if (p->weight <= p1->weight) {
			p1 = p;
			p_last = p2;
		}
		else if (p1->weight < 0) {
			p1 = p;
			p_last = p2;
		}
		p2 = p;
		p = p->next;
	}
	p_last->next = p1->next;
	p1->next = p2 = NULL;
	p3 = p1;

	p_last = p1 = p2 = p_node;
	p = p1->next;
	while (p != NULL) {
		if (p->weight <= p1->weight) {
			p1 = p;
			p_last = p2;
		}
		else if(p1->weight < 0){
			p1 = p;
			p_last = p2;
		}
		p2 = p;
		p = p->next;
	}
	p_last->next = p1->next;
	p1->next = p2 = NULL;

	if (p1 == p_node) {
		p1->next = p3;
		return 0;
	}

	else {
		p = (Tree_Node *)malloc(sizeof(Tree_Node));
		p->next = NULL;
		p->c = NULL;
		p->Left_Node = p3;
		p->Right_Node = p1;
		p->weight = p3->weight + p1->weight;

		p_last = p_node;
		while (p_last->next != NULL)
			p_last = p_last->next;
		p_last->next = p;
		return 1;
	}
}

int create_tree(int n, Weight_Record* record, int func) {

	Code_Record* p_code_record;
	p_code_record = (Code_Record*)malloc(sizeof(Code_Record)*n);
	int weight;
	int func_this = 0;
	for (int i = 0; i < n; i++) {
		cin >> p_code_record[i].c;
		cin >> p_code_record[i].code;
		p_code_record[i].weight = record[i].weight;
		func_this += p_code_record[i].weight * strlen(p_code_record[i].code);
	}
	//cout << "func = " << func << " and func_this = " << func_this << endl;
	if (func_this != func)
		return 0;
	
	int flag;
	Tree_in* in_node;
	in_node = (Tree_in*)malloc(sizeof(Tree_in));
	in_node->Left = in_node->Right = NULL;
	in_node->c = NULL;

	for (int i = 0; i < n; i++) {
		flag = Create(p_code_record[i].c, p_code_record[i].code, in_node, 0);
		if (flag == -1)
			return 0;
	}

	return 1;
}

int create_Hov(int n, Weight_Record* record) {
	Tree_Node *p_tree_begin;
	p_tree_begin = (Tree_Node *)malloc(sizeof(Tree_Node));
	Tree_Node *p;
	p = p_tree_begin;
	p->Left_Node = p->Right_Node = p->next = NULL;
	p->c = NULL;
	p->weight = -1;
	for (int i = 0; i < n; i++) {
		p->next = (Tree_Node *)malloc(sizeof(Tree_Node));
		p = p->next;
		p->Left_Node = p->Right_Node = p->next = NULL;
		cin >> p->c;
		cin >> p->weight;
		record[i].c = p->c;
		record[i].weight = p->weight;
	}

	p = p_tree_begin;

	while (Find(p_tree_begin)) {}
	return (Print_Hov(p_tree_begin->next) - p_tree_begin->next->weight);
}