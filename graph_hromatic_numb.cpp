//Найти хроматическое число графа, заданного матрицей инцидентности.
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <list>
#include <string>

using namespace std;

int getMaxPow(int **matrix, int V, int E, int *colors){//получение максимальной на текущий момент по степени вершины
	int currMax = 0;//текущая минимальная степень
	int currMaxNum = -1;//этот текущий номер
	for (int i = 0; i < V; i++)//проходим по всем вершинам
	{
		if (colors[i] == -1)//если они ещё не разукрашены
		{
			int power = 0;//счётчик её степени
			for (int j = 0; j < E; j++)//проходим по всем ребрам для данной вершины
				if (matrix[i][j] != 0)//если ребро есть
					power++;//увеличиваем степень вершины
			if (power >= currMax)//если эта мощность выше чем максимальная
			{
				currMax = power;//заменяем эту степень
				currMaxNum = i;//и номер вершины
			}
		}
	}
	return currMaxNum;//возвращаем максимальную вершину
}

void colorPrinting(int num, int **matrix, int V, int E, int*colors){//разукрашивание вершины num
	list<int> adj;//список из смежных с num вершин
	for (int j = 0; j < E; j++)//проходим по всем рёбрам
	{
		if (matrix[num][j] != 0)//если вершина num инцидента какому-то ребру
			for (int i1 = 0; i1 < V; i1++)//то ищем вторую вершину, инцидентную ребру
				if (matrix[i1][j] != 0 && i1 != num)//когда нашли
				{
					adj.push_back(i1);//заносим в список вершин
					break;
				}
	}
	list<int>::iterator it;

	int *minColor = new int[V + 1];//для того, чтобы определять минимальный доступный цвет
	for (int i = 0; i < V + 1; i++)
		minColor[i] = i + 1;
	for (it = adj.begin(); it != adj.end(); it++)//проходим по списку
	{
		if (*it != -1)
			minColor[colors[*it] - 1] = 0;//зануляем те цвета, которые уже есть в смежных вершинах
	}
	int min;//выбираем минимальный номер среди доступных цветов
	for (min = 0; min < V + 1; min++)
		if (minColor[min])
			break;
	colors[num] = minColor[min];//назначаем вершине num этот минимальный цвет
}

int _tmain(int argc, _TCHAR* argv[])
{
	int V, E;// количество строк в матрице(вершин), количество столбцов в матрице(рёбер)
	ifstream read("input.txt");//файл для считывания матрицы
	if (!read.is_open())//файл не открылся
	{
		cout << "File wasn't open!" << endl;
		return 1;
	}
	else
	{
		string s;
		char f;
		V = 0;
		E = 0;
		while (getline(read, s))//подсчитываем количество строк в матрице(вершин)
		{
			V++;
		}
		read.clear();
		read.seekg(0, ios_base::beg); //Стать в начало файла
		
		while (read.get(f)){//подсчитываем количество столбцов в матрице(рёбер)
			if (f == '\n')
				break;
			if (isdigit(f))
				E++;
		}
		read.clear();
		read.seekg(0, ios_base::beg); //Стать в начало файла

		int **matrix = new int*[V];//создаём матрицу инцидентности
		for (int i = 0; i < V; i++)
			matrix[i] = new int[E];
		for (int i = 0; i < V; i++)//пишем в матрицу инцидентности из файла
		{
			for (int j = 0; j < E; j++)
			{
				if (i != 0 || j != 0)//с учётом запятой
					read >> f;
				read >> matrix[i][j];//чтение числа
				if (matrix[i][j] > 1 || matrix[i][j] < -1)//защита от некорректного ввода
				{
					cout << "Wrong matrix!" << endl;
					return 1;
				}
			}
		}
		if (E == 0 || V == 0)
		{
			cout << "File is empty\n";
			return 1;
		}
		if (!read.eof())//если не был достигнут конец файла
		{
			cout << "File is wrong!" << endl;
			return 1;
		}
		
		//проверка корректности матрицы инцидентности
		for (int j = 0; j < E; j++)
		{
			int count2 = 0;//если в ребре не 2 вершины, то матрицa неверная
			for (int i = 0; i < V; i++)
				if (matrix[i][j] != 0)
					count2++;
			if (count2 != 2)
			{
				cout << "Matrix is broken!" << endl;
				return 1;
			}
		}

		//печать матрицы на экран
		cout << "Matrix of Your graph is: " << endl;
		for (int i = 0; i < V; i++)
		{
			for (int j = 0; j < E; j++)
				cout << matrix[i][j] << "\t";
			cout << endl;
		}

		int *colors = new int[V];//массив из цветов для каждой вершины
		for (int i = 0; i < V; i++)//изначально все неокрашены
			colors[i] = -1;

		ofstream write("output.txt");//файл с результатом
		
		while (true)
		{
			int a = getMaxPow(matrix, V, E, colors);//получаем вершину с наибольшей степенью
			if (a == -1)//если ПП вернула -1, то ни одной вершины уже нет, даже со степенью 0
				break;
			colorPrinting(a, matrix, V, E, colors);//вызываем окраску для вершины a
		}
		int max = 0;//для поиска хроматического числа
		for (int i = 0; i < V; i++)//печатаем все цвета на экран и в файл
		{
			cout << "Color of " << i + 1 << " is -> " << colors[i] << endl;
			write << "Color of " << i + 1 << " is -> " << colors[i] << endl;
			if (colors[i] > max)//параллельно ищем максимальный цвет, т.е. хроматическое число графа
				max = colors[i];
		}
		//печать хроматического числа
		cout << "So, chromatic number of this graph is: " << max << endl;
		write << "So, chromatic number of this graph is: " << max << endl;
	}
	return 0;
}

