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

	void push_back(int data);//Запись в конец
	void push_front(int data);//Добавить в начало списка
	int del_start(); //Удаление первого эл-та списка
	int del_back(); //удаление последнего эл-та списка
	void print_list();//Печать списка
	void clear(); //очистка и удаление списка
	void insert(int i, int data);//Добавить элемент на i-ое место
	void remove(int i);//удаление
	int read(int i, int* x); //чтение i-го элемента
	int get_start(int *x);
	int find_elem(int x);


private:
	class node{//каждый отдельный элемент списка
	public:
		node *next;//указатель на следующий элемент
		int data;//информационное поле элемента списка
		node(int data = 0, node *next = nullptr){//Конструктор с параметрами
			this->data = data;
			this->next = next;
		}
	};

	node *head;//Указатель в списки на голову
};

void list::push_back(int data)/*Добавить в конец списка*/{
	if (head == nullptr)//Если ни одного числа в списке
		head = new node(data);//Создаем голову и записываем в нее data
	else
	{
		node *curr = this->head;//Для перемещения по списку
		while (curr->next != nullptr)//Перемещаемся до конца списка
			curr = curr->next;
		curr->next = new node(data);//Добавляем новый элемент списка
	}
}
void list::push_front(int data)/*добавить в начало*/{
	node *old_head = head;//создаем переменную где храним старую голову
	node *new_head = new node;//Создаем новую голову
	new_head->data = data;//присваиваем ей инф поле
	new_head->next = old_head;//указываем next как старую голову
	head = new_head;//заменяем
}
int list::del_start()/*Извлечь из головы*/{
	if (head == nullptr)//если список пуст
		return 0;
	else
	{
		node *temp = head;//для хранения старой головы
		head = head->next;
		delete temp;//удаляем старую голову
		return 1;
	}
}
int list::del_back()/*Извлечение из конца списка*/{
	if (head == nullptr)//Если голова пуста
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
			node *curr = head;//Для перемещения по списку
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
void list::print_list()/*Печать списка*/{
	if (head == nullptr)//пустота списка
		cout << "List is empty" << endl;
	else
	{
		node *curr = head;//для передвижения внутри списка
		while (curr != nullptr)//пока очередной элемент списка не будет нулевым
		{
 			cout << curr->data << " "; //выводим инф.поле
			curr = curr->next;//сдвигаемся по списку
		}
		cout << endl;
	}
}
void list::insert(int i, int data){
	if (i < 0)//если был введён отрицательный номер элемента списка
		cout << "An invalid item number." << endl;
	else
	{
		if (head == nullptr)//Если вдруг голова пустая
			push_front(data);
		else
		{
			node *prev = head; //Для передвижения внутри списка
			for (int count = 0; count < i - 1; count++)//Передвигаемся по всему списку
			{
				if (prev->next == nullptr)//Если достигли конца списка ещё до достижения необходимого номера
				{
					cout << "An invalid item number. The item was written to the end of the list" << endl;
					break;
				}
				prev = prev->next;//К след.элементу
			}
			if (i == 0)
			{
				push_front(data);//Аналогично добавлению в начало списка
			}
			else
			{
				node *new_node = new node; //создаем новый элемент списка
				new_node->data = data; //записываем инф поле в данный элемент
				new_node->next = prev->next; //Помещаем данный элемент между i - 1 и i-м
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
		del_start();//Удаляем первый элемент списка, пока он не станет нулевым
}
int list::read(int i, int *x)/*Прочитать i-й элемент списка*/{
	if (head != nullptr)
	{
		node *curr = head; //для движения по списку
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
			*x = curr->data; //Возвращаем значения по номеру i
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
int list::find_elem(int x)/*Поиск первого вхождения элемента*/{
	int count = 0; //считать какой элемент по счёту совпал
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
	/*ofstream out("output.dat");//для записи результата
	ifstream in("input.dat"); //для чтения исходного списка
	if (!(in.is_open())) //Если файл не открыт
	{
		cout << "File wasn't open" << endl;
		ofstream tmp("input.dat");//создаем такой же файл
		tmp.close();
	}
	else
	{
		cout << "File input.dat was successfully opened" << endl;
		int x; //очередное число
		list *start_lst = new list();//создаём список
		list *list_chet = new list();//Список четных элементов
		list *dividing_by3 = new list();//Список делящийся на 3
		
		//заполняем исходный список
		while (in >> x)
		{
			start_lst->push_back(x);
		}
		if (!in.eof())
			cout << "File is broken. Error!" << endl;
		else
		{
			cout << "Starts list:" << endl;
			start_lst->print_list();//Печать исходного списка

			//Проходим по изначальному списку и формируем подсписки
			int i = 0; //счётчик для прохода по списку
			while (start_lst->read(i, &x))//пока мы можем считывать i-й элемент списка
			{
				bool check = true;//для проверки, вошло ли число в подсписок или нет
				if (x % 2 == 0)
				{
					list_chet->push_back(x);//заносим в подсписок
					check = false;
				}
				if (x % 3 == 0)
				{
					dividing_by3->push_back(x);//заносим в подсписок
					check = false;
				}
				if (!check)
					start_lst->remove(i);//удаляем элемент, если он вошёл хотя бы в один подсписок
				else
					i++;//В другом случае переходим на следующий элемент списка
			}
			
			//Печать на экран и запись результирующих списков в файл
			cout << "\nResult of programme is: " << endl;
			cout << "List of numbers that divided by 3: " << endl;
			dividing_by3->print_list();//Печать списка элементов кратных трём
			while (dividing_by3->get_start(&x))//запись в файл списка /3
				out << x << " ";
			out << "\n";
			cout << "List of even numbers: " << endl;
			list_chet->print_list();//печать списка четных элементов
			while (list_chet->get_start(&x))//запись в файл списка четных чисел
				out << x << " ";
			out << "\n";
			cout << "List of other numbers: " << endl;
			start_lst->print_list();//печать элементов оставшихся в списке
			while (start_lst->get_start(&x))//запись в файл остальных чисел
				out << x << " ";

			delete start_lst;//Освобождаем память
			delete list_chet;//освобождаем память
			delete dividing_by3;//освобождаем память
		}
	}
	in.close();//закрываем файлы
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

