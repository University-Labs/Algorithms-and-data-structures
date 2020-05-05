#include "stdafx.h"
#include <fstream>
#include <iostream>

using namespace std;

class list{
public:
	list(){
		head = nullptr;
	}
	~list(){
		clear();
	}

	void push_back(int data);//������ � �����
	void push_front(int data);//�������� � ������ ������
	int del_start(); //�������� ������� ��-�� ������
	int del_back(); //�������� ���������� ��-�� ������
	void print_list();//������ ������
	void clear(); //������� � �������� ������
	void insert(int i, int data);//�������� ������� �� i-�� �����
	void remove(int i);//��������
	int read(int i, int* x); //������ i-�� ��������
	int get_start(int *x);
	int find_elem(int x);


private:
	class node{//������ ��������� ������� ������
	public:
		node *next;//��������� �� ��������� �������
		int data;//�������������� ���� �������� ������
		node(int data = 0, node *next = nullptr){//����������� � �����������
			this->data = data;
			this->next = next;
		}
	};

	node *head;//��������� � ������ �� ������
};

void list::push_back(int data)/*�������� � ����� ������*/{
	if (head == nullptr)//���� �� ������ ����� � ������
		head = new node(data);//������� ������ � ���������� � ��� data
	else
	{
		node *curr = this->head;//��� ����������� �� ������
		while (curr->next != nullptr)//������������ �� ����� ������
			curr = curr->next;
		curr->next = new node(data);//��������� ����� ������� ������
	}
}
void list::push_front(int data)/*�������� � ������*/{
	node *old_head = head;//������� ���������� ��� ������ ������ ������
	node *new_head = new node;//������� ����� ������
	new_head->data = data;//����������� �� ��� ����
	new_head->next = old_head;//��������� next ��� ������ ������
	head = new_head;//��������
}
int list::del_start()/*������� �� ������*/{
	if (head == nullptr)//���� ������ ����
		return 0;
	else
	{
		node *temp = head;//��� �������� ������ ������
		head = head->next;
		delete temp;//������� ������ ������
		return 1;
	}
}
int list::del_back()/*���������� �� ����� ������*/{
	if (head == nullptr)//���� ������ �����
		return 0;
	else
	{
		if (head->next == nullptr)
		{
			node* temp = head;
			head = nullptr;
			delete temp;
		}
		else
		{
			node *curr = head;//��� ����������� �� ������
			node *prev = nullptr;
			while (curr->next != nullptr)
			{
				prev = curr;
				curr = curr->next;
			}
			delete prev->next;
			prev->next = nullptr;
		}
		return 1;
	}
}
void list::print_list()/*������ ������*/{
	if (head == nullptr)//������� ������
		cout << "List is empty" << endl;
	else
	{
		node *curr = head;//��� ������������ ������ ������
		while (curr != nullptr)//���� ��������� ������� ������ �� ����� �������
		{
 			cout << curr->data << " "; //������� ���.����
			curr = curr->next;//���������� �� ������
		}
		cout << endl;
	}
}
void list::insert(int i, int data){
	if (i < 0)//���� ��� ����� ������������� ����� �������� ������
		cout << "An invalid item number." << endl;
	else
	{
		if (head == nullptr)//���� ����� ������ ������
			push_front(data);
		else
		{
			node *prev = head; //��� ������������ ������ ������
			for (int count = 0; count < i - 1; count++)//������������� �� ����� ������
			{
				if (prev->next == nullptr)//���� �������� ����� ������ ��� �� ���������� ������������ ������
				{
					cout << "An invalid item number. The item was written to the end of the list" << endl;
					break;
				}
				prev = prev->next;//� ����.��������
			}
			if (i == 0)
			{
				push_front(data);//���������� ���������� � ������ ������
			}
			else
			{
				node *new_node = new node; //������� ����� ������� ������
				new_node->data = data; //���������� ��� ���� � ������ �������
				new_node->next = prev->next; //�������� ������ ������� ����� i - 1 � i-�
				prev->next = new_node;
			}
		}
	}
}
void list::remove(int i){
	if (i < 0 || head == nullptr)
		cout << "An invalid item number." << endl;
	else
	{
		node *curr = head;
		int size = 0;
		while (curr != nullptr)
		{
			curr = curr->next;
				size++;
		}
		curr = head;
		if (i == 0)
		{
			del_start();
			return;
		}
		if (i >= size)
			return;
		else
			for (int k = 0; k < i- 1; k++)
				curr = curr->next;
					if (i == size -1)
					{
						delete curr->next;
						curr->next = nullptr;
					}
					else
					{
						node *del = curr->next;
						curr->next = curr->next->next;
						delete del;
					}

		}
}
void list::clear(){
	while (head != nullptr)
		del_start();//������� ������ ������� ������, ���� �� �� ������ �������
}
int list::read(int i, int *x)/*��������� i-� ������� ������*/{
	if (head != nullptr)
	{
		node *curr = head; //��� �������� �� ������
		bool check_empty = false;
		for (int k = 0; k < i; k++)
		{
			if (curr->next == nullptr)
			{
				check_empty = true;
				break;
			}
			curr = curr->next;
		}
		if (!check_empty)
		{
			*x = curr->data; //���������� �������� �� ������ i
			return 1;
		}
		else
			return 0;
	}
	else
		return 0;
}
int list::get_start(int *x){
	if (head == nullptr)
		return 0;
	else
	{
		node *temp = head;
		*x = head->data;
		head = head->next;
		delete temp;
		return 1;
	}
}
int list::find_elem(int x)/*����� ������� ��������� ��������*/{
	int count = 0; //������� ����� ������� �� ����� ������
	if (head != nullptr)
	{
		node *curr = head;
		while (curr != nullptr)
		{
			if (curr->data == x)
				return count;
			curr = curr->next;
			count++;
		}
		return -1;
	}
	else
		return -1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	/*ofstream out("output.dat");//��� ������ ����������
	ifstream in("input.dat"); //��� ������ ��������� ������
	if (!(in.is_open())) //���� ���� �� ������
	{
		cout << "File wasn't open" << endl;
		ofstream tmp("input.dat");//������� ����� �� ����
		tmp.close();
	}
	else
	{
		cout << "File input.dat was successfully opened" << endl;
		int x; //��������� �����
		list *start_lst = new list();//������ ������
		list *list_chet = new list();//������ ������ ���������
		list *dividing_by3 = new list();//������ ��������� �� 3
		
		//��������� �������� ������
		while (in >> x)
		{
			start_lst->push_back(x);
		}
		if (!in.eof())
			cout << "File is broken. Error!" << endl;
		else
		{
			cout << "Starts list:" << endl;
			start_lst->print_list();//������ ��������� ������

			//�������� �� ������������ ������ � ��������� ���������
			int i = 0; //������� ��� ������� �� ������
			while (start_lst->read(i, &x))//���� �� ����� ��������� i-� ������� ������
			{
				bool check = true;//��� ��������, ����� �� ����� � ��������� ��� ���
				if (x % 2 == 0)
				{
					list_chet->push_back(x);//������� � ���������
					check = false;
				}
				if (x % 3 == 0)
				{
					dividing_by3->push_back(x);//������� � ���������
					check = false;
				}
				if (!check)
					start_lst->remove(i);//������� �������, ���� �� ����� ���� �� � ���� ���������
				else
					i++;//� ������ ������ ��������� �� ��������� ������� ������
			}
			
			//������ �� ����� � ������ �������������� ������� � ����
			cout << "\nResult of programme is: " << endl;
			cout << "List of numbers that divided by 3: " << endl;
			dividing_by3->print_list();//������ ������ ��������� ������� ���
			while (dividing_by3->get_start(&x))//������ � ���� ������ /3
				out << x << " ";
			out << "\n";
			cout << "List of even numbers: " << endl;
			list_chet->print_list();//������ ������ ������ ���������
			while (list_chet->get_start(&x))//������ � ���� ������ ������ �����
				out << x << " ";
			out << "\n";
			cout << "List of other numbers: " << endl;
			start_lst->print_list();//������ ��������� ���������� � ������
			while (start_lst->get_start(&x))//������ � ���� ��������� �����
				out << x << " ";

			delete start_lst;//����������� ������
			delete list_chet;//����������� ������
			delete dividing_by3;//����������� ������
		}
	}
	in.close();//��������� �����
	out.close();
	*/
	list a;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a.remove(2);
	a.print_list();
	return 0;
}

