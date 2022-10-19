#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include<unordered_map>
#include "pipe.h"
#include "utils.h"

using namespace std;

struct cs		//класс компрессорной станции
{
	string name;	// имя станции
	int quantity = 0;	// количество цехов, количество цехов в работе
	int work;
	double effect; // эффективность
};

template <typename T>

T InputCheck(T min, T max)
{
	T x{};
	while ((cin >> x).fail() || (x <= min) || (x >= max))
	{
		cin.clear();
		cin.ignore(10000, '\n');
	}
	return x;
}

istream& operator >> (istream& in, cs& s) // Ввод компрессорной станции
{
	cout << "Введите имя компрессорной станции: " << endl;
	cin.ignore(1000, '\n');
	cin.clear();
	getline(cin, s.name);
	cout << "Введите количество цехов: " << endl;
	s.quantity = InputCheck(0, 2147483647);
	cout << "Введите количество работающих цехов: " << endl;
	s.work = InputCheck(0, s.quantity);
	cout << "Введите эффективность: " << endl;
	s.effect = InputCheck(0.0, 2000000000000000000.0);
	return in;
}
	
ostream& operator << (ostream& out, const cs& s) // Печать компрессорной станции
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
		cout << " Эффективность:" << s.effect  << "\n" << endl;
	}
	return out;
}

void EditPipe(pipe& p)
{
	p.EditPipe();
}

void EditCs(cs& s)
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
		edt_cs = InputCheck(0,3);
		if (edt_cs == 1)
		{
			if (s.work == s.quantity)
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

void SaveObj(const pipe& p, const cs& s) 
{
	ofstream fout_pipe_cs;
	fout_pipe_cs.open("Out_pipe_cs.txt", ios::out);
	//fout_pipe_cs << p.length << "\n" << p.diameter << "\n" << p.priznak << "\n";
	fout_pipe_cs << s.name << "\n" << s.quantity << "\n" << s.work << "\n" << s.effect << endl;
	fout_pipe_cs.close();
}

void LoadObj(pipe& p, cs& s)
{
	ifstream fin_pipe_cs;
	fin_pipe_cs.open("Out_pipe_cs.txt", ios::in);
	if (fin_pipe_cs.is_open() == 0)
	{
		cout << "Ошибка открытия файла" << endl;
	}
	else
		if (fin_pipe_cs.peek() == EOF)
		{
			cout << "Ошибка чтения: нет данных в файле." << endl;
		}
		else
		{
			fin_pipe_cs >> p.length;
			fin_pipe_cs >> p.diameter;
			fin_pipe_cs >> p.priznak;
			fin_pipe_cs.ignore();
			getline(fin_pipe_cs, s.name);
			fin_pipe_cs >> s.quantity;
			fin_pipe_cs >> s.work;
			fin_pipe_cs >> s.effect;
			fin_pipe_cs.close();
			cout << "Загрузка выполнена." << endl;
		}
}

void menu()// меню
{
	setlocale(LC_ALL, "Russian");
	cout << " 1. Добавить трубу" << endl;
	cout << " 2. Добавить КС" << endl;
	cout << " 3. Просмотр всех объектов" << endl;
	cout << " 4. Редактировать трубу" << endl;
	cout << " 5. Редактировать КС" << endl;
	cout << " 6. Сохранить в файл" << endl;
	cout << " 7. Загрузить из файла" << endl;
	cout << " 0. Выход" << "\n" << endl;
}

int main()  // тело программы
{
	int value, danet, numb;
	double num;
	bool savepipe = true, savecs = true;
	pipe tb;
	unordered_map <int, pipe> pipes ({});
	cs kc;
	int n = 5;
	menu();
	while (1)
	{
		cout << " Выберите пункт:" << endl;
		switch (InputCheck(-1, 8))
		{
		case 0:
		{
			while (1)
			{
				if (!savepipe || !savecs)
				{
					cout << "Параметры не были сохранены, сохранить их?" << endl;
					cout << "1.Да" << endl;
					cout << "2.Нет" << endl;
					while (true) {
						danet = InputCheck(0, 3);
						if (danet == 1)
						{
							SaveObj(tb, kc);
							cout << "Сохранение выполнено." << endl;
							savepipe = true;
							savecs = true;
							break;
						}
						if (danet == 2)
						{
							exit(0);
						}
					}
				}
				else exit(0);
			}

		case 1:
		{
			cin >> tb;
			//pipes.insert(tb);
			savepipe = false;
			break;			
		case 2:
		{
			cin >> kc;
			savecs = false;
			break;
		}

		case 3:
		{
			cout << tb;
			cout << kc;
			break;
		}

		case 4:
		{
			EditPipe(tb);
			savepipe = false;
			break;
		}
		case 5:
		{
			EditCs(kc);
			savecs = false;
			break;
		}
		case 6:
		{
			SaveObj(tb, kc);
			cout << "Сохранение выполнено." << endl;
			savepipe = true;
			savecs = true;
			break;
		}
		case 7:
		{
			LoadObj(tb, kc);
		}

		}
		}
		}
	}
}