#include <fstream>
#include <sstream>  
#include "cs.h"
#include "Utils.h"

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

void LoadCs(ifstream& fin, cs& s)
{
	fin >> s.id; fin.ignore(); getline(fin,s.name); fin >> s.quantity; fin >> s.work; fin >> s.effect;
}

void cs::EditCs()
{
	int edt_cs;

	cout << "Для редактирования параметра остановки или запуска цеха, выберите соответствующий пункт цифрой: " << endl;
	cout << "1. Запуск цеха" << endl;
	cout << "2. Остановка цеха" << endl;
	edt_cs = InputCheck(1, 2);
	if (edt_cs == 1)
	{
		if (work = quantity)
		{
			cout << "Все цеха запущены" << endl;
		}
		else
		{
			work += 1;
			cout << "Цех запущен" << endl;
		}
	}
	if (edt_cs == 2)
	{
		if (work == 0)
		{
			cout << "Количество работающих цехов нельзя уменьшить" << endl;
		}
		else
		{
			work -= 1;
			cout << "Цех остановлен" << endl;
		}
	}


}

istream& operator >> (istream& in, cs& s) // Ввод компрессорной станции
{
	cout << "Введите имя компрессорной станции: " << endl;
	cin.ignore(1000, '\n');
	cin.clear();
	getline(cin, s.name);
	cout << "Введите количество цехов: " << endl;
	s.quantity = InputCheck(1, INT_MAX);
	cout << "Введите количество работающих цехов: " << endl;
	s.work = InputCheck(0, s.quantity );
	cout << "Введите эффективность: " << endl;
	s.effect = InputCheck(0.0, DBL_MAX);
	return in;
}

ostream& operator << (ostream& out, cs& s) // Печать компрессорной станции
{
	cout << " Название:" << s.name << endl;
	cout << " Количество цехов всего:" << s.quantity << endl;
	cout << " Количество цехов в работе:" << s.work << endl;
	cout << " Эффективность:" << s.effect << "\n" << endl;
	
	return out;
}

