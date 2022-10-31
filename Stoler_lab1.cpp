#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

#include "pipe.h"
#include "cs.h"
#include "utils.h"

using namespace std;

unordered_map <int, pipe> pipes;
unordered_map <int, cs> css;

vector <int> StringToNum(string& str)
{
	vector <int> vec;
	stringstream ss;
	string s;
	double d;
	ss << str;
	while (!ss.eof())
	{
		ss >> s;
		if (stringstream(s) >> d)
			vec.emplace_back(d);
		s = "";
	}
	return vec;
}

void menu()// меню
{
	setlocale(LC_ALL, "Russian");
	cout << " 1. Добавить трубу" << endl;
	cout << " 2. Добавить КС" << endl;
	cout << " 3. Просмотр всех объектов" << endl;
	cout << " 4. Редактирование труб" << endl;
	cout << " 5. Редактирование КС" << endl;
	cout << " 6. Поиск объектов" << endl;
	cout << " 7. Сохранить в файл" << endl;
	cout << " 8. Загрузить из файла" << endl;
	cout << " 9. Удалить объекты" << endl;
	cout << " 0. Выход" << "\n" << endl;
}

void NoAdd_Pipe()
{
	if (pipes.size() == 0)
	{
		cout << "Трубы не добавлены" << endl;
	}
}

void NoAdd_Cs()
{
	if (css.size() == 0)
	{
		cout << "КС не добавлены" << endl;
	}
}

void PrintAll()
{
	NoAdd_Pipe();
	NoAdd_Cs();

	for (auto& key_value : pipes)
	{
		int key = key_value.first;
		pipe value = key_value.second;
		cout << "id трубы:" << key << endl;
		cout << value << endl;
	}

	for (const auto& key_value : css)
	{
		int key = key_value.first;
		cs value = key_value.second;
		cout << "id КС:" << key << endl;
		cout << value << endl;
	}
}

void Edt_p()
{
	vector <int> str;
	string id;
	cout << "Введите id труб(-ы):" << endl;
	cin.ignore(1000, '\n');
	cin.clear();
	getline(cin, id);
	str = StringToNum(id);
	for (double i : str)
	{
		auto tb = pipes.find(i);
		if (tb != pipes.end())
		{
			(*tb).second.EditPipe();
		}
		else
		{
			cout << "Id " << i << " не найден" << endl;
		}
	}
}

void Edt_cs()
{
	vector <int> str;
	string id;
	cout << "Введите id компрессорной-(ых) станции-(й):" << endl;
	cin.ignore(1000, '\n');
	cin.clear();
	getline(cin, id);
	str = StringToNum(id);
	for (double i : str)
	{
		auto kc = css.find(i);
		if (kc != css.end())
		{
			(*kc).second.EditCs();
		}
		else
		{
			cout << "Id " << i << " не найден" << endl;
		}
	}
}

void Search()
{
	pipe tb;
	int ob;
	NoAdd_Pipe();
	NoAdd_Cs();
	bool find = false;
	cout << "Введите по какому объекту сделать поиск:" << endl;
	cout << "1. Труба" << endl;
	cout << "2. Компрессорная станция" << endl;
	ob = InputCheck(1, 2);

	if (ob == 1)
	{
		cout << "id найденных труб с признаком <в ремонте>:" << endl;
		for (const auto& tb : pipes)
		{
			if (tb.second.priznak == 1)
			{
				cout << tb.first << endl;
				bool find = true;
			}

		}
	}
	if (ob == 2)
	{
		int a;
		cout << "Выберите параметр поиска:" << endl;
		cout << "1. По названию" << endl;
		cout << "2. По еффективности" << endl;
		a = InputCheck(1, 2);
		if (a == 1)
			{
				cout << "Введите название станции:" << endl;
				string fname; // findname
				cin.ignore(1000, '\n');
				cin.clear();
				getline(cin, fname);
				cout << "id найденных КС с введенным названием:" << endl;
				for (const auto& kc : css)
				{
					if (kc.second.name.find(fname) != std::string::npos)
					{
						cout << kc.first << '\n';
					}
				}
			}
		if (a == 2)
			{
				cout << "Введите эффективность:" << endl;
				double eff;
				eff = InputCheck(0.0, DBL_MAX);

				cout << "id найденных КС с введенной эффективностью:" << endl;
				for (const auto& kc : css)
				{
					if (kc.second.effect == eff)
					{
						cout << kc.first << endl;
					}
				}
			}
	}
}

void SaveAll()
{
	ofstream ofile; // output file
	string name;
	cout << "Введите название файла для сохранения:" << endl;
	cin.ignore(1000, '\n');
	cin.clear();
	getline(cin, name);
	auto sp = pipes.size();
	auto sk = css.size();
	ofile.open(name, ios::out);
	if (ofile.is_open())
	{
		ofile << sp << "\n"; // запись количества труб
		ofile << sk << "\n"; // запись количества КС
		for (const auto& tb : pipes)
			SavePipe(ofile, tb.second);
		for (const auto& kc : css)
			SaveCs(ofile, kc.second);
		ofile.close();
	}
	cout << "Сохранение выполнено." << endl;
}

void LoadAll()
{
	ifstream ifile; //input file
	string name;
	cout << "Введите название файла из которого загрузить данные:" << endl;
	cin.ignore(1000, '\n');
	cin.clear();
	getline(cin, name);
	ifile.open(name, ios::in);

	if (ifile.is_open() == 0)
	{
		cout << "Ошибка открытия файла" << endl;
	}
	else if (ifile.peek() == EOF)
		{
			cout << "Ошибка чтения: нет данных в файле." << endl;
		}
		else
		{
			ifile >> pipe::MaxID; // количествo труб
			ifile >> cs::MaxID; //  количествo КС
			for (int i = 1; i <= pipe::MaxID; i++)
			{
				pipe tb = pipe();
				LoadPipe(ifile, tb);
				pipes.insert({ i, tb });
			}

			for (int i = 1; i <= cs::MaxID; i++)
			{
				cs kc = cs();
				LoadCs(ifile, kc);
				css.insert({ i, kc });
			}
			ifile.close();
			cout << "Загрузка выполнена." << endl;
		}
	++pipe::MaxID;
	++cs::MaxID;
}

void Delete()
{
	vector <int> str;
	string s;
	int elem;
	cout << "Введите какой объект вы хотите удалить:" << endl;
	cout << "1. Труба" << endl;
	cout << "2. Компрессорная станция" << endl;
	elem = InputCheck(1, 2);
	if (elem == 1)
	{
		cout << "Введите id объекта (-ов):" << endl;
		cin.ignore(1000, '\n');
		cin.clear();
		getline(cin, s);
		str = StringToNum(s);
		for (double i : str)
		{
			auto tb = pipes.find(i);
			if (tb != pipes.end())
			{
				pipes.erase(i);
				cout << "Объект удален" << endl;
			}
			else
			{
				cout << "Id " << i << " не найден" << endl;
			}
		}
	}

	if (elem == 2 && pipes.contains(elem) == 1)
	{
		cout << "Введите id объекта (-ов):" << endl;
		cin.ignore(1000, '\n');
		cin.clear();
		getline(cin, s);
		str = StringToNum(s);
		for (double i : str)
		{
			auto kc = css.find(i);
			if (kc != css.end())
			{
				css.erase(i);
				cout << "Объект удален" << endl;
			}
			else
			{
				cout << "Id " << i << " не найден" << endl;
			}
		}
	}
}

int main()  // тело программы
{
	bool savepipe = true, savecs = true;
	menu();
	while (1)
	{
		cout << "Выберите пункт:" << endl;
		switch (InputCheck(0, 9))
		{
			case 0:
			{
				while (1) // обязан быть, так как после сохранения происходит баг
				{
					if (!savepipe || !savecs)
					{
						cout << "Параметры не были сохранены, сохранить их?" << endl;
						cout << "1.Да" << endl;
						cout << "2.Нет" << endl;
						int danet;
						while (true) {
							danet = InputCheck(1, 2);
							if (danet == 1)
							{
								SaveAll();
								exit(0);
								savepipe = true;
								savecs = true;
								break;
							}
							if (danet == 2)
							{
								exit(0);
							}
						}
					} else exit(0);
				}
			}
			case 1: //ввод трубы и запись в контейнер
			{
				pipe tb = pipe();
				cin >> tb;
				pipes.insert({ tb.id, tb });
				++pipe::MaxID;
				savepipe = false;
				break;
			}
			case 2: //ввод КС и запись в контейнер
			{
				cs kc = cs();
				cin >> kc;
				css.insert({ kc.id, kc });
				++cs::MaxID;
				savecs = false;
				break;
			}
			case 3:// просмотр всех объектов
			{
				PrintAll();
				break;
			}
			case 4:// изменение трубы
			{
				Edt_p();
				savepipe = false;
				break;
			}
			case 5:// изменение КС
			{
				Edt_cs();
				savecs = false;
				break;
			}
			case 6: // поиск
			{
				Search();
				break;
			}
			case 7: // сохранение
			{
				if (pipes.size() == 0 && css.size() == 0)
				{
					cout << "Объекты не добавлены" << endl;
					break;
				} else SaveAll();
				savepipe = true;
				savecs = true;
				break;
			}
			case 8: // загрузка
			{
				LoadAll();
				break;

			}
			case 9: // удаление объектов
			{
				Delete();
				break;
			}
		}
	}
}
