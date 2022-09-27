#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct pipe		//структура труба
{
	double length, diameter;	// длина, диаметр
	int priznak;	// признак "в работе"
};

struct cs		// структура компрессорной станции
{
	string name;	// имя станции
	int quantity, work, effect;	// количество цехов, количество цехов в работе, эффективность
};

pipe InputPipe(bool& savepipe)
{
	pipe p;
	cout << " Введите длину новой трубы:";
	while (true)
	{
		cin >> p.length;
		if 
			(cin.fail() || (p.length <= 0)) 
		{
			cout << " Неправильный ввод длины трубы, попробуйте еще раз" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			continue;
		}
		else
			break;
	}
	cout << " Введите диаметр новой трубы:";
	while (true)
	{
		cin >> p.diameter;
		if (cin.fail() ||(p.diameter == 0) || (p.diameter < 0))
		{
			cout << "Неправильный ввод, попробуйте еще раз" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			continue;
		}
		else
			break;
	}
	p.priznak = 0;
	savepipe = false;
	return p;
}

void PrintPipe(pipe p)
{
	if ((p.length == 0) || (p.diameter == 0))
	{
		cout << "Труба не введена" << endl;
	}
	else
	{
		cout << "Характеристики трубы:" << endl;
		cout << " Длина:" << p.length << endl;
		cout << " Диаметр:" << p.diameter << endl;
		if (p.priznak == 1)
		{
			cout << " Признак: в ремонте" << "\n" << endl;
		}
		if (p.priznak == 0)
		{
			cout << " Признак: не в ремонте" << "\n" << endl;
		}
	}
}

cs InputCs(bool& savecs)
{
	cs s;
	cout << " Введите название для новой компрессорной станции: ";
	cin.ignore(1000, '\n');
	cin.clear();
	getline(cin, s.name);
	cout << " Введите количество цехов новой компрессорной станции: ";
	while (true)
	{
		cin >> s.quantity;
		if (cin.fail() || (s.quantity) < 1)
		{
			cout << "Неправильный ввод, попробуйте еще раз" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			continue;
		}
		else
			break;
	}
	cout << " Введите количество цехов в работе: ";
	while (true)
	{
		cin >> s.work;
		if (cin.fail() || (s.work < 0))
		{
			cout << "Неправильный ввод, попробуйте еще раз" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			continue;
		}
		if (s.work > s.quantity)
		{
			cout << " Введенное количество цехов в работе превышает количество всех цехов, введите новое значение: ";
			cin >> s.work;
		}
		else
			break;
	}
	cout << " Введите эффективность новой компрессорной станции: ";
	while (true)
	{
		cin >> s.effect;
		if (cin.fail() ||(s.effect) < 0)
		{
			cout << " Вы ввели неправильную эффективность, попробуйте еще раз";
			cin.clear();
			cin.ignore(1000, '\n');
			continue;
		}
		else
			break;
	}
	savecs = false;
	return s;
}

void PrintCs(cs s)
{
	if (s.quantity == 0) 
	{
		cout << "Компрессорная станция не введена" << endl;
	}
	else {
		cout << "Характеристики компрессорной станции:" << endl;
		cout << " Название:" << s.name << endl;
		cout << " Количество цехов всего:" << s.quantity << endl;
		cout << " Количество цехов в работе:" << s.work << endl;
		cout << " Эффективность:" << s.effect << "\n" << endl;
	}
}

void EditPipe(pipe& p, bool& savepipe)
{
	int e;
	if ((p.length == 0) || (p.diameter == 0))
	{
		cout << "Вы не ввели трубу, попробуйте еще раз" << endl;
	}
	else
	{
		cout << "Для редактирования признака трубы нажмите 1 или 0 (< 1 в ремонте >,< 0 не в ремонте>)" << endl;
		while (true)
		{
			cin >> e;
			if ((e > 1) || (e < 0) || cin.fail())
			{
				cout << "Вы ввели неправильное значение, попробуйте еще раз" << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				continue;
			}
			else
				break;
		}
		p.priznak = e;
		savepipe = false;
	}
}

void EditCs(cs& s, bool savecs)
{
	int l;
	if (s.quantity == 0)
	{
		cout << "Компрессорная станция не введена" << endl;
	}
	else {
		cout << "Для редактирования параметра остановки или запуска цеха, выберите соответствующий пункт цифрой: " << endl;
		cout << "1. Запуск цеха" << endl;
		cout << "2. Остановка цеха" << endl;
		while (true)
		{
			cin >> l;
			if ((l > 2) || (l < 1) || cin.fail())
			{
				cout << "Вы выбрали неправильный пункт, попробуйте еще раз" << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				continue;
			}
			else 
				break;
		}
		if (l == 1)
		{
			if (s.work == s.quantity)
			{
				cout << "Все цеха запущены" << endl;
			}
			else
			{
				s.work += 1;
			}
		}
		if (l == 2)
		{
			if (s.work == 0)
			{
				cout << "Количество работающих цехов нельзя уменьшить" << endl;
			}
			else
			{
				s.work -= 1;
			}
		}
		savecs = false;
	}
}

void SaveObj(const pipe& p, const cs& s, bool& savepipe, bool& savecs)
{
	ofstream fout_pipe_cs;
	fout_pipe_cs.open("Out_pipe_cs.txt", ios::out);
	fout_pipe_cs << p.length << "\n" << p.diameter << "\n" << p.priznak << "\n";
	fout_pipe_cs << s.name << "\n" << s.quantity << "\n" << s.work << "\n" << s.effect << "\n" << endl;
	fout_pipe_cs.close();
	savepipe = true;
	savecs = true;
}

void LoadObj(pipe& p, cs& s)
{
	ifstream fin_pipe_cs;
	fin_pipe_cs.open("Out_pipe_cs.txt", ios::in);
	if (!fin_pipe_cs.is_open())
	{
		cout << "Ошибка открытия файла" << endl;
	}
	else
	{
		fin_pipe_cs >> p.length;
		fin_pipe_cs >> p.diameter;
		fin_pipe_cs >> p.priznak;
		fin_pipe_cs >> s.name;
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
	int value, danet ;
	pipe tb{};
	cs kc{};
	bool savepipe = true, savecs = true;
	menu();
	while (true)
	{
		cout << "Выберите пункт меню: ";
		cin >> value;
		if ((cin.fail() || (value > 7) || (value < 0)))
		{	
			cout << "Неправильный ввод, попробуйте еще раз" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			continue;
		}
			switch (value)
			{
				case 0:
				{
					if (!savepipe || !savecs)
					{
						cout << "Параметры не были сохранены, сохранить их?" << endl;
						cout << "1.Да" << endl;
						cout << "2.Нет" << endl;
						cin >> danet;
						if (danet == 1)
						{
							SaveObj(tb, kc, savepipe, savecs);
							break;
						}
						if (danet == 2)
						{
							exit(0);
						}
					} else 
					exit(0);
				}
				case 1:
				{
					tb = InputPipe(savepipe);
					break;
				}

				case 2:
				{
					kc = InputCs(savecs);
					break;
				}

				case 3:
				{
					PrintPipe(tb);
					PrintCs(kc);
					break;
				}

				case 4:
				{
					EditPipe(tb, savepipe);
					break;
				}
				case 5:
				{
					EditCs(kc, savecs);
					break;
				}
				case 6:
				{
					SaveObj(tb, kc, savepipe, savecs);
					cout << "Сохранение выполнено." << endl;
					break;
				}
				case 7:
				{				
					LoadObj(tb,kc);
				}
			}
	}
}
