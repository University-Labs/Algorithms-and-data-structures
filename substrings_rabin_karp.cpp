//Пусть алфавит содержит d символов, и пусть текст  и образец – случайные строки длины n и m соответственно. 
//Подсчитать среднее число холостых срабатываний алгоритма Рабина-Карпа.
#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <conio.h>
#include <list>

#define alpha "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" //62 symbols
#define simple 2147483647//(pow 2, 31) - 1
using namespace std;

string getRandomString(int length, int alphaLen){
	string returnStr = "";
	for (int i = 0; i < length; i++)
	{
		returnStr += alpha[rand() % alphaLen];
	}
	return returnStr;
}
list<int>* algRabinKarp(string text, string pattern, int d){
	int lenPattern = pattern.length();
	int lenText = text.length();
	list<int>* sameHashes = new list<int>();//список включающий индексы подстрок с равным образцу хэшом

	int hashPattern = 0;//хэш для образца
	int hashText = 0; //хэш для подстроки текста

	int h = 1; //вычислим pow(d, M - 1) чтобы избежать повторных вычислений
	for (int i = 0; i < lenPattern - 1; i++)
		h = (h * d) % simple;

	//Вычислим хэш для образца и первой подстроки текста
	for (int i = 0; i < lenPattern; i++)
	{
		hashPattern = (d * hashPattern + (int)pattern[i]) % simple;
		hashText = (d * hashText + (int)text[i]) % simple;
	}
	//проверка подстрок в тексте одна за другой в поиске равного образцу хэша
	for (int i = 0; i < lenText - lenPattern + 1; i++)
	{
		if (hashPattern == hashText)
		{
			//заносим в массив слово с равным хэшом
			sameHashes->push_back(i);
		}
		//Это слово не последнее, строим хеш для следующего
		if (i < lenText - lenPattern)
		{
			hashText = (d * (hashText - h * text[i]) + text[i + lenPattern]) % simple;
			if (hashText < 0)
				hashText += simple;
		}
	}
	return sameHashes;
}
string inputPatt(int d){ //функция ввода строки
	string pattern;//образец
	char* mass = new char(); //массив с символами алфавита
	bool isContain = false; //содержит или нет паттерн символы не из алфавита
	strncat(mass, alpha, d);
	do{
		cin >> pattern; //ввод образца
		if (pattern == "###") //на случай если пользователь хочет закончить ввод
			break;
		int len = pattern.length();
		for (int i = 0; i < len; i++)//проход по каждому символу образца
		{
			isContain = false;
			for (int j = 0; j < d; j++)
				if (pattern[i] == mass[j])//если он из текущего алфавита, то переходим к следующему символу образца
				{
					isContain = true;
					break;
				}
			if (!isContain) //символ не из алфавита
			{
				cout << "These symbols aren't contained in alphabet! Input new pattern" << endl;
				break;
			}
		}
	} while (!isContain); //пока не закончится цикл по образцу и соответственно не проверятся все его символы
	return pattern;
}
int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));

	bool choocePattern = false; //режим ввода образца
	int d = 10;		//длина алфавита
	int n = 1000;	//символов в тексте
	int m = 5;		//символов в образце
	//объявление текста и образца
	string text;
	string pattern;


	ofstream fileInp("input.txt");// файл с начальными данными

	cout << "Input length of alphabet (no more than 62): " << endl;
	do{
		cin >> d;
		cin.sync();
		cin.clear();
	} while (d < 1 || d > 62); //ввод длины алфавита

	cout << "Input length of text:\t";
	do{
		cin >> n;
		cin.sync();
		cin.clear();
	} while (n < 1); //ввод длины текста
	
	//выбор - ввод образца или рандомная генерация
	cout << "Selection:\nPress 1 to enter a pattern from the keyboard\nPress 2 to generate a random pattern." << endl;
	while (true)
	{
		char symb = _getch();
		if (symb == '1')
		{
			choocePattern = true;
			break;
		}
		if (symb == '2')
		{
			choocePattern = false;
			break;
		}
	}

	if (choocePattern == false) //если случайная генерация образца
	{
		cout << "Input length of pattern:\t";
		do{
			cin >> m;
			cin.sync();
			cin.clear();
		} while (m < 1); //ввод длины образца
	}

	//создание текста
	text = getRandomString(n, d);

	//запись его в файл
	fileInp << text;
	
	int amountFound = 0;
	int amountFaults = 0;

	cout << "Your text were written to file input.txt" << endl;
	fileInp.close();//закрытие входного файла

	for (int i = 0; i < 50; i++)
	{
		if (choocePattern) //ввод образца с клавиатуры
		{
			cout << "Input new pattern for searhing: " << endl;
			pattern = inputPatt(d);
			m = pattern.length();
			if (pattern == "###")
				break;
		}
		else//генерация случайного образца
		{
			pattern = getRandomString(m, d);
		}
		string name = "output" + to_string(i) + ".txt";
		ofstream fileOut(name);//файл со строками с равным хэшем
		fileOut << "Pattern on this test is:\t" << pattern << endl;
		//вызываем алгоритм Рабина-Карпа для text и pattern
		list<int> *sameHashes = algRabinKarp(text, pattern, d);//массив содержит индексы слов с совпавшим хэшем
		int amountSame = 0;//количество совпадений строк

		for (auto it = sameHashes->begin(); it != sameHashes->end(); it++) //проход по всем элементам массива с равными образцу хэшами
		{
			if (pattern == text.substr(*it, pattern.length()))//если строки равны
				amountSame++;//увеличиваем количество повторений в текста паттерна
			fileOut << text.substr(*it, pattern.length()) << endl;
		}

		cout << "______________________________" << endl;
		cout << "Test number " << i + 1 << endl;
		cout << "Finally:" << endl;
		cout << amountSame << " same strings" << endl; //количество повторений строки
		amountFound += amountSame; 
		cout << sameHashes->size() - amountSame << " idle operation" << endl;//количество холостых срабатываний
		amountFaults += sameHashes->size() - amountSame;
		fileOut.close();
	}

	cout << "_____________________________\nResult:" << endl;
	if (amountFaults + amountFound != 0)
	{
		cout << "Faults are happened in " << 100 * amountFaults / (amountFaults + amountFound) << "% of result" << endl; //вывод результата тестов	
	}

	else
		cout << "No same patterns on all tests" << endl;
	return 0;
}