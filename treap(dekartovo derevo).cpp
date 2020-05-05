#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

struct Ducha //описание узла дерева
{
	int x;//ключ
	int y;//приоритет
	Ducha *left, *right; //указатель на левого и правого потомков
	Ducha(int key, int prior, Ducha *left = nullptr, Ducha *right = nullptr) { x = key, y = prior, this->left = left, this->right = right; }//создание нового эл-та дерева
};

Ducha* Merge(Ducha *L, Ducha *R) {//объединение двух поддеревьев (л и п)
	if (L == nullptr) //левого нет
		return R;
	if (R == nullptr)//правого нет
		return L;
	if (L->y > R->y)//приоритет левого больше приоритета правого
	{
		Ducha *a = Merge(L->right, R);//сливаем правое поддерево у левого с правым
		return new Ducha(L->x, L->y, L->left, a);//создаём новое дерево (с корнем в левом поддереве)
	}
	else
	{
		Ducha *a = Merge(L, R->left);//сливаем левое поддерево с левым поддеревом правого
		return new Ducha(R->x, R->y, a, R->right);//создаем новое дерево (с корнем в правом поддереве)
	}
}
void Split(Ducha *T, int x, Ducha *&L, Ducha *&R){//разделение дерева по ключу
	Ducha *a = nullptr;
	if (T->x <= x) //Если ключ узла меньше ключа для разделения
	{//идём вправо
		if (T->right == nullptr)//если нет правого поддерева
			R = nullptr;//то правое поддерево для данного разделения нулевое(дошли до такого узла)
		else
			Split(T->right, x, a, R);//иначе снова разделяем правое поддерево по split(чтобы убрать из него узлы, меньшие x)
		L = new Ducha(T->x, T->y, T->left, a);//Левым поддеревом становится левое поддерево изначального, а правым - левое поддерево правого поддерева
	}
	else
	{//идём влево
		if (T->left == nullptr)//если нет левого поддерева
			L = nullptr;//то дошли до конца разделения
		else
			Split(T->left, x, L, a);//снова разделяем левое поддерево по split(чтобы отсечь узлы большие x)
		R = new Ducha(T->x, T->y, a, T->right);//формируем из правого поддерева и левого поддерева от изначального правого новое правое поддерево
	}
}
Ducha* Add(Ducha *T, int x)
{
	Ducha *l, *r;
	Split(T, x, l, r);//разделяем дерево T по ключу x
	Ducha *m = new Ducha(x, rand() % 100);//создание одного узла с заданным ключом и случайным приоритетом
	return Merge(Merge(l, m), r); //склеиваем узел с ключом x сначала с левым поддеревом(где все ключи менее x), затем с правым(где все больше x)
}
Ducha* Delete(Ducha *T, int x){//удаление ключа из дерева
	Ducha *l, *r, *rl;
	Split(T, x - 1, l, r);// получили: в l - все ключи меньшие, либо равные x - 1, в r - больше либо равные x
	Split(r, x, rl, r);// получили в rl только сам узел x, а в r все остальные
	delete rl;
	return Merge(l, r);//объединяем получившиеся поддеревья
}
void Print(Ducha *node, int level){//печать дерева
	if (node == nullptr)//узел пуст
		return;
	else
	{
		Print(node->left, level + 1); //вызываем функцию для печати левого поддерева
		for (int i = 0; i < level; i++)//для наглядности печатаем пробелы
			cout << "    ";
		cout << node->x << "(" << node->y << ")" << endl;//печатаем инф. поле
		Print(node->right, level + 1);//Переходим к правому поддереву
	}
}
static int countss = 0;
void create_mass(Ducha *node, int *massive)//сама процедура создания массива
{
	if (node == nullptr)
		return;
	else
	{
		create_mass(node->left, massive);//создаем в порядке ЛПК
		create_mass(node->right, massive);
		massive[countss++] = node->x;
	}
}
void make_massive(Ducha *node, int *massive){//создание массива(обёртка)
	countss = 0;
	create_mass(node, massive);
}
void print_to_file(Ducha *t, int level, ofstream &out){//запись в файл
	if (t == nullptr)//узел пуст
		return;
	else
	{
		print_to_file(t->left, level + 1, out); //вызываем функцию для печати левого поддерева
		for (int i = 0; i < level; i++)//для наглядности печатаем пробелы
			out << "    ";
		out << t->x << "\n";//печатаем инф. поле
		print_to_file(t->right, level + 1, out);//Переходим к правому поддереву
	}
}



int _tmain(int argc, _TCHAR* argv[])
{
	ifstream inp("input.txt");//для открытия файла для чтения
	ofstream outp("output.txt");//для открытия файла для записи

	if (!inp.is_open())
	{
		cout << "File input.text wasn't open" << endl;
		ofstream n("input.txt");
		n.close();
	}
	else
	{
		Ducha *first = nullptr; //первое исходное дерево
		Ducha *second = nullptr;//второе исходное дерево
		int amount_in_first = 0, amount_in_second = 0; //количество элементов в каждом дереве
		int x; //очередная переменная при считывании из файла
		char c;//для нахождения конца строки
		if (inp.get(c))//считаем один символ
		{
			inp.seekg(0, ios_base::beg); //Стать в начало файла
			if (c != '\n')//первое дерево не пустое
			{
				while (inp >> x)//читаем число
				{
					amount_in_first++;
					if (first == nullptr)
						first = new Ducha(x, rand() % 100); //создаём дерево
					else
						first = Add(*&first, x);
					inp.get(c); //считываем 1 символ
					if (c == '\n')//выходим при символе конца строки
						break;
				}
			}
			else
				inp.get(c);//возвращаем указатель туда же

			cout << "First tree was successfuly read" << endl;
			inp.get(c);//читаем \n или первую цифру

			if (c != '\n')//если второй список не пуст
			{
				inp.seekg(-1, ios_base::cur); //перепрыгнуть назад в файле
				while (inp >> x)//читаем число
				{
					amount_in_second++;
					if (second == nullptr)
						second = new Ducha(x, rand() % 100); //создаём дерево
					else
						second = Add(*&second, x);
					inp.get(c); //считываем 1 символ
					if (c == '\n')//если конец строки, то прерываем цикл
						break;
				}
			}
			cout << "Second tree was successfully read" << endl;

			if (!inp.eof())
				cout << "File is broken" << endl;
			else
			{
				cout << "First tree:" << endl;
				if (first)// печатаем оба исходных дерева на экран
					Print(first, 0);
				else
					cout << "Tree is empty" << endl;

				cout << "Second tree:" << endl;
				if (second)// печатаем оба исходных дерева на экран
					Print(second, 0);
				else
					cout << "Tree is empty" << endl;
				int *massive1 = new int[amount_in_first]; //массив из всех элементов дерева
				int *massive2 = new int[amount_in_second];//массив из всех элементов дерева
				if (first)
					make_massive(first, massive1);//формирование массивов
				if (second)
					make_massive(second, massive2);

				//сама процедура удаления и формирования нового дерева
				Ducha *Result_tree = nullptr;
				if (amount_in_first != 0 && amount_in_second != 0)
					for (int i = 0; i < amount_in_first; i++)
					{
						for (int j = 0; j < amount_in_second; j++)
							if (massive1[i] == massive2[j])//если есть одинаковые элементы
							{
								first = Delete(*&first, massive1[i]);//удаляем их из исходных
								second = Delete(*&second, massive1[i]);
								if (Result_tree == nullptr)//если результирующее дерево еще пусто
									Result_tree = new Ducha(massive1[i], rand() % 100);//создаем его и добавляем в него этот элемент
								else
									Result_tree = Add(*&Result_tree, massive1[i]);//просто добавляем в дерево повторяющийся элемент
								break;
							}
					}
				cout << "First tree after changing:" << endl;
				if (first)//печатаем результаты
					Print(first, 0);
				else
					cout << "Tree is empty" << endl;
				cout << "Second tree after changing" << endl;
				if (second)//печатаем результаты
					Print(second, 0);
				else
					cout << "Tree is empty" << endl;
				cout << "Result tree is:" << endl;
				if (Result_tree)//печатаем результаты
				{
					Print(Result_tree, 0);
					print_to_file(Result_tree, 0, outp);//запись в файл
				}
				else
					cout << "Tree is empty" << endl;
				delete massive1, massive2;
			}
		}
		else
			cout << "File is empty!" << endl;
	}
	inp.close();
	outp.close();
	return 0;
}

