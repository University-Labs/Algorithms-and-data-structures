//Найти абсолютные центры и радиус неориентированного графа, предполагая, что веса всех вершин равны 1. Использовать итерационный метод.
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <list>
#define INF 100000000

using namespace std;

double floyd(double **matrix, int amount, double **ways){//поиск всех кратчайших путей в графе
	for (int i = 0; i < amount; i++)//формирование корректной матрицы дл¤ поиска
		for (int j = 0; j < amount; j++)
		{
			if (matrix[i][j] == 0)
				ways[i][j] = INF;
			else
				ways[i][j] = matrix[i][j];
			if (i == j)
				ways[i][j] = 0;
		}

	for (int k = 0; k < amount; k++)//јлгоритм ‘лойда
		for (int i = 0; i < amount; i++)
			for (int j = 0; j < amount; j++)
				ways[i][j] = min(ways[i][j], ways[i][k] + ways[k][j]);

	double max = 0;//дл¤ максимального числа
	for (int i = 0; i < amount; i++)//проходим по всей матрице и ищим максимальное число
		for (int j = 0; j < amount; j++)
		{
			if (ways[i][j] > max && ways[i][j] != INF)//≈сли число превосходит текущий максимум и путь существует
				max = ways[i][j];
		}
	return (max / 2);//возвращаем max/2, т.к. веса вершин по 1
}
double checkWay(double weight, double **ways, int amount, int u, int v, double lambda){//проверить, есть ли абсолютный центр на ребре (u,v)
	double add = 0.001;//шаг передвижени¤ по ребру
	double point = 0;//сдвиг по ребру (u,v)
	while (point <= weight)//ѕока сдвиг не дойдЄт до другого конца ребра
	{
		bool isCenter = true;//¤вл¤етс¤ ли точка на ребре центром
		for (int j = 0; j < amount; j++)//ѕросмотр путей до остальных вершин дл¤ u и v
		{
			if (ways[u][j] + point <= lambda || weight - point + ways[v][j] <= lambda)//если рассто¤ние от точки point до j-ой вершины меньше lambda
			{
				isCenter = true;
			}
			else
			{
				isCenter = false;//иначе эта точка не ¤вл¤етс¤ центром
				break;
			}
		}
		if (isCenter == true)//если центр найден
			break;
		point += add;//измен¤ем положение точки
	}
	if (point <= weight)//если точка располагаетс¤ на ребре
		return point;
	else
		return -1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	ifstream read("input.txt");//файл дл¤ чтени¤
	if (!read.is_open())
		cout << "Error of file input.txt" << endl;
	else
	{
		int amount = 0;//количество вершин в графе
		string s;
		char ch;
		while (getline(read, s))//подсчитываем количество строк в матрице(вершин)
		{
			amount++;
		}
		read.clear();
		read.seekg(0, ios_base::beg); //—тать в начало файла

		double **c = new double*[amount];//изначальна¤ матрица смежности
		double **ways = new double*[amount];//матрица кратчайших путей
		for (int i = 0; i < amount; i++)//
		{
			c[i] = new double[amount];
			ways[i] = new double[amount];
		}
		/*„тение матрицы смежности из файла*/
		for (int i = 0; i < amount; i++)//
			for (int j = 0; j < amount; j++)
			{
				if (i == 0 && j == 0)
				{
					read >> c[i][j];
				}
				else
				{
					read.get(ch);
					read >> c[i][j];
				}
			}
		read.close();
		//вывод матрицы
		cout << "Your graph matrix is: " << endl;
		for (int i = 0; i < amount; i++)
		{
			for (int j = 0; j < amount; j++)
				cout << c[i][j] << "\t";
			cout << endl;
		}

		ofstream write("output.txt");//дл¤ записи в файл
		list<pair< pair<int, int>, double>> centers;//содержит центры графа
		double lambda =  floyd(c, amount, ways);// изначальный максимальный вес пути
		for (int i = 0; i < amount; i++)
		{
			for (int j = 0; j < amount; j++)
				if (ways[i][j] == INF)//≈сли нет пути от какой то вершины, то нет абсолютного центра
				{
					write << "Here is no Absolute center!" << endl;
					cout << "Here is no Absolute center!" << endl;
					return 1;
				}
		}
				
		double delta = 0.001;//точность (дл¤ увеличени¤ максимально допустимого рассто¤ни¤)
		bool found = false;//сигнализатор того, был найден центр или нет
		while (!found)//пока не найдЄм центр
		{
			for (int i = 0; i < amount; i++)//проходим по каждому элементу матрицы смежности
				for (int j = 0; j < amount, i > j; j++)
				{
					if (c[i][j] != 0)//если он не нулевой, то ребро существует
					{
						double distance = checkWay(c[i][j], ways, amount, i, j, lambda);//вычисл¤ем рассто¤ние нa котором котором на ребре расолагаетс¤ центр
						if (distance != -1)//центр есть
						{
							found = true;
							centers.push_back(make_pair(make_pair(i, j), distance));//заносим в список центров
						}
					}
				}
			if (found)
				break;
			lambda += delta;//увеличиваем максимально допустимую длину пути
		}
		
		cout << "Centers of this graph are: " << endl;
		list<pair< pair<int, int>, double>>::iterator it;//дл¤ движени¤ по списку
																													if (lambda / (int)lambda < 1.001)
																														lambda = (int)lambda;
		for (it = centers.begin(); it != centers.end(); it++)//проход по списку и вывод всех центров														
		{
			write << "Center on the edge (" << it->first.first + 1 << "; " << it->first.second + 1 << ") on the distance from 1st = " << it->second << endl;
			cout << "Center on the edge (" << it->first.first + 1 << "; " << it->first.second + 1 << ") on the distance from 1st = " << it->second << endl;
		}
		write << "Graph radius = " << lambda << endl;//вывод радиуса графа
		cout << "Graph radius = " << lambda << endl;
	}
	return 0;
}
