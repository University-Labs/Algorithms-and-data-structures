//Требуется по заданной строке s, произведя некоторых её препроцессинг, 
//научиться за O(log|s|) отвечать на запросы наибольшего общего префикса (longest common prefix, lcp)
// для двух произвольных суффиксов с позициями i и j.
#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <math.h>
#include <fstream>

using namespace std;

int getMaxChar(string text){//возвращает максимальный номер символа в строке
	int maxnum = (int)text[0];
	int len = text.length();
	for (int i = 1; i < len; i++)//проход по каждому символу
	{
		int curnum = (int)text[i];
		if (curnum > maxnum)//если текущий больше максимального, то заменяем его
			maxnum = curnum;
	}
	return maxnum;
}
int getMinChar(string text){
	int mnum = (int)text[0];
	int len = text.length();
	for (int i = 1; i < len; i++)//проход по каждому символу
	{
		int curnum = (int)text[i];
		if (curnum < mnum)//если текущий меньше минимального, то заменяем его
			mnum = curnum;
	}
	return mnum;
}
string makeSuffix(int num, int *p, string str)//возвращает num-суффикс строки str
{
	string strRes;
	for (int i = p[num]; i < str.length(); i++)//проходим от символа p[num] до конца строки
		strRes += str[i];//добавляем каждый символ строки к результату
	return strRes;
}

int findLCP(int firstpos, int secondpos, string str, int **c){//Возвращает длину общего префикса для позиций firstpos и secondpos
	int log_n = (int)log2(str.length());
	int temppos = firstpos;
	int len = 0;//длина совпавшего префикса
	for (int pow2 = log_n; pow2 >= 0; pow2--)//проходим по классам эквивалентности от конца к началу
	{
		if (c[pow2][firstpos] == c[pow2][secondpos])//Если классы эквивалентности равны
		{
			len += 1<<pow2;//добавляем к длине префикса сдвиг
			firstpos += 1 << pow2;//сдвигаемся вправо
			secondpos += 1 << pow2;
		}
	}
	if ((int)str.length() - len < 0) //на случай ввода одинаковой позиции i и j
		return (int)str.length() - temppos;
	else
		return len;
}

int _tmain(int argc, _TCHAR* argv[])
{
	string text;//исходный текст
	cout << "Press 1 to input string from the keyboard\nPress 2 to input string from the file" << endl;
	bool decision;//ввод с клавы или с файла
	while (true)
	{
		char symb = _getch();
		if (symb == '1')
		{
			decision = true;
			break;
		}
		if (symb == '2')
		{
			decision = false;
			break;
		}
	}
	if (decision == true)//ввод с клавиатуры
	{
		cout << "Input your string: " << endl;
		ofstream source("input.txt");
		cin >> text;//читаем строку с клавиатуры
		source << text;//пишем в исходный файл
		source.close();
	}
	else// ввод с файла
	{
		ifstream in("input.txt");
		if (in.is_open()) //если файл был открыт
		{
			in >> text;//считали оттуда строку
			if (text.length() == 0)//если она пуста
			{
				cout << "string is empty!" << endl;
				return 2;
			}
			cout << "Your string is: " << text << endl;
		}
		else//файл не был открыт
		{
			cout << "Error of the file" << endl;
			return 1;
		}
	}


	int length = text.length() + 1;//длина текста + 1(дописываем символ в конец)
	int log_n = (int)log2(length) + 1; //Количество шагов при поиске

	int **c = new int*[log_n + 1]; //массив для хранения классов эквивалентности с каждого шага
	for (int i = 0; i < log_n + 1; i++)
		c[i] = new int[length];

	int *p = new int[length]; //суффиксный массив

	int sizeMass = getMaxChar(text) + 2; //максимальный диапазон элементов, встречающихся в строке
	vector<int> amountSymb(sizeMass, 0); //массив подсчёта повторений символов

	//ДОБАВЛЯЕМ К СТРОКЕ ДОПОЛНИТЕЛЬНЫЙ СИМВОЛ В КОНЕЦ, КОТОРЫЙ БУДЕТ ОКАНЧИВАТЬ строку
	string oldText = text;
	text += getMinChar(text) - 1;

	//формирование суффиксного массива для циклических сдвигов длины 1
	for (int i = 0; i < length; i++) //подсчёт числа повторений каждого элемента
		amountSymb[text[i]]++;
	for (int i = 1; i < sizeMass; ++i) //подсчёт числа элементов предшествующих заданному
		amountSymb[i] += amountSymb[i - 1];

	for (int i = length - 1; i >= 0; i--) //формирование суффиксного массива с помощью массива предшествующих элементов
		p[--amountSymb[text[i]]] = i;

	//формирование классов эквивалентности для длины 1
	c[0][p[0]] = 0;//первый по алфавитному порядку суффикс принадлежит классу эквивалентности 0
	int currClass = 1;
	for (int i = 1; i < length; ++i)  //для всех остальных символов в лексикографическом порядке
	{
		if (text[p[i]] != text[p[i - 1]])  
			currClass += 1;//если они не равны, то увеличиваем текущий класс
		c[0][p[i]] = currClass - 1; //задаём класс эквивалентности
	}
	//сортировка для длин больше 1
	int *pn = new int[length];//перестановка в порядке сортировки по вторым эл-ам
	int *cNew = new int[length];//новые классы эквивалентности

	for (int h = 0; (1 << h) < length; ++h) //удваиваем шаг для обеспечения необходимой сложности
	{
		for (int i = 0; i < sizeMass; i++)//обнуляем счетчик повторений символов
			amountSymb[i] = 0;
		for (int i = 0; i < length; ++i) //сортируем по вторым половинам строки 2^h
		{
			pn[i] = p[i] - (1 << h);
			if (pn[i] < 0)  pn[i] += length;
		}
		for (int i = 0; i < length; i++) //сортируем по первым половинам сортировкой подсчётом
			++amountSymb[c[h][pn[i]]];//подсчёт элементов принадлежащих заданному классу эквивалентности
		for (int i = 1; i < currClass; i++) //подсчёт элементов с предшествующими классами
			amountSymb[i] += amountSymb[i - 1];
		for (int i = length - 1; i >= 0; i--) //формируем суффиксный массив для строки длины 2^h
			p[--amountSymb[c[h][pn[i]]]] = pn[i];

		//пересчитываем классы эквивалентности
		cNew[p[0]] = 0; //для первого лексикографически - класс 0
		currClass = 1;
		for (int i = 1; i < length; i++) 
		{
			int mid1 = (p[i] + (1 << h)) % length;
			int mid2 = (p[i - 1] + (1 << h)) % length;
			if (c[h][p[i]] != c[h][p[i - 1]] || c[h][mid1] != c[h][mid2]) //если у первой или второй половины не совпадают классы с предыдущим суффиксом
				currClass++;//переход к следующему номеру класса
			cNew[p[i]] = currClass - 1; //назначение класса очередному символу
		}
		for (int i = 0; i < length; i++)//копируем в строку c[h+1] классы эквивалентности
			c[h+1][i] = cNew[i];
	}
	//сдвигаем на элемент из конца строки
	for (int i = 1; i < length; i++)
		p[i - 1] = p[i];
	text = oldText;//восстанавливаем старый текст
	length = text.length();//и старую длину
	cout << "Suffix massive is: " << endl;
	for (int i = 0; i < length; i++)
		cout << i + 1 << ") pos num. " << p[i] << "; suf is:" << makeSuffix(i, p, text) << endl;//печатаем суффиксы строки в правильном порядке


	int firstpos, secondpos; //позиции для поиска наибольшего префикса
	//ввод первого индекса для поиска
	cout << "Input first pos for searching" << endl;
	do{
		cin >> firstpos;
		cin.sync();
		cin.clear();
		if (firstpos < 0 || firstpos > length - 1)
			cout << "Input pos again " << endl;
	} while (firstpos < 0 || firstpos > length - 1);
	//ввод второго индекса для поиска
	cout << "Input second pos for searching" << endl;
	do{
		cin >> secondpos;
		cin.sync();
		cin.clear();
		if (secondpos < 0 || secondpos > text.length() - 1)
			cout << "Input pos again " << endl;
	} while (secondpos < 0 || secondpos > text.length() - 1);

	cout << endl << "_______________________________________" << endl;
	//вычисление длины самого длинного общего префикса для firstpos и secondpos
	int lenLCP = findLCP(firstpos, secondpos, text, c);
	cout << "Length of Longest Common Prefix " << lenLCP << endl;

	ofstream out("output.txt");//файл для записи выходных данных
	cout << "Longest Common Prefix is: ";
	out << "Longest Common Prefix is: ";
	//печать самого длинного префикса
	for (int i = 0; i < lenLCP; i++)
	{
		cout << text[firstpos + i];
		out << text[firstpos + i];
	}
	cout << endl;
	out.close();

	return 0;
}

