
//Найти в дереве поддерево, корнем которого будет узел с заданным значением ключа, и удалить все вершины, принадлежащие самому левому пути этого поддерева.
#include "stdafx.h"
#include <iostream>
#include <queue>
#include <fstream>
#include <string>

using namespace std;


typedef int T;
typedef enum { BLACK, RED } color; //цвета

struct node{
	T data;//ключ
	node *left;//левый
	node *right;//правый
	node *parent;//родитель
	color nodeColor;//цвет
	node(T dat, node *l, node *r, node *p, color color){
		data = dat;
		left = l;
		right = r;
		parent = p;
		nodeColor = color;
	}
};
#define nilNode &sentinel  //пустой nil узел
node sentinel = { 0, nilNode, nilNode, nullptr, BLACK };

class RBTree{
private:
	node *root;//корень дерева
public:
	RBTree(){
		root = nilNode;
	}
	void insertData(T data);	//вставка элемента по ключу
	void fixInsert(node *node);	//балансировка после вставки
	void deleteNode(T data);	//удаление элемента по ключу
	void fixDelete(node *node);	//балансировка после удаления
	node* findElem(T data);		//поиск элемента по ключу
	void printTree();			//печать дерева
	void fileTree(ofstream &file);
	void rotateLeft(node *x);	//левый поворот
	void rotateRight(node *x);	//правый поворот

	void deleteLeftChilds(T key);//удаление всех элементов в левом пути от ключа key
};
string getColor(color x){
	return x == BLACK ? "Black" : " Red ";
}

void RBTree::rotateLeft(node *x){//левый поворот
	node *t = x->right; //запоминаем правого сына
	x->right = t->left; //и заменяем его 
	if (t->left != nilNode && t->left != nullptr) t->left->parent = x;//выставляем родителя для него, если он не листовой

	if (t != nullptr && t != nilNode) t->parent = x->parent;//Делаем родителем правого потомка х - родителя узла х
	if (x->parent) {
		if (x == x->parent->left) //если х - левый потомок своего родителя
			x->parent->left = t; //далаем новым левым потомком узел t(правое поддерево х)
		else
			x->parent->right = t;//иначе делаем новым правым потомком узел t.
	}
	else {
		root = t;//иначе помещаем узел t в корень
	}

	t->left = x;//для старого правого сына левым потомком делаем изначальный узел
	x->parent = t;//обновляем указатель на родителя для узла
}
void RBTree::rotateRight(node *x){//правый поворот
	node *t = x->left; //запоминаем левого сына
	x->left = t->right; //и заменяем его 
	if (t->right != nilNode && t->right != nullptr) t->right->parent = x;//выставляем родителя для него, если он не листовой

	if (t != nullptr && t != nilNode) t->parent = x->parent;//Делаем родителем правого потомка х - родителя узла х
	if (x->parent) {
		if (x == x->parent->right) //если х - правый потомок своего родителя
			x->parent->right = t; //далаем новым левым потомком узел t(правое поддерево х)
		else
			x->parent->left = t;//иначе делаем новым правым потомком узел t.
	}
	else {
		root = t;//иначе помещаем узел t в корень
	}

	t->right = x;//для старого правого сына левым потомком делаем изначальный узел
	if (x != nilNode) x->parent = t;//обновляем указатель на родителя для узла
}
void RBTree::insertData(T data){//вставка узла
	if (root == nilNode)// если корень nil
		root = new node(data, nilNode, nilNode, nullptr, BLACK);//вставляем в него новый узел
	else
	{
		node *curr = root, *parent = nullptr;
		while (curr != nilNode)//пока не дойдём до пустого узла в дереве
		{
			parent = curr;//запоминаем родителя узла
			if (data > curr->data) //Если больше, то направо
				curr = curr->right;
			else
				curr = curr->left;//меньше или равны - налево
		}
		node *newNode = new node(data, nilNode, nilNode, parent, RED);//создаём на этом месте новый узел с родителем parent
		if (data > parent->data)//определяем каким сыном у parent является новый узел
			parent->right = newNode;
		else
			parent->left = newNode;
		fixInsert(newNode); //восстанавливаем КЧД
	}
}
void RBTree::fixInsert(node *x){//восстановление свойств КЧД
	while (x != root && x->parent->nodeColor == RED)//пока не дошли до корня и цвет родителя узла - красный
	{
		node *uncle;//дядя узла x
		if (x->parent->parent->left == x->parent) //если родитель х является левым сыном 
		{
			uncle = x->parent->parent->right;//то дядя правым
			if (uncle->nodeColor == RED)//если цвет дяди красный
			{
				x->parent->nodeColor = BLACK;//просто перекрашиваем их
				uncle->nodeColor = BLACK;
				x->parent->parent->nodeColor = RED;//дедушку делаем красным
				x = x->parent->parent;//движемся вверх по дереву
			}
			else
			{
				//дядя черного цвета
				if (x == x->parent->right)//x - right and x->parent - left
				{
					x = x->parent;
					rotateLeft(x);//выполняем поворот влево для родителя
				}
				x->parent->nodeColor = BLACK; //перекрашиваем родителя
				x->parent->parent->nodeColor = RED; //и дедушку
				rotateRight(x->parent->parent);//и выполняем поворот вправо для дедушки
			}
		}
		else
		{
			uncle = x->parent->parent->left;//иначе дядя - левый сын
			if (uncle->nodeColor == RED)//дядя - красный?
			{
				x->parent->nodeColor = BLACK;//простая перекраска
				uncle->nodeColor = BLACK;
				x->parent->parent->nodeColor = RED;
				x = x->parent->parent;//движемся вверх по дереву
			}
			else
			{//дядя черный
				if (x == x->parent->left)//x - left and x->parent - right
				{
					x = x->parent;
					rotateRight(x);//поворот вправо относительно родителя
				}
				x->parent->nodeColor = BLACK;//перекрашиваем родителя
				x->parent->parent->nodeColor = RED;//и дедушку
				rotateLeft(x->parent->parent);//выполняем поворот влево для дедушки
			}
		}
	}
	root->nodeColor = BLACK;//на случай если корень перекрасился в красный
}
void RBTree::deleteNode(T data){//функция удаления узла
	node *x = findElem(data);//поиск этого элемента
	node *y; //узел, который удаляется в действительности
	node *t; //узел, который встанет на место удаляемого
	if (x != nullptr)// нашли элемент с заданным ключом
	{
		if (x->left == nilNode || x->right == nilNode) {//если один из детей нулевой, то этот узел и удаляем
			y = x;
		}
		else {//если оба ребёнка не нулевые
			y = x->right;//исчим в правом поддереве минимальный узел
			while (y->left != nilNode) y = y->left;
		}
		//определяем для какого узла будем вызывать балансировку
		if (y->left != nilNode)
			t = y->left;
		else
			t = y->right;

		t->parent = y->parent;//меняем указателей на родителя
		if (y->parent)//и от родителя к ребёнку
			if (y == y->parent->left)
				y->parent->left = t;
			else
				y->parent->right = t;
		else
			root = t;
		if (y != x)//если был случай удаления с двумя детьми
			x->data = y->data; //перемещаем информацию, а удаляем другой узел

		if (y->nodeColor == BLACK)//если удаляемый узел был черного цвета
			fixDelete(t);//вызываем балансирование
		delete y;//чистим память
	}
}
void RBTree::fixDelete(node *x){
	while (x != root && x->nodeColor == BLACK) { //пока не дошли до корня и узёл черный
		if (x == x->parent->left) {//если узел -левый сын
			node *bro = x->parent->right;//то его брат - правый сын
			if (bro->nodeColor == RED) {//если брат - красный
				bro->nodeColor = BLACK;//просто перекрашиваем его
				x->parent->nodeColor = RED;//и родителя
				rotateLeft(x->parent); //поворачиваем относительно родителя
				bro = x->parent->right;
			}
			if (bro->left->nodeColor == BLACK && bro->right->nodeColor == BLACK) { //если оба сына брата черные
				bro->nodeColor = RED;//то просто перекрашиваем брата
				x = x->parent;//и идём вверх по дереву
			}
			else {//есть красные сыновья
				if (bro->right->nodeColor == BLACK) {//правый ребенок брата - черный
					bro->left->nodeColor = BLACK;//перекрашиваем брата
					bro->nodeColor = RED; //и левого сына
					rotateRight(bro);//делаем вращение вправо вокруг брата
					bro = x->parent->right;
				}
				bro->nodeColor = x->parent->nodeColor; //перекрашиваем брата в цвет отца
				x->parent->nodeColor = BLACK;//отца 
				bro->right->nodeColor = BLACK;//и правого ребёнка в черный
				rotateLeft(x->parent); //поворот родителя влево
				x = root; //завершаем алгоритм
			}
		}
		else {
			node *bro = x->parent->left; //брат - слева
			if (bro->nodeColor == RED) {//цвет брата - красный
				bro->nodeColor = BLACK; //перекрашиваем его в черный
				x->parent->nodeColor = RED;//а родителя в красный
				rotateRight(x->parent);//поворачиваем направо
				bro = x->parent->left;
			}
			if (bro->right->nodeColor == BLACK && bro->left->nodeColor == BLACK) {//если оба сына брата черные
				bro->nodeColor = RED;//перекрашиваем брата в красный
				x = x->parent;//и идем вверх по дереву
			}
			else {
				if (bro->left->nodeColor == BLACK) { //Если левый сын брата черный
					bro->right->nodeColor = BLACK;//цвет правого сына брата - черный
					bro->nodeColor = RED;//сам цвет брата - красный
					rotateLeft(bro);//поворачиваем влево относительно брата
					bro = x->parent->left;
				}
				bro->nodeColor = x->parent->nodeColor;//перекрашиваем брата в цвет отца
				x->parent->nodeColor = BLACK;//отца
				bro->left->nodeColor = BLACK;//и левого ребенка в черный
				rotateRight(x->parent);// правый поворот вокруг родителя
				x = root;//и завершаем алгоритм
			}
		}
	}
	x->nodeColor = BLACK;//цвет узла
	root->nodeColor = BLACK;//и корня выставляем в черный
}
void RBTree::printTree(){//печать содержимого дерева
	queue <node*> que;//очередь с узлами дерева
	que.push(root);//заносим корень
	if (root != nilNode)//дерево не пустое
	{
		while (!que.empty())//пока не опустошится очередь
		{
			cout << "";
			cout << que.front()->data << "(" << (getColor(que.front()->nodeColor)) << ")" << ' ';//печатаем из начала очереди
			if (que.front()->left != nilNode)//если левый сын не nil
			{
				cout << que.front()->left->data << ' ';//печатаем его
				que.push(que.front()->left);// и заносим в очередь
			}
			else
			{
				cout << " - ";//печатаем прочерк вместо него
			}
			if (que.front()->right != nilNode)//правый ребёнок есть
			{
				cout << que.front()->right->data << ' ';//печатаем его
				que.push(que.front()->right);//и заносим в очередь
			}

			else
			{
				cout << " - ";//печатаем прочерк вместо него
			}
			que.pop();//убираем из очереди
			cout << endl;
		}
	}
	else cout << "Tree is empty!" << endl;
}
void RBTree::fileTree(ofstream &filew){
	queue <node*> que;//очередь с узлами дерева
	que.push(root);//заносим корень
	if (root != nilNode)//дерево не пустое
	{
		while (!que.empty())//пока не опустошится очередь
		{
			filew << que.front()->data << "(" << (getColor(que.front()->nodeColor)) << ")" << ' ';//печатаем из начала очереди
			if (que.front()->left != nilNode)//если левый сын не nil
			{
				filew << que.front()->left->data << ' ';//печатаем его
				que.push(que.front()->left);// и заносим в очередь
			}
			else
			{
				filew << " - ";//печатаем прочерк вместо него
			}
			if (que.front()->right != nilNode)//правый ребёнок есть
			{
				filew << que.front()->right->data << ' ';//печатаем его
				que.push(que.front()->right);//и заносим в очередь
			}

			else
			{
				filew << " - ";//печатаем прочерк вместо него
			}
			que.pop();//убираем из очереди
			filew << endl;
		}
	}
	else filew << "Tree is empty!" << endl;
}
node * RBTree::findElem(T data){//поиск элемента по ключу
	node *curr = root;
	while (curr != nilNode)//пока не дошли до листа
	{
		if (curr->data == data)//если нашли заданный ключ
			return curr;//возврат этого элемента
		else
			curr = curr->data > data ? curr->left : curr->right;//поиск дальше
	}
	return nullptr;
}
void RBTree::deleteLeftChilds(T key)//удаление левых детей младше, чем T
{
	node *x = findElem(key);//находим этот узел
	if (x == nullptr){
		cout << "I cant find this value in the tree< " << endl;
	}
	else
	{
		queue<int> queueDelete; //вектор из узлов для удаления
		x = x->left; //двигаемся в левое поддерева от заданного узла
		while (x != nilNode) {//пока не дошли до листового узла
			queueDelete.push(x->data);//заносим узел в очередь
			x = x->left;//двигаемся вниз по дереву
		}
		while (queueDelete.empty() == false)//пока не очистим всю очередь
		{
			deleteNode(queueDelete.front());//исчим и удаляем элемент по ключу
			queueDelete.pop();//убираем его из очереди
		}
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	RBTree tr;//само дерево
	int size;//размер дерева
	int currel;
	cout << "Input size of tree" << endl;
	do{
		cin >> size;
		cin.sync();
		cin.clear();
	} while (size < 1);//размер дерева
	for (int i = 0; i < size; i++)// вводим элементы дерева
	{
		cout << "Input key num. " << i + 1 << ":\t ";
		while (!(cin >> currel))//защита от некорректного ввода
		{
			cin.sync();
			cin.clear();
		}
		tr.insertData(currel);//включаем в дерево
	}
	cout << "Tree was done. Your tree is:" << endl;
	ofstream in("input.txt");//файлы для записи исходных данных
	ofstream out("output.txt");//и результата
	tr.fileTree(in);//печатаем на экран
	tr.printTree();//и в файл
	cout << "___________________________________" << endl;
	cout << "Enter key for deletting: " << endl;
	while (!(cin >> currel)){//ввод ключа для удаления левого пути
		cin.sync();
		cin.clear();
	}

	tr.deleteLeftChilds(currel);//удаляем все узлы в самом левом пути от узла с ключом currel
	tr.printTree();//печатаем на экран
	tr.fileTree(out);//и в файл

	in.close();//закрываем
	out.close();//файлы
	return 0;
}
