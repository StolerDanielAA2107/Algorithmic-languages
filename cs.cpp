#include "cs.h"
#include "Utils.h"

using namespace std;

istream& operator >> (istream& in, cs& s) // ���� ������������� �������
{
	cout << "������� ��� ������������� �������: " << endl;
	cin.ignore(1000, '\n');
	cin.clear();
	getline(cin, s.name);
	cout << "������� ���������� �����: " << endl;
	s.quantity = InputCheck(0, INT_MAX);
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
		cout << " �������������� ������������� �������:" << endl;
		cout << " ��������:" << s.name << endl;
		cout << " ���������� ����� �����:" << s.quantity << endl;
		cout << " ���������� ����� � ������:" << s.work << endl;
		cout << " �������������:" << s.effect << "\n" << endl;
	}
	return out;
}

void cs::EditCs(cs& s)
{
	int edt_cs;
	if (s.quantity == 0)
	{
		cout << "������������� ������� �� �������" << endl;
	}
	else {
		cout << "��� �������������� ��������� ��������� ��� ������� ����, �������� ��������������� ����� ������: " << endl;
		cout << "1. ������ ����" << endl;
		cout << "2. ��������� ����" << endl;
		edt_cs = InputCheck(0, 3);
		if (edt_cs == 1)
		{
			if (s.work == s.effect)
			{
				cout << "��� ���� ��������" << endl;
			}
			else
			{
				s.work += 1;
				cout << "��� �������" << endl;
			}
		}
		if (edt_cs == 2)
		{
			if (s.work == 0)
			{
				cout << "���������� ���������� ����� ������ ���������" << endl;
			}
			else
			{
				s.work -= 1;
				cout << "��� ����������" << endl;
			}
		}

	}
}