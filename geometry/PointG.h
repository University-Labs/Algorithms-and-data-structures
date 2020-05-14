#pragma once
#include <string>

using namespace std;
class PointG//класс реализует точку, с  учётом её координат и наименования
{
private:
	double x;//x-координата
	double y;//y-координата
	string name;//наименование
public:
	PointG();
	PointG(double a, double b, string name);
	double getX();//возвращает x-координату
	double getY();//возвращает y-координату
	string getName();//возвращает наименование
};

