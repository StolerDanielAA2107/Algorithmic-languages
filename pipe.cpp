#include <fstream>
#include <sstream>
#include "pipe.h"
#include "Utils.h"

using namespace std;

int pipe::MaxID = 1;

pipe::pipe()
{
	id = pipe::MaxID++;
	length = { 0.0 };
	diameter = { 0 };
	priznak = { 0 };
	connect = { 0 };
}

pipe::pipe(int value)
{
	id = pipe::MaxID++;
	length = { 100.0 };
	diameter = { value };
	priznak = { 0 };
	connect = { 1 };
}

void pipe::changesign()
{
	priznak = priznak == 1 ? 0 : 1;
}

void pipe::connect1() // connect to 1
{
	connect = 1;
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
	cout << "�������� ������� �����: " << endl;
	cout << "1. 500mm" << endl;
	cout << "2. 700mm" << endl;
	cout << "3. 1400mm" << endl;
	switch (InputCheck(1, 3)) {
	case 1: p.diameter = 500; break;
	case 2: p.diameter = 700; break;
	case 3: p.diameter = 1400; break;
	}
	p.priznak = false;
	return in;
}

ostream& operator << (ostream& out, const pipe& p) // ������ �����
{
	cout << " �����:" << p.length << endl;
	cout << " �������:" << p.diameter << endl;
	if (p.priznak == 1) {
		cout << " �������: � �������" << "\n" << endl;
	}
	if (p.priznak == 0) {
		cout << " �������: �� � �������"  << endl;
	}
	if (p.connect == 1) {
		cout << " �������� ��� �����������: ���" << "\n" << endl;
	}
	if (p.connect == 0) {
		cout << " �������� ��� �����������: ��" << "\n" << endl;
	}
	return out;
}



