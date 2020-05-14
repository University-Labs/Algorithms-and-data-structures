#include "PointG.h"

PointG::PointG()
{
	x = y = 0;
	name = "XXX";
}
PointG::PointG(double a, double b, string name) //конструктор для создания точки
{
	this->name = name;	//наименование
	x = a;				//координата x
	y = b;				//координата y
}
double PointG::getX(){
	return x;
}
double PointG::getY(){
	return y;
}
string PointG::getName(){
	return name;
}
