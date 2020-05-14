//Задано число N, где N – количество точек на плоскости. Построить стягивающее дерево так, чтобы оно было оптимальным. Оптимальное дерево имеет минимальную сумму длин входящих в него ребер. 
//Все ребра – это расстояния между вершинами, заданными координатами точек на плоскости. 
//Для решения задачи использовать алгоритм Борувки.
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class graph{
private:
	float **matrix;
	int amount = -1;

public:
	graph(float **matrix, int amount){
		this->matrix = new float*[amount];
		for (int i = 0; i < amount; i++)
		{
			this->matrix[i] = new float[amount];
		}
		this->amount = amount;
		for (int i = 0; i < amount; i++)
			for (int j = 0; j < amount; j++)
				this->matrix[i][j] = matrix[i][j];
	}
	void printMatrix(){
		if (amount > -1)
		{
			for (int i = 0; i < amount; i++)
			{
				for (int j = 0; j < amount; j++)
					cout << matrix[i][j] << " ";
				cout << endl;
			}
		}
	}
	int getAmount(){
		return amount;
	}
	float **getMatrix(){
		return matrix;
	}
};

vector<pair<float, float>> points; //массив точек на плоскости

int minKey(int key[], bool includedVX[], int amount)//нахождение минимального пути среди ещё не добавленных в остовое дерево вершин
{
	int min = INT_MAX;
	int minNum = -1;
	for (int v = 0; v < amount; v++)//проходим по всем элементам key
		if (includedVX[v] == false && key[v] < min)//если вершина ещё не добавлена в остовое и путь до неё меньше минимального
			min = key[v], minNum = v;//то минимальная вершина - эта
	return minNum;
}
void Pryma(int **graph, int amount)
{
	int *parent = new int[amount];//Массив, в котором хранится минимальный остов
	int *key = new int[amount];//пути из которых будет выбираться минимальный элемент
	bool *includedVX = new bool[amount];//массив, где 0 - вершина ещё не в MST, 1 - вершина в MST

	for (int i = 0; i < amount; i++)//изначально все пути равны бесконечности, не посещены
		key[i] = INT_MAX, includedVX[i] = false;

	//в качестве начальной вершины ставим 0-ую
	key[0] = 0;//путь до неё нуль
	parent[0] = -1; //у первого элемента в дереве нет родителя
	int u;

	//в остовом дереве amount вершин(все вершины графа)
	for (int i = 0; i < amount - 1; i++)
	{
		u = minKey(key, includedVX, amount);//выбираем вершину, путь к которой минимальный, и она не добавлена в остовое дерево 
		if (u == -1)
			break;
		includedVX[u] = true;//вершина добавлена
		for (int v = 0; v < amount; v++)//для каждой смежной с u вершины, еще не включённой в остов, обновляем путь
			if (graph[u][v] && includedVX[v] == false && graph[u][v] < key[v])
				parent[v] = u, key[v] = graph[u][v];
	}    
	if (u == -1)//значит не дерево
		cout << "WOW! Your graph is not connected!" << endl;
	else
	{
		printf("Edge \tWeight\n");
		for (int i = 1; i < amount; i++)
			printf("%d - %d \t%d \n", parent[i] + 1, i + 1, graph[i][parent[i]]);
	}
}
void Kruskal(graph gr){
	int *set = new int[gr.getAmount()];//определяет к какому множеству относится i-ая вершина
	int amount = gr.getAmount();
	for (int i = 0; i < amount; i++)
		set[i] = i;
	float **matrix = gr.getMatrix();
	vector < pair <float, pair<int, int>>> edges; //содержит рёбра
	for (int i = 0; i < amount; i++)
		for (int j = i; j < amount; j++)
			if (matrix[i][j] != 0)//составляем вектор из рёбер графа
				edges.push_back(make_pair(matrix[i][j], make_pair(i, j)));
	sort(edges.begin(), edges.end());//сортировка по возрастанию

	//результирующее дерево:
	vector<pair<float, pair<int, int>>> tree;

	for (int i = 0; i < edges.size(); i++)//проходим по каждому ребру
	{
		int from = edges[i].second.first;//откуда
		int to = edges[i].second.second;//куда
		if (set[from] != set[to]){//если они из разных множеств
			tree.push_back(edges[i]);//заносим в результирующее дерево
			int old_set = set[from];
			int new_set = set[to];
			for (int j = 0; j < amount; j++)
			{
				if (set[j] == old_set)//и полностью второе множество заносим в первое(объединяем их)
					set[j] = new_set;
			}
		}
	}
	//вывод остова
	int size = tree.size();
	if (size != amount - 1)//значит не дерево!
	{
		cout << "WOW! Your graph is not connected!" << endl;
	}
	else
	{
		printf("Edge \tWeight\n");
		for (int i = 0; i < tree.size(); i++)
			cout << tree[i].second.first + 1 << " - " << tree[i].second.second + 1 << "\t" << tree[i].first << endl;
	}

}
void Boruvka(graph gr)//Борувка
{
	ofstream f("result.txt"); //запись результата в файл
	int amount = gr.getAmount();
	float **matrix = gr.getMatrix();
	vector < pair <float, pair<int, int>>> edges; //содержит все рёбра графа(сначла вес, потом (u,v))
	for (int i = 0; i < amount; i++)
		for (int j = i; j < amount; j++)
			if (matrix[i][j] != 0)//составляем вектор из рёбер графа
				edges.push_back(make_pair(matrix[i][j], make_pair(i, j)));
	sort(edges.begin(), edges.end());//сортировка по возрастанию

	int *set = new int[gr.getAmount()];//определяет к какому множеству относится i-ая вершина
	for (int i = 0; i < amount; i++)//для каждой i-ой вершины изначально своё множество
		set[i] = i;

	int *cheapest = new int[amount]; //хранит индекс кратчайшего ребра включения для множества

	for (int v = 0; v < amount; ++v)
	{
		cheapest[v] = -1;//изначально неизвестны кратчайшие пути от каждого множества
	}

	int amountTrees = amount; //изначально  у нас amount деревьев по 1 элементу

	//пока не соединим все деревья в одно
	while (amountTrees > 1)
	{
		for (int v = 0; v < amount; ++v)
		{
			cheapest[v] = -1;
		}

		for (int i = 0; i < edges.size(); i++)//обновляем кратчайшее ребро для каждой компоненты связности
		{
			int setFrom = set[edges[i].second.first];//находим в каком множестве находятся вершины данного ребра
			int setTo = set[edges[i].second.second];
			if (setFrom == setTo)//если они лежат в одном множестве, то игнорируем это ребро
				continue;
			if (cheapest[setFrom] == -1 || edges[cheapest[setFrom]].first > edges[i].first)//если кратчайшей вершины в этой итерации цикла ещё нет, либо вес этого ребра больше чем текущего
				cheapest[setFrom] = i;//меняем кратчайшее ребро для данной компоненты

			if (cheapest[setTo] == -1 || edges[cheapest[setTo]].first > edges[i].first)//аналогично для второй вершины ребра
				cheapest[setTo] = i;
		}
		for (int i = 0; i < amount; i++)//для каждой вершины добавляем в mst новое ребро
		{
			if (cheapest[i] != -1)//если есть кратчайшее ребро для этой вершины
			{
				int setFrom = set[edges[cheapest[i]].second.first];
				int setTo = set[edges[cheapest[i]].second.second];
				if (setFrom == setTo)
					continue;
				cout << "Line from " << edges[cheapest[i]].second.first + 1 << "(" << points[edges[cheapest[i]].second.first].first << "; " << points[edges[cheapest[i]].second.first].second << ") to " << edges[cheapest[i]].second.second + 1 << "(" << points[edges[cheapest[i]].second.second].first << "; " << points[edges[cheapest[i]].second.second].second << ") with weight " << matrix[edges[cheapest[i]].second.first][edges[cheapest[i]].second.second] << " included in MST" << endl;
				f << "Line from " << edges[cheapest[i]].second.first + 1 << "(" << points[edges[cheapest[i]].second.first].first << "; " << points[edges[cheapest[i]].second.first].second << ") to " << edges[cheapest[i]].second.second + 1 << "(" << points[edges[cheapest[i]].second.second].first << "; " << points[edges[cheapest[i]].second.second].second << ") with weight " << matrix[edges[cheapest[i]].second.first][edges[cheapest[i]].second.second] << " included in MST" << endl;
				//Объединение множеств
				for (int j = 0; j < amount; j++)
				{
					if (set[j] == setFrom)//и полностью второе множество заносим в первое(объединяем их)
						set[j] = setTo;
				}
				amountTrees--;//множеств стало меньше
			}
		}
	}
	return;
}

int _tmain(int argc, _TCHAR* argv[])
{
	ifstream file("input.txt");
	if (!file.is_open())
	{
		cout << "NO FILE! END OF PROGRAMM" << endl;
		return 1;
	}
	int N; //количество точек
	if (!(file >> N)){
		cout << "File is empty" << endl;
		return 1;
	}
	if (N < 1)
	{
		cout << "Wrong amount of points" << endl;
		return 1;
	}
	float **massiv = new float*[N];
	for (int i = 0; i < N; i++)//массив расстояний точек
		massiv[i] = new float[N];
	float x, y; //координаты
	int i = 0;
	while (file >> x && file >> y)//читаем координаты из файла
	{
		points.push_back(make_pair(x, y)); //массив координат
		i++;
		if (i > N)
		{
			cout << "Wrong points!";
			return 1;
		}
	}
	if (i < N)
	{
		cout << "Wrong points!";
		return 1;
	}
	cout << "Your points:" << endl;
	for (int i = 0; i < N; i++) //вывод всех точек
	{
		cout << "Point num. " << i + 1 << "(" << points[i].first << ";" << points[i].second << ")" << endl;
	}
	for (int i = 0; i < N; i++)//формируем массив из расстояний между точками (формируем матрицу смежности графа)
		for (int j = 0; j < N; j++)
		{
			//корень из квадрат расстояний между точками
			massiv[i][j] = sqrt((points[i].first - points[j].first) * (points[i].first - points[j].first) + (points[i].second - points[j].second) * (points[i].second - points[j].second));
		}
	ofstream resM("matrix.txt");
	cout << "Matrix of weight" << endl;
	for (int i = 0; i < N; i++)//печатаем матрицу на экран и в файл
	{
		for (int j = 0; j < N; j++)
		{
			cout.setf(std::ios::fixed);
			cout.precision(2);
			cout << massiv[i][j] << " ";
			resM.setf(std::ios::fixed);
			resM.precision(2);
			resM << massiv[i][j] << " ";
		}
			resM << endl;
			cout << endl;
	}
	resM.close();
	graph *gr = new graph(massiv, N);//создать граф
	cout << "Edges of MST:" << endl;
	Boruvka(*gr);//выполнить задание
	file.close();
	return 0;
}

