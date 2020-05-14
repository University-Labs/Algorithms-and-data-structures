//Найти наибольшую общую подстроку для двух строк.
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>
#define MAX_CHAR 256

using namespace std;

class SuffixTreeNode{
public:
	SuffixTreeNode *children[MAX_CHAR]; //все возможные дети узла
	SuffixTreeNode *suffixLink;//суффиксная ссылка из данной вершины

	//ребро, которое идёт в эту вершину
	int begin;
	int *end;//конец у листьев изменяется в конце каждого расширения


	bool leaf;
	int number;
};

class SuffixTree{
private:
	SuffixTreeNode *root = NULL; //корень

	//Для хранения текущей точки для расширения, в случае если она находится в середине ребра
	//нужно знать по какому ребру идти и сколько символов по нему двигаться
	SuffixTreeNode *activeNode = NULL; //активная нода в текущем расширении
	int activeEdge = -1; //какое ребро выбрать при поиске точки
	int activeLength = 0; //текущая длина до конца текста
	int totalEnd = -1; //текущий символ на листьях
	int suffixLeftToAdd = 0; //как много суффиксов еще добавить в дерево
	int totalNumber = 0;//текущий номер вершины

	string text;//текст по которому строится дерево
	int posSeparate = -1;//позиция, на которой разделяются 1 и 2 строки
	SuffixTreeNode *createNewNode(int start, int *end); //создание новой ноды
	int lengthOfEdge(SuffixTreeNode *n);//возвращает длину ребра в node n
	int skipCount(SuffixTreeNode *currNode);//совершает прыжок через всё ребро, с заменой ActiveNode
	void pushNode(int pos); //добавление одного символа в дерево
	void setLeaf(SuffixTreeNode *node);//установка номеров вершин и флагов листьев
	int searchString(SuffixTreeNode *node, int len);//осуществляет рекурсивный поиск повторяющейся подстроки максимальной длины
public:
	void buildTree(string text);//построение дерева по тексту
	void printTree();//печать дерева
	string getMaxString();//получение максимальной повторяющейся строки
};

int maxDepth = -1; //содержат максимальную глубину
int startIndex = -1;//содержит начальный индекс

SuffixTreeNode *SuffixTree::createNewNode(int begin, int *end)//создаёт новый узел с заданным началом и концом ребра, идущего в него
{
	SuffixTreeNode *node = new SuffixTreeNode();

	node->suffixLink = root;//изначально суффиксная ссылка не выставлена
	node->begin = begin;//ребро до вершины
	node->end = end;
	node->leaf = false;
	return node;
}
int SuffixTree::lengthOfEdge(SuffixTreeNode *node) //возвращает длину ребра, ведущего в узел дерева
{
	if (node == root) //если узел - корневой
		return 0;
	return *node->end - node->begin + 1;
}
int SuffixTree::skipCount(SuffixTreeNode *currNode)//спуск по ребру, в случае, если его длина меньше длины до текущей активной вершины
{
	if (activeLength >= lengthOfEdge(currNode))
	{
		activeEdge += lengthOfEdge(currNode); //изменяем текущее активное ребро
		activeLength -= lengthOfEdge(currNode);//сдвигаемся на всю длину ребра
		activeNode = currNode;//обновляем активный узел
		return 1;
	}
	else
		return 0;
}
void SuffixTree::pushNode(int i)//добавление очередного символа в дерево
{
	totalEnd = i; //увеличиваем счётчик листьев
	suffixLeftToAdd += 1; //должны добавить дополнительный суффикс
	SuffixTreeNode *lastNewNode = NULL; //новая нода с предыдущего расширения(для восстановления суффиксных ссылок)
	int *splitEnd; //для определения узла при разрезании ребра

	while (suffixLeftToAdd != 0) //пока не добавили все суффиксы
	{
		if (activeLength == 0)//Если ActiveNode  и есть точка увеличения, 
			activeEdge = i;//то смотрим в сторону ребра с символом i

		if (activeNode->children[text[activeEdge]] == NULL) //Если нет ребра по данному символу
		{
			activeNode->children[text[activeEdge]] = createNewNode(i, &totalEnd);//добавляем новый узел
			if (lastNewNode != NULL)//если на текущей итерации уже были добавлены суффиксы
			{
				lastNewNode->suffixLink = activeNode;//то обновляем суффиксную ссылку
				lastNewNode = NULL;
			}
		}
		else //если есть ребро по символу currEdge
		{
			SuffixTreeNode *nextNode = activeNode->children[text[activeEdge]];
			//Если прошли полностью по ребру currNode
			//при этом мы обновили активный узел
			if (skipCount(nextNode))
			{
				continue;//тогда запускаем вставку суффикса заново с тем же значением SuffixLeftToAdd
			}

			if (text[nextNode->begin + activeLength] == text[i])//Если данный символ уже есть в дереве
			{
				if (lastNewNode != NULL && activeNode != root)
				{
					lastNewNode->suffixLink = activeNode;
					lastNewNode = NULL;
				}
				activeLength++;//увеличиваем дальность активной точки
				break;//далее все узлы будут 3-го вида, поэтому можно заканчивать цикл вставки
			}
			else//символ к которому нужно производить вставку находится на ребре
			{
				//Разрезам ребро по активному символу
				splitEnd = new int();
				*splitEnd = nextNode->begin + activeLength - 1;//определяем точку разреза
				
				SuffixTreeNode *split = createNewNode(nextNode->begin, splitEnd);//Создаем новый внутренний узел
				activeNode->children[text[activeEdge]] = split; //изменяем ребенка по данному символу
				split->children[text[i]] = createNewNode(i, &totalEnd);//создаём лист
				nextNode->begin += activeLength; //сдвигаем старое ребро
				split->children[text[nextNode->begin]] = nextNode; //и далаем его ребенком нового

				if (lastNewNode != NULL)
				{
					lastNewNode->suffixLink = split;//добавляем суффиксную ссылку узлу с предыдущего расширения
				}
				lastNewNode = split;//и обновляем узел для формирования суф. ссылки
			}
		}
		suffixLeftToAdd -= 1; //добавили один суффикс
		if (activeNode == root && activeLength > 0)//когда активная нода была корнем
		{
			activeLength--;//уменьшаем длину на 1(удалили первый элемент из пути)
			activeEdge = i - suffixLeftToAdd + 1; //изменяем активное ребро
		}
		else 
			if (activeNode != root)
				activeNode = activeNode->suffixLink;//следуем по суффиксной ссылке вверх по дереву
	}
}
void SuffixTree::setLeaf(SuffixTreeNode *node){//расстановка номером вершин и пометок листов
	if (node == NULL)  return;
	bool leaf = true;
	totalNumber++;//номер вершины увеличивается
	node->number = totalNumber;//номер вершины
	for (int i = 0; i < MAX_CHAR; i++)
	{
		if (node->children[i] != NULL)//текущий узел не лист
		{
			leaf = false;
			setLeaf(node->children[i]);
		}
	}
	if (leaf)//не было потомков у узла, тогда он лист
		node->leaf = true;
}

void SuffixTree::buildTree(string text)
{
	this->text = text;
	int len = text.length();

	for (int i = 0; i < len; i++)//определение начала второй строчки
		if (text[i] == '$')
		{
			posSeparate = i + 1;
			break;
		}
	//Создаём корневой узел
	int *minusOne = new int();
	*minusOne = -1;
	root = createNewNode(-1, minusOne);
	activeNode = root; //изначально точкой роста является корень

	for (int i = 0; i< len; i++)//добавляем в дерево элементы текста посимвольно
		pushNode(i);
	setLeaf(root);
}
void SuffixTree::printTree(){//печать дерева
	if (root == NULL)//дерево пусто
		cout << "Tree is empty" << endl;
	else
	{
		queue<SuffixTreeNode*> ochered;//очередь для обхода в ширину
		ochered.push(root);
		while (!ochered.empty())//пока очередь не пуста
		{
			SuffixTreeNode *tmp = ochered.front();
			for (int i = 0; i < MAX_CHAR; i++)//смотрим всех детей вершины
				if (tmp->children[i])
				{
					cout << "Edge from " << tmp->number << " to " << tmp->children[i]->number << " with text: "; //выводим информацию о ребре
					for (int j = tmp->children[i]->begin; j <= *tmp->children[i]->end; j++)// и строку на нём
						cout << text[j];
					if (tmp->children[i]->leaf == false)
						cout << " ||| Suffix link from "<< tmp->children[i]->number << " to " << tmp->children[i]->suffixLink->number;
					cout << endl;
					ochered.push(tmp->children[i]);//добавляем в очередь ребенка вершины
				}
			ochered.pop();
		}
	}
}

int SuffixTree::searchString(SuffixTreeNode *node, int len){//поиск позиций подстроки
	bool firstStr = false, secondStr = false; //результат поиска first или second строки в листах
	if (node->leaf == false)
	{
		for (int i = 0; i < MAX_CHAR; i++)
		{
			if (node->children[i] != NULL)//текущий узел не лист
			{
				int res = searchString(node->children[i], len + lengthOfEdge(node->children[i]));
				if (res == 1)
					firstStr = true;
				else
					if (res == 2)
						secondStr = true;
					else
					{
						firstStr = true;
						secondStr = true;
					}
			}
		}
		if (firstStr && secondStr)
		{
			if (len > maxDepth)
			{
				maxDepth = len;
				startIndex = *node->end - maxDepth + 1;
			}
			return 0;
		}
		else
		{
			if (firstStr)
				return 1;
			if (secondStr)
				return 2;
		}
	}
	else
	{
		if (node->begin >= posSeparate)
			return 2;
		else
			return 1;
	}
	return 3;
}
string SuffixTree::getMaxString(){//возвращает максимальную общую подстроку двух строк
	searchString(root, 0); //сам поиск строки
	string res = "";
	if (maxDepth > 0)
	{
		for (int i = startIndex; i < startIndex + maxDepth; i++)//запись символов в результирующую строчку
			res += text[i];
		return res;
	}
	else
		return "No common strings";
}


bool checkCorrect(string str){//проверка, чтобы среди текста не было лишнего символа разделителя
	int len = str.length();
	for (int i = 0; i < len; i++)
		if (str[i] == '$' || str[i] == '#')
			return false;
	return true;
}

int main()
{
	ifstream in("input.txt");
	if (in.is_open() == false)//файл не был открыт - ошибка
	{
		cout << "File input.txt wasn't open" << endl;
		return 1;
	}

	string str1, str2; //первая и вторая исходные строки

	//читаем строчки из файла
	in >> str1;
	in >> str2;
	in.close();

	if (str1 == "" || str2 == ""){//если в файле было недостаточно данных для составления двух строк
		cout << "File is empty! Input strings from the keyboard : " << endl;
		cout << "Input first string : ";
		do{
			cin >> str1;
		} while (str1 == "");
		cout << "Input second string : ";
		do{
			cin >> str2;
		} while (str2 == "");
		//записываем эти строки во входной файл
		ofstream wr("input.txt");
		wr << str1 << endl << str2;
		wr.close();
	}

	if (!checkCorrect(str1) || !checkCorrect(str2))//проверка на отсутствие разделителей в изначальных строчках
	{
		cout << "Delete separator-symbols '$' and '#' from your strings" << endl;
		return 1;
	}

	string text = str1 + "$" + str2 + "#";// текст по которому строится суффиксное дерево
	cout << "_____________________________________________________________" << endl << "Your strings are " << str1 << " and " << str2 << endl;
	cout << "Buildings suffix tree for " << text << endl;

	SuffixTree *tree = new SuffixTree();//создание дерева
	tree->buildTree(text);//его построение
	tree->printTree();//печать всех рёбер

	string commonStr;//общая строка
	cout << "_____________________________________________________________" << endl;
	commonStr = tree->getMaxString(); //получение максимальной строки
	if (commonStr != "No common strings")
		cout << "Longest common string for " << str1 << " and " << str2 << " is: " << commonStr << endl;
	else
		cout << commonStr << endl;
	ofstream out("output.txt");
	out << commonStr;//запись максимальной общей строки в файл
	out.close();
	return 0;
}