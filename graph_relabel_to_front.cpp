//Найти максимальный поток методом «поднять и в начало». 
//Увеличить пропускную способность заданного ребра в с раз и подсчитать максимальный поток. Сравнить число операций.
#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <string>

using namespace std;
vector<list<int>> neib; //вектор из списков, где каждый список содержит всех соседий для определенной вершины

void push(int u, int v, int **c, int **f, int *e){//метод проталкивания
	int min_num = min(c[u][v] - f[u][v], e[u]);//находим минимум из избытка в изначальной вершине и остаточной пропускной способности (u,v)
	f[u][v] += min_num;//пропускаем поток по этому ребру
	f[v][u] = -f[u][v];//отрицательный - по противоположному
	e[u] -= min_num;//Убираем избыток у начальной вершины
	e[v] += min_num;//Добавляем его в конечную
}
void lift(int u, int *h, int **c, int **f, int amount){//метод подъема вершины
	int curr_height = 2 * amount;//максимальная высота вершины
	list<int>::iterator it;
	for (it = neib[u].begin(); it != neib[u].end(); it++)//движемся по списку соседей вершины u
		if (c[u][*it] != f[u][*it] && h[*it] < curr_height)//и ищим минимальную из высот соседей в остаточной сети
			curr_height = h[*it];
	h[u] = curr_height + 1;//делаем высоту на 1 больше чем минимум
}
bool discharge(int u, int *h, int **c, int *e, int** f, int amount, int *opera){//сама операция разгрузки вершины
	bool change_h = false;//был ли осуществлён подъем вершины
	list<int>::iterator it;
	it = neib[u].begin();//первый сосед
	while (e[u] > 0)//пока есть избыток
	{
		if (it == neib[u].end())//Если мы просмотрели уже всех соседей и среди них нет доступных
		{
			opera[0] += 1;
			change_h = true;//значит мы изменяли высоту
			lift(u, h, c, f, amount);//поднимаем u
			it = neib[u].begin();//и просматриваем список соседей заново
		}
		else
		{
			int v = *it;
			if (c[u][v] > f[u][v] && h[u] == h[v] + 1)//если остаточная пропускная способность положительна и высоты различны не более чем на 1
			{
				opera[1] += 1;
				push(u, v, c, f, e);//проталкиваем жидкость
			}
			else
				it++;//иначе к след соседу u
		}
	}
	return change_h;//были ли подъемы вершины
}
void make_preflow(int *e, int ** c, int ** f, int amount, int src){//формирование предпотока и списка соседей
	neib.resize(amount);
	for (int i = 0; i < amount; i++)
		for (int j = 0; j < amount; j++)
			if (c[i][j] > 0 || c[j][i] > 0)//заносим в список, если есть ребро или обратное ему
				neib[i].push_back(j);

	for (int i = 0; i < amount; i++)
		if (c[src][i] > 0) {//для каждой вершины, которая смежна с истоком
			e[i] = c[src][i];//проталкиваем в неё жидкость, равную пропускной способности
			f[src][i] = c[src][i];
			f[i][src] = -f[src][i];
		}
}
int lifttofront(int **c, int** f, int *e, int *h, int src, int dest, int amount, int *opera){//метод поиска потока
	make_preflow(e, c, f, amount, src);//формируем предпоток
	list<int> L;//список из всех возможных для разгрузки вершин
	int currentV;
	for (int u = 0; u < amount; u++)
		if (u != src && u != dest)
			L.push_back(u);
	list<int>::iterator cur = L.begin();//берём первую вершину из этого списка
	while (cur != L.end()) //пока не дошли до конца списка
	{
		currentV = *cur;
		if (discharge(currentV, h, c, e, f, amount, opera)) {//если при разгрузке вершины currentV произошёл подъем её
			L.erase(cur);
			cur = L.insert(L.begin(), currentV); //то пишем её в начало списка
		}
		cur++;//движемся дальше по списку
	}
	return e[dest];//возвращаем весь избыток, который получился в стоке. Он и равен максимальному потоку
}

int _tmain(int argc, _TCHAR* argv[])
{
	ifstream read("input.txt");
	if (!read.is_open())
		cout << "Error of file input.txt" << endl;
	else
	{
		int* operations1 = new int[2];
		operations1[0] = 0;
		operations1[1] = 0;
		int *operations2 = new int[2];//число операций в ходе работы алгоритма
		operations2[0] = 0;
		operations2[1] = 0;
		int amount = 0;//количество вершин в графе
		string s; 	
		char ch;
		while (getline(read, s))//подсчитываем количество строк в матрице(вершин)
		{
			amount++;
		}
		read.clear();
		read.seekg(0, ios_base::beg); //Стать в начало файла
		int src = 0, dest = amount - 1; //что исток, а что сток

		int **f = new int*[amount];//предпоток
		int **c = new int*[amount];//пропускные способности(сеть)
		for (int i = 0; i < amount; i++)
		{
			f[i] = new int[amount];
			c[i] = new int[amount];
		}
		int *e = new int[amount];//избыточный поток для каждой вершины
		for (int i = 0; i < amount; i++)
			e[i] = 0;
		for (int i = 0; i < amount; i++)
			for (int j = 0; j < amount; j++)
				f[i][j] = 0;

		int *h = new int[amount];//функция высоты
		for (int i = 0; i < amount; i++)
			h[i] = 0;//изначально 0
		h[src] = amount;//для истока равна количеству вершин в графе

		/*Чтение матрицы смежности из файла*/
		for (int i = 0; i < amount; i++)//
			for (int j = 0; j < amount; j++)
				if (i == 0 && j == 0)
					read >> c[i][j];
				else
				{
					read.get(ch);
					read >> c[i][j];
				}
		cout << "Your graph matrix is: " << endl;
		for (int i = 0; i < amount; i++)
		{
			for (int j = 0; j < amount; j++)
				cout << c[i][j] << "\t";
				cout << endl;
		}

		int result = lifttofront(c, f, e, h, src, dest, amount, operations1);//вызов функции нахождения потока
		//печать потока на экран
		if (result == 0)//потока в сток нет
		{
			cout << "Flow is not exist" << endl;
			return 1;
		}

		cout << " Maximum flow(1st) is: " << result << endl;
		cout << "It consists of these edges: " << endl;
		for (int i = 0; i < amount; i++)
			for (int j = 0; j < amount; j++)
				if (f[i][j] > 0)
					cout << "(" << i << "; " << j << ") with flow: " << f[i][j] << "/" << c[i][j] << endl;

		cout << "Operation lift = " << operations1[0] << endl;
		cout << "Operation push = " << operations1[1] << endl;
		cout << "Input edge that you want to increase ";
		int u, v; double cap; //(u,v) - ребро, cap - раз
		do{
			cin >> u >> v;
		} while (u < 0 || v < 0 || u >= amount || v >= amount || c[u][v] == 0);
		cout << "How many times do you want to increase the edge?" << endl;
		do{
			cin >> cap;
		} while (cap < 0);

		c[u][v] *= cap;//увеличиваем ребро
		/*Снова зануляем остальные массивы*/
		for (int i = 0; i < amount; i++)
			e[i] = 0;
		for (int i = 0; i < amount; i++)
			for (int j = 0; j < amount; j++)
				f[i][j] = 0;
		for (int i = 0; i < amount; i++)
			h[i] = 0;//изначально 0
		h[src] = amount;//для истока равна количеству вершин в графе
		int result2 = lifttofront(c, f, e, h, src, dest, amount, operations2);
		cout << " Maximum flow(2nd) is: " << result2 << endl;
		cout << "It consists of these edges: " << endl;
		for (int i = 0; i < amount; i++)
			for (int j = 0; j < amount; j++)
				if (f[i][j] > 0)
					cout << "(" << i << "; " << j << ") with flow: " << f[i][j] << "/" << c[i][j] << endl;

		cout << "Operation lift = " << operations2[0] << endl;
		cout << "Operation push = " << operations2[1] << endl;

		cout << "So if you increase edge (" << u << "; " << v << ") in " << cap << " times" << endl;
		cout << "Operation Push would increase by " << operations2[0] - operations1[0] << endl;
		cout << "Operation Lift would increase by " << operations2[1] - operations1[1] << endl;
	}
	read.close();
	return 0;
}
