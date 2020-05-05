#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

struct Ducha //�������� ���� ������
{
	int x;//����
	int y;//���������
	Ducha *left, *right; //��������� �� ������ � ������� ��������
	Ducha(int key, int prior, Ducha *left = nullptr, Ducha *right = nullptr) { x = key, y = prior, this->left = left, this->right = right; }//�������� ������ ��-�� ������
};

Ducha* Merge(Ducha *L, Ducha *R) {//����������� ���� ����������� (� � �)
	if (L == nullptr) //������ ���
		return R;
	if (R == nullptr)//������� ���
		return L;
	if (L->y > R->y)//��������� ������ ������ ���������� �������
	{
		Ducha *a = Merge(L->right, R);//������� ������ ��������� � ������ � ������
		return new Ducha(L->x, L->y, L->left, a);//������ ����� ������ (� ������ � ����� ���������)
	}
	else
	{
		Ducha *a = Merge(L, R->left);//������� ����� ��������� � ����� ���������� �������
		return new Ducha(R->x, R->y, a, R->right);//������� ����� ������ (� ������ � ������ ���������)
	}
}
void Split(Ducha *T, int x, Ducha *&L, Ducha *&R){//���������� ������ �� �����
	Ducha *a = nullptr;
	if (T->x <= x) //���� ���� ���� ������ ����� ��� ����������
	{//��� ������
		if (T->right == nullptr)//���� ��� ������� ���������
			R = nullptr;//�� ������ ��������� ��� ������� ���������� �������(����� �� ������ ����)
		else
			Split(T->right, x, a, R);//����� ����� ��������� ������ ��������� �� split(����� ������ �� ���� ����, ������� x)
		L = new Ducha(T->x, T->y, T->left, a);//����� ���������� ���������� ����� ��������� ������������, � ������ - ����� ��������� ������� ���������
	}
	else
	{//��� �����
		if (T->left == nullptr)//���� ��� ������ ���������
			L = nullptr;//�� ����� �� ����� ����������
		else
			Split(T->left, x, L, a);//����� ��������� ����� ��������� �� split(����� ������ ���� ������� x)
		R = new Ducha(T->x, T->y, a, T->right);//��������� �� ������� ��������� � ������ ��������� �� ������������ ������� ����� ������ ���������
	}
}
Ducha* Add(Ducha *T, int x)
{
	Ducha *l, *r;
	Split(T, x, l, r);//��������� ������ T �� ����� x
	Ducha *m = new Ducha(x, rand() % 100);//�������� ������ ���� � �������� ������ � ��������� �����������
	return Merge(Merge(l, m), r); //��������� ���� � ������ x ������� � ����� ����������(��� ��� ����� ����� x), ����� � ������(��� ��� ������ x)
}
Ducha* Delete(Ducha *T, int x){//�������� ����� �� ������
	Ducha *l, *r, *rl;
	Split(T, x - 1, l, r);// ��������: � l - ��� ����� �������, ���� ������ x - 1, � r - ������ ���� ������ x
	Split(r, x, rl, r);// �������� � rl ������ ��� ���� x, � � r ��� ���������
	delete rl;
	return Merge(l, r);//���������� ������������ ����������
}
void Print(Ducha *node, int level){//������ ������
	if (node == nullptr)//���� ����
		return;
	else
	{
		Print(node->left, level + 1); //�������� ������� ��� ������ ������ ���������
		for (int i = 0; i < level; i++)//��� ����������� �������� �������
			cout << "    ";
		cout << node->x << "(" << node->y << ")" << endl;//�������� ���. ����
		Print(node->right, level + 1);//��������� � ������� ���������
	}
}
static int countss = 0;
void create_mass(Ducha *node, int *massive)//���� ��������� �������� �������
{
	if (node == nullptr)
		return;
	else
	{
		create_mass(node->left, massive);//������� � ������� ���
		create_mass(node->right, massive);
		massive[countss++] = node->x;
	}
}
void make_massive(Ducha *node, int *massive){//�������� �������(������)
	countss = 0;
	create_mass(node, massive);
}
void print_to_file(Ducha *t, int level, ofstream &out){//������ � ����
	if (t == nullptr)//���� ����
		return;
	else
	{
		print_to_file(t->left, level + 1, out); //�������� ������� ��� ������ ������ ���������
		for (int i = 0; i < level; i++)//��� ����������� �������� �������
			out << "    ";
		out << t->x << "\n";//�������� ���. ����
		print_to_file(t->right, level + 1, out);//��������� � ������� ���������
	}
}



int _tmain(int argc, _TCHAR* argv[])
{
	ifstream inp("input.txt");//��� �������� ����� ��� ������
	ofstream outp("output.txt");//��� �������� ����� ��� ������

	if (!inp.is_open())
	{
		cout << "File input.text wasn't open" << endl;
		ofstream n("input.txt");
		n.close();
	}
	else
	{
		Ducha *first = nullptr; //������ �������� ������
		Ducha *second = nullptr;//������ �������� ������
		int amount_in_first = 0, amount_in_second = 0; //���������� ��������� � ������ ������
		int x; //��������� ���������� ��� ���������� �� �����
		char c;//��� ���������� ����� ������
		if (inp.get(c))//������� ���� ������
		{
			inp.seekg(0, ios_base::beg); //����� � ������ �����
			if (c != '\n')//������ ������ �� ������
			{
				while (inp >> x)//������ �����
				{
					amount_in_first++;
					if (first == nullptr)
						first = new Ducha(x, rand() % 100); //������ ������
					else
						first = Add(*&first, x);
					inp.get(c); //��������� 1 ������
					if (c == '\n')//������� ��� ������� ����� ������
						break;
				}
			}
			else
				inp.get(c);//���������� ��������� ���� ��

			cout << "First tree was successfuly read" << endl;
			inp.get(c);//������ \n ��� ������ �����

			if (c != '\n')//���� ������ ������ �� ����
			{
				inp.seekg(-1, ios_base::cur); //������������ ����� � �����
				while (inp >> x)//������ �����
				{
					amount_in_second++;
					if (second == nullptr)
						second = new Ducha(x, rand() % 100); //������ ������
					else
						second = Add(*&second, x);
					inp.get(c); //��������� 1 ������
					if (c == '\n')//���� ����� ������, �� ��������� ����
						break;
				}
			}
			cout << "Second tree was successfully read" << endl;

			if (!inp.eof())
				cout << "File is broken" << endl;
			else
			{
				cout << "First tree:" << endl;
				if (first)// �������� ��� �������� ������ �� �����
					Print(first, 0);
				else
					cout << "Tree is empty" << endl;

				cout << "Second tree:" << endl;
				if (second)// �������� ��� �������� ������ �� �����
					Print(second, 0);
				else
					cout << "Tree is empty" << endl;
				int *massive1 = new int[amount_in_first]; //������ �� ���� ��������� ������
				int *massive2 = new int[amount_in_second];//������ �� ���� ��������� ������
				if (first)
					make_massive(first, massive1);//������������ ��������
				if (second)
					make_massive(second, massive2);

				//���� ��������� �������� � ������������ ������ ������
				Ducha *Result_tree = nullptr;
				if (amount_in_first != 0 && amount_in_second != 0)
					for (int i = 0; i < amount_in_first; i++)
					{
						for (int j = 0; j < amount_in_second; j++)
							if (massive1[i] == massive2[j])//���� ���� ���������� ��������
							{
								first = Delete(*&first, massive1[i]);//������� �� �� ��������
								second = Delete(*&second, massive1[i]);
								if (Result_tree == nullptr)//���� �������������� ������ ��� �����
									Result_tree = new Ducha(massive1[i], rand() % 100);//������� ��� � ��������� � ���� ���� �������
								else
									Result_tree = Add(*&Result_tree, massive1[i]);//������ ��������� � ������ ������������� �������
								break;
							}
					}
				cout << "First tree after changing:" << endl;
				if (first)//�������� ����������
					Print(first, 0);
				else
					cout << "Tree is empty" << endl;
				cout << "Second tree after changing" << endl;
				if (second)//�������� ����������
					Print(second, 0);
				else
					cout << "Tree is empty" << endl;
				cout << "Result tree is:" << endl;
				if (Result_tree)//�������� ����������
				{
					Print(Result_tree, 0);
					print_to_file(Result_tree, 0, outp);//������ � ����
				}
				else
					cout << "Tree is empty" << endl;
				delete massive1, massive2;
			}
		}
		else
			cout << "File is empty!" << endl;
	}
	inp.close();
	outp.close();
	return 0;
}

