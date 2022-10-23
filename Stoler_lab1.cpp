#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "pipe.h"
#include "cs.h"
#include "utils.h"
#include <unordered_map>

using namespace std;

void menu()// меню
{
	setlocale(LC_ALL, "Russian");
	cout << " 1. Добавить трубу" << endl;
	cout << " 2. Добавить КС" << endl;
	cout << " 3. Просмотр всех объектов" << endl;
	cout << " 4. Редактировать трубу" << endl;
	cout << " 5. Редактировать КС" << endl;
	cout << " 6. Поиск объектов" << endl;
	cout << " 7. Сохранить в файл" << endl;
	cout << " 8. Загрузить из файла" << endl;
	cout << " 9. Удалить объекты" << endl;
	cout << " 0. Выход" << "\n" << endl;
}

bool FileExist(string name)
{
	bool isExist = false;
	std::ifstream fin(name.c_str());

	if (fin.is_open())
		isExist = true;

	fin.close();
	return isExist;
}
istream& inStr(istream& in, string& s)
{
	size_t l;
	in.read((char*)&l, sizeof(l));
	s = string(l, ' ');
	in.read(s.data(), l);
	return in;
}
void file2map(istream& in_file, unordered_map<string, string>& m)
{
	ifstream ifile;
	string name;
	cout << "Введите название файла из которого загрузить данные" << endl;
	cin.ignore(1000, '\n');
	cin.clear();
	getline(cin, name);
	ifile.open(name, ios::in);
	if (ifile.is_open() == 0)
	{
		cout << "Ошибка открытия файла" << endl;
	}
	else
		if (ifile.peek() == EOF)
		{
			cout << "Ошибка чтения: нет данных в файле" << endl;
		}
		else
			if (ifile.is_open())
			{
				size_t l;
				in_file.read((char*)&l, sizeof(l));
				for (int i = 0; i < l; ++i)
				{
					int key;
					inStr(in_file, key);
					inStr(in_file, m[key]);
				}
				
				cout << "Загрузка выполнена." << endl;
			}
	ifile.close();
}
int main()  // тело программы
{
	int danet;
	bool savepipe = true, savecs = true;
	unordered_map <int, pipe> pipes;
	unordered_map <int, cs> css;
	menu();
	while (1)
	{
		cout << "Выберите пункт:" << endl;
		switch (InputCheck(0, 9))
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
						danet = InputCheck(1, 2);
						if (danet == 1)
						{
							//SaveObj(tb, kc);
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
			break;
		}
		case 4:// изменение трубы
		{
			if (pipes.size() == 0)
			{
				cout << "Трубы не добавлены" << endl;
				break;
			}
			cout << "Введите идентификатор трубы:" << endl;
			auto id = InputCheck(1, 10000);

			if (id > pipes.size())
			{
				cout << "Трубы с данным идентификатором не существует" << endl;
				break;
			}
			auto& item = *pipes.find(id);
			if (pipes.find(id) != pipes.end())
			{
				auto& pipe = item.second;
				pipe.EditPipe();
			}
			savepipe = false;
			break;
		}
		case 5:// изменение КС
		{
			if (css.size() == 0)
			{
				cout << "КС не добавлены" << endl;
				break;
			}
			cout << "Введите id Компрессорной станции:" << endl;
			auto id = InputCheck(1, 10000);

			if (id > css.size())
			{
				cout << "КС с данным идентификатором не существует" << endl;
				break;
			}
			auto& item = *css.find(id);
			if (css.find(id) != css.end())
			{
				auto& cs = item.second;
				cs.EditCs();
			}
			savecs = false;
			break;
		}
		/*case 6:
		{

		}*/
		case 7:
		{
			ofstream ofile;
			string name;
			cout << "Введите название файла для сохранения:" << endl;
			cin.ignore(1000, '\n');
			cin.clear();
			getline(cin, name);
			ofile.open(name, ios::out);
			if (ofile.is_open())
			{
				for (const auto& tb : pipes)
					SavePipe(ofile, tb.second);
				for (const auto& kc : css)
					SaveCs(ofile, kc.second);
				ofile.close();
			}
			cout << "Сохранение выполнено." << endl;
			savepipe = true;
			savecs = true;
			break;


		}
		case 8:
		{
			ifstream in("data", ios::binary);
			file2map(in, tb);

			for (auto& s : p) cout << s.first << "  " << s.second << endl;
		}
		}
	}
}
	

