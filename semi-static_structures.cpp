#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
#define N 1000

using namespace std;

class stack{
public:
	stack(){ //конструктор
		uv = -1;
	}
	void print_stack();//печать
	int push(double x);//добавить
	int pop(double *x);//извлечь
	int check();//проверка пустоты
	void clear();//очистка стека
private:
	int uv;//указатель на вершину
	double st[N];//массив, в котором содержатся элементы стека
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
	if (uv >= N - 1) //Если переполнен стек
	{
		return 0;
	}
	else
		st[++uv] = x;//запись числа в стек
	return 1;
}
int stack::pop(double *x){
	if (uv == -1)//Если стек пуст
	{
		return 0;
	}
	else
		*x = st[uv--];//извлекаем элемент в x
	return 1;
}
int stack::check(){//Проверка пустоты стека
	if (uv == -1)
		return 0;
	else
		return 1;
}
void stack::clear(){//Очистка стека(перемещение указателя)
	uv = -1;
}


class queue{//очередь
public:
	queue(){//создание очереди
		ul = ur = -1;
	}
	int add_to_q(double x);//добавление в очередь(в правый конец)
	int delete_from_q(double *x);//удаление из очереди(левый конец)
	void print_queue();//печать очереди
	int check();//проверка пустоты очереди
	void clear();//очистка очереди
private:
	int ul, ur;//указатели на стороны очереди
	double q[N];//массив, в котором содержатся элементы очереди
};

int queue::add_to_q(double x){
	if ((ul == 0 && ur == N - 1) || (ul - 1 == ur))//Если очередь переполнена
	{
		return 0;
	}
	else
	{
		if (ur == N - 1)
			ur = 0;//Переместить указатель в начало, если он уже в конце
		else
			ur++;

		if (ul == -1)//Если 0 элементов
		{
			ul = ur = N/2;
		}

		q[ur] = x;
	}
	return 1;
}
int queue::delete_from_q(double *x){
	if (ul == -1 && ur == -1)//Если очередь уже пуста
	{
		return 0;
	}
	else
	{
		*x = q[ul];//Присваиваем значению указателя элемент очереди
		if (ul == ur) //Если всего 1 элемент
			ul = ur = -1;
		else
		{
			if (ul == N - 1)//Если указатель на начало очереди находился в конце массива
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
	ifstream inp("input.dat"); // // создание объекта класса ifstream и открытие файла
	ofstream outp("output.dat");//// создание объекта класса ofstream и открытие файла
	if (!(inp.is_open()))//Открыт ли файл
	{
		cout << "File input.dat not found\n" << endl;
		ofstream new_f("input.dat"); //создание файла
		new_f.close();
	}
	else
	{
		cout << "File input.dat was successfully open\n" << endl;

		stack st1, st2; //создание изначальных стеков
		queue que; //создание изначальной очереди
		stack result; //создание результирующего стека

		//БЛОК СЧИТЫВАНИЯ ДАННЫХ ИЗ ФАЙЛА:
		double x; //очередное число
		char is_eos;//для проверки конца строки
		while (inp >> x)//Пока успешно идёт считывание
		{
			if (x == 1001)
				break;
			if (!st1.push(x))//заполняем стек 1
			{
				cout << "Stack 1 is overflow" << endl;
				system("pause");
				return 1;
			}
			inp.get(is_eos);//считываем 1 символ
			if (is_eos == '\n')
				break;
			if (is_eos != ' ')//вдруг буквы в файле(после чисел)
			{
				cout << "File is broken" << endl;
				system("pause");
				return 1;
			}
		}
		while (inp >> x)//Пока успешно идёт считывание
		{	
			if (x == 1001)
				break;
			if (!st2.push(x))//заполняем стек 2
			{
				cout << "Stack 2 is overflow" << endl;
				system("pause");
				return 1;
			}
			inp.get(is_eos); //считываем 1 символ
			if (is_eos == '\n')
				break;
			if (is_eos != ' ')//вдруг буквы в файле(после числа)
			{
				cout << "File is broken" << endl;
				system("pause");
				return 1;
			}
		}
		while (inp >> x)//Пока успешно идёт считывание
		{
			if (x == 1001)
				break;
			if (!que.add_to_q(x))
			{
				cout << "Queue is overflow" << endl;
				system("pause");
				return 1;
			}
			if(inp.get(is_eos)) //считываем 1 символ
				if (is_eos != ' ')//вдруг буквы в файле(после числа)
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

		//БЛОК РАБОТЫ С ДАННЫМИ:
		stack temp; //временно перемещаем числа стека сюда
		double one, two; //Для сохранения сюда чисел из стека
		bool exit_from_cycle = false; //на случай если в очереди номер элемента > макс номер в стеке
		bool over = false; //для переполнения стека
		while (que.check())//пока не дойдем до конца очереди
		{
			que.delete_from_q(&x);//помещаем очередной элмент из очереди в x
			for (int j = 0; j <= x; j++)
			{
				if (!(st1.pop(&one)) || !(st2.pop(&two)))//Если не удалось считать
					exit_from_cycle = true;
				else
				{
					if (!temp.push(one) || !temp.push(two))//заносим во временный стек значения
						over = true;
				}
				if (exit_from_cycle)
					break;//выходим из цикла, если произошла ошибка
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
			result.push(one + two); //заносим в результирующий стек сумму
			for (int j = 0; j <= x; j++)//возвращаем значения из временного стека в исходные
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
				result.print_stack();//печатаем результирующий стек
				while (result.check())//пока стек не пуст, записываем его числа в файл
				{
					result.pop(&x);
					outp << x << " ";
				}
			}
		}

	inp.close();//закрытие файлов
	outp.close();
	system("pause");
	return 0;
}

