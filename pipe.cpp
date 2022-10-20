#include "pipe.h"
#include"Utils.h"

using namespace std;

//void pipe::UniqueID(int id_p)
//{
//	id_p = ++nextID;
//}

void pipe::EditPipe(pipe& p)
{
	bool edt_p;
	if ((p.length == 0) || (p.diameter == 0))
	{
		cout << " Вы не ввели трубу, попробуйте еще раз" << endl;
	}
	else
	{
		cout << " Для редактирования признака трубы нажмите 1 или 0 (< 1 в ремонте >,< 0 не в ремонте>)" << endl;
		edt_p = InputCheck(-1, 2);
		if (edt_p == true)
		{
			p.priznak = 1;
		}
		if (edt_p == false)
		{
			p.priznak = 0;
		}
	}
}

pipe::pipe(double length, double diameter, bool priznak)
{
	//this->id_p = id_p;
	this->length = length;
	this->diameter = diameter;
	this->priznak = priznak;
}

istream& operator >> (istream& in, pipe& p) // Ввод трубы
{
	cout << "Введите длину трубы: " << endl;
	p.length = InputCheck(0.0, DBL_MAX);
	cout << "Введите диаметр трубы: " << endl;
	p.diameter = InputCheck(0.0, DBL_MAX);
	p.priznak = false;
	return in;
}

ostream& operator << (ostream& out,  pipe& p) // Печать трубы
{
	if ((p.length == 0) || (p.diameter == 0))
	{
		cout << "Труба не введена" << endl;
	}
	else
	{
		cout << "Характеристики трубы:" << endl;
		cout << " Длина:" << p.length << endl;
		cout << " Диаметр:" << p.diameter << endl;
		if (p.priznak == 1)
		{
			cout << " Признак: в ремонте" << "\n" << endl;
		}
		if (p.priznak == 0)
		{
			cout << " Признак: не в ремонте" << "\n" << endl;
		}
	}
	return out;
}

