//Сортировка с помощью разделения.
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <conio.h>

using namespace std;

struct element{//один элемент массива
	int first;//три числовых
	int second;
	int third;
	string fourth;// и два строковых поля
	string fifth;
};
int compare(element element1, element element2, int field);//функция сравнения двух элементов по полю field
void hoar(int left, int right, element* massive, int field1, int field2, int field3);//функция, которая сортирует массив
int randomNumber(){//случайное число 
	return rand() % 50;
}
string randomString(){//случайная строка длины 5
	string str;
	int index;
	char alpha[] = "abcdefghijklmnopqrstuvwxyz";
	for (int i = 0; i < 5; i++)
	{
		index = rand() % 23;
		str += alpha[index];
	}
	return str;
}
class massive{//массив
private:
	element *array;//сам массив
	int size = 0;//размер массива
public:
	void create_random();//создать с рандомными данными
	void create_from_file();//считать из файла
	void sort();//отсортировать
	void print();//распечатать
};


void massive::create_random(){//создать с рандомными данными
	cout << "Create new massive with random data" << endl;
	if (size != 0)//если массив уже есть
	{
		cout << "You already have data. Old data will be destroyed. Press Enter" << endl;
		if (_getch() == 13)//по нажатию на Enter удаляет старый массив
		{
			delete[] array;
			size = 0;
			array = nullptr;
		}
		else//иначе старый массив сохраняется
		{
			cout << "Old massive was saved" << endl;
			ofstream in("input.txt");//и помещается в файл с исходным массивом
			for (int i = 0; i < size; i++)
				in << array[i].first << "\t" << array[i].second << "\t" << array[i].third << "\t" << array[i].fourth << "\t" << array[i].fifth << endl;
			return;
		}
	}
	int amount;//количество
	cout << "Input size of data massive: ";//ввод размера массива данных
	do{
		cin >> amount;
		cin.clear();                
		fflush(stdin);              //очищаем поток ввода
	} while (amount < 1);

	//создание массива данных
	size = amount;
	array = new element[size];

	//заполнение массива рандомными данными;
	ofstream in("input.txt");
	for (int i = 0; i < size; i++)
	{
		array[i].first = randomNumber();
		array[i].second = randomNumber();
		array[i].third = randomNumber();
		array[i].fourth = randomString();
		array[i].fifth = randomString();
		in << array[i].first << "\t" << array[i].second << "\t" << array[i].third << "\t" << array[i].fourth << "\t" << array[i].fifth << endl;//запись в файл
	}
	cout << "Massive was successfully created" << endl;
}
void massive::create_from_file(){//считать из файла
	cout << "Create new massive from the file" << endl;
	ifstream a("file.txt");//file for read
	if (!a.is_open())//файл не открылся, создаем его по новой
	{
		ofstream b("file.txt");
		b.close();
		a.close();
		a.open("file.txt");//и открываем его же
	}
	int count = 0;//amount of elements
	string str;
	while (getline(a, str))//count amount of strings in file
	{
		count++;
	}
	a.clear();
	a.seekg(0, ios_base::beg); //Стать в начало файла
	if (size != 0)//если массив уже есть
	{
		delete[] array; array = nullptr;
	}
	size = count; //size of array

	//create massive 
	array = new element[size];
	int index = 0;
	char *string = new char[1024];
	ofstream in("input.txt");//файл куда записывается исходный массив
	while (index < size)//form massive
	{
		a.getline(string, 1024);//читаем строку из файла и делим её на отдельные части
		array[index].first = atoi(strtok(string, "\t"));
		array[index].second = atoi(strtok(NULL, "\t"));
		array[index].third = atoi(strtok(NULL, "\t"));
		array[index].fourth = strtok(NULL, "\t");
		array[index].fifth = strtok(NULL, "\t");
		in << array[index].first << "\t" << array[index].second << "\t" << array[index].third << "\t" << array[index].fourth << "\t" << array[index].fifth << endl;

		index++;//двигаемся к следующему элементу массива
	}
	cout << "Massive was loaded from the file" << endl;
}
void massive::print(){//распечатать
	cout << "Your massive is: " << endl;
	if (size == 0)//массива нет
		cout << "Massive is empty" << endl;
	else
	{
		for (int i = 0; i < size; i++)
			cout << array[i].first << "\t" 
				<< array[i].second << "\t"
				<< array[i].third << "\t"
				<< array[i].fourth << "\t" 
				<< array[i].fifth << endl;
	}
}
void massive::sort(){
	cout << "Sorting starts" << endl;
	if (size != 0)//массив есть
	{
		int firstfield = 0;//поля для сортировки
		int secondfield = 0;
		int thirdfield = 0;
		do
		{
			cout << "Input first field for sorting" << endl;
			do{//считываем с клавиатуры номер 1 поля для сортировки
				cin >> firstfield;
				cin.clear();                //сбрасываем коматозное состояние cin
				fflush(stdin);              //очищаем поток ввода
			} while (firstfield < 1 || firstfield > 5);
			cout << "Input second field for sorting" << endl;
			do{//считываем с клавиатуры номер 2 поля для сортиовки
				cin >> secondfield;
				cin.clear();                //сбрасываем коматозное состояние cin
				fflush(stdin);              //очищаем поток ввода
			} while (secondfield < 1 || secondfield > 5 || firstfield == secondfield);
			cout << "Input third field for sorting" << endl;
			do{//считываем с клавиатуры номер 3 поля для сортировки
				cin >> thirdfield;
				cin.clear();                //сбрасываем коматозное состояние cin
				fflush(stdin);              //очищаем поток ввода
			} while (thirdfield < 1 || thirdfield > 5 || thirdfield == secondfield || thirdfield == firstfield);

			cout << "The data will be sorted by fields " << firstfield << ", then " << secondfield << " and then " << thirdfield << endl;
			cout << "Everything is correct? Press Enter" << endl;
		} while (_getch() != 13);//подтвердить поля нажатием Enter

		hoar(0, size - 1, array, firstfield, secondfield, thirdfield);//сама сортировка

		cout << "Sorting was finished" << endl;
		ofstream out("output.txt");//запись результирующего отсортированного массива в файл
		for (int i = 0; i < size; i++)
			out << array[i].first << "\t" << array[i].second << "\t" << array[i].third << "\t" << array[i].fourth << "\t" << array[i].fifth << endl;
	}
	else
		cout << "Massive is empty" << endl;
}

void hoar(int left, int right, element* massive, int field1, int field2, int field3){
	bool stop = false;//флаг нахождения элемента для перестановки
	int currL = left;//текущий левый элемент для перестановки
	int currR = right;//текущий правый элемент для перестановки
	element centerEl = massive[(currL + currR) / 2];//опорный элемент
	do
	{
		stop = false;//элемент ещё не найден
		while (stop == false)//пока не нашли левый элемент для перестановки
		{
			if (compare(massive[currL], centerEl, field1) == 1)//слева(поле 1) > опорного(поле 1)
				stop = true;//необходима перестановка
			if (compare(massive[currL], centerEl, field1) == 0)//если элементы равны по 1 полю
			{
				if (compare(massive[currL], centerEl, field2) == 1)//слева(поле 2) > опорного(поле 2)
					stop = true;//необходима перестановка
				if (compare(massive[currL], centerEl, field2) == 0)//если элементы равны по 2 полю
				{
					if (compare(massive[currL], centerEl, field3) == 1)//слева (поле 3) > опорного (поле 3)
						stop = true;//нужна перестановка
					if (compare(massive[currL], centerEl, field3) == 0)//если равны по трём полям
						stop = true;//переставляем
				}
			}
			if (stop == false)//если не нужна перестановка
				currL++;//сдвигаем указатель
		}
		stop = false;
		while (stop == false)//пока не нашли правый элемент для перестановки
		{
			if (compare(massive[currR], centerEl, field1) == -1)//элемент справа меньше опорного по полю 1
				stop = true;
			if (compare(massive[currR], centerEl, field1) == 0)//если равен по полю 1
			{
				if (compare(massive[currR], centerEl, field2) == -1)//меньше по полю 2
					stop = true;
				if (compare(massive[currR], centerEl, field2) == 0)//равен по полю 2
				{
					if (compare(massive[currR], centerEl, field3) == -1)//меньше по полю 3
						stop = true;
					if (compare(massive[currR], centerEl, field3) == 0)//равен по полю 3
						stop = true;
				}
			}
			if (stop == false)//не нужна перестановка
				currR--;//сдвиг указателя
		}

		if (currL <= currR)//если были найдены элементы на неправильных позициях
		{
			element tmp = massive[currL];//меняем их местами
			massive[currL] = massive[currR];
			massive[currR] = tmp;

			currR--; currL++;
		}
	} while (currL < currR);
	if (left < currR)//запускаем просмотр для массивов меньшего размера
		hoar(left, currR, massive, field1, field2, field3);
	if (right > currL)//запускаем просмотр для массивов  меньшего размера
		hoar(currL, right, massive, field1, field2, field3);
}
int compare(element element1, element element2, int field){
	switch (field)//сравнение двух элементов массива по полю field
	//return 1 - больше первый; return 0 - равны; return -1 - больше второй
	{
	case 1:
	{
		int first = element1.first;
		int second = element2.first;
		if (first == second)
			return 0;
		if (first > second)
			return 1;
		else
			return -1;
		break;
	}
	case 2:
	{
		int first = element1.second;
		int second = element2.second;
		if (first == second)
			return 0;
		if (first > second)
			return 1;
		else
			return -1;
		break;
	}
	case 3:
	{
		int first = element1.third;
		int second = element2.third;
		if (first == second)
			return 0;
		if (first > second)
			return 1;
		else
			return -1;
		break;
	}
	case 4:
	{
		string first = element1.fourth;
		string second = element2.fourth;
		if (first == second)
			return 0;
		if (first > second)
			return 1;
		else
			return -1;
		break;
	}
	case 5:
	{
		string first = element1.fifth;
		string second = element2.fifth;
		if (first == second)
			return 0;
		if (first > second)
			return 1;
		else
			return -1;
		break;
	}
	default:
		return 0;
		break;
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));

	massive mass;//массив из 5 полей

	bool finish = false;
	cout << "Choose the number of option:" << endl;
	cout << "1. Load massive from the file" << endl;
	cout << "2. Generate random massive" << endl;
	cout << "3. Print massive" << endl;
	cout << "4. Sort massive" << endl;
	cout << "5. Exit" << endl << endl << endl;
	while (true)
	{
		finish = false;
		switch (_getch()){
		case '1': cout << "1. "; mass.create_from_file(); break;
		case '2': mass.create_random(); break;
		case '3': mass.print(); break;
		case '4': mass.sort(); break; 
		case '5': finish = true; break;
		default: break;
		}
		if (finish)
			break;
	}
	return 0;
}
