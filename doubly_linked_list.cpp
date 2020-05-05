#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

class list2{
public:
	list2(){
		first = nullptr;
		last = nullptr;
	}
	~list2(){
		clear();
	}

	void push_back(double data);//������ � �����
	void push_front(double data);
	int del_start(); //�������� ������� ��-�� ������
	int del_back(); //�������� ���������� ��-�� ������
	void print_list();//������ ������
	void clear(); //������� � �������� ������
	void insert(double data, int index);//�������� ������� ����� i-��
	void remove(int i);//�������� �� ������
	int find_by_num(int num, double *x);
	int find_by_value(double x, int *num);
	void add_before_i(int i, list2* A);//�������� ����� i-� �������
	void write_to_file(ofstream &out);//�������� ������ � ����
private:

	class node{
	public:
		node *next;//��������� �������
		node *prev; //���������� �������
		double data; //�������������� ����
		node(double data = 0){
			this->data = data;
			this->next = nullptr;
			this->prev = nullptr;
		}
	};
	node *first, *last; //������ �������
};

void list2::add_before_i(int i, list2* A)
{
	if (first == nullptr)//���� ����������� ������ ����
		return;
	else
		if (i < 0)
			cout << "Index isn't negative" << endl;
		else
		{
			int count = 0;
			node *amount = first;
			while (amount != nullptr)
			{
				count++;
				amount = amount->next;
			}
			if (count + 1 > i)
			{
				node *curr = A->first;//������ �� ������� ������, ������� ����� �����������
				while (curr != nullptr)//���� �� ����� �� ����� ����������� ������
				{
					insert(curr->data, i);//��������� �� ����� i
					curr = curr->next;//�������� ������ �� ����������� ������
					i++;//����������� i
				}
			}
			else
				cout << "You can't add list after " << i << " element" << endl;
		}
}
int list2::find_by_value(double x, int *num){
	if (first == nullptr)//���� � ������ ��� �� 1 ��������
		return 0;
	else
	{
		node *curr = first; //��� ����������� �� ������
		bool find = false;
		int count = 0;//������� ���������� �������� � ������
		while (!find && curr != nullptr)//���� �� ����� � �� ����� ������
		{
			if (curr->data == x)//���� �����
				find = true;
			else
			{
				curr = curr->next;//��������� �� ������ �����
				count++;
			}
		}
		if (!find)
			return 0;
		else
		{
			*num = count;//���������� ���� ������
			return 1;
		}
	}
}
int list2::find_by_num(int num, double *x)//����� �� ������
{
	if (num < 0)
		return 0;
	else
	{
		node *curr = first;
		int count = 0; //�������
		while (curr != nullptr && count < num)
		{
			curr = curr->next;
			count++;
		}
		if (curr != nullptr)//���� ����� ������� ����
		{
			*x = curr->data;//���������� ��� ��� ���� � ����������
			return 1;
		}
		else
			return 0;
	}
}
void list2::push_back(double data){//����������  � �����
	if (last == nullptr)//���� ������ ����
		first = last = new node(data);
	else
	{
		node *curr = this->last;//��� ������������ �� ������
		curr->next = new node(data);//������� ����� �������
		curr->next->prev = curr;//���� prev � ������ �������� ������ �� ����������
		last = curr->next;
	}
}
void list2::push_front(double data){//���������� � ������
	if (first == nullptr)//���� ������ ����
		first = last = new node(data);
	else
	{
		node *new_first = new node(data);//������� �����  ������� ������
		new_first->next = first;//������������� ����� ����� ����� ��������� � ������ first
		first->prev = new_first;
		first = new_first;//����� first ��� ����� �������� �������
	}
}
int list2::del_start(){//�������� �� ������
	if (first == nullptr)//���� � ������ �� ������ ��������
		return 0;
	else
	{
		if (first->next == nullptr)//���� ������� ������������
		{
			delete first;//������� ������ �������
			first = nullptr;//������������� ������ � nullptr
			last = nullptr;
			return 1;
		}
		else
		{
			node *old_head = first;//���������� ������ ������ �������
			first = first->next;//�������� ������ �������
			first->prev == nullptr;
			delete old_head;//������� ���
			return 1;
		}
	}
}
int list2::del_back(){//�������� �� ����� ������
	if (last == nullptr)//���� ������ ����
		return 0;
	else
	{
		if (last->prev == nullptr)//���� ���� ������� � ������
		{
			first = nullptr;
			last = nullptr;
			return 1;
		}
		else
		{
			node *curr = last;//��� ������������ �� ������
			curr->prev->next = nullptr;
			last = curr->prev;
			delete curr;//������� ���� �������
			return 1;
		}
	}
}
void list2::print_list(){//������ ������
	if (first == nullptr)
		cout << "List is empty" << endl;
	else
	{
		node *curr = first;//��� ������������ ������ �����f
		while (curr != nullptr)//���� ��������� ������� ������ �� ����� �������
		{
			cout << curr->data << " "; //������� ���.����
			curr = curr->next;//���������� �� ������
		}
		cout << endl;
	}
}
void list2::insert(double data, int index){//������� �������� � �������� �����
	if (index < 0)//���� ��� ����� ������������� ����� �������� ������
		cout << "An invalid item number." << endl;
	else
	{
		if (first == nullptr || index == 0)//���� ����� ������ ������� ������������
			push_front(data);//���������� � ������
		else
		{
			node *prev = first; //��� ������������ ������ ������
			int count = 0; //�������
			while (prev->next != nullptr)
			{
				if (count == index - 1)//���� �������� ����������� �����
				{
					node *new_node = new node(data); //������� ����� ������� ������
					new_node->next = prev->next; //�������� ������ ������� ����� i - 1 � i-�
					new_node->prev = prev;
					prev->next = new_node;
					new_node->next->prev = new_node;
					break;
				}
				count++;
				prev = prev->next;//� ����.��������
			}
			if ((count <= index - 1) && prev->next == nullptr) //���� �� ����� �� ����� �������
			{
				push_back(data);//���������� � �����
			}
		}
	}
}
void list2::remove(int i){//�������� �������� � ������������ �������
	if (first == nullptr)//��� �� ������ ��������
	{
		cout << "List is empty already" << endl;
		return;
	}
	else
		if (i < 0)//����� ������������ �����
		{
			cout << "It's impossible to delete a negative number" << endl;
			return;
		}
		else
			if (i == 0)//���� ������� ������� �������
			{
				del_start(); //�������� �� ������ ������
				return;
			}
			else
			{
				node *curr = first;
				int index = 0;
				while (curr != nullptr)
				{
					if (i == index) break;
					curr = curr->next;
					index++;
				}
				if (curr == nullptr) return;
				else
					if (curr->next == nullptr)
					{
						node *laste = last; 
						last = last->prev; 
						last->next = nullptr; 
						delete laste;
					}
					else
					{
						curr->prev->next = curr->next;
						curr->next->prev = curr->prev;
						delete curr;
					}
			}
}
void list2::clear(){//������� ����� ������
	while (first != nullptr)
		del_start();//������� ������ ������� ������, ���� �� �� ������ �������
}
void list2::write_to_file(ofstream &out)//������ � ����
{
	node *curr = first;
	while (curr != nullptr)
	{
		out << curr->data << " ";
		curr = curr->next;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
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
		list2 first_list;//������ ������(� ������� ���������)
		list2 second_list; //������ ������(������� ���������)
		double x; //��������� ���������� ��� ���������� �� �����
		char c;//��� ���������� ����� ������
		if (inp.get(c))//������� ���� ������
		{
			inp.seekg(0, ios_base::beg); //����� � ������ �����
			if (c != '\n')//������ ������ �� ����
			{
				while (inp >> x)//������ �����
				{
					first_list.push_back(x);//���������� � ������
					inp.get(c); //��������� 1 ������
					if (c == '\n')//������� ��� ������� ����� ������
						break;
				}
			}
			else
				inp.get(c);//���������� ��������� ���� ��

			cout << "First list was successfuly read" << endl;
			inp.get(c);//������ \n ��� ������ �����

			if (c != '\n')//���� ������ ������ �� ����
			{
				inp.seekg(-1, ios_base::cur); //������������ ����� � �����
				while (inp >> x)//������ �����
				{
					second_list.push_back(x);//���������� � ������
					inp.get(c); //��������� 1 ������
					if (c == '\n')//���� ����� ������, �� ��������� ����
						break;
				}
			}
			cout << "Second list was successfully read" << endl;

			int number = -1; //����� ������� � �������� ��������� ����� ������
			if (inp >> number)//���� ������� ������� �����
			{
				cout << "Number was successfully read" << endl;
				if (number >= 0)//����� ������������� �����
					if (!inp.eof())//��� ���� ���������� � �����
					{
						cout << "Error of reading data from file." << endl;
					}
					else
					{
						cout << "\nInformation:" << endl;
						cout << "First list is: ";
						first_list.print_list();//������ ���� � ������ ������
						cout << "Second list is: ";
						second_list.print_list();//������ ���� � ������ ������
						cout << "Add second list before " << number << " elem of first list " << endl;//������ ���� � i
						cout << "........." << endl;
						cout << "Result list: ";
						first_list.add_before_i(number, &second_list);//��������� �������� ���������� � ������� ������ ��������� �������
						first_list.print_list();//������� ��������� �� �����
						first_list.write_to_file(outp);//���������� ��� � ����
					}
				else
				{
					cout << "The number i must be non-negative.";
				}
			}
			else
			{
				cout << "Error of reading number from file" << endl;
			}
		}
		else
			cout << "File is empty.." << endl;
	}
	inp.close();
	outp.close();
	*/
	list2 a;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a.push_back(5);
	a.remove(3);
	a.remove(2);
	a.remove(0);
	a.remove(1);
	a.print_list();
	return 0;
}
