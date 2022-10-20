#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "pipe.h"
#include "cs.h"
#include "utils.h"
#include <unordered_map>



using namespace std;

void EditPipe(pipe& p)
{
	p.EditPipe(p);
}

void EditCs(cs& s)
{
	s.EditCs(s);
}
template<typename int, typename pipe>

void print_map(std::unordered_map<int, pipe> const& pipes)
{
	for (auto const& pair : pipes) {
		std::cout << "{" << pair.first << ": " << pair.second << "}\n";
	}
}
//void SaveObj(const pipe& p, const cs& s) 
//{
//	ofstream fout_pipe_cs;
//	fout_pipe_cs.open("Out_pipe_cs.txt", ios::out);
//	//fout_pipe_cs << p.length << "\n" << p.diameter << "\n" << p.priznak << "\n";
//	fout_pipe_cs << s.name << "\n" << s.quantity << "\n" << s.work << "\n" << s.effect << endl;
//	fout_pipe_cs.close();
//}

//void LoadObj(pipe& p, cs& s)
//{
//	ifstream fin_pipe_cs;
//	fin_pipe_cs.open("Out_pipe_cs.txt", ios::in);
//	if (fin_pipe_cs.is_open() == 0)
//	{
//		cout << "Ошибка открытия файла" << endl;
//	}
//	else
//		if (fin_pipe_cs.peek() == EOF)
//		{
//			cout << "Ошибка чтения: нет данных в файле." << endl;
//		}
//		else
//		{
//			/*fin_pipe_cs >> p.length;
//			fin_pipe_cs >> p.diameter;
//			fin_pipe_cs >> p.priznak;*/
//			fin_pipe_cs.ignore();
//			getline(fin_pipe_cs, s.name);
//			fin_pipe_cs >> s.quantity;
//			fin_pipe_cs >> s.work;
//			fin_pipe_cs >> s.effect;
//			fin_pipe_cs.close();
//			cout << "Загрузка выполнена." << endl;
//		}
//}

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
	double length{};
	double diameter{};
	bool priznak{};
	int value, danet, numb;
	double num;
	bool savepipe = true, savecs = true;
	pipe tb{};
	cs kc{};
	unordered_map <int, pipe> pipes;
	unordered_map <int, cs> css;
	menu();
	while (1)
	{
		cout << " Выберите пункт:" << endl;
		switch (InputCheck(0, 7))
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
		
		case 1:
		{
			cin >> tb;
			pipes.insert({pipes.size() + 1, tb});
			savepipe = false;
			break;
		}
		case 2:
		{
			cin >> kc;
			//css.insert(make_pair(++css.size,kc));
			savecs = false;
			break;
		}

		case 3:
		{
			for (const auto& key_value : pipes) {
				int key = key_value.first;
				pipe value = key_value.second;
				cout << "|\tid трубы\t|\tзначения\t|" << endl;
				cout << key << " - " << value << endl;
			}
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
			//SaveObj(tb, kc);
			cout << "Сохранение выполнено." << endl;
			savepipe = true;
			savecs = true;
			break;
		}
		case 7:
		{
			//LoadObj(tb, kc);
		}

		}
		}
		}
	}

