#include <fstream>
#include <sstream>  
#include "cs.h"
#include "Utils.h"

using namespace std;

int cs::MaxID = 1;

cs::cs()
{
	id = MaxID++;
	name = { "" };
	quantity = { 0 };
	work = { 0 };
	effect = { 0.0 };
}

void cs::addwork()
{
	work += 1;
}

void cs::reducework()
{
	work -= 1;
}

void SaveCs(ofstream& fout, const cs& s)
{
	fout << s.id << "\n" << s.name << "\n" << s.quantity << "\n" << s.work << "\n" << s.effect << endl;
}

void LoadCs(ifstream& fin, cs& s)
{
	fin >> s.id; fin.ignore(); getline(fin,s.name); fin >> s.quantity; fin >> s.work; fin >> s.effect;
}

istream& operator >> (istream& in, cs& s) // ���� ������������� �������
{
	cout << "������� ��� ������������� �������: " << endl;
	cin.ignore(1000, '\n');
	cin.clear();
	getline(cin, s.name);
	cout << "������� ���������� �����: " << endl;
	s.quantity = InputCheck(1, INT_MAX);
	cout << "������� ���������� ���������� �����: " << endl;
	s.work = InputCheck(0, s.quantity );
	cout << "������� �������������: " << endl;
	s.effect = InputCheck(0.0, DBL_MAX);
	return in;
}

ostream& operator << (ostream& out, cs& s) // ������ ������������� �������
{
	cout << " ��������:" << s.name << endl;
	cout << " ���������� ����� �����:" << s.quantity << endl;
	cout << " ���������� ����� � ������:" << s.work << endl;
	cout << " �������������:" << s.effect << "\n" << endl;
	
	return out;
}

