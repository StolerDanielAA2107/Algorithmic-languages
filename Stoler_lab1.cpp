#include <iostream>
#include <fstream>

using namespace std;

struct pipe		//структура труба
{
	double length;	// длина 
	double diameter; // диаметр
	int priznak;	// признак "в работе"
};

struct cs		// структура компрессорной станции
{
	string name;	// имя станции
	int quantity; // количество цехов 
	int effect;  // эффективность
};

pipe InputPipe()
{
	pipe y;
	cout << " Введите длину новой трубы: ";
	cin >> y.length;
	while (true)
	{
		if ((y.length) < 0)
		{
			cout << "Вы ввели неправильную длину трубы, попробуйте еще раз";
			cin >> y.length;
		}
		else
			break;
	}
	cout << " Введите диаметр новой трубы:";
	cin >> y.diameter;
	while (true)
	{
		if ((y.diameter) < 0)
		{
			cout << "Вы ввели неправильный диаметр трубы, попробуйте еще раз";
			cin >> y.diameter;
		}
		else
			break;
	}
	cout << " Введите признак: ( 1 для выбора признака <в работе>, 0 для выбора признака <не в работе>)";
	cin >> y.priznak;
	while (true)
	{
		if ((y.priznak > 1) || (y.priznak < 0))
		{
			cout << "Вы ввели неправильный признак трубы, попробуйте еще раз";
			cin >> y.priznak;
		}
		else
			break;
	}
	return y;
}

void PrintPipe(pipe y)
{
	cout << " Длина:" << y.length << endl;
	cout << " Диаметр:" << y.diameter << endl;
	if (y.priznak == 1)
	{
		cout << " Признак: в работе"<< "\n" << endl;
	}
	else 
	{
		cout << " Признак: не в работе" << "\n" << endl;
	}
}

cs InputCs()
{
	cs s;
	cout << " Введите имя для новой компрессорной станции: ";
	cin >> s.name;
	cout << " Введите количество цехов новой компрессорной станции: ";
	cin >> s.quantity;
	while (true)
	{
		if ((s.quantity) < 0)
		{
			cout << " Вы ввели неправильное количество цехов, попробуйте еще раз";
			cin >> s.quantity;
		}
		else
			break;
	}
	cout << "Введите эффективность новой компрессорной станции: ";
	cin >> s.effect;
	while (true)
	{
		if ((s.effect) < 0)
		{
			cout << "Вы ввели неправильную эффективность, попробуйте еще раз";
			cin >> s.effect;
		}
		else
			break;
	}
	return s;
}

void PrintCs(cs s)
{
	cout << " Имя:" << s.name << endl;
	cout << " Количество цехов:" << s.quantity << endl;
	cout << " Эффективность:" << s.effect << "\n" << endl;
}

void EditPipe(pipe& y)
{
	int e;
	double r;
	cout << "Для редактирования параметра выберите пункт" << endl;
	cout << "1. Диаметр" << endl;
	cout << "2. Длина" << endl;
	cout << "3. Признак" << endl;
	cin >> e;
	if ((e > 3) || (e < 1))
	{
		cout << "Вы выбрали неправильный пункт, попробуйте еще раз" << endl;
	}
	else
	{
		cout << "Введите новое значение параметра:" << endl;
		cin >> r;
	}
	if (e == 1)
	{
		 y.diameter = r;
	}

	if (e == 2)
	{
		y.length = r;
	}

	if (e == 3)
	{
		y.priznak = r;
	}
}

void EditCs(cs& s)
{
	int l;
	double t;
	cout << "Для редактирования параметра выберите пункт" << endl;
	cout << "1. Имя" << endl;
	cout << "2. Количество цехов" << endl;
	cout << "3. Эффективность" << "\n" << endl;
	cin >> l;
	if ((l > 3) || (l < 1))
	{
		cout << "Вы выбрали неправильный пункт, попробуйте еще раз" << endl;
	}

	else
	{
		cout << "Введите новое значение параметра:" << endl;
		cin >> t;
	}
	if (l == 1)
	{
		s.name = t;
	}

	if (l == 2)
	{
		s.quantity = t;
	}

	if (l == 3)
	{
		s.effect = t;
	}
	
}

void SaveObj(const pipe& y, const cs& s)
{
	ofstream fout_pipe;
	ofstream fout_cs;
	fout_pipe.open("Out_pipe.txt", ios::out);
	fout_pipe << y.length << "\n" << y.diameter << "\n" << y.priznak << "\n" << endl;


	fout_cs.open("Out_cs.txt", ios::out);
	fout_cs <<  s.name << "\n" <<  s.effect << "\n" <<  s.quantity  << "\n" << endl;
	fout_pipe.close();
	fout_cs.close();
}

pipe LoadPipe()
{
	pipe y;
	ifstream fin_pipe;
	fin_pipe.open("Out_pipe.txt", ios::in);
    fin_pipe >> y.length;
	fin_pipe >> y.diameter;
	fin_pipe >> y.priznak;
	fin_pipe.close();
	return y;
}

cs LoadCs()
{
	cs s;
	ifstream fin_cs;
	fin_cs.open("Out_cs.txt", ios::in);
	fin_cs >> s.name;
	fin_cs >> s.effect;
	fin_cs >> s.quantity;
	fin_cs.close();
	return s;
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
	int value;
	pipe tb{};
	cs kc{};	
	while (true)
	{
		menu();
		cout << " Выберите пункт меню" << "\n" << endl;
		cin >> value;
			if ((value > 7) || (value < 0))
			{
				cout << " Вы выбрали неправильный пункт, попробуйте еще раз" << "\n" << endl;
			}
		if (value == 0)
		{
			exit(0);
		}
			switch (value)
			{
				case 1:
				{
					tb = InputPipe();
					break;
				}

				case 2:
				{
					kc = InputCs();
					break;
				}

				case 3:
				{
					cout << " Характеристики трубы:" << endl;
					PrintPipe(tb);
					cout << " Характеристики компрессорной станции" << endl;
					PrintCs(kc);
					break;
				}

				case 4:
				{
					EditPipe(tb);
					break;
				}
				case 5:
				{
					EditCs(kc);
				}
				case 6:
				{
					SaveObj(tb, kc);
				}

				case 7:
				{					
					tb = LoadPipe();
					kc = LoadCs();
				}
			}
	}
}
