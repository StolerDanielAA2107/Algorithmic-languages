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

double pipe::GetDiameter() const
{
	return diameter;
}

istream& operator >> (istream& in, pipe& p) // ���� �����
{
	cout << "������� ����� �����: " << endl;
	p.length = InputCheck(0.0, 2000000000000000000.0);
	cout << "������� ������� �����: " << endl;
	p.diameter = InputCheck(0.0, 2000000000000000000.0);
	p.priznak = false;
	return in;
}

ostream& operator << (ostream& out, const pipe& p) // ������ �����
{
	if ((p.GetLength() == 0) || (p.GetDiameter() == 0))
	{
		cout << "����� �� �������" << endl;
	}
	else
	{
		cout << "�������������� �����:" << endl;
		cout << " �����:" << p.GetLength() << endl;
		cout << " �������:" << p.GetDiameter << endl;
		/*if (p.priznak == 1)
		{
			cout << " �������: � �������" << "\n" << endl;
		}
		if (p.priznak == 0)
		{
			cout << " �������: �� � �������" << "\n" << endl;
		}*/
	}
	return out;
}
