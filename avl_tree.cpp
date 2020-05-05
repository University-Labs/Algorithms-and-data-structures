#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;


struct nodeAVL {//Узел дерева
	double data; // ключ
	nodeAVL *left, *right;//указатели на левого и правого потомков
	int height; //высота

	nodeAVL(double data) {//конструктор с параметром
		this->data = data;
		left = NULL;
		right = NULL;
		height = 1;
	}
};

int Height(nodeAVL* node) { //определить высоту дерева
	if (node) //если дерево не пусто
		return node->height;//высота
	else
		return 0;//высота 0
}
int BalanceLevel(nodeAVL* node) { //определение уровня баланса узла
	return Height(node->right) - Height(node->left);
}
void ChangeHeight(nodeAVL* node) //изменение высоты дерева при балансе и добавлении
{
	int left, right;

	left = Height(node->left);//высота левого потомка
	right = Height(node->right);//высота правого потомка
	node->height = (left > right ? left : right) + 1;//высота узла - максимальное из двух
}
nodeAVL* RightTurn(nodeAVL* node) //малый правый поворот
{
	nodeAVL* left_s = node->left;//запоминаем левого сына узла
	node->left = left_s->right;//меняем левого сына узла
	left_s->right = node;//для старого левого сына правым потомком делаем изначальный узел
	ChangeHeight(node);//меняем высоту
	ChangeHeight(left_s);//меняем высоту
	return left_s;//возвращаем получившийся узел
}
nodeAVL* LeftTurn(nodeAVL* node) // малый левый поворот
{
	nodeAVL* right_s = node->right;//запоминаем правого сына узла
	node->right = right_s->left;//меняем правого сына у изначального узла
	right_s->left = node;//для старого правого сына левым потомком делаем изначальный узел
	ChangeHeight(node);//меняем высоту
	ChangeHeight(right_s);//меняем высоту
	return right_s;//возвращаем получившийся узел
}
nodeAVL* Balance(nodeAVL* node)//функция балансировки узла
{
	ChangeHeight(node); //поправляем высоту 
	if (BalanceLevel(node) == 2) //Если правое поддерево перевешивает
	{
		if (BalanceLevel(node->right) < 0)// Если узел слева на уровень ниже
			node->right = RightTurn(node->right);//совершаем малый правый поворот
		return LeftTurn(node);//малый левый поворот
	}

	if (BalanceLevel(node) == -2)//если левое поддерево перевешивает
	{
		if (BalanceLevel(node->left) > 0)//если узел справа на уровень ниже
			node->left = LeftTurn(node->left);//совершаем малый левый поворот
		return RightTurn(node);//малый правый поворот
	}
	return node;//Если всё и так сбалансированно, возвращаем тот же узел
}
nodeAVL* Push(nodeAVL* node, double data)//добавление элемента в дерево
{
	if (!node)//дерево пусто(дошли до его конца)
	{
		return new nodeAVL(data);
	}
	if (data < node->data)//Если число меньше ключа в узле
		node->left = Push(node->left, data);//идем рекурсивно влево
	else
		node->right = Push(node->right, data);//идем рекурсивно вправо
	return Balance(node);//вызываем балансировку
}
nodeAVL* FindMin(nodeAVL* node) // поиск узла с минимальным ключом 
{
	if (node->left != NULL)//пока не дошли до конца
		return FindMin(node->left);//вызываем рекурсивно поиск
	else return node;//возвращаем етот узел(он минимальный)
}
nodeAVL* RemoveMin(nodeAVL* node) // удаление узла с минимальным ключом
{
	if (node->left == nullptr)//eсли нет левого потомка
		return node->right;//возвращаем правого потомка

	node->left = RemoveMin(node->left);//ведем удаление дальше

	return Balance(node);//вызываем балансировку
}
nodeAVL* DelElem(nodeAVL* node, double a) // удаление ключа a из АВЛ дерева
{
	if (node == nullptr) //дерево пусто(элемента нет)
		return 0;
	if (a < node->data)//Если данные меньше ключа узла(исщим ключ)
		node->left = DelElem(node->left, a);//идем влево
	else if (a > node->data)
		node->right = DelElem(node->right, a);//идем вправо
	else//если равно
	{
		nodeAVL* left = node->left;//Сохраняем его потомки
		nodeAVL* right = node->right;
		delete node;//удаляем этот элемент

		if (right == nullptr)//Если нет правого поддерева
			return left;//то просто возвращаем в дерево левого потомка
		//если же правое поддерево есть
		nodeAVL* min = FindMin(right);//находим минимум в этом поддереве
		min->right = RemoveMin(right);//и ставим его на место старого узла
		min->left = left;//присоединяем к нему старый левый узел

		return Balance(min);//балансируем получившееся дерево
	}

	return Balance(node);//вызываем балансировку после удаления
}

static int count_elem = 0;
void print(nodeAVL *node, int level){//симметричный обход
	if (node == nullptr)//узел пуст
		return;
	else
	{
		print(node->left, level + 1); //вызываем функцию для печати левого поддерева
		for (int i = 0; i < level; i++)//для наглядности печатаем пробелы
			cout << "  ";
		count_elem++;
		cout << node->data << endl;//печатаем инф. поле
		print(node->right, level + 1);//Переходим к правому поддереву
	}
}
void print_to_file(nodeAVL *t, int level, ofstream &out){//запись в файл
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


int _tmain(int argc, _TCHAR* argv[])
{
	ifstream inp("input_tree.txt");//для открытия файла для чтения
	ifstream inp_sled("input_sled.txt");
	ofstream outp("output.txt");//для открытия файла для записи

	if (!inp.is_open() || !inp_sled.is_open())
	{
		cout << "Files were not opened" << endl;
		ofstream n("input_tree.txt");
		n.close();
	}
	else
	{
		inp_sled.seekg(0, ios_base::end);//определяем размер файла
		int sizeoff = inp_sled.tellg();
		inp_sled.seekg(0, ios_base::beg); //переставляем указатель на начало
		if (sizeoff == 0)//файл пуст
			cout << "File inp_sled.txt is empty" << endl;
		else
		{
			char *footprint = new char[sizeoff]; //след

			char c; //очередной символ из файла
			int k = 0;
			while (inp_sled.get(c))//считываем след из файла
			{
				if (c != '0' && c != '1')
				{
					cout << "Wrong track!" << endl;
					return 1;
				}
				footprint[k++] = c;
			}
			if (footprint[0] != '1')//если не верно начало следа
			{
				cout << "Wrong track!" << endl;
				return 1;
			}

			double x; //число для считывания
			if (inp >> x)
			{
				nodeAVL *tree = new nodeAVL(x);//создаем корень дерева
				while (inp >> x)
					tree = Push(tree, x);//заполняем авл дерево
				cout << "Your tree is: " << endl;
				print(tree, 0); //печатаем дерево
				cout << "Your track is: ";
				for (int i = 0; i < sizeoff; i++)//печатаем след, узел которого нужно удалитб
					cout << footprint[i];
				cout << endl << endl;

				//обработка следа
				nodeAVL *tmp = tree;//запоминаем корень дерева
				bool error = false;//есть ли данный элемент в дереве
				for (int i = 1; i < sizeoff; i++)//проходим по каждому элементу "следа"
				{
					if (footprint[i] == '0')
					{
						if (tmp->left == nullptr)//если такого потомка нет
						{
							error = true; break;//устанавливаем флажок ошибки и выходим
						}
						tmp = tmp->left;//идем влево
					}
					else
					{
						if (tmp->right == nullptr)//нет правого потомка
						{
							error = true; break;//флажок и выход
						}
						tmp = tmp->right;//идем вправо
					}
				}
				if (error)//Если не нашли узел
					cout << "Key wasnt found" << endl;
				else
				{
					tree = DelElem(tree, tmp->data);// удаляем узел с данным ключом
				}

				cout << "Resulting tree" << endl; count_elem = 0;
				print(tree, 0);//печатаем получившееся дерево
				if (!count_elem)
					cout << "Tree is empty" << endl;

				//запись в файл
				print_to_file(tree, 0, outp);
			}
			else
				cout << "File tree is empty" << endl;
		}
	}
	inp_sled.close();//закрываем файлы
	inp.close();//закрываем файлы
	outp.close(); //закрываем файлы
	return 0;
}