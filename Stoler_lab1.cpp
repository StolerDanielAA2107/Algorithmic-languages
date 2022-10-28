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
	cout << " 4. Редактирование труб" << endl;
	cout << " 5. Редактирование КС" << endl;
	cout << " 6. Поиск объектов" << endl;
	cout << " 7. Сохранить в файл" << endl;
	cout << " 8. Загрузить из файла" << endl;
	cout << " 9. Удалить объекты" << endl;
	cout << " 0. Выход" << "\n" << endl;
}

void NoAdd_Pipe(unordered_map <int, pipe> pipes)
{
	if (pipes.size() == 0)
	{
		cout << "Трубы не добавлены" << endl;
	}
}

void NoAdd_Cs(unordered_map <int, cs> css)
{
	if (css.size() == 0)
	{
		cout << "КС не добавлены" << endl;
	}
}

int main()  // тело программы
{
	bool savepipe = true, savecs = true;
	unordered_map <int, pipe> pipes;
	unordered_map <int, cs> css;
	unordered_map <int, pipe> timeless_pipes;
	menu();
	while (1)
	{
		int max_p = pipes.size(); // размер контейнера труб (понадобится для того чтобы не писать проверки)
		int max_cs = css.size(); // то же самое для кс
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
					int danet;
					while (true) {
						danet = InputCheck(1, 2);
						if (danet == 1)
						{
							//SavePipe(tb);
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
			NoAdd_Pipe(pipes);
			NoAdd_Cs(css);

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
			cout << "Введите идентификатор трубы:" << endl;
			auto id = InputCheck(1, max_p);
			
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
			cout << "Введите id Компрессорной станции:" << endl;
			auto id = InputCheck(1, max_cs);

			auto& item = *css.find(id);
			if (css.find(id) != css.end())
			{
				auto& cs = item.second;
				cs.EditCs();
			}
			savecs = false;
			break;
		}
		case 6: // поиск
		{
			pipe tb;
			int ob,sv;
			//NoAdd_Pipe(pipes);
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
				if (find == false)
				{
					cout << "Не найдено" << endl;
				}
				if (find == true)
				{
					cout << "Сохранить найденные трубы?:" << endl;
					cout << "1. Да" << endl;
					cout << "2. Нет" << endl;
					sv = InputCheck(1, 2); //saveobjects

					if (sv == 1)
					{
						for (const auto& tb : pipes)
						{
							if (tb.second.priznak == 1)
							{
								pipe tb = pipe();
								timeless_pipes.insert({ tb.id, tb });
								++pipe::MaxID;

							}
						}
						pipes.clear();

						//pipes.insert({});
						//++pipe::MaxID;
						savepipe = false;
						break;
					}
					if (sv == 2)
					{
						continue;
					}
				}
			}
			if (ob == 2)
			{
				int a;
				cout << "Выберите параметр поиска:" << endl;
				cout << "1. По названию" << endl;
				cout << "2. По количеству незадействованных цехов" << endl;
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
				/*if (a == 2)
				{
					cout << "Введите количество незадействованных цехов:" << endl;
					
					ceh = InputCheck(1,)
					{
						cout << "id найденных КС с таким количеством:" << endl;
						for (const auto& kc : css)
						{
							if (kc.second. == name)
								cout << kc.first << endl;
						}
					}
				}*/
			}
			break;
		}
		case 7: // сохранение
		{
			if (pipes.size() == 0 && css.size() == 0)
			{
				cout << "Объекты не добавлены" << endl;
				break;
			}

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
			savepipe = true;
			savecs = true;
			break;


		}
		case 8: // загрузка
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
				else
					if (ifile.peek() == EOF)
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
								pipes.insert({i, tb});
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
			break;
		
		}
		case 9: // удаление объектов
		{
			int elem;
			/*NoAdd_Pipe(pipes);
			NoAdd_Cs(css);*/
			cout << "Введите какой объект вы хотите удалить:" << endl;
			cout << "1. Труба" << endl;
			cout << "2. Компрессорная станция" << endl;
			elem = InputCheck(1, 2);
			if (elem == 1)
			{
				cout << "Введите id объекта:" << endl;
				auto id = InputCheck(1, max_p);
				pipes.erase(id);
			}
			
			if (elem == 2)
			{
				cout << "Введите id объекта:" << endl;
				auto id = InputCheck(1, max_cs);
				css.erase(id);
			}
			cout << "Объект удален" << endl;

		}
		}
	}
	
}

