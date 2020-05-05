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

	void push_back(double data);//Запись в конец
	void push_front(double data);
	int del_start(); //Удаление первого эл-та списка
	int del_back(); //удаление последнего эл-та списка
	void print_list();//Печать списка
	void clear(); //очистка и удаление списка
	void insert(double data, int index);//Добавить элемент после i-го
	void remove(int i);//удаление по номеру
	int find_by_num(int num, double *x);
	int find_by_value(double x, int *num);
	void add_before_i(int i, list2* A);//добавить перед i-м номером
	void write_to_file(ofstream &out);//записать список в файл
private:

	class node{
	public:
		node *next;//следующий элемент
		node *prev; //предыдущий элемент
		double data; //информационное поле
		node(double data = 0){
			this->data = data;
			this->next = nullptr;
			this->prev = nullptr;
		}
	};
	node *first, *last; //первый элемент
};

void list2::add_before_i(int i, list2* A)
{
	if (first == nullptr)//Если изначальный список пуст
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
				node *curr = A->first;//укажем на вершину списка, который нужно скопировать
				while (curr != nullptr)//пока не дойдём до конца переданного списка
				{
					insert(curr->data, i);//добавляем на место i
					curr = curr->next;//движемся дальше по переданному списку
					i++;//увеличиваем i
				}
			}
			else
				cout << "You can't add list after " << i << " element" << endl;
		}
}
int list2::find_by_value(double x, int *num){
	if (first == nullptr)//если в списке нет ни 1 элемента
		return 0;
	else
	{
		node *curr = first; //для перемещения по списку
		bool find = false;
		int count = 0;//счетчик количества проходов в списке
		while (!find && curr != nullptr)//пока не нашли и не конец списка
		{
			if (curr->data == x)//если нашли
				find = true;
			else
			{
				curr = curr->next;//двигаемся по списку далее
				count++;
			}
		}
		if (!find)
			return 0;
		else
		{
			*num = count;//возвращаем этот индекс
			return 1;
		}
	}
}
int list2::find_by_num(int num, double *x)//поиск по номеру
{
	if (num < 0)
		return 0;
	else
	{
		node *curr = first;
		int count = 0; //счетчик
		while (curr != nullptr && count < num)
		{
			curr = curr->next;
			count++;
		}
		if (curr != nullptr)//если такой элемент есть
		{
			*x = curr->data;//записываам его инф поле в переменную
			return 1;
		}
		else
			return 0;
	}
}
void list2::push_back(double data){//добавление  в конец
	if (last == nullptr)//Если список пуст
		first = last = new node(data);
	else
	{
		node *curr = this->last;//для передвижения по списку
		curr->next = new node(data);//создаем новый элемент
		curr->next->prev = curr;//поле prev у нового элемента ставим на предыдущий
		last = curr->next;
	}
}
void list2::push_front(double data){//добавление в начало
	if (first == nullptr)//если список пуст
		first = last = new node(data);
	else
	{
		node *new_first = new node(data);//создаем новый  элемент списка
		new_first->next = first;//устанавливаем связь между новым элементом и старым first
		first->prev = new_first;
		first = new_first;//новый first это новый введеный элемент
	}
}
int list2::del_start(){//удаление из начала
	if (first == nullptr)//Если в списке ни одного элемента
		return 0;
	else
	{
		if (first->next == nullptr)//Если элемент единственный
		{
			delete first;//удаляем первый элемент
			first = nullptr;//устанавливаем голову в nullptr
			last = nullptr;
			return 1;
		}
		else
		{
			node *old_head = first;//Запоминаем старый первый элемент
			first = first->next;//заменяем первый элемент
			first->prev == nullptr;
			delete old_head;//удаляем его
			return 1;
		}
	}
}
int list2::del_back(){//удаление из конца списка
	if (last == nullptr)//если список пуст
		return 0;
	else
	{
		if (last->prev == nullptr)//если один элемент в списке
		{
			first = nullptr;
			last = nullptr;
			return 1;
		}
		else
		{
			node *curr = last;//для передвижения по списку
			curr->prev->next = nullptr;
			last = curr->prev;
			delete curr;//удаляем этот элемент
			return 1;
		}
	}
}
void list2::print_list(){//печать списка
	if (first == nullptr)
		cout << "List is empty" << endl;
	else
	{
		node *curr = first;//для передвижения внутри спискf
		while (curr != nullptr)//пока очередной элемент списка не будет нулевым
		{
			cout << curr->data << " "; //выводим инф.поле
			curr = curr->next;//сдвигаемся по списку
		}
		cout << endl;
	}
}
void list2::insert(double data, int index){//вставка элемента в заданное место
	if (index < 0)//если был введён отрицательный номер элемента списка
		cout << "An invalid item number." << endl;
	else
	{
		if (first == nullptr || index == 0)//Если вдруг первый элемент единственный
			push_front(data);//добавление в начало
		else
		{
			node *prev = first; //Для передвижения внутри списка
			int count = 0; //счётчик
			while (prev->next != nullptr)
			{
				if (count == index - 1)//Если достигли необходимый номер
				{
					node *new_node = new node(data); //создаем новый элемент списка
					new_node->next = prev->next; //Помещаем данный элемент между i - 1 и i-м
					new_node->prev = prev;
					prev->next = new_node;
					new_node->next->prev = new_node;
					break;
				}
				count++;
				prev = prev->next;//К след.элементу
			}
			if ((count <= index - 1) && prev->next == nullptr) //Если не дошли до этого элмента
			{
				push_back(data);//записываем в конец
			}
		}
	}
}
void list2::remove(int i){//удаление элемента с произвольным номером
	if (first == nullptr)//нет ни одного элемента
	{
		cout << "List is empty already" << endl;
		return;
	}
	else
		if (i < 0)//ввели отрцитальный номер
		{
			cout << "It's impossible to delete a negative number" << endl;
			return;
		}
		else
			if (i == 0)//если удаляем нулевой элемент
			{
				del_start(); //удаление из начала списка
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
void list2::clear(){//очистка всего списка
	while (first != nullptr)
		del_start();//Удаляем первый элемент списка, пока он не станет нулевым
}
void list2::write_to_file(ofstream &out)//запись в файл
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
	/*ifstream inp("input.dat");//для открытия файла для чтения
	ofstream outp("output.dat");//для открытия файла для записи

	if (!inp.is_open())
	{
		cout << "File input.dat wasn't open" << endl;
		ofstream n("input.dat");
		n.close();
	}
	else
	{
		list2 first_list;//первый список(в который добавляем)
		list2 second_list; //второй список(который добавляем)
		double x; //очередная переменная при считывании из файла
		char c;//для нахождения конца строки
		if (inp.get(c))//считаем один символ
		{
			inp.seekg(0, ios_base::beg); //Стать в начало файла
			if (c != '\n')//первый список не пуст
			{
				while (inp >> x)//читаем число
				{
					first_list.push_back(x);//записываем в список
					inp.get(c); //считываем 1 символ
					if (c == '\n')//выходим при символе конца строки
						break;
				}
			}
			else
				inp.get(c);//возвращаем указатель туда же

			cout << "First list was successfuly read" << endl;
			inp.get(c);//читаем \n или первую цифру

			if (c != '\n')//если второй список не пуст
			{
				inp.seekg(-1, ios_base::cur); //перепрыгнуть назад в файле
				while (inp >> x)//читаем число
				{
					second_list.push_back(x);//записываем в список
					inp.get(c); //считываем 1 символ
					if (c == '\n')//если конец строки, то прерываем цикл
						break;
				}
			}
			cout << "Second list was successfully read" << endl;

			int number = -1; //номер начиная с которого вставляем новый список
			if (inp >> number)//если удалось считать число
			{
				cout << "Number was successfully read" << endl;
				if (number >= 0)//вдруг отрицательное число
					if (!inp.eof())//еще есть информация в файле
					{
						cout << "Error of reading data from file." << endl;
					}
					else
					{
						cout << "\nInformation:" << endl;
						cout << "First list is: ";
						first_list.print_list();//печать инфы о первом списке
						cout << "Second list is: ";
						second_list.print_list();//печать инфы о втором списке
						cout << "Add second list before " << number << " elem of first list " << endl;//печать инфы о i
						cout << "........." << endl;
						cout << "Result list: ";
						first_list.add_before_i(number, &second_list);//выполняем операцию добавления к первому списку элементов второго
						first_list.print_list();//выводим результат на экран
						first_list.write_to_file(outp);//записываем его в файл
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
