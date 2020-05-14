//Найти самый короткий простой цикл во взвешенном графе, заданном взвешенной матрицей смежности. 
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#define INF 100000000

using namespace std;

class graph{
private:
	int **matrix;
	int amount = -1;

public:
	graph(int **matrix, int amount){
		this->matrix = new int*[amount];
		for (int i = 0; i < amount; i++)
		{
			this->matrix[i] = new int[amount];
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
	int **getMatrix(){
		return matrix;
	}
};

vector<int> shortest_cycle; //содержит кратчайший цикл
int shortestLength = INF;//содержит длину кратчайшего цикла

void print_cycle(vector<int> cycle, int **matrix, int amount, int a){//печать очередного цикла на экран и замена минимального при необходимости
	vector<int>::iterator it;
	int prev = -1;//предыдущий элемент в цикле
	bool flag = false;//выводим начиная с элемента, равного концу цикла
	int lengthOfWay = 0;//длина пути
	for (it = cycle.begin(); it != cycle.end(); it++)//проходим по всему вектору
	{
		if (*it == a + 1)//если дошли в векторе до нашего элемента, с которого начинается цикл
			flag = true;
		if (flag)//то начиная с него выводим на экран цикл
		{
			if (prev != -1)//если это вдруг первый элемент цикла, то длины пути до него ещё нет
				lengthOfWay += matrix[prev][*it - 1];//добавляем длину пути
			cout << *it << " ";//печатаем на экран
			prev = *it - 1;//обновляем предыдущий элемент цикла(чтобы можно было находить ребро в матрице смежности)
		}
	}
	cout << "with length " << lengthOfWay << endl;
	flag = false;
	if (lengthOfWay < shortestLength)//если новая длина меньше минимальной
	{
		vector<int> tmp_vector;//то записываем все элементы цикла в новый вектор
		for (it = cycle.begin(); it != cycle.end(); it++)
		{
			if (*it == a + 1)
				flag = true;
			if (flag)
				tmp_vector.push_back(*it);
		}
		shortestLength = lengthOfWay;//и обновляем минимальную длину
		shortest_cycle = tmp_vector;//и минимальный сам цикл
	}
}
void dfs(int v, graph gr, int *visited, vector<int> cycle){//собственно сам поиск циклов
	visited[v] = 1; //Если мы прошли через вершину, но пока не проверили все её смежные вершины
	cycle.push_back(v + 1);//заносим в вектор цикла эту вершину
	int **matrix = gr.getMatrix();
	for (int i = 0; i < gr.getAmount(); i++)//проходим по каждым смежным с v вершиной
		if (matrix[v][i] != 0 && visited[i] == 1)//если проходили через эту вершину, то очевидно цикл
		{
			cycle.push_back(i + 1);//добавляем в вектор цикла
			print_cycle(cycle, matrix, gr.getAmount(), i);//проверяем на минимальность
			cycle.pop_back();//извлекаем эту же вершину
		}
		else
			if (matrix[v][i] != 0 && visited[i] == 0)//если ещё не посещали эту вершину
			{
				dfs(i, gr, visited, cycle);//рекурсивно идём вглубь графа
			}
	int a = cycle[cycle.size() - 1];
	cycle.pop_back();//извлекаем этот элемент(как бы на шаг назад в графе)
	visited[v] = 2; //помечаем вершину как исследованную
	visited[a] = 0;
}

list<int> cutpoints;//список из шарниров
void searchCutpoint(int v, int parent, int **matrix, int amount, int *depth, int *minDepth, int *visited, int curDepth) {
	//v - текущая вершина, parent - её родитель в дереве обхода, matrix - матрица смежности,
	//depth - глубина каждой вершины в дереве обхода, minDepth - миним. глубина среди потомков v в дереве обхода, и минимальной глубины самой v
	//visited - посещена вершина или нет, curDepth - текущая глубина
	visited[v] = 1;//вершину посетили
	depth[v] = minDepth[v] = curDepth;
	int childCount = 0;//количество детей у вершины в дереве обхода в глубину
	for (int next = 0; next < amount; next++)//проходим по всем соседям v
	{
		if (matrix[v][next] != 0)
		{
			if (next == parent)//если попался непосредственный родитель v, то ничего не делаем
				continue;
			if (visited[next] == 0)//если сосед ещё не был посещён
			{
				searchCutpoint(next, v, matrix, amount, depth, minDepth, visited, curDepth + 1);//обработка этой вершины
				childCount++;//количество детей у v увеличивается на 1
				minDepth[v] = min(minDepth[v], minDepth[next]);//обновляем minDepth(после возврата назад в вершину при обходе)
				if (minDepth[next] >= depth[v] && parent != -1)//Если не было обратного ребра
					cutpoints.push_back(v);
			}
			else
				minDepth[v] = min(minDepth[v], depth[next]);//Есть ребро в предка в дереве обхода
			if (parent == -1 && childCount > 1)//если при обходе в глубину у корня более 1 потомка
				cutpoints.push_back(v);
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	ifstream a("input.txt"); //файл для чтения
	ofstream b("output.txt"); //файл для записи
	if (a.is_open())
	{
		int **matrix, amount; //список смежности и его размер
		if (!(a >> amount))//считываем размер матрицы
		{
			cout << "Wrong file!";
			return 1;
		}
		if (amount < 1)//некорректное число размера матрицы
		{
			cout << "Wow! Your graph is very small!";
			return 1;
		}
		matrix = new int*[amount];//матрица смежности
		for (int i = 0; i < amount; i++)
			matrix[i] = new int[amount];

		for (int i = 0; i < amount; i++)
			for (int j = 0; j < amount; j++)
			{
				char ff;//чтобы запятую считать)
				ff = a.get();
				if (!(a >> matrix[i][j]))//заполняем матрицу смежности
				{
					cout << "Error in file!"; return 1;
				}
				
			}

		graph *gr = new graph(matrix, amount);//сам граф
		vector<int> cycle; //для хранения цикла
		
		cout << "Your graph is: " << endl;
		cout << "----------------------------------------------------" << endl;
		for (int i = 0; i < amount; i++)
		{
			for (int j = 0; j < amount; j++)
				cout << matrix[i][j] << " ";
			cout << endl;
		}
		cout << "-----------------------------------------------------" << endl;
		cout << endl;
		/*
	   //НАХОЖДЕНИЕ ТОЧЕК СОЧЛЕНЕНИЯ ГРАФА
		int *visited = new int[amount];//для хранения истории посещённых вершин
		for (int i = 0; i < amount; i++)
			visited[i] = 0;//изначально ни одну вершину мы не посетили
		int *depth = new int[amount]; //хранит время захода в вершину
		for (int i = 0; i < amount; i++)
			depth[i] = -1;
		int *minDepth = new int[amount];//самая низкая глубина соседей(в дереве поиска в глубину) и самой вершины
		for (int i = 0; i < amount; i++)
			minDepth[i] = -1;

		cout << "Cutpoints are: " << endl;
		searchCutpoint(0, -1, matrix, amount, depth, minDepth, visited, 0);
		cutpoints.sort();
		cutpoints.unique();//удаление повторяющихся элементов
		if (cutpoints.size() > 0)//вывод шарниров
			for (auto it = cutpoints.begin(); it != cutpoints.end(); it++)
				cout << "Vertex " << *it << ";" << endl;
		else
			cout << "No cutpoints" << endl;
			*/

	}
	else
		cout << "File doesnt exist" << endl;
	return 0;
}
