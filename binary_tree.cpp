#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;


struct node //���� ������
{
	double data;  //�������������� ����
	node *left, *right; //����� � ������ ������� ������
};

struct tree{
	node *root = NULL;//������ ������
};


void find_em(node *(&t), node *(&par), int data){
	if (!t)
	{
		par = nullptr;
		t = nullptr;
	}
	else
	{
		while (t->data != data)
		{
			par = t;
			if (t->data > data)
				t = t->left;
			else
				t = t->right;
			if (t == NULL)
			{
				par = nullptr;
				break;
			}
		}
	}
}
int delete_elem(node **t, int data){
	node *elem = *t;
	node *parent = nullptr;
	find_em(elem, parent, data);
	if (elem == nullptr)
		return 0;
	//��� ��������((
	if (elem->left == NULL && elem->right == NULL)
	{
		if (parent != nullptr)
		{
			if (parent->data > elem->data)
				parent->left = nullptr;
			else
				parent->right = nullptr;
			delete elem;
		}
		else
		{
			elem = nullptr;
		}
		return 1;
	}
	//1 �������
	if (elem->left == NULL && elem->right != NULL || elem->left != NULL && elem->right == NULL)
	{
		if (parent != nullptr)
		{
			if (parent->data > elem->data){
				if (elem->left != nullptr)
				{
					parent->left = elem->left;
					delete elem;
				}
				else
				{
					parent->left = elem->right;
					delete elem;
				}
			}
			else
			{
				if (elem->left != nullptr)
				{
					parent->right = elem->left;
					delete elem;
				}
				else
				{
					parent->right = elem->right;
					delete elem;
				}
			}
		}
		else
		{
			if (elem->left != nullptr)
			{
				elem = elem->left;
				delete elem->left;
				elem->left = NULL;
			}
			else
			{
				elem = elem->right;
				delete elem->right;
				elem->right = NULL;
			}
		}
		return 1;
	}
	//2 �������(������� ��������) �� � ������� ������� ���������� ���� ��� ������ �������
	if (elem->right->left == NULL)
	{
		if (parent != nullptr){
			if (parent->data > elem->data)
			{
				node *tmp = elem->left;
				parent->left = elem->right;
				parent->left->left = elem->left;
				delete elem;
			}
			else
			{
				node *tmp = elem->left;
				parent->right = elem->right;
				parent->right->left = elem->left;
				delete elem;
			}
		}
		else
		{
			node *el = elem;
			elem->right->left = elem->left;
			elem = elem->right;
			delete el;
		}
		return 1;
	}
	//����� ������� ������ �������� ���� � ����� ���������
	if (elem->right != nullptr && elem->left != nullptr){
		;
	}
	return 0;
}

/*������� ������ �������� � �������� ������*/
void push(double a, node **t)
{
	if (*t == nullptr)//������ ������
	{
		*t = new node;//������� ����� ����
		(*t)->data = a;
		(*t)->left = (*t)->right = nullptr;//������ � ����� ������� ����� 0
	}
	else
	{
		if (a >= (*t)->data)//���� �������� ������ ��� � ������ ����
			push(a, &(*t)->right);//�������� � ������� �������
		else
			push(a, &(*t)->left);//�������� � ������ �������
	}
}
/*������� ������ �������� � �������� ���������*/
node* finding_elem(double data, node*t){
	if (t == nullptr)
		return nullptr;
	else
	{
		if (t->data < data)
			t = finding_elem(data, t->right);
		else
		if (t->data > data)
			t = finding_elem(data, t->left);
		else
		return t;
	}
}
node* find_elem(double a, node *t)
{
	if (!t)
		return NULL;
	else
	{
		while (t->data != a)
		{
			if (t->data > a)
				t = t->left;
			else
				t = t->right;
			if (t == NULL)
				break;
		}
	}
	return t;
}

static int count = 0; //��� ������������ ������������������ �� ������
/*������� �������� ������������������(������ ���������� � ������� ���)*/
void posl(node *t, double mass[]){
	if (t == nullptr)//������ �����
		return;
	else
	{
		posl(t->left, mass);//��� � ������ ���������
		mass[::count++] = t->data;//��������� ���� � ������
		posl(t->right, mass);//��� � ������� ���������
	}
}
void create_posl(node *t, double mass[]){
	::count = 0;//���������� ����������� ���������� ��������
	posl(t, mass);//�������� ���� ������� ������������
}

/*������� �������� ������������ ������*/
node* create_tree(node **t, double mass[], int begin, int end){
	if (begin > end)//���� ����� �� ������, ����� ������ ��� �������� ������� ����������
		return NULL;
	int center = (begin + end) / 2; //������� �������� �������
	*t = new node;//������� ����� ����
	(*t)->data = mass[center];//���������� � ���� ����������� ������� �������
	(*t)->left = create_tree(&(*t)->left, mass, begin, center - 1);//��������� ����� ���������(�������� ������� �� ������ �� �������� -1)
	(*t)->right = create_tree(&(*t)->right, mass, center + 1, end);//��������� ������ ���������(�������� ������� �� �������� +1 �� �����)
	return *t;//���������� ������������ ���� � ��� ��������
}
/*������� ����������� ������ �� ������*/
void print(node *t, int level){//������������ �����
	if (t == nullptr)//���� ����
		return;
	else
	{
		print(t->left, level + 1); //�������� ������� ��� ������ ������ ���������
		for (int i = 0; i < level; i++)//��� ����������� �������� �������
			cout << "  ";
		cout << t->data << endl;//�������� ���. ����
		print(t->right, level + 1);//��������� � ������� ���������
	}
}
/*������ � ����*/
void print_to_file(node *t, int level, ofstream &out){//������ � ����
	if (t == nullptr)//���� ����
		return;
	else
	{
		print_to_file(t->left, level + 1, out); //�������� ������� ��� ������ ������ ���������
		for (int i = 0; i < level; i++)//��� ����������� �������� �������
			out << "  ";
		out << t->data << "\n";//�������� ���. ����
		print_to_file(t->right, level + 1, out);//��������� � ������� ���������
	}
}
//������ �����(���)
void pryamoy(node *t){
	if (t == nullptr)//���� ����
		return;
	else
	{
		cout << t->data << " ";
		pryamoy(t->left);
		pryamoy(t->right);
	}
	cout << endl;
}
//�������� �����(���)
void obratniy(node *t){ 
	if (t == nullptr)//���� ����
		return;
	else
	{
		obratniy(t->left);
		obratniy(t->right);
		cout << t->data << " ";
	}
	cout << endl;
}

double amount(node* node, int a)
{
	if (node->left == nullptr || node->right == nullptr)
	{
		return 0;
	}
	return (a + amount(node->right, a + 1) + amount(node->left, a + 1));
}
int amount_of_vn(node *node, int am){
	if (node->left == nullptr || node->right == nullptr)
		return 0;
	else
		return amount_of_vn(node->right, am) + amount_of_vn(node->left, am) + 1;
}
int _tmain(int argc, _TCHAR* argv[])
{
	tree a;
	push(30, &a.root);
	push(128, &a.root);
	push(9, &a.root);
	push(242, &a.root);
	push(222, &a.root);
	push(45, &a.root);
	push(36, &a.root);
	push(127, &a.root);
	push(26, &a.root);
	print(a.root, 0);
	cout << "RJKBXTCND: " << amount(a.root, 0) << endl;
	cout << amount_of_vn(a.root, 0);
	cout << endl << endl;
	/*ifstream inp("input.dat");//��� �������� ����� ��� ������
	ofstream outp("output.dat");//��� �������� ����� ��� ������

	if (!inp.is_open())
	{
		cout << "File input.dat wasn't open" << endl;
		ofstream n("input.dat");
		n.close();
	}
	else
	{
		tree start_t; //��������� ������
		tree result_t;//��������������(����������� ������)
		double x; //��������� ���������� ��� ���������� �� �����
		char c;//��� ���������� ����� ������
		int size = 0; //���������� ����� � ������/�������

		cout << "Now reading of information from file is happened.." << endl;
		while (inp >> x)
		{
			push(x, &start_t.root); //���������� ����� � ������
			size++;//���������� �����
		}
		if (size > 0)
		{
			double *mass = new double[size]; //�������� ������� ��� �������� ������������������

			cout << "Your tree is: " << endl;
			print(start_t.root, 0); //�������� �������� ������
			delete_elem(&start_t.root, 60);
			push(60, &start_t.root);
			print(start_t.root, 0);
			create_posl(start_t.root, mass);//������ ������������������ �� �����������

			cout << "\nYour sequence is: " << endl;
			for (int i = 0; i < size; i++)// ������ ������������������
				cout << mass[i] << " ";
			cout << endl;

			create_tree(&result_t.root, mass, 0, size - 1);//������������ ������

			cout << "Result tree is: " << endl;
			print(result_t.root, 0);//������ �� ����� ��������������� ������
			cout << endl;

			print_to_file(result_t.root, 0, outp);//������ � ����
		}
		else
		{
			cout << "File is empty" << endl;
		}
	}
	
	inp.close();
	outp.close();*/

	return 0;
}

