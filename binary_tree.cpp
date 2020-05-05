#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;


struct node //узел дерева
{
	double data;  //Информационное поле
	node *left, *right; //Левый и Правый потомок дерева
};

struct tree{
	node *root = NULL;//корень дерева
};


void find_em(node *(&t), node *(&par), int data){
	if (!t)
	{
		par = nullptr;
		t = nullptr;
	}
	else
	{
		while (t->data != data)
		{
			par = t;
			if (t->data > data)
				t = t->left;
			else
				t = t->right;
			if (t == NULL)
			{
				par = nullptr;
				break;
			}
		}
	}
}
int delete_elem(node **t, int data){
	node *elem = *t;
	node *parent = nullptr;
	find_em(elem, parent, data);
	if (elem == nullptr)
		return 0;
	//нет потомков((
	if (elem->left == NULL && elem->right == NULL)
	{
		if (parent != nullptr)
		{
			if (parent->data > elem->data)
				parent->left = nullptr;
			else
				parent->right = nullptr;
			delete elem;
		}
		else
		{
			elem = nullptr;
		}
		return 1;
	}
	//1 потомок
	if (elem->left == NULL && elem->right != NULL || elem->left != NULL && elem->right == NULL)
	{
		if (parent != nullptr)
		{
			if (parent->data > elem->data){
				if (elem->left != nullptr)
				{
					parent->left = elem->left;
					delete elem;
				}
				else
				{
					parent->left = elem->right;
					delete elem;
				}
			}
			else
			{
				if (elem->left != nullptr)
				{
					parent->right = elem->left;
					delete elem;
				}
				else
				{
					parent->right = elem->right;
					delete elem;
				}
			}
		}
		else
		{
			if (elem->left != nullptr)
			{
				elem = elem->left;
				delete elem->left;
				elem->left = NULL;
			}
			else
			{
				elem = elem->right;
				delete elem->right;
				elem->right = NULL;
			}
		}
		return 1;
	}
	//2 потомка(простая ситуация) но у правого потомка удаляемого узла нет левого потомка
	if (elem->right->left == NULL)
	{
		if (parent != nullptr){
			if (parent->data > elem->data)
			{
				node *tmp = elem->left;
				parent->left = elem->right;
				parent->left->left = elem->left;
				delete elem;
			}
			else
			{
				node *tmp = elem->left;
				parent->right = elem->right;
				parent->right->left = elem->left;
				delete elem;
			}
		}
		else
		{
			node *el = elem;
			elem->right->left = elem->left;
			elem = elem->right;
			delete el;
		}
		return 1;
	}
	//Самый обычный случай удаления узла с двумя потомками
	if (elem->right != nullptr && elem->left != nullptr){
		;
	}
	return 0;
}

/*ФУНКЦИЯ ЗАПИСИ ЭЛЕМЕНТА В БИНАРНОЕ ДЕРЕВО*/
void push(double a, node **t)
{
	if (*t == nullptr)//дерево пустое
	{
		*t = new node;//создаем новый узел
		(*t)->data = a;
		(*t)->left = (*t)->right = nullptr;//правый и левый потомок равны 0
	}
	else
	{
		if (a >= (*t)->data)//Если аргумент больше чем в данном узле
			push(a, &(*t)->right);//движемся к правому потомку
		else
			push(a, &(*t)->left);//движемся к левому потомку
	}
}
/*ФУНКЦИЯ ПОИСКА ЭЛЕМЕНТА С ЗАДАННЫМ ЗНАЧЕНИЕМ*/
node* finding_elem(double data, node*t){
	if (t == nullptr)
		return nullptr;
	else
	{
		if (t->data < data)
			t = finding_elem(data, t->right);
		else
		if (t->data > data)
			t = finding_elem(data, t->left);
		else
		return t;
	}
}
node* find_elem(double a, node *t)
{
	if (!t)
		return NULL;
	else
	{
		while (t->data != a)
		{
			if (t->data > a)
				t = t->left;
			else
				t = t->right;
			if (t == NULL)
				break;
		}
	}
	return t;
}

static int count = 0; //для формирования последовательности из дерева
/*ФУНКЦИИ СОЗДАНИЯ ПОСЛЕДОВАТЕЛЬНОСТИ(чтение происходит в порядке ЛКП)*/
void posl(node *t, double mass[]){
	if (t == nullptr)//дерево пусто
		return;
	else
	{
		posl(t->left, mass);//идём к левому поддереву
		mass[::count++] = t->data;//сохраняем ключ в массив
		posl(t->right, mass);//идём к правому поддереву
	}
}
void create_posl(node *t, double mass[]){
	::count = 0;//глобальную статическую переменную зануляем
	posl(t, mass);//вызываем саму функцию формирования
}

/*ФУНКЦИЯ СОЗДАНИЯ ВЫРОВНЕННОГО ДЕРЕВА*/
node* create_tree(node **t, double mass[], int begin, int end){
	if (begin > end)//Если дошли до случая, когда прошли все элементы данного подмассива
		return NULL;
	int center = (begin + end) / 2; //находим середину массива
	*t = new node;//создаем новый узел
	(*t)->data = mass[center];//записываем в него центральный элемент массива
	(*t)->left = create_tree(&(*t)->left, mass, begin, center - 1);//формируем левое поддерево(элементы массива от начала до половины -1)
	(*t)->right = create_tree(&(*t)->right, mass, center + 1, end);//формируем правое поддерево(элементы массива от половины +1 до конца)
	return *t;//возвращаем получившийся узел в его родителя
}
/*ФУНКЦИЯ ОТОБРАЖЕНИЯ ДЕРЕВА НА ЭКРАНЕ*/
void print(node *t, int level){//симметричный обход
	if (t == nullptr)//узел пуст
		return;
	else
	{
		print(t->left, level + 1); //вызываем функцию для печати левого поддерева
		for (int i = 0; i < level; i++)//для наглядности печатаем пробелы
			cout << "  ";
		cout << t->data << endl;//печатаем инф. поле
		print(t->right, level + 1);//Переходим к правому поддереву
	}
}
/*ПЕЧАТЬ В ФАЙЛ*/
void print_to_file(node *t, int level, ofstream &out){//запись в файл
	if (t == nullptr)//узел пуст
		return;
	else
	{
		print_to_file(t->left, level + 1, out); //вызываем функцию для печати левого поддерева
		for (int i = 0; i < level; i++)//для наглядности печатаем пробелы
			out << "  ";
		out << t->data << "\n";//печатаем инф. поле
		print_to_file(t->right, level + 1, out);//Переходим к правому поддереву
	}
}
//Прямой обход(КЛП)
void pryamoy(node *t){
	if (t == nullptr)//узел пуст
		return;
	else
	{
		cout << t->data << " ";
		pryamoy(t->left);
		pryamoy(t->right);
	}
	cout << endl;
}
//Обратный обход(ЛПК)
void obratniy(node *t){ 
	if (t == nullptr)//узел пуст
		return;
	else
	{
		obratniy(t->left);
		obratniy(t->right);
		cout << t->data << " ";
	}
	cout << endl;
}

double amount(node* node, int a)
{
	if (node->left == nullptr || node->right == nullptr)
	{
		return 0;
	}
	return (a + amount(node->right, a + 1) + amount(node->left, a + 1));
}
int amount_of_vn(node *node, int am){
	if (node->left == nullptr || node->right == nullptr)
		return 0;
	else
		return amount_of_vn(node->right, am) + amount_of_vn(node->left, am) + 1;
}
int _tmain(int argc, _TCHAR* argv[])
{
	tree a;
	push(30, &a.root);
	push(128, &a.root);
	push(9, &a.root);
	push(242, &a.root);
	push(222, &a.root);
	push(45, &a.root);
	push(36, &a.root);
	push(127, &a.root);
	push(26, &a.root);
	print(a.root, 0);
	cout << "RJKBXTCND: " << amount(a.root, 0) << endl;
	cout << amount_of_vn(a.root, 0);
	cout << endl << endl;
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
		tree start_t; //начальное дерево
		tree result_t;//результирующее(выровненное дерево)
		double x; //очередная переменная при считывании из файла
		char c;//для нахождения конца строки
		int size = 0; //количество чисел в дереве/массиве

		cout << "Now reading of information from file is happened.." << endl;
		while (inp >> x)
		{
			push(x, &start_t.root); //записываем число в дерево
			size++;//количество чисел
		}
		if (size > 0)
		{
			double *mass = new double[size]; //создание массива для хранения последовательности

			cout << "Your tree is: " << endl;
			print(start_t.root, 0); //печатаем исходное дерево
			delete_elem(&start_t.root, 60);
			push(60, &start_t.root);
			print(start_t.root, 0);
			create_posl(start_t.root, mass);//создаём последовательность по возрастанию

			cout << "\nYour sequence is: " << endl;
			for (int i = 0; i < size; i++)// печать последовательности
				cout << mass[i] << " ";
			cout << endl;

			create_tree(&result_t.root, mass, 0, size - 1);//формирование дерева

			cout << "Result tree is: " << endl;
			print(result_t.root, 0);//печать на экран результирующего дерева
			cout << endl;

			print_to_file(result_t.root, 0, outp);//запись в файл
		}
		else
		{
			cout << "File is empty" << endl;
		}
	}
	
	inp.close();
	outp.close();*/

	return 0;
}

