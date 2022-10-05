#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct pipe		//структура труба
{
	double length, diameter;	// длина, диаметр
	bool priznak;	// признак "в работе"
};

struct cs		// структура компрессорной станции
{
	string name;	// имя станции
	int quantity, work;	// количество цехов, количество цехов в работе
	double effect; // эффективность
};

void InputCheckInt(int& numb)
{
	while (true)
	{
		cin >> numb;
		if (cin.fail() || numb < 0)
		{
			cout << " Неправильный ввод, попробуйте еще раз" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			continue;
		}
		return;
	}
}
	
void InputCheckDouble(double& num)
{
	while (true)
	{
		cin >> num;
		if (cin.fail() || num <= 0)
		{
			cout << " Неправильный ввод, попробуйте еще раз" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			continue;
		}
		return;
	}
}
	
void InputCheckBool(bool& n)
{
	while (true)
	{
		cin >> n;
		if (cin.fail())
		{
			cout << " Неправильный ввод, попробуйте еще раз" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			continue;
		}
		return;
	}
}

pipe InputPipe()
{
	pipe p;
	cout << " Введите длину новой трубы:";
	InputCheckDouble(p.length);
	cout << " Введите диаметр новой трубы:";
	InputCheckDouble(p.diameter);
	p.priznak = false;
	return p;
}

void PrintPipe(pipe& p)
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

cs InputCs()
{
	cs s;
	cout << " Введите название для новой компрессорной станции: ";
	cin.ignore(1000, '\n');
	cin.clear();
	getline(cin, s.name);
	cout << " Введите количество цехов новой компрессорной станции: ";
	InputCheckInt(s.quantity);
	while (1)
	{
		if (s.quantity == 0)
		{
			cout << "Количество цехов не может быть равным 0, попробуйте еще раз" << endl;
			InputCheckInt(s.quantity);
		}
		else break;
	}
	cout << " Введите количество цехов в работе: ";
	InputCheckInt(s.work);
	while (1) {
		if (s.work > s.quantity)
		{
			cout << " Количество работающих цехов не может превышать количество всех цехов, попробуйте еще раз " << endl;
			InputCheckInt(s.work);
		}
		else break;
	}
	s.effect = (static_cast<double>(s.work) / s.quantity) * 100;
	return s;
}

void PrintCs(cs& s)
{
	if (s.quantity == 0) 
	{
		cout << "Компрессорная станция не введена" << endl;
	}
	else {
		cout << " Характеристики компрессорной станции:" << endl;
		cout << " Название:" << s.name << endl;
		cout << " Количество цехов всего:" << s.quantity << endl;
		cout << " Количество цехов в работе:" << s.work << endl;
		cout << " Эффективность:" << s.effect << "%" << "\n" << endl;
	}
}

void EditPipe(pipe& p)
{
	bool edt_p;
	if ((p.length == 0) || (p.diameter == 0))
	{
		cout << " Вы не ввели трубу, попробуйте еще раз" << endl;
	}
	else
	{
		cout << " Для редактирования признака трубы нажмите 1 или 0 (< 1 в ремонте >,< 0 не в ремонте>)" << endl;
		InputCheckBool(edt_p);
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
		InputCheckInt(edt_cs);
		if (edt_cs == 1)
		{
			if (s.work == s.quantity)
			{
				cout << "Все цеха запущены" << endl;
			}
			else
			{
				s.work += 1;
				s.effect = (static_cast<double>(s.work) / s.quantity) * 100;
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
				s.effect = (static_cast<double>(s.work) / s.quantity) * 100;
				cout << "Цех остановлен" << endl;
			}
		}
	
	}
}

void SaveObj(const pipe& p, const cs& s) 
{
	ofstream fout_pipe_cs;
	fout_pipe_cs.open("Out_pipe_cs.txt", ios::out);
	fout_pipe_cs << p.length << "\n" << p.diameter << "\n" << p.priznak << "\n";
	fout_pipe_cs << s.name << "\n" << s.quantity << "\n" << s.work << "\n" << endl;
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
			s.effect = ((static_cast<double>(s.work)) / s.quantity) * 100;;
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
	pipe tb{};
	cs kc{};
	menu();
	while (true)
	{
		cout << "Выберите пункт меню: ";
		InputCheckInt(value);
		if (value > 8 || value < 0)
		{
			cout << "Вы выбрали неправильный пункт, попробуйте еще раз " << endl;
		}
			switch (value)
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
								InputCheckInt(danet);
								if (danet < 1 || danet > 2)
								{
									cout << "Вы ввели неправильный пункт, попробуйте еще раз" << endl;
								}

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
						else
							exit(0);
					}
				}

				case 1:
				{
					tb = InputPipe();
					savepipe = false;
					break;
				}

				case 2:
				{
					kc = InputCs();
					savecs = false;
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
					LoadObj(tb,kc);
				}
				
			}
	}
}
