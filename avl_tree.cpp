#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;


struct nodeAVL {//���� ������
	double data; // ����
	nodeAVL *left, *right;//��������� �� ������ � ������� ��������
	int height; //������

	nodeAVL(double data) {//����������� � ����������
		this->data = data;
		left = NULL;
		right = NULL;
		height = 1;
	}
};

int Height(nodeAVL* node) { //���������� ������ ������
	if (node) //���� ������ �� �����
		return node->height;//������
	else
		return 0;//������ 0
}
int BalanceLevel(nodeAVL* node) { //����������� ������ ������� ����
	return Height(node->right) - Height(node->left);
}
void ChangeHeight(nodeAVL* node) //��������� ������ ������ ��� ������� � ����������
{
	int left, right;

	left = Height(node->left);//������ ������ �������
	right = Height(node->right);//������ ������� �������
	node->height = (left > right ? left : right) + 1;//������ ���� - ������������ �� ����
}
nodeAVL* RightTurn(nodeAVL* node) //����� ������ �������
{
	nodeAVL* left_s = node->left;//���������� ������ ���� ����
	node->left = left_s->right;//������ ������ ���� ����
	left_s->right = node;//��� ������� ������ ���� ������ �������� ������ ����������� ����
	ChangeHeight(node);//������ ������
	ChangeHeight(left_s);//������ ������
	return left_s;//���������� ������������ ����
}
nodeAVL* LeftTurn(nodeAVL* node) // ����� ����� �������
{
	nodeAVL* right_s = node->right;//���������� ������� ���� ����
	node->right = right_s->left;//������ ������� ���� � ������������ ����
	right_s->left = node;//��� ������� ������� ���� ����� �������� ������ ����������� ����
	ChangeHeight(node);//������ ������
	ChangeHeight(right_s);//������ ������
	return right_s;//���������� ������������ ����
}
nodeAVL* Balance(nodeAVL* node)//������� ������������ ����
{
	ChangeHeight(node); //���������� ������ 
	if (BalanceLevel(node) == 2) //���� ������ ��������� ������������
	{
		if (BalanceLevel(node->right) < 0)// ���� ���� ����� �� ������� ����
			node->right = RightTurn(node->right);//��������� ����� ������ �������
		return LeftTurn(node);//����� ����� �������
	}

	if (BalanceLevel(node) == -2)//���� ����� ��������� ������������
	{
		if (BalanceLevel(node->left) > 0)//���� ���� ������ �� ������� ����
			node->left = LeftTurn(node->left);//��������� ����� ����� �������
		return RightTurn(node);//����� ������ �������
	}
	return node;//���� �� � ��� ���������������, ���������� ��� �� ����
}
nodeAVL* Push(nodeAVL* node, double data)//���������� �������� � ������
{
	if (!node)//������ �����(����� �� ��� �����)
	{
		return new nodeAVL(data);
	}
	if (data < node->data)//���� ����� ������ ����� � ����
		node->left = Push(node->left, data);//���� ���������� �����
	else
		node->right = Push(node->right, data);//���� ���������� ������
	return Balance(node);//�������� ������������
}
nodeAVL* FindMin(nodeAVL* node) // ����� ���� � ����������� ������ 
{
	if (node->left != NULL)//���� �� ����� �� �����
		return FindMin(node->left);//�������� ���������� �����
	else return node;//���������� ���� ����(�� �����������)
}
nodeAVL* RemoveMin(nodeAVL* node) // �������� ���� � ����������� ������
{
	if (node->left == nullptr)//e��� ��� ������ �������
		return node->right;//���������� ������� �������

	node->left = RemoveMin(node->left);//����� �������� ������

	return Balance(node);//�������� ������������
}
nodeAVL* DelElem(nodeAVL* node, double a) // �������� ����� a �� ��� ������
{
	if (node == nullptr) //������ �����(�������� ���)
		return 0;
	if (a < node->data)//���� ������ ������ ����� ����(����� ����)
		node->left = DelElem(node->left, a);//���� �����
	else if (a > node->data)
		node->right = DelElem(node->right, a);//���� ������
	else//���� �����
	{
		nodeAVL* left = node->left;//��������� ��� �������
		nodeAVL* right = node->right;
		delete node;//������� ���� �������

		if (right == nullptr)//���� ��� ������� ���������
			return left;//�� ������ ���������� � ������ ������ �������
		//���� �� ������ ��������� ����
		nodeAVL* min = FindMin(right);//������� ������� � ���� ���������
		min->right = RemoveMin(right);//� ������ ��� �� ����� ������� ����
		min->left = left;//������������ � ���� ������ ����� ����

		return Balance(min);//����������� ������������ ������
	}

	return Balance(node);//�������� ������������ ����� ��������
}

static int count_elem = 0;
void print(nodeAVL *node, int level){//������������ �����
	if (node == nullptr)//���� ����
		return;
	else
	{
		print(node->left, level + 1); //�������� ������� ��� ������ ������ ���������
		for (int i = 0; i < level; i++)//��� ����������� �������� �������
			cout << "  ";
		count_elem++;
		cout << node->data << endl;//�������� ���. ����
		print(node->right, level + 1);//��������� � ������� ���������
	}
}
void print_to_file(nodeAVL *t, int level, ofstream &out){//������ � ����
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


int _tmain(int argc, _TCHAR* argv[])
{
	ifstream inp("input_tree.txt");//��� �������� ����� ��� ������
	ifstream inp_sled("input_sled.txt");
	ofstream outp("output.txt");//��� �������� ����� ��� ������

	if (!inp.is_open() || !inp_sled.is_open())
	{
		cout << "Files were not opened" << endl;
		ofstream n("input_tree.txt");
		n.close();
	}
	else
	{
		inp_sled.seekg(0, ios_base::end);//���������� ������ �����
		int sizeoff = inp_sled.tellg();
		inp_sled.seekg(0, ios_base::beg); //������������ ��������� �� ������
		if (sizeoff == 0)//���� ����
			cout << "File inp_sled.txt is empty" << endl;
		else
		{
			char *footprint = new char[sizeoff]; //����

			char c; //��������� ������ �� �����
			int k = 0;
			while (inp_sled.get(c))//��������� ���� �� �����
			{
				if (c != '0' && c != '1')
				{
					cout << "Wrong track!" << endl;
					return 1;
				}
				footprint[k++] = c;
			}
			if (footprint[0] != '1')//���� �� ����� ������ �����
			{
				cout << "Wrong track!" << endl;
				return 1;
			}

			double x; //����� ��� ����������
			if (inp >> x)
			{
				nodeAVL *tree = new nodeAVL(x);//������� ������ ������
				while (inp >> x)
					tree = Push(tree, x);//��������� ��� ������
				cout << "Your tree is: " << endl;
				print(tree, 0); //�������� ������
				cout << "Your track is: ";
				for (int i = 0; i < sizeoff; i++)//�������� ����, ���� �������� ����� �������
					cout << footprint[i];
				cout << endl << endl;

				//��������� �����
				nodeAVL *tmp = tree;//���������� ������ ������
				bool error = false;//���� �� ������ ������� � ������
				for (int i = 1; i < sizeoff; i++)//�������� �� ������� �������� "�����"
				{
					if (footprint[i] == '0')
					{
						if (tmp->left == nullptr)//���� ������ ������� ���
						{
							error = true; break;//������������� ������ ������ � �������
						}
						tmp = tmp->left;//���� �����
					}
					else
					{
						if (tmp->right == nullptr)//��� ������� �������
						{
							error = true; break;//������ � �����
						}
						tmp = tmp->right;//���� ������
					}
				}
				if (error)//���� �� ����� ����
					cout << "Key wasnt found" << endl;
				else
				{
					tree = DelElem(tree, tmp->data);// ������� ���� � ������ ������
				}

				cout << "Resulting tree" << endl; count_elem = 0;
				print(tree, 0);//�������� ������������ ������
				if (!count_elem)
					cout << "Tree is empty" << endl;

				//������ � ����
				print_to_file(tree, 0, outp);
			}
			else
				cout << "File tree is empty" << endl;
		}
	}
	inp_sled.close();//��������� �����
	inp.close();//��������� �����
	outp.close(); //��������� �����
	return 0;
}