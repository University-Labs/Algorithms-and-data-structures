#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

class list_1_cycle{//����������� 1 �������
public:
	list_1_cycle() //�����������
	{
		first = nullptr;
		last = nullptr;
	}
	~list_1_cycle(){
		clear();
	}
	void push_back(double data); //���������� � �����
	void push_start(double data); //���������� � ������
	int del_back(double *x);//�������� �� �����
	int del_start(double *x); //�������� �� ������
	int del_from_position(int n, double *x);//�������� �� �������
	void push_to_position(int n, double data); //���������� � ������������ �������
	void print_list();//������
	int size();//����������� �������
	int read(int n, double *x);//������ ��� ��������
	void  clear(); //������� ������
private:
	struct node{
	public:
		node *next;//��������� �� ���������
		double data; //��� ����
		node(double data = 0){
			this->data = data;
			this->next = nullptr;
		}
	};
	node *first, *last;//��������� � ������
};

class list_2_cycle_head{//���������� ����������� ������ � �������
public:
	list_2_cycle_head(){ //���������� �� ���������
		head->data = 0;//���������� ���������
		head->next = nullptr;//������ �� ������
		head->prev = nullptr;//������ �� ���������
	}
	~list_2_cycle_head(){
		clear();
	}
	void push_back(double data); //���������� � �����
	void push_start(double data); //���������� � ������
	void push_to_position(int n, double data);//���������� � ������������ ������� � ������
	int del_back(double *x);//�������� �� �����
	int del_start(double *x);//�������� �� ������
	int del_from_position(int n, double *x); //�������� � ������������ �������
	void print_list();//������ ������
	int read(int n, double *x); //������ ��� ��������
	int size(); //������ ������
	void clear(); //������� ������
private:
	struct node{
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
	node *head = new node; //������
};

class list_2_cycle{//����������� 2 �������
public:
	list_2_cycle(){ //���������� �� ���������
		first = nullptr;
	}
	~list_2_cycle(){
		clear();
	}
	void push_back(double data); //���������� � �����
	void push_start(double data); //���������� � ������
	void push_to_position(int n, double data);//���������� � ������������ ������� � ������
	int del_back(double *x);//�������� �� �����
	int del_start(double *x);//�������� �� ������
	int del_from_position(int n, double *x); //�������� � ������������ �������
	void print_list();//������ ������
	void print_reverse();//������ ��������
	int size();//������ ������
	void create_list_from(list_1_cycle &A, list_2_cycle_head &B, list_2_cycle &C);//������������ ������ ������
	int read(int n, double *x);//������ ��� ��������
	void clear(); //������� ������
	void write_to_file(ofstream &outp);//������ � ����
	int clear_memory();//������ ������
private:
	struct node{
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
	node *first; //������ �������
};


void list_2_cycle_head::push_back(double data){//���������� � ����� ������
	if (head->data == 0)
	{
		node *new_elem = new node(data);
		new_elem->next = new_elem;//������������� ���� prev � next
		new_elem->prev = new_elem;
		head->next = new_elem; //������ �� 1 ��������
		head->prev = new_elem;
		head->data = 1; //��������� � ������� ������
	}
	else
	{
		node *new_elem = new node(data);
		new_elem->next = head->next; //��������� ���� next ������������ ����
		new_elem->prev = head->prev;//��������� ���� prev ������������ ����
		head->prev->next = new_elem;//��������� ���� next ��� ���������� ����
		head->next->prev = new_elem;//��������� ���� prev ��� ������� ����
		head->prev = new_elem;//��������� ������ ���������� ��������
		head->data++; //��������� � ������� ������ +1
	}
}
void list_2_cycle_head::push_start(double data){//���������� � ������ ������
	if (head->data == 0)//���� ������ ��� ����
	{
		node *new_elem = new node(data);//������� ����� ������� � ������������� �����
		new_elem->next = new_elem;
		new_elem->prev = new_elem;
		head->next = head->prev = new_elem;//������������� ������ ������� � ���������
		head->data = 1; //������ ������ ������������� � 1
	}
	else
	{
		node *new_elem = new node(data);//������� ����� ������� 
		new_elem->next = head->next;//������������� ����� � ������ ��������
		new_elem->prev = head->prev;
		head->prev->next = new_elem;//���������� ���� next � ���������� ��������
		head->next->prev = new_elem;//���������� � ���� prev � ������� ��������
		head->next = new_elem;//����� ������ ������� - �����
		head->data++;//����������� ����������
	}
}
void list_2_cycle_head::print_list(){//������ ������
	if (head->next == nullptr)//�������
		cout << "List is empty" << endl;
	else
	{
		node *curr = head->next;//� curr ���������� 1 ������� ������
		int size = head->data;//������ ������
		for (int i = 0; i < size; i++)//��������� �� ������
		{
			cout << curr->data << " ";//�������� �������
			curr = curr->next;//��������� � ����������
		}
		cout << endl;
	}
}
void list_2_cycle_head::push_to_position(int n, double data){//���������� � ������������ ������� � ������
	if (n < 0)//������������ �����
	{
		cout << "number must be non negative" << endl;
		return;
	}
	if (head->data == 0)//������ ����
		if (n != 0)
		{
			cout << "Impossible position, your list is empty" << endl;
			return;
		}
		else//��������� �� 0 �����
		{
			push_back(data);
			return;
		}
	if (n > head->data)//���� ����� ������ ��� ������
	{
		cout << "Impossible position, your list has only " << (int)head->data << " elements" << endl;
		return;
	}
	node *curr = head->next;//��� ������������ �� ������
	for (int i = 0; i < n; i++)
		curr = curr->next;//�������� � ������� ��������
	if (n == 0) //���� ��������� � ������ ������
		push_start(data);
	else
		if (curr == head->next)//���� ��������� �� ��������� �������
		{
			push_back(data);
		}
		else
		{
			node *new_elem = new node(data);//������� ����� �������
			new_elem->next = curr;//���� next ��������� �� ������� �������
			new_elem->prev = curr->prev;//���� prev �� ����������
			curr->prev->next = new_elem;//� ����������� ��������� � ���� next ��������� �����
			curr->prev = new_elem;//� ���������� �������� � ���� prev ��������� �����
			head->data++;//����������� ����������
		}
}
int list_2_cycle_head::del_back(double *x){//�������� �� ����� ������
	if (head->data == 0)//���� ������ ������
		return 0;
	else
		if (head->data == 1)//������ �� 1 ��������
		{
			*x = head->next->data;//���������� ��� ���� ��  1 ��������
			head->data = 0;
			head->next = head->prev = nullptr;//�������� ������ � ��������� ��������
			return 1;
		}
		else
		{
			node *curr = head->prev;//���������� ��������� �������
			curr->prev->next = head->next;//������������� ����� 
			head->next->prev = curr->prev;
			head->prev = curr->prev;//������������� ����� ��������� ������� ������
			*x = curr->data;//���������� ���� ���� � ����������
			head->data--;//��������� ���������� ���������
			delete curr;//������� �������
			return 1;
		}
}
int list_2_cycle_head::del_start(double *x){//�������� �� ������
	if (head->data == 0)//���� �� ������ ��������
		return 0;
	else
		if (head->data == 1)//���� ���� �������
		{
			*x = head->next->data;//���������� ��� ����
			head->next = head->prev = nullptr;//�������� ������
			head->data = 0;//��������� � ������ 0
			return 1;
		}
		else
		{
			node *curr = head->next;//���������� � curr ������ �������
			curr->prev->next = curr->next;//���������� �����
			curr->next->prev = curr->prev;
			head->data--;//��������� ������� ���������
			head->next = curr->next;//������������� ����� ������ �������
			*x = curr->data;//��������� ��� ���� � ����������
			delete curr;//������� ������� �������
			return 1;
		}
}
int list_2_cycle_head::del_from_position(int n, double *x){//������� � ������������ �������
	if (n >= head->data)//���� ��������� ������ ������
		return 0;
	if (n < 0)//������������ �����
		return 0;
	if (head->data == 1)//���� ������� ����� 1
		if (n == 0)//� �� �������� ��� �������
		{
			*x = head->next->data;//��������� ���� ����
			head->next = head->prev = nullptr;//�������� ������ �������
			head->data = 0;
			return 1;
		}
		else
			return 0;
	if (n == 0)//���� ������� ������� � ������� 0
	{
		del_start(x);//������� �� ������
		return 1;
	}
	else
	{
		node *curr = head->next->next;//��� �������� �� ������
		for (int i = 1; i < n; i++)//��������� � ������� ��������
		{
			curr = curr->next;
		}
		if (curr->next == head->next)//���� �� ��������� � ������
		{
			del_back(x);//������� �� �����
			return 1;
		}
		else
		{
			curr->prev->next = curr->next;//�������� �����
			curr->next->prev = curr->prev;
			head->data--;//��������� ��� �� ���������
			*x = curr->data;
			delete curr;//������� ���
			return 1;
		}
	}
}
int list_2_cycle_head::read(int n, double *x){
	if (n >= head->data)//���� ����� ������������
		return 0;
	else
	{
		node *curr = head->next;//������ �������
		for (int i = 0; i < n; i++)//��������� �� ������� ��������
			curr = curr->next;
		*x = curr->data;//���������� � ���������� ��� ����
		return 1;
	}
}
int list_2_cycle_head::size(){//������ ������
	return head->data;//����� ���� data �� ������ ������
}
void list_2_cycle_head::clear(){//������� ������
	double a;
	while (head->data != 0)//���� ������ �� ����
		del_start(&a);//������� �� ������
}



void list_1_cycle::push_back(double data){ //���������� � �����
	if (first == nullptr)//������ ����
	{
		node *new_elem = new node(data);//��������� ����� �������
		new_elem->next = new_elem;//������������� ��� ���� next
		first = last = new_elem;//���������� ����� �������� first � next
	}
	else
	{
			node *new_elem = new node(data);//��������� ����� �������
			new_elem->next = first;//��������� �� ����� ��������� - ������
			last->next = new_elem;//��������� �� ��������� - �����
			last = new_elem;//������ ����� ������� ���������
	}
}
void list_1_cycle::push_start(double data){ //���������� � ������
	if (first == nullptr)//������ ����
	{
		node *new_elem = new node(data);//������� ����� �������
		new_elem->next = new_elem;//������ ��� ������������
		first = last = new_elem;
	}
	else
	{
		node *new_elem = new node(data);//������� ����� �������
		new_elem->next = first;//��������� �����
		last->next = new_elem;//� ����� ��������� ������
		first = new_elem;//��������� ������ ������� ������
	}
}
void list_1_cycle::push_to_position(int n, double data){//�������� � ����������� �������
	if (n < 0)//����� ������������
	{
		cout << "number must be non negative" << endl;
		return;
	}
	if (n == 0)//��������� � ������ ������
	{
		push_start(data);
		return;
	}
	int razm = size();
	if (n > razm)//���� ��� ������ ������ � ������
	{
		cout << "Impossible position, your list has only " << razm << " elements" << endl;
		return;
	}
	if (n == razm)//��������� � ����� ������
	{
		push_back(data);
		return;
	}
	node *curr = first;//������� ��������� �� ������ ������� ������
	for (int i = 0; i < n - 1; i++)//��������� �� �������� ����� ���, ������� ��� ���������
		curr = curr->next;
	node *new_elem = new node(data);//������� ����� ��e����
	new_elem->next = curr->next;//���������� ����� � ������������ ��������
	curr->next = new_elem;//���������� ����� �� ����������� � ������
	
}
int list_1_cycle::del_back(double *x){//�������� �� �����
	if (first == nullptr)//�������
		return 0;
	if (first == last)//��������� �������
	{
		*x = first->data;//���������� ��� ���� � ����������
		first = last = nullptr;//�������� ������ � ����� ������
		return 1;
	}
	node *curr = first;//������ ������� ������
	while (curr->next != last)//��������� �� ��������������
		curr = curr->next;
	delete last;//������� ���������
	*x = curr->data;//���������� ��� ���� � ����������
	curr->next = first;//���������� ������ �����
	last = curr;//����� ��������� ������� 
	return 1;
}
int list_1_cycle::del_start(double *x){//�������� �� ������ ������
	if (first == nullptr)//����
		return 0;
	if (first == last)//1 �������
	{
		*x = first->data;//���������� ��� ����
		delete first;//������� ���� �������
		first = last = nullptr;//��������
		return 1;
	}
	node *curr = first;//���������� 1 ��������
	first = curr->next;//�������� ������ ������� ������
	last->next = first;//���������� �����
	*x = curr->data;
	delete curr;//������� ���� �������
	return 1;
}
int list_1_cycle::del_from_position(int n, double *x){//�������� �� ������������ �������
	if (n < 0)//������������ �����
		return 0;
	if (first == nullptr)//������ ����
		return 0;
	if (first == last)//���� 1 ������� � ������
		if (n == 0)//���� ����������� ����� = 0
		{
			*x = first->data;//���������� ��� ����
			delete first;//������� ���
			first = last = nullptr;//��������
			return 1;
		}
		else
			return 0;
	if (n == 0)//���� ������� �� ������ ������
	{
		del_start(x);
		return 1;
	}
	int razm = size();//������ ������
	if (n >= razm)//���� �� ��������
		return 0;
	node *curr = first;//���������� 1 �������
	for (int i = 0; i < n - 1; i++)//�������� �� ����������� ��������
		curr = curr->next;
	if (curr->next == last)//���� ������ ������� ���������
		del_back(x);//������� �� �����
	else
	{
		node *for_del = curr->next;//���������� ������ �������
		curr->next = curr->next->next;//���������� �����
		*x = for_del->data;//���������� ��� ����
		delete for_del;
	}
	return 1;
}
void list_1_cycle::print_list(){
	if (first == nullptr)//������ ����
		cout << "List is empty" << endl;
	else
	{
		node *curr = first;//���������� ������ �������
		do{
			cout << curr->data << " ";//��������
			curr = curr->next;//��������� ������
		} while (curr != first);//���� �� ��������� ����� �� ��������
		cout << endl;
	}
}
int list_1_cycle::size(){//������
	if (first == nullptr)//������ ����
		return 0;
	node *curr = first;//���������� ������ �������
	int size = 0;//��� �������
	do
	{
		curr = curr->next;//��������� �� ������
		size++;//����������� ������
	} while (curr != first);//���� �� ��������� ���������� ��������
	return size;
}
int list_1_cycle::read(int n, double *x){//������ ��� ��������
	if (n >= size() || n < 0) //������������ �����
		return 0;
	else
	{
		node *curr = first;//��������� ������ �������
		for (int i = 0; i < n; i++)//��������� � ��� ������� �� �������
			curr = curr->next;
		*x = curr->data;//���������� ��� ���� � ����������
		return 1;
	}
}
void list_1_cycle::clear(){//������� ������
	double a;
	while (first != nullptr)//���� ������ �� ����
		del_start(&a);//������� �� ������
}

void list_2_cycle::push_back(double data)//��������� � ����� ������������ ������
{
	if (first == nullptr)//������ ����
	{
		node *new_elem = new node(data);
		new_elem->next = new_elem;//������������� ���� prev � next
		new_elem->prev = new_elem;
		first = new_elem; //������ �� 1 ��������
	}
	else
	{
		node *new_elem = new node(data);
		new_elem->next = first; //��������� ���� next ������������ ����
		new_elem->prev = first->prev;//��������� ���� prev ������������ ����
		first->prev->next = new_elem;//��������� ���� next ��� ����, ��������������� ������������
		first->prev = new_elem;//��������� ���� prev ����, ���������� ����� ������������
	}
}
void list_2_cycle::push_start(double data){
	if (first == nullptr)//���� ������ ��� ����
	{
		node *new_elem = new node(data);//������� ����� ������� � ������������� �����
		new_elem->next = new_elem;
		new_elem->prev = new_elem;
		first = new_elem;//������������� ������ �������
	}
	else
	{
		node *new_elem = new node(data);//������� ����� ������� 
		new_elem->next = first;//������������� ����� � ������ ��������
		new_elem->prev = first->prev;
		first->prev->next = new_elem;
		first->prev = new_elem;//��������� ����� � ������
		first = new_elem;//������� ������ ������� first
	}
}
void list_2_cycle::push_to_position(int n, double data){//���������� � ������������ ������� � ������
	if (n < 0)//������������ �����
	{
		cout << "number must be non negative" << endl;
		return;
	}
	if (first == nullptr)//������ ����
		if (n != 0)
		{
			cout << "Impossible position, your list is empty" << endl;
			return;
		}
		else//��������� �� 0 �����
		{
			push_back(data);
			return;
		}
	int razm = size();//��� ������� ������
	if (n > razm)//���� ����� ������ ��� ������
	{
		cout << "Impossible position, your list has only " << razm << " elements" << endl;
		return;
	}
	node *curr = first;//��� ������������ �� ������
	for (int i = 0; i < n; i++)
		curr = curr->next;//�������� � ������� ��������
	if (n == 0) //���� ��������� � ������ ������
		push_start(data);
	else
		if (curr == first)//���� ��������� �� ��������� �������
		{
			push_back(data);
		}
		else
		{
			node *new_elem = new node(data);//������� ����� �������
			new_elem->next = curr;//���������� ��� �����(next �� ������� �������, prev �� ��������������)
			new_elem->prev = curr->prev;
			curr->prev->next = new_elem;//���������� ����� � ������
			curr->prev = new_elem;
		}
}
int list_2_cycle::del_back(double *x){//�������� �� ����� ������
	int razm = size();//������ ������
	if (first == nullptr)//������ ����
		return 0;
	else
		if (razm == 1)//����� 1 �������
		{
			*x = first->data;//��������� ��� ����
			first = nullptr;//�������� �������
			return 1;
		}
		else
		{
			node *curr = first->prev;//���������� ��������� �������
			curr->prev->next = first;//������������� ����� 
			first->prev = curr->prev;
			*x = curr->data;
			delete curr;//������� �������
			return 1;
		}
}
int list_2_cycle::del_start(double *x){//�������� �� ������
	int razm = size();//������ ������
	if (first == nullptr)//�������
		return 0;
	else
		if (razm == 1)//1 �������
		{
			*x = first->data;//���� ��� ��� ���� � ���������� � ����������
			first = nullptr;//�������� ������ �������
			return 1;
		}
		else
		{
			node *curr = first;//���������� 1 �������
			first = first->next;//�������� first ������
			curr->prev->next = first;//���������� �����
			first->prev = curr->prev;//�������� ��������� �������
			*x = curr->data;//����� ��� ���� � ���������� � ����������
			delete curr;//������� ���� �������
			return 1;
		}
}
int list_2_cycle::del_from_position(int n, double *x){//������� � ������������ �������
	int razm = size();
	if (n >= razm)//���� ��������� ������ ������
		return 0;
	if (n < 0)//������������ �����
		return 0;
	if (first->next == first)//���� ������� ����� 1
		if (n == 0)//� �� �������� ��� �������
		{
			*x = first->data;//��������� ���� ����
			first = nullptr;//�������� ������ �������
			return 1;
		}
		else
			return 0;
	if (n == 0)//���� ������� ������� � ������� 0
	{
		del_start(x);//������� �� ������
		return 1;
	}
	else
	{
		node *curr = first->next;//��� �������� �� ������
		for (int i = 1; i < n; i++)//��������� � ������� ��������
		{
			curr = curr->next;
		}
		if (curr->next == first)//���� �� ��������� � ������
		{
			del_back(x);//������� �� �����
			return 1;
		}
		else
		{
			curr->prev->next = curr->next;//�������� �����
			curr->next->prev = curr->prev;
			*x = curr->data;
			delete curr;//������� ���
			return 1;
		}
	}
}
void list_2_cycle::print_list(){//������ ������
	if (first == nullptr)//������ ����
		cout << "List is empty" << endl;
	else
	{
		node *curr = first;//���������� ������ �������
		do{
			cout << curr->data << " ";
			curr = curr->next;//�������� ������ �� ������
		} while (curr != first);//���� �� ������� � ������� ��������
		cout << endl;
	}
}
void list_2_cycle::print_reverse(){//������ ��������
	if (first == nullptr)//�������
		cout << "List is empty" << endl;
	else
	{
		node *curr = first->prev;//���������� ��������� �������
		do
		{
			cout << curr->data << " ";
			curr = curr->prev;//��������� �� ����� � ������
		} while (curr != first->prev);//���� �� ����� ����� � ����� �� ��������
		cout << endl;
	}
}
int list_2_cycle::size(){//������
	if (first == nullptr)//���� ����
		return 0;
	node *curr = first;
	int size = 0;//��� �������
	do
	{
		curr = curr->next;//��������� �� ������
		size++;//����������� ������
	} while (curr != first);//���� �� ����� ����� � ������ ������
	return size;
}
int list_2_cycle::read(int n, double *x){//������ ��� ��������
	if (n >= size() || n < 0)//���� ������������ ����� 
		return 0;
	else
	{
		node *curr = first;
		for (int i = 0; i < n; i++)//��������� � ������� ��������
			curr = curr->next;
		*x = curr->data;//���������� ��� ���� ����� ��������
		return 1;
	}
}
void list_2_cycle::clear(){//������� ������
	double a;
	while (first != nullptr)
		del_start(&a);//������� �� ������ ���� �� ������ ��
}
void list_2_cycle::write_to_file(ofstream &outp)//������ � ����
{
	node *curr = first;//���������� 1 �������
	int sizeoflst = size();//������ ������
	while(sizeoflst)//���� �� ������ �� ����� ������
	{
		outp << curr->data << " ";//����� � ����
		curr = curr->next;//��������� ������ �� ������
		sizeoflst--;
	}
}
void list_2_cycle::create_list_from(list_1_cycle &A, list_2_cycle_head &B, list_2_cycle &C){//����������� ������ ���������� ���������
	double elem;//��� ���������� �����
	while (A.del_start(&elem))//���������
		push_back(elem);	  //������ ��
	while (C.del_start(&elem))//
		push_back(elem);	  //
	while (B.del_start(&elem))//�������� �������
		push_back(elem);	  //� ��������������

	//���� ������������� �����
	bool check_repeat = false;//��� �����������, ��� �� ������ �����
	node *curr1 = first;//��� ��������������� ������� �� ������
	int counter1 = 0;//������� ������ ������� �����(����� ����� ����� ������� �������)
	int counter2;//������� ������ ������� �����(����� ����� ����� ������� �������)
	while (first != nullptr && curr1 != first->prev)//���� �� ��������� ����� ������, ���� ���� ������ �� ����� ����
	{
		double element = curr1->data;//���������� � ���������� ��� ���� 
		node *curr = curr1->next;//����������-node ��� ������� �����
		check_repeat = false;//������� ������� ���������� ����� 0
		counter2 = counter1 + 1;//����� ������ ����� �� 2 ����� ������� �� ���������� ��������
		while (curr != first)//���� �� ����� �� ������ ������
		{
			if (curr->data == element)//���� ���.���� ���������� �������� ������ ����� ����������� �������� �� �������� �����
			{
				check_repeat = true;//������� ����� 1
				curr = curr->prev;//���������� �� 1 �����
				del_from_position(counter2 ,&elem);//������� ���� �������
				curr = curr->next;//��������� � ���������� ��������
			}
			else
			{
				counter2++;//��������� +1 � ��������
				curr = curr->next;//��������� �� ������
			}
		}
		if (check_repeat)//���� ��� ������
		{
			curr1 = curr1->prev;
			del_from_position(counter1, &elem);//�� ������� ���� �������
			curr1 = curr1->next;
		}
		else
		{
			counter1++;//��������� +1 � ��������
			curr1 = curr1->next;//��������� �� ������
		}
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	ifstream inp("input.dat");//��� �������� ����� ��� ������
	ofstream outp("output.dat");//��� �������� ����� ��� ������

	if (!inp.is_open())
	{
		cout << "File input.dat wasn't open" << endl;
		ofstream n("input.dat");
		n.close();
	}
	else
	{
		list_1_cycle list1;//������ ������(�����������
		list_2_cycle list2; //������ ������(����������)
		list_2_cycle_head list3; //������ ������(���������� � �������)
		double x; //��������� ���������� ��� ���������� �� �����
		char c;//��� ���������� ����� ������
		if (inp.get(c))//������� ���� ������
		{
			inp.seekg(0, ios_base::beg); //����� � ������ �����
			if (c != '\n')//������ ������ �� ����
			{
				while (inp >> x)//������ �����
				{
					list1.push_back(x);//���������� � ������
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
					list2.push_back(x);//���������� � ������
					inp.get(c); //��������� 1 ������
					if (c == '\n')//���� ����� ������, �� ��������� ����
						break;
				}
			}
			cout << "Second list was successfully read" << endl;

			inp.seekg(-1, ios_base::cur); //������������ ����� � �����
			while (inp >> x)//������ �����
			{
				list3.push_back(x);//���������� � ������
			}
			cout << "Third list was successfully read\n---------------------------------------------" << endl;
			if (!inp.eof())
				cout << "File is broken" << endl;
			else
			{
				cout << "First list (single-linked list):" << endl;
				list1.print_list(); //������ ������ 1
				cout << "Second list (double-linked list):" << endl;
				list2.print_list();//������ ������ 2
				cout << "Third list(double-linked list with head):" << endl;
				list3.print_list();//������ ������ 3

				list_2_cycle result; //��� ����������
				
				cout << "Result list is: " << endl;
				result.create_list_from(list1, list3, list2);//��������� �������������� ������
				result.print_list();//������ �� �����
				result.write_to_file(outp);//������ � ����
			}
		}
		else
			cout << "File is empty!" << endl;
	}
	inp.close();
	outp.close();
	return 0;
}