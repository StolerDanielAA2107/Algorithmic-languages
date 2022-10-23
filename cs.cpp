#include "cs.h"
#include "Utils.h"
#include <fstream>
#include <sstream>  // ������ getline

int cs::MaxID = 1;

using namespace std;

cs::cs()
{
	id = MaxID;
	name = "";
	quantity = 0;
	work = 0;
	effect = 0.0;
}

void SaveCs(ofstream& fout, const cs& s)
{
	fout << s.id << "\n" << s.name << "\n" << s.quantity << "\n" << s.work << "\n" << s.effect << endl;
}

void cs::EditCs()
{
	int edt_cs;

	cout << "��� �������������� ��������� ��������� ��� ������� ����, �������� ��������������� ����� ������: " << endl;
	cout << "1. ������ ����" << endl;
	cout << "2. ��������� ����" << endl;
	edt_cs = InputCheck(1, 2);
	if (edt_cs == 1)
	{
		if (work = quantity)
		{
			cout << "��� ���� ��������" << endl;
		}
		else
		{
			work += 1;
			cout << "��� �������" << endl;
		}
	}
	if (edt_cs == 2)
	{
		if (work == 0)
		{
			cout << "���������� ���������� ����� ������ ���������" << endl;
		}
		else
		{
			work -= 1;
			cout << "��� ����������" << endl;
		}
	}


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
	if (s.quantity == 0)
	{
		cout << "������������� ������� �� �������" << "\n" << endl;
	}
	else {
		cout << " ��������:" << s.name << endl;
		cout << " ���������� ����� �����:" << s.quantity << endl;
		cout << " ���������� ����� � ������:" << s.work << endl;
		cout << " �������������:" << s.effect << "\n" << endl;
	}
	return out;
}
