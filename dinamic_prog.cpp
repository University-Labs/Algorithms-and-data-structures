//Дано прямоугольное поле размером n*m клеток. 
//Можно совершать шаги длиной в одну клетку вправо или вниз. Посчитать, сколькими способами можно попасть из левой верхней клетки в правую нижнюю.
#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

long getAmountWays(int n, int m){//получение количества способов попасть в клетку n,m
	long **amountWays = amountWays = new long*[n];//матрица промежуточных результатов
	for (int i = 0; i < n; i++)
	{
		amountWays[i] = new long[m];
		amountWays[i][0] = 1;//количество способов пройти по строке - 1 для каждой клетки
	}
	for (int i = 0; i < m; i++)
		amountWays[0][i] = 1;//количество способов пройти по столбцу - 1 для каждой клетки

	for (int i = 1; i < n; i++)//цикл по строчкам
		for (int j = 1; j < m; j++)//цикл по столбцам
		{
			//попасть в клетку i,j мы можем или из клетки слева (i, j-1)
			//или из клетки сверху (i-1, j)
			if (amountWays[i][j - 1] + amountWays[i - 1][j] < 0)
				return -1;
			amountWays[i][j] = amountWays[i][j - 1] + amountWays[i - 1][j];
		}
	//проверка на переполнение
		return amountWays[n - 1][m - 1];
}


int _tmain(int argc, _TCHAR* argv[])
{
	int n, m;//размеры прямоугольного поля

	cout << "Input n and m:" << endl;
	do{ //ввод строчек поля
		cout << "n = ";
		cin >> n;
		cin.sync();
		cin.clear();
	} while (n < 1);
	do{ //ввод столбцов поля
		cout << "m = ";
		cin >> m;
		cin.sync();
		cin.clear();
	} while (m < 1);

	long amountWays = getAmountWays(n, m);//получить количество путей

	if (amountWays < 0)
		cout << "Number overflow" << endl;
	else
		cout << "Amount of ways from top-left to bottom-right corner is " << amountWays << endl;
	//запись исходных данных
	ofstream inp("input.txt");
	inp << n << " " << m;
	inp.close();
	//запись результата
	ofstream out("output.txt");
	out << amountWays;
	out.close();
	return 0;
}