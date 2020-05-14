//Сбалансированное многопутевое слияние.
#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <ctime>
#define STRING_MAX "~~~~~"

using namespace std;

struct element{//один элемент массива
	int first;//три числовых
	int second;
	int third;
	string fourth;// и два строковых поля
	string fifth;
	element(int first, int second, int third, string fourth, string fifth){
		this->first = first;
		this->second = second;
		this->third = third;
		this->fourth = fourth;
		this->fifth = fifth;
	}
	element(string in_str){
		std::istringstream strForSplit(in_str);
		string tmp;

		std::getline(strForSplit, tmp, '\t');//разделяем по символу табуляции (так записаны в файлах)
		first = atoi(tmp.c_str());
		std::getline(strForSplit, tmp, '\t');
		second = atoi(tmp.c_str());
		std::getline(strForSplit, tmp, '\t');
		third = atoi(tmp.c_str());
		std::getline(strForSplit, tmp, '\t');
		fourth = tmp;
		std::getline(strForSplit, tmp, '\t');
		fifth = tmp;
	}
	element(){ first = second = third = 0; fourth = fifth = ""; }
};
void openFiles(int amountFiles, vector<fstream> *files_A, vector<fstream> *files_B, int mode){//открывает заново файлы, либо переставляет файловый указатель в начало
	string filename1, filename2;
	if (mode == 1)//если читал A->B
	{
		for (int i = 0; i < amountFiles; i++)
		{
			files_A->at(i).close();//закрываю файлы A
			filename1 = "A-" + to_string(i + 1) + ".txt";
			files_A->at(i).open(filename1, fstream::out | fstream::in | fstream::trunc); //открываю их, очищаю
			files_B->at(i).clear();
			files_B->at(i).seekg(0, ios_base::beg); //готовлю файлы B для чтения из них
		}
	}
	else //если читал B->A
	{
		for (int i = 0; i < amountFiles; i++)
		{
			files_B->at(i).close();//закрываю файлы B
			filename2 = "B-" + to_string(i + 1) + ".txt";
			files_B->at(i).open(filename2, fstream::out | fstream::in | fstream::trunc); //открываю их, очищаю
			files_A->at(i).clear();
			files_A->at(i).seekg(0, ios_base::beg);//готовлю файлы A для чтения из них
		}
	}
}
int checkTheFinish(fstream *file_A, fstream *file_B){//Функция возвращает какой файл пуст
	//1 - пуст первый, -1 - пуст второй, 2 - ни один не пустой, 0 - оба пусты
	long old_pos1 = file_A->tellg(); //сохраняем старое положение файлового указателя
	long old_pos2 = file_B->tellg(); 
	file_A->seekg(0, std::ios::end); //переставляем файловый указатель на конец
	file_B->seekg(0, std::ios::end);
	long size1 = file_A->tellg(); //считываем его положение, оно и будет размером файла
	long size2 = file_B->tellg();
	file_A->seekg(0, old_pos1);//возвращаем файловому указателю изначальное положение
	file_B->seekg(0, old_pos2);
	
	if (size1 == 0)//пуст первый
		if (size2 == 0)//пуст второй
			return 0;
		else
			return 1;
	else
		if (size2 == 0)//пуст второй
			return -1;
		else
			return 2;
}
int compare(element element1, element element2, int field){//функция сравнения двух элементов по полю field
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
int randomNumber(){//случайное число 
	return rand() % 50;
}
string randomString(){//случайная строка длины 5
	string str;
	int index;
	char alpha[] = "abcdefghijklmnopqrstuvwxyz";
	for (int i = 0; i < 5; i++)
	{
		index = rand() % 26;
		str += alpha[index];
	}
	return str;
}
void hoar(int left, int right, vector<element> *massive, int field1, int field2, int field3)//функция, которая сортирует массив
{
	bool stop = false;//флаг нахождения элемента для перестановки
	int currL = left;//текущий левый элемент для перестановки
	int currR = right;//текущий правый элемент для перестановки
	element centerEl = massive->at((currL + currR) / 2);//опорный элемент
	do
	{
		stop = false;//элемент ещё не найден
		while (stop == false)//пока не нашли левый элемент для перестановки
		{
			if (compare((*massive)[currL], centerEl, field1) == 1)//слева(поле 1) > опорного(поле 1)
				stop = true;//необходима перестановка
			if (compare((*massive)[currL], centerEl, field1) == 0)//если элементы равны по 1 полю
			{
				if (compare((*massive)[currL], centerEl, field2) == 1)//слева(поле 2) > опорного(поле 2)
					stop = true;//необходима перестановка
				if (compare((*massive)[currL], centerEl, field2) == 0)//если элементы равны по 2 полю
				{
					if (compare((*massive)[currL], centerEl, field3) == 1)//слева (поле 3) > опорного (поле 3)
						stop = true;//нужна перестановка
					if (compare((*massive)[currL], centerEl, field3) == 0)//если равны по трём полям
						stop = true;//переставляем
				}
			}
			if (stop == false)//если не нужна перестановка
				currL++;//сдвигаем указатель
		}
		stop = false;
		while (stop == false)//пока не нашли правый элемент для перестановки
		{
			if (compare((*massive)[currR], centerEl, field1) == -1)//элемент справа меньше опорного по полю 1
				stop = true;
			if (compare((*massive)[currR], centerEl, field1) == 0)//если равен по полю 1
			{
				if (compare((*massive)[currR], centerEl, field2) == -1)//меньше по полю 2
					stop = true;
				if (compare((*massive)[currR], centerEl, field2) == 0)//равен по полю 2
				{
					if (compare((*massive)[currR], centerEl, field3) == -1)//меньше по полю 3
						stop = true;
					if (compare((*massive)[currR], centerEl, field3) == 0)//равен по полю 3
						stop = true;
				}
			}
			if (stop == false)//не нужна перестановка
				currR--;//сдвиг указателя
		}

		if (currL <= currR)//если были найдены элементы на неправильных позициях
		{
			element el = (*massive)[currL];
			(*massive)[currL] = (*massive)[currR];
			(*massive)[currR] = el;
			currR--; currL++;
		}
	} while (currL < currR);
	if (left < currR)//запускаем просмотр для массивов меньшего размера
		hoar(left, currR, massive, field1, field2, field3);
	if (right > currL)//запускаем просмотр для массивов  меньшего размера
		hoar(currL, right, massive, field1, field2, field3);
}

int setStartPositions(int amountFiles, vector<int> *currNumber, vector<element> *currElement, vector<fstream> *files, bool replacedWas){
	/*Функция устанавливает начальный элемент серии для каждого файла*/
	string strtmp;
	element max = element(INT_MAX, INT_MAX, INT_MAX, STRING_MAX, STRING_MAX);
	for (int i = 0; i < amountFiles; i++) //проход по каждому файлу
	{
		getline(files->at(i), strtmp); //чтение очередной строки из текущего файла
		if (strtmp != "") //если есть элементы в файле
		{
			(*currNumber)[i] = 1; //номер элемента в серии
			(*currElement)[i] = element(strtmp); //текущий элемент в серии
		}
		else//элементов нету
		{
			(*currNumber)[i] = 0;
			(*currElement)[i] = max;//текущим элементом делаем условно бесконечный
		}
	}
	if ((*currNumber)[0] == 0) //все файлы пусты
		return 1;
	if ((*currNumber)[1] == 0 && replacedWas == false)// если есть всего 1 файл с данными, и прежде не было слияний то все серии отсортированы
		return 1;
	return 0;
}
void createOneChapter(int amountFiles, vector<int> *currNumber, vector<element> *currElement, vector<fstream> *files_A, fstream *file_B, int field1, int field2, int field3, int lenChapter){
	/*Функция создаёт очередную серию, сливая по серии из остальных файлов*/
	string strtmp;

	int min_index = -1; //номер серии, содержащей минимальный элемент
	element max(INT_MAX, INT_MAX, INT_MAX, STRING_MAX, STRING_MAX);//максимальный элемент
	element min; //минимальный элемент
	element *tmp;
	

	while (true)
	{
		min = max; // изначально минимальный не вычислен
		min_index = -1;//и его индекс за пределами диапазона

		for (int i = 0; i < amountFiles; i++)//проход по каждому текущему элементу серии
		{
			tmp = &currElement->at(i);
			int comp1 = compare(min, *tmp, field1); //сравнение по первому полю
			if (comp1 == 1)//если минимальный больше чем текущий
			{
				min = *tmp; //заменяем его
				min_index = i;
			}
			else
			{
				if (comp1 == 0)//если они равны
				{
					int comp2 = compare(min, *tmp, field2); //сравнение по второму полю
					if (comp2 == 1)//минимальный > текущий
					{
						min = *tmp;//замена
						min_index = i;
					}
					else
					{
						if (comp2 == 0)//минимальный = текущий
							if (compare(min, *tmp, field3) == 1) //если минимальный > текущий
							{
								min = *tmp;//замена
								min_index = i;
							}
					}
				}
			}
		}

		if (min_index == -1)// все серии окончены а минимум не обновлён
			break;//завершено формирование новой серии из старых
		else
		{
			*file_B << min.first << "\t" << min.second << "\t"
					<< min.third << "\t" << min.fourth << "\t"
					<< min.fifth << endl;	//Запись минимального элемента в новый файл
			(*currNumber)[min_index] += 1;//номер элемента в серии увеличиваем на 1
			if ((*currNumber)[min_index] > lenChapter)//если из данного файла взяли всю серию
			{
				(*currElement)[min_index] = max;//заменяем элемент в массиве 
			}
			else
			{
				getline(files_A->at(min_index), strtmp);//читаем из файла следующий элемент в серии
				if (strtmp != "") //если есть элементы в файле
				{
					(*currElement)[min_index] = element(strtmp);//создаем элемент
				}
				else//элементов нетy
					(*currElement)[min_index] = max;//заменяем максимальным
			}
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));

	//Характеристики сортировки
	int amountFiles; //количество файлов
	int lenChapter; //длина серии
	int size; //размер массива данных
	int field1; //первое поле для сортировки
	int field2; //второе поле для сортировки
	int field3; //третье поле для сортировки


	//Создание изначальных данных
	cout << "Input size of data massive: ";//ввод размера массива данных
	do{
		cin >> size; 
		cin.clear();
		fflush(stdin);              //очищаем поток ввода
	} while (size < 1);

	cout << "Input length of series: "; //ввод изначальной длины серии
	do{
		cin >> lenChapter;
		cin.clear();
		fflush(stdin);              //очищаем поток ввода
	} while (lenChapter < 1);

	cout << "Input amount of files: "; //количество файлов
	do{
		cin >> amountFiles;
		cin.clear();
		fflush(stdin);              //очищаем поток ввода
	} while (amountFiles < 2 || amountFiles > 100);

	cout << "Input first field for sorting" << endl;
	do{//считываем с клавиатуры номер 1 поля для сортировки
		cin >> field1;
		cin.clear();
		fflush(stdin);              //очищаем поток ввода
	} while (field1 < 1 || field1 > 5);
	cout << "Input second field for sorting" << endl;
	do{//считываем с клавиатуры номер 2 поля для сортиовки
		cin >> field2;
		cin.clear();                //сбрасываем коматозное состояние cin
		fflush(stdin);              //очищаем поток ввода
	} while (field2 < 1 || field2 > 5 || field1 == field2);
	cout << "Input third field for sorting" << endl;
	do{//считываем с клавиатуры номер 3 поля для сортировки
		cin >> field3;
		cin.clear();                //сбрасываем коматозное состояние cin
		fflush(stdin);              //очищаем поток ввода
	} while (field3 < 1 || field3 > 5 || field3 == field2 || field3 == field1);
	

	unsigned int startTime = clock(); //стартовое время

	ofstream in("input.txt");//файл с данными для сортировки
	for (int i = 0; i < size; i++) //массив для ввода в файл рандомных элементов
	{
		in << randomNumber() << "\t" << randomNumber() << "\t"
			<< randomNumber() << "\t" << randomString() << "\t"
			<< randomString() << endl;
	}
	cout << "Massive was successfully created" << endl;
	in.close();

	ifstream readIn("input.txt"); //открываем на чтение стартовый массив

	vector<fstream> *files_A = new vector<fstream>(amountFiles); //файлы A-xxx
	vector<fstream> *files_B = new vector<fstream>(amountFiles); //файлы B-xxx
	string filename1; //имя первого файла
	string filename2; //имя второго файла
	for (int i = 0; i < amountFiles; i++)//создание всех файлов
	{
		filename1 = "A-" + to_string(i + 1) + ".txt";
		filename2 = "B-" + to_string(i + 1) + ".txt";
		files_A->at(i).open(filename1, fstream::out);
		files_B->at(i).open(filename2, fstream::out);
	}

	int currChapter = 0;//номер текущего элемента в серии
	int currFile = 0; //номер текущего файла

	string str;

	vector<element> massive; //массив из элементов одной серии
	element tmpe;

	while (getline(readIn, str))//пока в исходном файле есть элементы
	{
		element elem(str);//создание элемента из этих полей
		if (currChapter == lenChapter)//если было уже считано из файла lenChapter элементов
		{
			hoar(0, lenChapter - 1, &massive, field1, field2, field3);//сортируем получившийся массив
			for (int i = 0; i < lenChapter; i++)//записываем в текущий файл
			{
				tmpe = massive[i];
				files_A->at(currFile) << tmpe.first << "\t"
					<< tmpe.second << "\t" << tmpe.third << "\t"
					<< tmpe.fourth << "\t" << tmpe.fifth << endl;
			}
			massive.clear(); //очистка массива
			currChapter = 1; //текущий номер в серии начинается сначала
			currFile++; //следующая серия в следующий файл
			if (currFile == amountFiles)//если записана серия уже в каждый файл
				currFile = 0; //то запись её снова в первый файл
		}
		else//если ещё считана не вся серия
			currChapter++;
		massive.push_back(elem);//добавление этого элемента в массив
	}
	if (massive.size() != 0) //последняя серия неполная но присутствует
	{
		if (currFile == amountFiles)//определяем в какой файл её писать
			currFile = 0;
		hoar(0, massive.size() - 1, &massive, field1, field2, field3);//сортируем
		int size = massive.size();
		for (int i = 0; i < size; i++)//записываем в текущий файл
		{
			tmpe = massive[i];
			files_A->at(currFile) << tmpe.first << "\t"
				<< tmpe.second << "\t" << tmpe.third << "\t"
				<< tmpe.fourth << "\t" << tmpe.fifth << endl;
		}
	}
	vector<int> *currElemNum = new vector<int>(amountFiles); //номер элемента в сериях
	vector<element> *currElemVal = new vector<element>(amountFiles); //сам текущий элемент в сериях

	for (int i = 0; i < amountFiles; i++)//закрытие этих файлов
	{
		files_A->at(i).close();
		files_B->at(i).close();
	}

	for (int i = 0; i < amountFiles; i++)//открываем каждый файл
	{
		filename1 = "A-" + to_string(i + 1) + ".txt";
		filename2 = "B-" + to_string(i + 1) + ".txt";
		files_A->at(i).open(filename1, fstream::in);
		files_B->at(i).open(filename2, fstream::out | fstream::in);
		if (files_A->at(i).is_open() == false || files_B->at(i).is_open() == false)//файл не открылся, ошибка чтения
		{
			cout << "Fatal error in reading files" << endl;
			return -1;
		}
	}
	int mode = 1;//текущий режим слияния (1 - из А в В, -1 - из В в А)
	int numberofmerge = 1; //номер слияния
	while (checkTheFinish(&files_A->at(1), &files_B->at(1)) != 0)//пока серии находятся не только в первом файле
	{
		cout << "Merge num. " << numberofmerge << endl; //номер текущего слияния
		numberofmerge++;
		int fileCount = 0;
		bool replace = false;//были ли слияния
		if (mode == 1)// если перекидываю из A в B
		{
			while (setStartPositions(amountFiles, currElemNum, currElemVal, files_A, replace) != 1) //пока не будут все записи в файлах B
			{
				if (fileCount == amountFiles)//если очередную серию нужно читать в первый файл
					fileCount = 0;
				createOneChapter(amountFiles, currElemNum, currElemVal, files_A, &files_B->at(fileCount++), field1, field2, field3, lenChapter);//слияние серий в одну
				replace = true;//было слияние
			}
		}
		else//иначе перекидываю из B в A
		{
			while (setStartPositions(amountFiles, currElemNum, currElemVal, files_B, replace) != 1)//пока не будут все записи в файлах A
			{
				if (fileCount == amountFiles)//если очередную серию нужно читать в первый файл
					fileCount = 0;
				createOneChapter(amountFiles, currElemNum, currElemVal, files_B, &files_A->at(fileCount++), field1, field2, field3, lenChapter);//слияние серий в одну
				replace = true;//было слияние
			}
		}

		lenChapter *= amountFiles;//длина слитой серии равна сумме длин серий из каждого файла
		openFiles(amountFiles, files_A, files_B, mode); //открытие файлов и перестановка ф. указателей
		mode *= -1;//меняем режим чтения в другую сторону
	}

	int resFile = checkTheFinish(&files_A->at(0), &files_B->at(0)); //какой файл пуст
	for (int i = 1; i < amountFiles; i++)//закрываем все файлы и удаляем их, кроме первых
	{
		files_A->at(i).close();//закрываем
		files_B->at(i).close();
		str = "A-" + to_string(i + 1) + ".txt";
		remove(str.c_str());//удаляем
		str = "B-" + to_string(i + 1) + ".txt";
		remove(str.c_str());
	}
	remove("output.txt");//удаляем файл если он уже есть
	if (resFile == -1)//если итоговый отсортированный массив в файле A-1
	{
		files_A->at(0).close();
		files_B->at(0).close();
		rename("A-1.txt", "output.txt");//то переименовываем его
		remove("B-1.txt");				//и B-1 удаляем
	}
	else
	{
		if (resFile == 1)//Если итоговый отсортированный массив в файле B-1
		{
			files_A->at(0).close();
			files_B->at(0).close();
			rename("B-1.txt", "output.txt");//то переименовываем его
			remove("A-1.txt");				//и А-1 удаляем
		}
		else
		{
			cout << "Something is eror with files" << endl;
			return -1;
		}
	}
	
	double time = (double)((int)((clock() - startTime) / 10)) / 200; /*СМЕКАЛОЧКА*/
	cout << "Sort finished!" << endl;
	cout << "time of sort = " << time << "sec";
	return 0;
}
