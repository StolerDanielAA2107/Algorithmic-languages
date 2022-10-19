#include "pipe.h"
using namespace std;

//pipe::pipe()
//{
//	length = 0;
//	diameter = 0;
//	priznak = 0;
//}

double pipe::GetLength() const
{
	return length;
}


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

double pipe::GetDiameter() const
{
	return diameter;
}

istream& operator >> (istream& in, pipe& p) // Ввод трубы
{
	cout << "Введите длину трубы: " << endl;
	p.length = InputCheck(0.0, 2000000000000000000.0);
	cout << "Введите диаметр трубы: " << endl;
	p.diameter = InputCheck(0.0, 2000000000000000000.0);
	p.priznak = false;
	return in;
}

ostream& operator << (ostream& out, const pipe& p) // Печать трубы
{
	if ((p.GetLength() == 0) || (p.GetDiameter() == 0))
	{
		cout << "Труба не введена" << endl;
	}
	else
	{
		cout << "Характеристики трубы:" << endl;
		cout << " Длина:" << p.GetLength() << endl;
		cout << " Диаметр:" << p.GetDiameter << endl;
		/*if (p.priznak == 1)
		{
			cout << " Признак: в ремонте" << "\n" << endl;
		}
		if (p.priznak == 0)
		{
			cout << " Признак: не в ремонте" << "\n" << endl;
		}*/
	}
	return out;
}
