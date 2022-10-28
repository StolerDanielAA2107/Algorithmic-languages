#include "pipe.h"
#include "Utils.h"
#include <fstream>
#include <sstream>

int pipe::MaxID = 1;

using namespace std;

pipe::pipe()
{
	id = MaxID;
	length = 0.0;
	diameter = 0.0;
	priznak = 0;
}

void pipe::EditPipe()
{
	bool edt_p;

		cout << " Для редактирования признака трубы нажмите 1 или 0 (< 1 в ремонте >,< 0 не в ремонте>)" << endl;
		edt_p = InputCheck(0, 1);
		if (edt_p == true)
		{
			priznak = true;
		}
		if (edt_p == false)
		{
			priznak = false;
		}
		cout << "Параметр изменен" << endl;
}

void LoadPipe(ifstream& fin, pipe& p)
{
	fin >> p.id; fin >> p.length; fin >> p.diameter; fin >> p.priznak;
}

void SavePipe(ofstream& fout, const pipe& p)
{
	fout << p.id << "\n" << p.length << "\n" << p.diameter << "\n" << p.priznak << endl;
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

ostream& operator << (ostream& out, const pipe& p) // Печать трубы
{
	if ((p.length == 0) || (p.diameter == 0))
	{
		cout << "Труба не введена" << endl;
	}
	else
	{
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


