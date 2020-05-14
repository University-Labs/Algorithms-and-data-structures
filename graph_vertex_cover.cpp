//Выбор переводчиков.
//Предположим, что организации нужно нанять переводчиков с французского, немецкого, греческого, итальянского, испанского, русского и китайского
//языков на английский и что имеется пять кандидатур А, В, С, D и Е.
//Каждая кандидатура владеет только некоторым собственным подмножеством из указанного выше множества языков и требует вполне определенную зарплату. 
//Необходимо решить, каких переводчиков (с указанных выше языков на английский) надо нанять, чтобы затраты на зарплату были наименьшими. 
//Очевидно, что это — задача о наименьшем покрытии.
//Если, например, требования на оплату труда у всех претендентов одинаковые и группы языков, на которых они говорят, указаны ниже в матрице Т, 
//то решение задачи будет таким: нужно нанять переводчиков В, С и D.

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <list>

using namespace std;

list<int> curr; //текущий набор переводчиков
list<int> minCombo; //содержит список с минимальным набором переводчиков
double minPrice = -1; //содержит минимальную цену набора
void formCombo(int **massiv, int translators, int languages, bool *is_activ, double* prices)/*Сама функция нахождения и выбора переводчиков*/{
	int numLang = -1;//Изначально неизвестно, какой из языков ещё не включён в текущее множество
	for (int j = 0; j < languages; j++)//есть ли не покрытый ещё язык и получение его номер
		if (is_activ[j] == false)//если ещё не добавили во множество
		{
			numLang = j;//номер языка, сочетание с котором мы ищем
			break;
		}
	if (numLang == -1)//если все языки уже во множестве
	{
		double currPrice = 0; //цена текущего набора
		list<int>::iterator it;
		for (it = curr.begin(); it != curr.end(); it++)//находим стоимость данного набора
			currPrice += prices[*it];
		if (minPrice == -1 || currPrice < minPrice)//Если эта стоимость меньше минимальной
		{
			minCombo = curr;//то заменяем набор переводчиков
			minPrice = currPrice;//и стоимость
		}
		return;
	}
	for (int i = 0; i < translators; i++)//проходим по каждому переводчику
	{
		if (massiv[i][numLang] == 1)//и смотрим, знает ли он текущий для поиска язык
		{//добавляем этого переводчика ко множеству
			curr.push_back(i);
			bool *tmp = new bool[languages];//сохраняем во временный массив текущую включаемость в набор языков
			for (int k = 0; k < languages; k++)
				tmp[k] = is_activ[k];
 			for (int j = 0; j < languages; j++)//затем изменяем массив включения языков, добавляя туда те языки, которые изучает i-ый переводчик
				if (massiv[i][j] == 1)
					is_activ[j] = true;
			formCombo(massiv, translators, languages, is_activ, prices);//рекурсивно вызываем эту же функцию, но теперь уже массив is_activ изменён
			for (int k = 0; k < languages; k++)//заменяем массив назад
				is_activ[k] = tmp[k];
			curr.pop_back();//извлекаем из текущего набора последнего переводчика
		}
	}
	return;
}
void formMatrix(int **massiv, int translators, int languages){//сформировать матрицу смежности для построения графа
	int index = 0;//передвижение внутри таблицы
	int **matrix = new int*[translators + languages];//матрица смежности (очевидно что данные не из таблицы равны 0)
	for (int i = 0; i < translators + languages; i++)
	{
		matrix[i] = new int[translators + languages];
	}
	ofstream matrF("matrix.txt");//туда пишем матрицу
	for (int i = 0; i < translators + languages; i++)
	{
		index = 0;//на каждой строке обнуляем индекс прохода по таблице
		for (int j = 0; j < translators + languages; j++)
		{
			if (j > translators - 1 && i < translators)//если находимся в правом верхнем угле, соответствующему значениям из таблицы
				matrix[i][j] = massiv[i][index++];
			else
				matrix[i][j] = 0;//иначе они все нулевые
		}
	}
	for (int i = 0; i < translators + languages; i++)//пишем эту матрицу в файл
	{
		for (int j = 0; j < translators + languages; j++)
			matrF << matrix[i][j] << " ";
		matrF << endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	ifstream r("input.txt");//отсюда входная таблица
	ifstream rp("prices.txt");//отсюда цены каждого переводчика
	if (r.is_open() && rp.is_open())
	{
		double a; //число для считывания
		char f;
		int b;
		int translators = 0;//всего переводчиков
		int languages = 0;//всего языков
		while (rp >> a)//подсчёт переводчиков в файле
		{
			if (a < 0)
			{
				cout << "Wrong price!";
				return 1;
			}
			translators++;
		}
		while (r >> b)//подсчёт языков в файле
		{
			languages++;
			if (r.get(f))
				if (f == '\n')
					break;
		}
		r.clear();
		rp.clear();
		r.seekg(0, ios_base::beg); //Стать в начало файла
		rp.seekg(0, ios_base::beg); //Стать в начало файла
		if (translators == 0 || languages == 0)
		{
			cout << "Files are empty!" << endl;
			return 1;
		}
		int **massiv = new int*[translators];//массив переводчики - языки
		double *prices = new double[translators]; //зарплаты переводчикам
		for (int i = 0; i < translators; i++)
			massiv[i] = new int[languages];

		for (int i = 0; i < translators; i++)//считываем зарплаты из файла
			rp >> prices[i];
		for (int i = 0; i < translators; i++) //считываем матрицу переводчик/языки
			for (int j = 0; j < languages; j++)
			{
				r >> massiv[i][j];
				if (massiv[i][j] > 1 || massiv[i][j] < 0)//обработка некорректных значения  матрицы
				{
					cout << "File is broken!!";
					return 1;
				}
			}
		if (!r.eof())//если не дошли до конца файла
		{
			cout << "Supernumerary data";
			return 1;
		}
		formMatrix(massiv, translators, languages);
		cout << "\t";
		for (int i = 0; i < languages; i++)
			cout << "b" << i+1 << "\t";
		cout << endl;
		for (int i = 0; i < translators; i++)
		{
			cout << "A" << i + 1 << "\t";
			for (int j = 0; j < languages; j++)
				cout << massiv[i][j] << "\t";
			cout << "with price " << prices[i];
			cout << endl;
		}
		r.close();
		rp.close();

		bool *is_activ = new bool[languages];//для всех языков активные ли они в текущей комбинации или ещё нет
		for (int i = 0; i < languages; i++)
		{
			is_activ[i] = false;
		}
		formCombo(massiv, translators, languages, is_activ, prices);//формируем набор переводчиков минимальной стоимости
		ofstream res("result.txt");
		if (minPrice >= 0)//если нашли такой набор
		{
			res << "Minimal combination of translators is: ";
			cout << "Minimal combination of translators is: ";
			list<int>::iterator it;
			for (it = minCombo.begin(); it != minCombo.end(); it++)//печатаем на экран и в файл
			{
				res << "A" << *it + 1 << " ";
				cout << "A" << *it + 1 << " ";
			}
			cout << ". And You should pay him " << minPrice << "$" << endl;
			res << ". And You should pay him " << minPrice << "$" << endl;
		}
		else
		{
			cout << "You haven't any combination" << endl;
			res << "You haven't any combination" << endl;
		}
	}
	else
		cout << "Error of open file";
	return 0;
}

