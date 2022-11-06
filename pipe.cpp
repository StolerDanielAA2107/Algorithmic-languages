#include <fstream>
#include <sstream>
#include "pipe.h"
#include "Utils.h"

using namespace std;

int pipe::MaxID = 1;

pipe::pipe()
{
	id = MaxID++;
	length = { 0.0 };
	diameter = { 0.0 };
	priznak = { 0 };
}

void pipe::EditPipe()
{
	bool edt_p;
	cout << " ��� �������������� �������� ����� ������� 1 ��� 0 (< 1 � ������� >,< 0 �� � �������>)" << endl;
		edt_p = InputCheck(0, 1);
		if (edt_p == true)
		{
			priznak = true;
		}
		if (edt_p == false)
		{
			priznak = false;
		}
		cout << "�������� �������" << endl;
}

void LoadPipe(ifstream& fin, pipe& p)
{
	fin >> p.id; fin >> p.length; fin >> p.diameter; fin >> p.priznak;
}

void SavePipe(ofstream& fout, const pipe& p)
{
	fout << p.id << "\n" << p.length << "\n" << p.diameter << "\n" << p.priznak << endl;
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

ostream& operator << (ostream& out, const pipe& p) // ������ �����
{
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
	return out;
}
	
void swap(bool &a, bool &b)
{
	int temp = a;
	a = b;
	b = temp;
}


