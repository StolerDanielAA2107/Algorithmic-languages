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
		cout << " �� �� ����� �����, ���������� ��� ���" << endl;
	}
	else
	{
		cout << " ��� �������������� �������� ����� ������� 1 ��� 0 (< 1 � ������� >,< 0 �� � �������>)" << endl;
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

istream& operator >> (istream& in, pipe& p) // ���� �����
{
	cout << "������� ����� �����: " << endl;
	p.length = InputCheck(0.0, DBL_MAX);
	cout << "������� ������� �����: " << endl;
	p.diameter = InputCheck(0.0, DBL_MAX);
	p.priznak = false;
	return in;
}

ostream& operator << (ostream& out,  pipe& p) // ������ �����
{
	if ((p.length == 0) || (p.diameter == 0))
	{
		cout << "����� �� �������" << endl;
	}
	else
	{
		cout << "�������������� �����:" << endl;
		cout << " �����:" << p.length << endl;
		cout << " �������:" << p.diameter << endl;
		if (p.priznak == 1)
		{
			cout << " �������: � �������" << "\n" << endl;
		}
		if (p.priznak == 0)
		{
			cout << " �������: �� � �������" << "\n" << endl;
		}
	}
	return out;
}

