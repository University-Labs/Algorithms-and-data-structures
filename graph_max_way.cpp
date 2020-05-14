//Найти максимальный простой путь между двумя заданными вершинами графа, заданного списковой структурой.
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <iterator> 
#include <list>
#include <queue> // очередь
#include <stack> // стек

using namespace std;

class node{//один элемент списка смежности
private: int key;//ключ
		 int weight;//вес вершины (здесь не пригодится)
public:
	node(){
		int key = 0;
		int weight = 1;
	}
	node(int key){
		this->key = key;
		weight = 1;
	}
	int Key(){
		return key;
	}
	int Weight(){
		return weight;
	}
};
const bool operator< (node &v1, node &v2)//для сортировки списка перегружаем оператор
{
	return v1.Key() < v2.Key();
}
class graphVertex{//список смежности для одной вершины
public: list<node> *list_sm;//список
		graphVertex(){
			list_sm = new list<node>();
		}
		void addItem(int key){//добавление элемента
			if (key > 0)
			{
				node a(key);//создание нового элемента списка
				list_sm->push_back(a);//добавление его к списку
			}
			list_sm->sort();//сортируем по возрастанию
		}
		void printString(){//печать одной строки
			list<node>::iterator it;
			for (it = list_sm->begin(); it != list_sm->end(); it++)
				cout << it->Key() << " ";
		}
};
void PrintDFS(int startVertex, graphVertex graph[], int count){//обходд в глубину
	int *nodes = new int[count]; //массив вершин
	for (int i = 0; i < count; i++)
		nodes[i] = 0; //изначально все вершины не посещённые
	stack<int> stack; // стек с порядком посещения вершин
	list<node>::reverse_iterator it; //для передвижения по списку смежных вершин

	stack.push(startVertex - 1);//первая вершина в стеке
	while (!stack.empty())//пока стек не пустой
	{
		int currNode = stack.top(); //текущая вершина
		stack.pop(); //извлекаем её
		if (nodes[currNode] == 2) continue;//уже были на этой вершине

		nodes[currNode] = 2;//стартовая вершина - посещённая
		for (it = graph[currNode].list_sm->rbegin(); it != graph[currNode].list_sm->rend(); it++)//проходим список с конца на начало
		{
			if (nodes[it->Key() - 1] != 2)//если вершину ещё не посетили
			{
				stack.push(it->Key() - 1);//записываем в стек
			}
		}
		cout << currNode + 1 << " ";
	}
	delete[] nodes;
}
void PrintBFS(int startVertex, graphVertex graph[], int count){//обход в ширину
	int *nodes = new int[count]; //массив вершин
	for (int i = 0; i < count; i++)
		nodes[i] = 0; //изначально все вершины не посещённые
	queue<int> queue; // стек с порядком посещения вершин
	list<node>::iterator it; //для передвижения по списку смежных вершин

	queue.push(startVertex - 1);

	while (!queue.empty())//пока очередь не пуста
	{
		int currNode = queue.front();//текущая вершина - вершина очереди
		queue.pop();// извлекаем обработанную вершину
		nodes[currNode] = 2;//посетили эту вершину
		for (it = graph[currNode].list_sm->begin(); it != graph[currNode].list_sm->end(); it++)//проходим список вершин с начала до конца
		{
			if (nodes[it->Key() - 1] == 0)//если вершину ещё не посетили
			{
				nodes[it->Key() - 1] = 1;//посетили её
				queue.push(it->Key() - 1);//записываем в стек
			}
		}
		cout << currNode + 1 << " "; // выводим номер вершины
	}
}
class rasst{//вспомогательный класс для назождения минимального простого пути
public:int rassto;//расстояние до этой вершины
	   int visit;//посещена или нет
	   rasst(){
		   rassto = visit = 0;
	   }
};
static list<int> maxWay; //список, содержащий максимальный простой путь
void MaxWae(int currVertex, int endVertex, graphVertex graph[], int count, int visited[], int path[], int &pathLength);
void FindLongestWay(int startVertex, int endVertex, graphVertex graph[], int count){
	int *visited = new int[count];//индикатор того, была ли посещена i-я вершина
	int *path = new int[count]; //простой путь максимум общее количество звён в графе
	for (int i = 0; i < count; i++)
	{
		visited[i] = 0;
	}
	int length = 0;
	MaxWae(startVertex - 1, endVertex - 1, graph, count, visited, path, length);//функция нахождение максимального пути
}
void MinWae(int startVertex, int endVertex, graphVertex graph[], int count)//функция нахождения минимального пути
{
	stack<int> resultStack;
	
	rasst *nodes = new rasst[count]; //массив вершин
	queue<int> queue; // очередь с порядком посещения вершин
	list<node>::iterator it; //для передвижения по списку смежных вершин

	queue.push(startVertex - 1);
	bool end = false;
	while (!queue.empty())
	{
		int currNode = queue.front();//текущая вершина - вершина очереди
		queue.pop();// извлекаем обработанную вершину
		nodes[currNode].visit = 2;//посетили эту вершину
		int a = nodes[currNode].rassto;
		for (it = graph[currNode].list_sm->begin(); it != graph[currNode].list_sm->end(); it++)
		{
			if (nodes[it->Key() - 1].visit == 0)//если вершину ещё не посетили
			{
				nodes[it->Key() - 1].rassto = a + 1;//расстояние до етой вершины в глубину
				nodes[it->Key() - 1].visit = 1;//посетили её
				cout << "Now im in " << it->Key() << " and distance: " << nodes[it->Key() - 1].rassto << endl;
				queue.push(it->Key() - 1);//записываем в стек
				if (it->Key() == endVertex)
					end = true;
			}
		}
		if (end)
			break;
	}
	cout << "\n" << nodes[endVertex - 1].rassto << endl;
	delete[] nodes;
}
void MaxWae(int currVertex, int endVertex, graphVertex graph[], int count, int visited[], int path[], int &pathLength){//функция нахождения максимального из простых путей
	
	visited[currVertex] = 1; //посетили текущую вершину
	path[pathLength++] = currVertex;//записываем эту вершину в путь

	if (currVertex == endVertex)//если дошли до необходимой вершины
	{
		if (pathLength > maxWay.size())//нужно ли перезаписывать путь?
		{
			maxWay.clear();
			for (int i = 0; i < pathLength; i++)
				maxWay.push_back(path[i] + 1);
		}
	}
	else // если это не нужная нам вершина
	{
		//смотрим смежные вершины с данной
		list<node>::iterator it;
		for (it = graph[currVertex].list_sm->begin(); it != graph[currVertex].list_sm->end(); ++it)
			if (visited[it->Key() - 1] == 0)//если эту вершину ещё не посетили
			{
				MaxWae(it->Key() - 1, endVertex, graph, count, visited, path, pathLength);//рекурсивно ищем путь
			}
	} 

	pathLength--;//уменьшаем путь
	visited[currVertex] = 0;//удаляем вершину из посещённых
}
void WriteMatrixToFile(graphVertex graph[], int count){
	int **matrix = new int*[count];//матрица смежности
	for (int i = 0; i < count; i++)
		matrix[i] = new int[count];
	for (int i = 0; i < count; i++)//изначально зануляем матрицу
		for (int j = 0; j < count; j++)
			matrix[i][j] = 0;
	list<node>::iterator it;
	for (int i = 0; i < count; i++)//заполнение матрицы
	{
		for (it = graph[i].list_sm->begin(); it != graph[i].list_sm->end(); it++)
		{
			matrix[i][it->Key() - 1] = 1;//если смежная вершина, то 1
		}
	}
	ofstream write("matrix.txt");//открытие файла
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count - 1; j++)
			write << matrix[i][j] << ", ";//запись матрицы в файл
		write << matrix[i][count - 1];
		write << endl;
	}
	write.close();//закрытие файла
	for (int i = 0; i < count; i++)//очищение памяти
		delete[] matrix[i];
	delete[] matrix;
}
void PrintMatrixToScreen(graphVertex graph[], int count){
	int **matrix = new int*[count];//матрица смежности
	for (int i = 0; i < count; i++)
		matrix[i] = new int[count];
	for (int i = 0; i < count; i++)//изначально зануляем матрицу
		for (int j = 0; j < count; j++)
			matrix[i][j] = 0;
	list<node>::iterator it;
	for (int i = 0; i < count; i++)//заполнение матрицы
	{
		for (it = graph[i].list_sm->begin(); it != graph[i].list_sm->end(); it++)
		{
			matrix[i][it->Key() - 1] = 1;//если смежная вершина, то 1
		}
	}
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count - 1; j++)
			cout << matrix[i][j] << ", ";//печать на экран
		cout << matrix[i][count - 1];
		cout << endl;
	}
	for (int i = 0; i < count; i++)//очищение памяти
		delete[] matrix[i];
	delete[] matrix;
}

int num = 0;//номер при обходе
void dfs(int v, int p, graphVertex graph[], int count, bool used[], int parent[], int ftree[]) {
	used[v] = true;//зашли в эту вершину
	parent[v] = ftree[v] = num++; //номер обхода и 
	int children = 0;//количество потомков вершины
	list<node>::iterator it;
	for (it = graph[v].list_sm->begin(); it != graph[v].list_sm->end(); ++it) {
		int to = it->Key() - 1;
		if (to == p)  continue;
		if (used[to])
			ftree[v] = min(ftree[v], parent[to]);
		else {
			dfs(to, v, graph, count, used, parent, ftree);
			ftree[v] = min(ftree[v], ftree[to]);
			if (ftree[to] >= parent[v] && p != -1)
				cout << v + 1 << " ";
			++children;
		}
	}
	if (p == -1 && children > 1)
		cout << v + 1 << " ";
}
void FindSharnir(graphVertex graph[], int count){
	bool *visited = new bool[count];
	for (int i = 0; i < count; i++)
		visited[i] = false;
	int tin[50], fup[50];
	dfs(0, -1, graph, count, visited, tin, fup);
}


int _tmain(int argc, _TCHAR* argv[])
{
	int key; //для чтения из файла
	char symbol; //чтобы находить символ ":"
	ifstream read("inputList.txt");//файл, содержащий исходные списки рёбер
	if (read.is_open())//если файл открылся
	{
		int max_num = 0;
		while (read >> key)
		{
			read.get(symbol);
			if (key < 1){
				cout << "Incorrect file!" << endl;
				return 1;
			}	
			if (key > max_num)//определяем размер массива(графа)
			{
				max_num = key;
			}
		}
		if (max_num > 0)
		{
			read.clear();
			read.seekg(0, ios_base::beg); //Стать в начало файла
			graphVertex *graff = new graphVertex[max_num]; //создание графа в виде списков смежности
			int index = 0; // номер вершины, для которой написан список в файле
			while (read >> key)
			{
				if (key > 0)

				{
					if (read.get(symbol) && symbol == ':')//если символ читается и он двоеточие
					{
						index = key;//меняем номер списка смежности
					}
					else
					{
						graff[index - 1].addItem(key);//добавляем новую вершину в список
					}
				}
				else
				{
					cout << "Wrong data on file. End of working" << endl;
					return 1;
				}
			}

			cout << "Your graph is:" << endl;
			for (int i = 0; i < max_num; i++)    //печать списков смежности на экран
			{
				cout << "From " << i + 1 << " vertex: ";
				graff[i].printString();
				cout << endl;
			}
			
			int from, to; //откуда и куда
			
			cout << "Input  starting vertex: ";
			while (!(cin >> from) || from < 1 || from > max_num) // Проверка, что введено было именно правильное число
			{
				cin.clear();
				cin.sync();
				cout << "Try again(: ";
			}
			cout << "Input  end vertex: ";
			while (!(cin >> to) || to < 1 || to > max_num) // Проверка, что введено было именно правильное число
			{
				cin.clear();
				cin.sync();
				cout << "Try again(: ";
			}

			ofstream resultWay("MaxWay.txt");//для записи в файл максимального пути
			cout << "The longest way from "<< from << " to "<< to << endl;
			resultWay << "The longest way from " << from << " to " << to << endl;

			FindLongestWay(from, to, graff, max_num);//вызов функции поиска максимального пути

			if (maxWay.size() > 0)//если этот путь существует
			{
				list<int>::iterator it;
				for (it = maxWay.begin(); it != maxWay.end(); it++)//проходим от начала списка до конца
				{
					resultWay << *it << " ";
					cout << *it << " ";//выводим на экран элементы пути и записываем их в файл
				}
				cout << endl;
			}
			else//такого пути нет
			{
				resultWay << "Way doesn't exist" << endl;
				cout << "Way doesn't exist" << endl;
			}
			WriteMatrixToFile(graff, max_num);

			cout << "Sharnirs: ";
			FindSharnir(graff, max_num);
			delete[] graff;//очистка памяти
		}
		else//файл пуст
			cout << "File is empty" << endl;
	}
	else
	{
		cout << "File doesnt exist" << endl;
		ofstream tmp("inputList.txt");//создаём пустой файл с таким названием
		tmp.close();
	}

	read.close();//закрываем файл
	return 0;
}

