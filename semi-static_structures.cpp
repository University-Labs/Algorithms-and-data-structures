#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
#define N 1000

using namespace std;

class stack{
public:
	stack(){ //�����������
		uv = -1;
	}
	void print_stack();//������
	int push(double x);//��������
	int pop(double *x);//�������
	int check();//�������� �������
	void clear();//������� �����
private:
	int uv;//��������� �� �������
	double st[N];//������, � ������� ���������� �������� �����
};

void stack::print_stack(){
	cout << "Stack is: ";
	if (uv == -1)
		cout << "empty" << endl;
	else
	{
		for (int i = uv; i >= 0; i--)
			cout << st[i] << " ";
		cout << endl;
	}
}
int stack::push(double x){
	if (uv >= N - 1) //���� ���������� ����
	{
		return 0;
	}
	else
		st[++uv] = x;//������ ����� � ����
	return 1;
}
int stack::pop(double *x){
	if (uv == -1)//���� ���� ����
	{
		return 0;
	}
	else
		*x = st[uv--];//��������� ������� � x
	return 1;
}
int stack::check(){//�������� ������� �����
	if (uv == -1)
		return 0;
	else
		return 1;
}
void stack::clear(){//������� �����(����������� ���������)
	uv = -1;
}


class queue{//�������
public:
	queue(){//�������� �������
		ul = ur = -1;
	}
	int add_to_q(double x);//���������� � �������(� ������ �����)
	int delete_from_q(double *x);//�������� �� �������(����� �����)
	void print_queue();//������ �������
	int check();//�������� ������� �������
	void clear();//������� �������
private:
	int ul, ur;//��������� �� ������� �������
	double q[N];//������, � ������� ���������� �������� �������
};

int queue::add_to_q(double x){
	if ((ul == 0 && ur == N - 1) || (ul - 1 == ur))//���� ������� �����������
	{
		return 0;
	}
	else
	{
		if (ur == N - 1)
			ur = 0;//����������� ��������� � ������, ���� �� ��� � �����
		else
			ur++;

		if (ul == -1)//���� 0 ���������
		{
			ul = ur = N/2;
		}

		q[ur] = x;
	}
	return 1;
}
int queue::delete_from_q(double *x){
	if (ul == -1 && ur == -1)//���� ������� ��� �����
	{
		return 0;
	}
	else
	{
		*x = q[ul];//����������� �������� ��������� ������� �������
		if (ul == ur) //���� ����� 1 �������
			ul = ur = -1;
		else
		{
			if (ul == N - 1)//���� ��������� �� ������ ������� ��������� � ����� �������
				ul = 0;
			else
				ul++;
		}
		return 1;
	}
}
void queue::print_queue(){
	cout << "Queue is: ";
	if (ul == -1 && ur == -1)
		cout << "empty!" << endl;
	else
	{
		if (ul <= ur)
			for (int i = ul; i <= ur; i++)
				cout << q[i] << " ";
		else
		{
			for (int i = 0; i <= ur; i++)
				cout << q[i] << " ";
			for (int i = ul; i < N; i++)
				cout << q[i] << " ";
		}
		cout << endl;
	}
}
int queue::check(){
	if ((ul == -1) && (ur == -1))
		return 0;
	else
		return 1;
}
void queue::clear(){
	ul = ur = -1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	ifstream inp("input.dat"); // // �������� ������� ������ ifstream � �������� �����
	ofstream outp("output.dat");//// �������� ������� ������ ofstream � �������� �����
	if (!(inp.is_open()))//������ �� ����
	{
		cout << "File input.dat not found\n" << endl;
		ofstream new_f("input.dat"); //�������� �����
		new_f.close();
	}
	else
	{
		cout << "File input.dat was successfully open\n" << endl;

		stack st1, st2; //�������� ����������� ������
		queue que; //�������� ����������� �������
		stack result; //�������� ��������������� �����

		//���� ���������� ������ �� �����:
		double x; //��������� �����
		char is_eos;//��� �������� ����� ������
		while (inp >> x)//���� ������� ��� ����������
		{
			if (x == 1001)
				break;
			if (!st1.push(x))//��������� ���� 1
			{
				cout << "Stack 1 is overflow" << endl;
				system("pause");
				return 1;
			}
			inp.get(is_eos);//��������� 1 ������
			if (is_eos == '\n')
				break;
			if (is_eos != ' ')//����� ����� � �����(����� �����)
			{
				cout << "File is broken" << endl;
				system("pause");
				return 1;
			}
		}
		while (inp >> x)//���� ������� ��� ����������
		{	
			if (x == 1001)
				break;
			if (!st2.push(x))//��������� ���� 2
			{
				cout << "Stack 2 is overflow" << endl;
				system("pause");
				return 1;
			}
			inp.get(is_eos); //��������� 1 ������
			if (is_eos == '\n')
				break;
			if (is_eos != ' ')//����� ����� � �����(����� �����)
			{
				cout << "File is broken" << endl;
				system("pause");
				return 1;
			}
		}
		while (inp >> x)//���� ������� ��� ����������
		{
			if (x == 1001)
				break;
			if (!que.add_to_q(x))
			{
				cout << "Queue is overflow" << endl;
				system("pause");
				return 1;
			}
			if(inp.get(is_eos)) //��������� 1 ������
				if (is_eos != ' ')//����� ����� � �����(����� �����)
				{
					cout << "File is broken" << endl;
					system("pause");
					return 1;
				}
		}

		cout << "This is the first stack print" << endl;
		st1.print_stack();
		cout << "----------------------------------------------------------" << endl;
		cout << "This is the second stack print" << endl;
		st2.print_stack();
		cout << "----------------------------------------------------------" << endl;
		cout << "This is the queue" << endl;
		que.print_queue();
		cout << "----------------------------------------------------------" << endl;

		//���� ������ � �������:
		stack temp; //�������� ���������� ����� ����� ����
		double one, two; //��� ���������� ���� ����� �� �����
		bool exit_from_cycle = false; //�� ������ ���� � ������� ����� �������� > ���� ����� � �����
		bool over = false; //��� ������������ �����
		while (que.check())//���� �� ������ �� ����� �������
		{
			que.delete_from_q(&x);//�������� ��������� ������ �� ������� � x
			for (int j = 0; j <= x; j++)
			{
				if (!(st1.pop(&one)) || !(st2.pop(&two)))//���� �� ������� �������
					exit_from_cycle = true;
				else
				{
					if (!temp.push(one) || !temp.push(two))//������� �� ��������� ���� ��������
						over = true;
				}
				if (exit_from_cycle)
					break;//������� �� �����, ���� ��������� ������
				if (over)
				{
					cout << "Temp Stack overflow" << endl;
					break;
				}
			}
			if (exit_from_cycle)
				break;
			if (over)
				break;
			cout << "Push to stack: " << one << " + " << two << endl;
			result.push(one + two); //������� � �������������� ���� �����
			for (int j = 0; j <= x; j++)//���������� �������� �� ���������� ����� � ��������
			{
				temp.pop(&two);
				st2.push(two);
				temp.pop(&one);
				st1.push(one);
			}
		}
		if (exit_from_cycle)
			cout << "Error of creation a new stack!! You can't add elements which are not included in the input stacks" << endl;
		else
			if (!over)
			{
				cout << "----------------------------------------------------------" << endl;
				cout << "Result stack " << endl;
				result.print_stack();//�������� �������������� ����
				while (result.check())//���� ���� �� ����, ���������� ��� ����� � ����
				{
					result.pop(&x);
					outp << x << " ";
				}
			}
		}

	inp.close();//�������� ������
	outp.close();
	system("pause");
	return 0;
}

