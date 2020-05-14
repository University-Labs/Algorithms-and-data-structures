//Указать множество вершин графа, доступных из заданной вершины на путях, веса которых не превышают заданной величины. 
//Граф задан списковой структурой. Возможен отрицательный вес ребер.
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <iterator> 
#include <list>
#include <queue> // очередь
#include <stack> // стек
#define INF 1000000;//почти бесконечность

using namespace std;

class node{//один элемент списка смежности
private: int key;//ключ
		 int weight;//вес вершины (здесь не пригодится)
public:
	node(){
		int key = 0;
		int weight = 1;
	}
	node(int key, int weight){
		this->key = key;
		this->weight = weight;
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
		void addItem(int key, int weight){//добавление элемента
			if (key > 0)
			{
				node a(key, weight);//создание нового элемента списка
				list_sm->push_back(a);//добавление его к списку
			}
			list_sm->sort();//сортируем по возрастанию
		}
		void printString(){//печать одной строки
			list<node>::iterator it;
			for (it = list_sm->begin(); it != list_sm->end(); it++)
				cout << it->Key() << "(W: " << it->Weight() << ") ";
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
			matrix[i][it->Key() - 1] = it->Weight();//если смежная вершина, то 1
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
			matrix[i][it->Key() - 1] = it->Weight();//если смежная вершина, то 1
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

class InfoWay{
public:
	int length; //длина
	int from;	//откуда пришли
	InfoWay(){
		this->length = INF;
		this->from = -1;
	}
	InfoWay(int length, int from){
		this->length = length;
		this->from = from;
	}
};

void Dijkstra(int startVertex, graphVertex graph[], int count){//алгоритм дейкстры
	InfoWay* marks = new InfoWay[count];//пометки(содержат путь до этой вершины и предыдущую вершину
	marks[startVertex - 1].length = 0;//до стартовой вершины путь 0
	list<node>::iterator it;
	for (it = graph[startVertex - 1].list_sm->begin(); it != graph[startVertex - 1].list_sm->end(); it++)//прохрдим по каждой смежной с начальной вершине
	{
		marks[it->Key() - 1].from = startVertex;//заменяем предыдущую
		marks[it->Key() - 1].length = it->Weight();//и путь
	}
	bool *used = new bool[count];//массив пройдённых вершин
	for (int i = 0; i < count; i++)
		used[i] = false;

	while (true)
	{
		int minW = INF;//минимальный путь
		int minNUM = 0;
		for (int i = 0; i < count; i++)//проходим по всем вершинам
			if (!used[i] && marks[i].length < minW)//если еще не посетили и её путь меньше минимального
			{
				minW = marks[i].length;//обновляем минимальный путь
				minNUM = i + 1;//и номер
			}
		if (minNUM == 0)//если нет непройдённых вершин
			break;
		used[minNUM - 1] = true;//вершину с минимальынм путём отмечаем как посещённую
		list<node>::iterator it;
		for (it = graph[minNUM - 1].list_sm->begin(); it != graph[minNUM - 1].list_sm->end(); it++)//проходим все смежные вершины
		{
			if (marks[it->Key() - 1].length > marks[minNUM - 1].length + it->Weight() && !used[it->Key() - 1])//если вершина ещё не пройдена и текущая метка больше чем новый путь
			{
				marks[it->Key() - 1].length = marks[minNUM - 1].length + it->Weight();
				marks[it->Key() - 1].from = minNUM;//меняем их
			}
		}
	}

	int a = INF;
	cout << "Shortest way from " << startVertex << " are:" << endl;
	for (int i = 0; i < count; i++)
	{
		cout << "To " << i + 1 << ": ";

		list<int> way;
		if (i + 1 == startVertex)
			cout << startVertex << " ";
		else
		{
			if (marks[i].length == a)//если метка пути бесконечная
				cout << "NO WAY! ";
			else
			{
				for (int j = i; j != startVertex - 1;)//идём по массиву меток от конца до начала
				{
					way.push_front(j + 1);//заносим их в список
					j = marks[j].from - 1;
				}
				way.push_front(startVertex);//дописываем туда стартовый элемент
				list<int>::iterator it;
				for (it = way.begin(); it != way.end(); ++it)//распечатываем последовательность пути
				{
					cout << *it << " ";
					if (*it != *way.rbegin())
						cout << "- ";
				}
			}
		}
		if (marks[i].length == a)//если вес бесконечен
			cout << " with weight INFINITY" << endl;
		else
			cout << " with weight " << marks[i].length << endl;//печатаем вес
	}
}
void Ford(int startVertex, graphVertex graph[], int count){
	int *ways = new int[count];//список содержащий длину путей до i-й вершины
	bool is_changed = false;//были ли на очередной итерации изменения
	int *adressOfWay = new int[count];//массив, содержащий предыдущую вершину кратчайшем пути
	for (int i = 0; i < count; i++)
		adressOfWay[i] = -1;
	for (int i = 0; i < count; i++)
		ways[i] = INF;
	list<node>::iterator it;
	int a = INF;
	ways[startVertex - 1] = 0;//длина пути до стартовой вершины нулевая
	for (int k = 0; k < count; k++)
	{
		is_changed = false;//изначально в итерации нет изменений
		for (int i = 0; i < count; i++)//проходим по всем рёбрам графа
		{
			for (it = graph[i].list_sm->begin(); it != graph[i].list_sm->end(); it++)
			{
				int start = i + 1;//стартовая вершина
				int finish = it->Key();//конечная вершина
				int weight = it->Weight();//её вес
				if (ways[start - 1] < a)
					if (ways[start - 1] + weight < ways[finish - 1])//Если короче пройти через ещё одну вершину
					{
						ways[finish - 1] = ways[start - 1] + weight;//то заменяем этот путь
						is_changed = true;//произошли изменения в итерации
						adressOfWay[finish - 1] = start - 1;//указываем предыдущую в пути вершину в массив
					}
			}
		}
		if (!is_changed)//если не было изменений
			break;//просмотр закончен
	}

	//Extra-searching for negative cycles
	is_changed = false;//нет изменений
	for (int i = 0; i < count; i++)//проход по каждому ребру
	{
		for (it = graph[i].list_sm->begin(); it != graph[i].list_sm->end(); it++)
		{
			int start = i + 1;
			int finish = it->Key();
			int weight = it->Weight();
			if (ways[start - 1] < a)
				if (ways[start - 1] + weight < ways[finish - 1])
				{
					ways[finish - 1] = ways[start - 1] + weight;
					is_changed = true;//произошли изменения
					adressOfWay[finish - 1] = start - 1;
				}
		}
	}
	if (is_changed)//если были изменения - мы имеем цикл
		cout << "Oops, you have a negative cycle!" << endl;
	else
	{
		cout << "Shortest way from " << startVertex << " are:" << endl;
		for (int i = 0; i < count; i++)//смотрим каждую вершину
		{
			if (ways[i] == a)//если путь бесконечен то его нет
			{
				cout << "To " << i + 1 << ": No way" << endl;
			}
			else
			{
				vector<int> path;
				for (int curr = i; curr != -1; curr = adressOfWay[curr])//проходим по массиву последовательности путей
				{
					path.push_back(curr);//заносим в вектор
				}
				reverse(path.begin(), path.end());//переворачиваем вектор
				cout << "To " << i + 1 << ": ";
				for (size_t h = 0; h < path.size(); h++)//выводим получившийся путь
					cout << path[h] + 1 << " ";
				cout << "With weight " << ways[i];
				cout << endl;
			}
		}
	}
}


void printVertexFrom(int startVertex, int maxWeight, graphVertex graph[], int count)//распечатать вершины, доступные из Start, путь до которых не превышает Weight
{
	ofstream res("output.dat");
	int *ways = new int[count];//массив, в котором хранятся длины путей до каждой вершины
	for (int i = 0; i < count; i++)
		ways[i] = INF;//путь до всех вершин изначально бесконечен
	ways[startVertex - 1] = 0; //путь до начальной вершины - нулевой
	bool is_changed = false;//Вдруг на очередной итерации не произошло изменений, таким образом можно произвести выход из алгоритма поиска
	list<node>::iterator it;
	int a = INF;
	for (int k = 0; k < count; k++)
	{
		is_changed = false;//на очередной итерации нет изменений
		for (int i = 0; i < count; i++)//проходим по каждой вершине графа
		{
			for (it = graph[i].list_sm->begin(); it != graph[i].list_sm->end(); it++)//смотрим каждую вершину её списка смежности
			{//дуга (a,b) веса w
				int start = i + 1;//вершина a
				int finish = it->Key();//вершина b
				int weight = it->Weight();//вес пути w
				if (ways[start - 1] < a)
					if (ways[start - 1] + weight < ways[finish - 1])//Если дешевле пройти через ещё одну вершину
					{
						ways[finish - 1] = ways[start - 1] + weight;//заменяем этот путь
						is_changed = true;//произошли изменения за эту итерацию
					}
			}
		}
		if (!is_changed)//на итерации не было изменений - заканчиваем обход
			break;
	}

	//Extra-searching for negative cycles
	is_changed = false;
	for (int i = 0; i < count; i++)//если после всех итераций у нас всё ещё происходят изменения - то мы имеем цикл
	{
		for (it = graph[i].list_sm->begin(); it != graph[i].list_sm->end(); it++)//проходим по всем вершинам снова
		{
			int start = i + 1;
			int finish = it->Key();
			int weight = it->Weight();
			if (ways[start - 1] < a)
				if (ways[start - 1] + weight < ways[finish - 1])
				{
					ways[finish - 1] = ways[start - 1] + weight;
					is_changed = true;
				}
		}
	}

	if (is_changed)//если изменения были
	{
		cout << "Oops, you have a cycle!" << endl;//то цикл
		res << "Oops, you have a cycle!" << endl;
	}
	else
	{
		bool hm = false;
		res << "Available from " << startVertex << "  with a weight not exceeding " << maxWeight << ": " << endl;
		cout << "Available from " << startVertex << "  with a weight not exceeding " << maxWeight << ": " << endl;// иначе выводим вершины, удовл. весу
		for (int i = 0; i < count; i++)//Просмотр каждой вершины
		{
			if (ways[i] <= maxWeight)//если путь до этой вершины меньше либо равен макс весу
			{
				hm = true;
				cout << i + 1 << " ";//то выводим эту вершину
				res << i + 1 << " ";
			}
		}
		if (!hm)
		{
			cout << "none";
			res << "none";
		}
		cout << endl;
		res << endl;
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	int key, weight; //для чтения из файла
	char symbol; //чтобы находить символ ":"
	ifstream read("inputList.txt");//файл, содержащий исходные списки рёбер
	if (read.is_open())//если файл открылся
	{
		int max_num = 0;
		symbol = ' ';
		while (read >> key)
		{
			if (symbol != ',')
			{
				if (key < 1){
					cout << "Incorrect file!" << endl;
					return 1;
				}
				if (key > max_num)//определяем размер массива(графа)
				{
					max_num = key;
				}
			}
			read.get(symbol);
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
						read >> weight;
						graff[index - 1].addItem(key, weight);//добавляем новую вершину в список
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

			int startVertex, maxWeight; //начальная вершина и вес
			cout << "Input start vertex: ";
			while (!(cin >> startVertex) || startVertex < 1 || startVertex > max_num) // Проверка, что введено было именно правильное число
			{
				cin.clear();
				cin.sync();
				cout << "Try again(: ";
			}
			Ford(startVertex, graff, max_num);

			cout << "Input max weight: ";
			while (!(cin >> maxWeight)) // Проверка, что введено было именно число
			{
				cin.clear();
				cin.sync();
				cout << "Try again(: ";
			}

			printVertexFrom(startVertex, maxWeight, graff, max_num);

			WriteMatrixToFile(graff, max_num);
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

