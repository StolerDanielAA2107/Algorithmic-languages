#include "cs.h"
#include "Utils.h"

using namespace std;

istream& operator >> (istream& in, cs& s) // Ввод компрессорной станции
{
	cout << "Введите имя компрессорной станции: " << endl;
	cin.ignore(1000, '\n');
	cin.clear();
	getline(cin, s.name);
	cout << "Введите количество цехов: " << endl;
	s.quantity = InputCheck(0, INT_MAX);
	cout << "Введите количество работающих цехов: " << endl;
	s.work = InputCheck(0, s.quantity );
	cout << "Введите эффективность: " << endl;
	s.effect = InputCheck(0.0, DBL_MAX);
	return in;
}

ostream& operator << (ostream& out, cs& s) // Печать компрессорной станции
{
	if (s.quantity == 0)
	{
		cout << "Компрессорная станция не введена" << "\n" << endl;
	}
	else {
		cout << " Характеристики компрессорной станции:" << endl;
		cout << " Название:" << s.name << endl;
		cout << " Количество цехов всего:" << s.quantity << endl;
		cout << " Количество цехов в работе:" << s.work << endl;
		cout << " Эффективность:" << s.effect << "\n" << endl;
	}
	return out;
}

void cs::EditCs(cs& s)
{
	int edt_cs;
	if (s.quantity == 0)
	{
		cout << "Компрессорная станция не введена" << endl;
	}
	else {
		cout << "Для редактирования параметра остановки или запуска цеха, выберите соответствующий пункт цифрой: " << endl;
		cout << "1. Запуск цеха" << endl;
		cout << "2. Остановка цеха" << endl;
		edt_cs = InputCheck(0, 3);
		if (edt_cs == 1)
		{
			if (s.work == s.effect)
			{
				cout << "Все цеха запущены" << endl;
			}
			else
			{
				s.work += 1;
				cout << "Цех запущен" << endl;
			}
		}
		if (edt_cs == 2)
		{
			if (s.work == 0)
			{
				cout << "Количество работающих цехов нельзя уменьшить" << endl;
			}
			else
			{
				s.work -= 1;
				cout << "Цех остановлен" << endl;
			}
		}

	}
}