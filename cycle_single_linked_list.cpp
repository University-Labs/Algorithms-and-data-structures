#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

class list_1_cycle{//циклический 1 связный
public:
	list_1_cycle() //конструктор
	{
		first = nullptr;
		last = nullptr;
	}
	~list_1_cycle(){
		clear();
	}
	void push_back(double data); //добавление в конец
	void push_start(double data); //добавление в начало
	int del_back(double *x);//удаление из конца
	int del_start(double *x); //удаление из начала
	int del_from_position(int n, double *x);//удаление из позиции
	void push_to_position(int n, double data); //добавление в определенную позицию
	void print_list();//печать
	int size();//определение размера
	int read(int n, double *x);//чтение без удаления
	void  clear(); //очистка списка
private:
	struct node{
	public:
		node *next;//указатель на следующий
		double data; //инф поле
		node(double data = 0){
			this->data = data;
			this->next = nullptr;
		}
	};
	node *first, *last;//последний и первый
};

class list_2_cycle_head{//двусвязный циклический список с головой
public:
	list_2_cycle_head(){ //конструтор по умолчанию
		head->data = 0;//количество элементов
		head->next = nullptr;//ссылка на первый
		head->prev = nullptr;//ссылка на последний
	}
	~list_2_cycle_head(){
		clear();
	}
	void push_back(double data); //добавление в конец
	void push_start(double data); //добавление в начало
	void push_to_position(int n, double data);//добавление в определенную позицию в списке
	int del_back(double *x);//удаление из конца
	int del_start(double *x);//удаление из начала
	int del_from_position(int n, double *x); //удаление с определенной позиции
	void print_list();//печать списка
	int read(int n, double *x); //чтение без удаления
	int size(); //размер списка
	void clear(); //очистка списка
private:
	struct node{
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
	node *head = new node; //голова
};

class list_2_cycle{//циклический 2 связный
public:
	list_2_cycle(){ //конструтор по умолчанию
		first = nullptr;
	}
	~list_2_cycle(){
		clear();
	}
	void push_back(double data); //добавление в конец
	void push_start(double data); //добавление в начало
	void push_to_position(int n, double data);//добавление в определенную позицию в списке
	int del_back(double *x);//удаление из конца
	int del_start(double *x);//удаление из начала
	int del_from_position(int n, double *x); //удаление с определенной позиции
	void print_list();//печать списка
	void print_reverse();//печать наоборот
	int size();//размер списка
	void create_list_from(list_1_cycle &A, list_2_cycle_head &B, list_2_cycle &C);//формирование нового списка
	int read(int n, double *x);//чтение без удаления
	void clear(); //очистка списка
	void write_to_file(ofstream &outp);//запись в файл
	int clear_memory();//чистим память
private:
	struct node{
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
	node *first; //первый элемент
};


void list_2_cycle_head::push_back(double data){//добавление в конец списка
	if (head->data == 0)
	{
		node *new_elem = new node(data);
		new_elem->next = new_elem;//устанавливаем поля prev и next
		new_elem->prev = new_elem;
		head->next = new_elem; //список из 1 элемента
		head->prev = new_elem;
		head->data = 1; //добавляем к размеру списка
	}
	else
	{
		node *new_elem = new node(data);
		new_elem->next = head->next; //установка поля next добавляемого узла
		new_elem->prev = head->prev;//установка поля prev добавляемого узла
		head->prev->next = new_elem;//установка поля next для последнего узла
		head->next->prev = new_elem;//установка поля prev для первого узла
		head->prev = new_elem;//Установка нового последнего элемента
		head->data++; //добавляем к размеру списка +1
	}
}
void list_2_cycle_head::push_start(double data){//добавление в начало списка
	if (head->data == 0)//если список был пуст
	{
		node *new_elem = new node(data);//создаем новый элемент и устанавливаем связи
		new_elem->next = new_elem;
		new_elem->prev = new_elem;
		head->next = head->prev = new_elem;//устанавливаем первый элемент и последний
		head->data = 1; //размер списка устанавливаем в 1
	}
	else
	{
		node *new_elem = new node(data);//создаем новый элемент 
		new_elem->next = head->next;//устанавливаем связи у нового элемента
		new_elem->prev = head->prev;
		head->prev->next = new_elem;//выставляем поле next у последнего элемента
		head->next->prev = new_elem;//выставляем в поле prev у первого элемента
		head->next = new_elem;//новый первый элемент - новый
		head->data++;//увеличиваем количество
	}
}
void list_2_cycle_head::print_list(){//печать списка
	if (head->next == nullptr)//пустота
		cout << "List is empty" << endl;
	else
	{
		node *curr = head->next;//в curr записываем 1 элемент списка
		int size = head->data;//размер списка
		for (int i = 0; i < size; i++)//двигаемся по списку
		{
			cout << curr->data << " ";//печатаем текущий
			curr = curr->next;//двигаемся к следующему
		}
		cout << endl;
	}
}
void list_2_cycle_head::push_to_position(int n, double data){//добавление в определенную позицию в списке
	if (n < 0)//некорректный номер
	{
		cout << "number must be non negative" << endl;
		return;
	}
	if (head->data == 0)//список пуст
		if (n != 0)
		{
			cout << "Impossible position, your list is empty" << endl;
			return;
		}
		else//добавляем на 0 место
		{
			push_back(data);
			return;
		}
	if (n > head->data)//если номер больше чем размер
	{
		cout << "Impossible position, your list has only " << (int)head->data << " elements" << endl;
		return;
	}
	node *curr = head->next;//для передвижения по списку
	for (int i = 0; i < n; i++)
		curr = curr->next;//движемся к нужному элементу
	if (n == 0) //если добавляем в начало списка
		push_start(data);
	else
		if (curr == head->next)//если добавляем на последнюю позицию
		{
			push_back(data);
		}
		else
		{
			node *new_elem = new node(data);//создаем новый элемент
			new_elem->next = curr;//поле next указываем на текущий элемент
			new_elem->prev = curr->prev;//поле prev на предыдущий
			curr->prev->next = new_elem;//у предыдущего уэлемента в поле next указываем новый
			curr->prev = new_elem;//у следующего элемента в поле prev указываем новый
			head->data++;//увеличиваем количество
		}
}
int list_2_cycle_head::del_back(double *x){//удаление из конца списка
	if (head->data == 0)//если пустой список
		return 0;
	else
		if (head->data == 1)//список из 1 элемента
		{
			*x = head->next->data;//запоминаем инф поле из  1 элемента
			head->data = 0;
			head->next = head->prev = nullptr;//зануляем первый и последний элементы
			return 1;
		}
		else
		{
			node *curr = head->prev;//запоминаем последний элемент
			curr->prev->next = head->next;//устанавливаем связи 
			head->next->prev = curr->prev;
			head->prev = curr->prev;//устанавливаем новый последний элемент списка
			*x = curr->data;//запоминаем инфо поле в переменную
			head->data--;//уменьшаем количество элементов
			delete curr;//удаляем элемент
			return 1;
		}
}
int list_2_cycle_head::del_start(double *x){//удаление из начала
	if (head->data == 0)//если ни одного элемента
		return 0;
	else
		if (head->data == 1)//если один элемент
		{
			*x = head->next->data;//запоминаем инф поле
			head->next = head->prev = nullptr;//зануляем голову
			head->data = 0;//элементов в списке 0
			return 1;
		}
		else
		{
			node *curr = head->next;//запоминаем в curr первый элемент
			curr->prev->next = curr->next;//выставляем связи
			curr->next->prev = curr->prev;
			head->data--;//уменьшаем счётчик элементов
			head->next = curr->next;//устанавливаем новый первый элемент
			*x = curr->data;//сохраняем инф поле в переменной
			delete curr;//удаляем текущий элемент
			return 1;
		}
}
int list_2_cycle_head::del_from_position(int n, double *x){//удаляем с определенной позиции
	if (n >= head->data)//если превысили размер списка
		return 0;
	if (n < 0)//некорректный номер
		return 0;
	if (head->data == 1)//если элемент всего 1
		if (n == 0)//и мы пытаемся его удалить
		{
			*x = head->next->data;//сохраняем поле дата
			head->next = head->prev = nullptr;//зануляем первый элемент
			head->data = 0;
			return 1;
		}
		else
			return 0;
	if (n == 0)//если удаляем элемент с номером 0
	{
		del_start(x);//удаляем из начала
		return 1;
	}
	else
	{
		node *curr = head->next->next;//для движения по списку
		for (int i = 1; i < n; i++)//двигаемся к нужному элементу
		{
			curr = curr->next;
		}
		if (curr->next == head->next)//если он последний в списке
		{
			del_back(x);//удаляем из конца
			return 1;
		}
		else
		{
			curr->prev->next = curr->next;//заменяем связи
			curr->next->prev = curr->prev;
			head->data--;//уменьшаем кол во элементов
			*x = curr->data;
			delete curr;//удаляем его
			return 1;
		}
	}
}
int list_2_cycle_head::read(int n, double *x){
	if (n >= head->data)//если номер некорректный
		return 0;
	else
	{
		node *curr = head->next;//первый элемент
		for (int i = 0; i < n; i++)//двигаемся до нужного элемента
			curr = curr->next;
		*x = curr->data;//запоминаем в переменную инф поле
		return 1;
	}
}
int list_2_cycle_head::size(){//размер списка
	return head->data;//берем поле data из головы списка
}
void list_2_cycle_head::clear(){//очистка списка
	double a;
	while (head->data != 0)//пока список не пуст
		del_start(&a);//удаляем из начала
}



void list_1_cycle::push_back(double data){ //добавление в конец
	if (first == nullptr)//список пуст
	{
		node *new_elem = new node(data);//добавляем новый элемент
		new_elem->next = new_elem;//устанавливаем его поле next
		first = last = new_elem;//установить новые значения first и next
	}
	else
	{
			node *new_elem = new node(data);//добавляем новый элемент
			new_elem->next = first;//следующим за новым элементом - первый
			last->next = new_elem;//следующий за последним - новый
			last = new_elem;//делаем новый элемент последним
	}
}
void list_1_cycle::push_start(double data){ //добавление в начало
	if (first == nullptr)//список пуст
	{
		node *new_elem = new node(data);//создаем новый элемент
		new_elem->next = new_elem;//делаем его единственным
		first = last = new_elem;
	}
	else
	{
		node *new_elem = new node(data);//соаздем новый элемент
		new_elem->next = first;//обновляем связи
		last->next = new_elem;//с новым элементом списка
		first = new_elem;//обновляем первый элемент списка
	}
}
void list_1_cycle::push_to_position(int n, double data){//добавить в определеную позицию
	if (n < 0)//номер некорректный
	{
		cout << "number must be non negative" << endl;
		return;
	}
	if (n == 0)//добавляем в начало списка
	{
		push_start(data);
		return;
	}
	int razm = size();
	if (n > razm)//если нет такого номера в списке
	{
		cout << "Impossible position, your list has only " << razm << " elements" << endl;
		return;
	}
	if (n == razm)//добавляем в конец списка
	{
		push_back(data);
		return;
	}
	node *curr = first;//создаем указатель на первый элемент списка
	for (int i = 0; i < n - 1; i++)//двигаемся до элемента перед тем, который нам необходим
		curr = curr->next;
	node *new_elem = new node(data);//создаем новый элeмент
	new_elem->next = curr->next;//выставляем связь к последующему элементу
	curr->next = new_elem;//выставляем связь от предыдущего к новому
	
}
int list_1_cycle::del_back(double *x){//удаление из конца
	if (first == nullptr)//пустота
		return 0;
	if (first == last)//последний элемент
	{
		*x = first->data;//запоминаем инф поле в переменную
		first = last = nullptr;//зануляем начало и конец списка
		return 1;
	}
	node *curr = first;//первый элемент списка
	while (curr->next != last)//двигаемся до предпоследнего
		curr = curr->next;
	delete last;//удаляем последний
	*x = curr->data;//запоминаем инф поле в переменную
	curr->next = first;//выставляем верную связь
	last = curr;//новый последний элемент 
	return 1;
}
int list_1_cycle::del_start(double *x){//удаление из начала списка
	if (first == nullptr)//пуст
		return 0;
	if (first == last)//1 элемент
	{
		*x = first->data;//запоминаем инф поле
		delete first;//удаляем этот элемент
		first = last = nullptr;//зануляем
		return 1;
	}
	node *curr = first;//запоминаем 1 элементы
	first = curr->next;//сдвигаем первый элемент вправо
	last->next = first;//выставляем связь
	*x = curr->data;
	delete curr;//удаляем этот элемент
	return 1;
}
int list_1_cycle::del_from_position(int n, double *x){//удаление из определенной позиции
	if (n < 0)//некорректный номер
		return 0;
	if (first == nullptr)//список пуст
		return 0;
	if (first == last)//если 1 элемент в списке
		if (n == 0)//если необходимый номер = 0
		{
			*x = first->data;//запоминаем инф поле
			delete first;//удаляем его
			first = last = nullptr;//зануляем
			return 1;
		}
		else
			return 0;
	if (n == 0)//если удаляем из начала списка
	{
		del_start(x);
		return 1;
	}
	int razm = size();//размер списка
	if (n >= razm)//если он превышен
		return 0;
	node *curr = first;//запоминаем 1 элемент
	for (int i = 0; i < n - 1; i++)//движемся до предыдущего элемента
		curr = curr->next;
	if (curr->next == last)//если нужный элемент последний
		del_back(x);//удаляем из конца
	else
	{
		node *for_del = curr->next;//запоминаем нужный элемент
		curr->next = curr->next->next;//выставляем связи
		*x = for_del->data;//запоминаем инф поле
		delete for_del;
	}
	return 1;
}
void list_1_cycle::print_list(){
	if (first == nullptr)//список пуст
		cout << "List is empty" << endl;
	else
	{
		node *curr = first;//запоминаем первый элемент
		do{
			cout << curr->data << " ";//печатаем
			curr = curr->next;//двигаемся дальше
		} while (curr != first);//пока не достигнем этого же элемента
		cout << endl;
	}
}
int list_1_cycle::size(){//размер
	if (first == nullptr)//список пуст
		return 0;
	node *curr = first;//запоминаем первый элемент
	int size = 0;//для размера
	do
	{
		curr = curr->next;//двигаемся по списку
		size++;//увеличиваем размер
	} while (curr != first);//пока не достигнем начального элемента
	return size;
}
int list_1_cycle::read(int n, double *x){//чтение без удаления
	if (n >= size() || n < 0) //некорректный номер
		return 0;
	else
	{
		node *curr = first;//запоминем первый элемент
		for (int i = 0; i < n; i++)//двигаемся с его помощью до нужного
			curr = curr->next;
		*x = curr->data;//запоминаем инф поле в переменную
		return 1;
	}
}
void list_1_cycle::clear(){//очистка списка
	double a;
	while (first != nullptr)//пока список не пуст
		del_start(&a);//удаляем из начала
}

void list_2_cycle::push_back(double data)//занесение в конец циклического списка
{
	if (first == nullptr)//список пуст
	{
		node *new_elem = new node(data);
		new_elem->next = new_elem;//устанавливаем поля prev и next
		new_elem->prev = new_elem;
		first = new_elem; //список из 1 элемента
	}
	else
	{
		node *new_elem = new node(data);
		new_elem->next = first; //установка поля next добавляемого узла
		new_elem->prev = first->prev;//установка поля prev добавляемого узла
		first->prev->next = new_elem;//установка поля next для узла, предшествующего добавляемому
		first->prev = new_elem;//Установка поля prev узла, следующего после добавляемого
	}
}
void list_2_cycle::push_start(double data){
	if (first == nullptr)//если список был пуст
	{
		node *new_elem = new node(data);//создаем новый элемент и устанавливаем связи
		new_elem->next = new_elem;
		new_elem->prev = new_elem;
		first = new_elem;//устанавливаем первый элемент
	}
	else
	{
		node *new_elem = new node(data);//создаем новый элемент 
		new_elem->next = first;//устанавливаем связи у нового элемента
		new_elem->prev = first->prev;
		first->prev->next = new_elem;
		first->prev = new_elem;//обновляем связи в списке
		first = new_elem;//двигаем вперед элемент first
	}
}
void list_2_cycle::push_to_position(int n, double data){//добавление в определенную позицию в списке
	if (n < 0)//некорректный номер
	{
		cout << "number must be non negative" << endl;
		return;
	}
	if (first == nullptr)//список пуст
		if (n != 0)
		{
			cout << "Impossible position, your list is empty" << endl;
			return;
		}
		else//добавляем на 0 место
		{
			push_back(data);
			return;
		}
	int razm = size();//для размера списка
	if (n > razm)//если номер больше чем размер
	{
		cout << "Impossible position, your list has only " << razm << " elements" << endl;
		return;
	}
	node *curr = first;//для передвижения по списку
	for (int i = 0; i < n; i++)
		curr = curr->next;//движемся к нужному элементу
	if (n == 0) //если добавляем в начало списка
		push_start(data);
	else
		if (curr == first)//если добавляем на последнюю позицию
		{
			push_back(data);
		}
		else
		{
			node *new_elem = new node(data);//создаем новый элемент
			new_elem->next = curr;//выставляем его связи(next на текущий элемент, prev на предшествующий)
			new_elem->prev = curr->prev;
			curr->prev->next = new_elem;//выставляем связи в списке
			curr->prev = new_elem;
		}
}
int list_2_cycle::del_back(double *x){//удаление из конца списка
	int razm = size();//размер списка
	if (first == nullptr)//список пуст
		return 0;
	else
		if (razm == 1)//всего 1 элемент
		{
			*x = first->data;//сохраняем инф поле
			first = nullptr;//зануляем элемент
			return 1;
		}
		else
		{
			node *curr = first->prev;//запоминаем последний элемент
			curr->prev->next = first;//устанавливаем связи 
			first->prev = curr->prev;
			*x = curr->data;
			delete curr;//удаляем элемент
			return 1;
		}
}
int list_2_cycle::del_start(double *x){//удаление из начала
	int razm = size();//размер списка
	if (first == nullptr)//пустота
		return 0;
	else
		if (razm == 1)//1 элемент
		{
			*x = first->data;//берём его инф поле и запоминаем в переменную
			first = nullptr;//зануляем первый элемент
			return 1;
		}
		else
		{
			node *curr = first;//запоминаем 1 элемент
			first = first->next;//сдвигаем first вправо
			curr->prev->next = first;//выставляем связи
			first->prev = curr->prev;//исключая удаляемый элемент
			*x = curr->data;//берем инф поле и запоминаем в переменную
			delete curr;//удаляем этот элемент
			return 1;
		}
}
int list_2_cycle::del_from_position(int n, double *x){//удаляем с определенной позиции
	int razm = size();
	if (n >= razm)//если превысили размер списка
		return 0;
	if (n < 0)//некорректный номер
		return 0;
	if (first->next == first)//если элемент всего 1
		if (n == 0)//и мы пытаемся его удалить
		{
			*x = first->data;//сохраняем поле дата
			first = nullptr;//зануляем первый элемент
			return 1;
		}
		else
			return 0;
	if (n == 0)//если удаляем элемент с номером 0
	{
		del_start(x);//удаляем из начала
		return 1;
	}
	else
	{
		node *curr = first->next;//для движения по списку
		for (int i = 1; i < n; i++)//двигаемся к нужному элементу
		{
			curr = curr->next;
		}
		if (curr->next == first)//если он последний в списке
		{
			del_back(x);//удаляем из конца
			return 1;
		}
		else
		{
			curr->prev->next = curr->next;//заменяем связи
			curr->next->prev = curr->prev;
			*x = curr->data;
			delete curr;//удаляем его
			return 1;
		}
	}
}
void list_2_cycle::print_list(){//печать списка
	if (first == nullptr)//список пуст
		cout << "List is empty" << endl;
	else
	{
		node *curr = first;//запоминаем первый элемент
		do{
			cout << curr->data << " ";
			curr = curr->next;//движемся дальше по списку
		} while (curr != first);//пока не вернёмся к первому элементу
		cout << endl;
	}
}
void list_2_cycle::print_reverse(){//печать наоборот
	if (first == nullptr)//пустота
		cout << "List is empty" << endl;
	else
	{
		node *curr = first->prev;//запоминаем последний элемент
		do
		{
			cout << curr->data << " ";
			curr = curr->prev;//двигаемся от конца к началу
		} while (curr != first->prev);//пока не придём снова к этому же элементу
		cout << endl;
	}
}
int list_2_cycle::size(){//размер
	if (first == nullptr)//если пуст
		return 0;
	node *curr = first;
	int size = 0;//для размера
	do
	{
		curr = curr->next;//двигаемся по списку
		size++;//увеличиваем размер
	} while (curr != first);//пока не придём снова к началу списка
	return size;
}
int list_2_cycle::read(int n, double *x){//чтение без удаления
	if (n >= size() || n < 0)//если некорректный номер 
		return 0;
	else
	{
		node *curr = first;
		for (int i = 0; i < n; i++)//двигаемся к нужному элементу
			curr = curr->next;
		*x = curr->data;//записываем инф поля этого элемента
		return 1;
	}
}
void list_2_cycle::clear(){//очистка списка
	double a;
	while (first != nullptr)
		del_start(&a);//удаляем из начала пока не удалим всё
}
void list_2_cycle::write_to_file(ofstream &outp)//запись в файл
{
	node *curr = first;//запоминаем 1 элемент
	int sizeoflst = size();//размер списка
	while(sizeoflst)//пока не пройдём по всему списку
	{
		outp << curr->data << " ";//пишем в файл
		curr = curr->next;//двигаемся дальше по списку
		sizeoflst--;
	}
}
void list_2_cycle::create_list_from(list_1_cycle &A, list_2_cycle_head &B, list_2_cycle &C){//составление списка уникальных элементов
	double elem;//для очередного числа
	while (A.del_start(&elem))//считываем
		push_back(elem);	  //данные из
	while (C.del_start(&elem))//
		push_back(elem);	  //
	while (B.del_start(&elem))//исходных списков
		push_back(elem);	  //в результирующие

	//ищем повторяющиеся числа
	bool check_repeat = false;//для определения, был ли повтор числа
	node *curr1 = first;//для первоначального прохода по списку
	int counter1 = 0;//счётчик внутри первого цикла(чтобы знать какой элемент удалять)
	int counter2;//счётчик внутри второго цикла(чтобы знать какой элемент удалять)
	while (first != nullptr && curr1 != first->prev)//пока не достигнем конца списка, либо пока список не будет пуст
	{
		double element = curr1->data;//записываем в переменную инф поля 
		node *curr = curr1->next;//переменная-node для второго цикла
		check_repeat = false;//признак повтора изначально равен 0
		counter2 = counter1 + 1;//чтобы начать поиск во 2 цикле начиная со следующего элемента
		while (curr != first)//пока не дойдём до начала списка
		{
			if (curr->data == element)//если инф.поле очередного элемента списка равно сохранённому значению из основого цикла
			{
				check_repeat = true;//признак равен 1
				curr = curr->prev;//сдвигаемся на 1 назад
				del_from_position(counter2 ,&elem);//удаляем этот элемент
				curr = curr->next;//двигаемся к следующему элементу
			}
			else
			{
				counter2++;//добавляем +1 к счётчику
				curr = curr->next;//двигаемся по списку
			}
		}
		if (check_repeat)//если был повтор
		{
			curr1 = curr1->prev;
			del_from_position(counter1, &elem);//то удаляем этот элемент
			curr1 = curr1->next;
		}
		else
		{
			counter1++;//добавляем +1 к счётчику
			curr1 = curr1->next;//двигаемся по списку
		}
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	ifstream inp("input.dat");//для открытия файла для чтения
	ofstream outp("output.dat");//для открытия файла для записи

	if (!inp.is_open())
	{
		cout << "File input.dat wasn't open" << endl;
		ofstream n("input.dat");
		n.close();
	}
	else
	{
		list_1_cycle list1;//первый список(односвязный
		list_2_cycle list2; //второй список(двусвязный)
		list_2_cycle_head list3; //третий список(двусвязный с головой)
		double x; //очередная переменная при считывании из файла
		char c;//для нахождения конца строки
		if (inp.get(c))//считаем один символ
		{
			inp.seekg(0, ios_base::beg); //Стать в начало файла
			if (c != '\n')//первый список не пуст
			{
				while (inp >> x)//читаем число
				{
					list1.push_back(x);//записываем в список
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
					list2.push_back(x);//записываем в список
					inp.get(c); //считываем 1 символ
					if (c == '\n')//если конец строки, то прерываем цикл
						break;
				}
			}
			cout << "Second list was successfully read" << endl;

			inp.seekg(-1, ios_base::cur); //перепрыгнуть назад в файле
			while (inp >> x)//читаем число
			{
				list3.push_back(x);//записываем в список
			}
			cout << "Third list was successfully read\n---------------------------------------------" << endl;
			if (!inp.eof())
				cout << "File is broken" << endl;
			else
			{
				cout << "First list (single-linked list):" << endl;
				list1.print_list(); //печать списка 1
				cout << "Second list (double-linked list):" << endl;
				list2.print_list();//печать списка 2
				cout << "Third list(double-linked list with head):" << endl;
				list3.print_list();//печать списка 3

				list_2_cycle result; //для результата
				
				cout << "Result list is: " << endl;
				result.create_list_from(list1, list3, list2);//формируем результирующий список
				result.print_list();//печать на экран
				result.write_to_file(outp);//печать в файл
			}
		}
		else
			cout << "File is empty!" << endl;
	}
	inp.close();
	outp.close();
	return 0;
}