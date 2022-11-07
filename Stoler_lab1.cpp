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

void menu() { // меню
	setlocale(LC_ALL, "Russian");
	cout << " 1. Добавить трубу" << endl;
	cout << " 2. Добавить КС" << endl;
	cout << " 3. Просмотр всех объектов" << endl;
	cout << " 4. Поиск объектов" << endl;
	cout << " 5. Сохранить в файл" << endl;
	cout << " 6. Загрузить из файла" << endl;
	cout << " 7. Удалить объекты" << endl;
	cout << " 0. Выход" << "\n" << endl; 
}

vector <int> StringToNum(string& str) {
	vector <int> vec;
	stringstream ss;
	string s;
	double d;
	ss << str;
	while (!ss.eof()) {
		ss >> s;
		if (stringstream(s) >> d)
			vec.emplace_back(d);
		s = "";
	}
	return vec;
}

void NoAdd_Pipe() {
	if (pipes.size() == 0) {
		cout << "Трубы не добавлены" << endl;
	}
}

void NoAdd_Cs() {
	if (css.size() == 0) {
		cout << "КС не добавлены" << endl; }
}

void PrintAll() {
	NoAdd_Pipe();
	NoAdd_Cs();

	for (auto& key_value : pipes) {
		int key = key_value.first;
		pipe value = key_value.second;
		cout << "id трубы:" << key << endl;
		cout << value << endl; }

	for (const auto& key_value : css) {
		int key = key_value.first;
		cs value = key_value.second;
		cout << "id КС:" << key << endl;
		cout << value << endl; }
}

void Search() {
	while (1) {
		int ob;
		if (pipes.size() == 0 && css.size() == 0) {
			cout << "Объекты не добавлены" << endl;
			break;
		} else
		cout << "Введите по какому объекту сделать поиск:" << endl;
		cout << "1. Труба" << endl;
		cout << "2. Компрессорная станция" << endl;
		cout << "0. Выход" << endl;
		ob = InputCheck(0, 2);
		while (1) {
			if (ob == 1) {
				cout << "1. Показать трубы в ремонте" << endl;
				cout << "2. Показать трубы не в ремонте" << endl;
				cout << "3. Поменять состояние только введенных труб" << endl;
				cout << "4. Отправить все трубы в ремонт" << endl;
				cout << "5. Вернуть трубы из ремонта" << endl;
				cout << "0. Выход" << endl;
				int v = InputCheck(0, 5);

				if (v == 1) {
					cout << "id найденных труб с признаком <в ремонте>:" << endl;
					for (const auto& tb : pipes) {
						if (tb.second.priznak == 1) {
							cout << tb.first << endl;
						}
					}
					break;
				}

				if (v == 2) {
					cout << "id найденных труб с признаком <не в ремонте>:" << endl;
					for (const auto& tb : pipes) {
						if (tb.second.priznak == 0) {
							cout << tb.first << endl;
						}
					}
					break;
				}

				if (v == 3) {
					vector <int> vec;
					string id;
					cout << "Введите id труб(-ы):" << endl;
					cin.ignore(1000, '\n');                                  
					cin.clear();											 
					getline(cin, id);
					vec = StringToNum(id);
					for (int i : vec) {
						auto tb = pipes.find(i);
						if (tb != pipes.end()) {
							(*tb).second.changesign() ;
							cout << (*tb).second.priznak << endl;
							cout << "Состояние трубы с ID " << i << " изменено" << endl;
						} else {
							cout << "Id " << i << " не найден" << endl;
						}
					}
					break;
				}

				if (v == 4) {
					for (auto& tb : pipes) {
						tb.second.priznak = 1;
					}
					cout << "Все трубы отправлены в ремонт" << endl;
					break;
				}

				if (v == 5) {
					for (auto& tb : pipes) {
						tb.second.priznak = 0;
					}
					cout << "Все трубы вернулись из ремонта" << endl;
					break;
				}

				if (v == 0) {
					break;
				}
			}
			break;
		}
		if (ob == 2) {
			int a;
			cout << "Выберите параметр поиска:" << endl;
			cout << "1. По названию" << endl;
			cout << "2. По проценту незадействованных цехов" << endl;
			cout << "3. Запустить  1 цех только указанным КС" << endl;
			cout << "4. Остановить 1 цех только указанным КС" << endl;
			cout << "5. Запустить всем КС 1 цех" << endl;
			cout << "6. Остановить у всех КС 1 цех" << endl;
			cout << "0. Выход" << endl;
			a = InputCheck(0, 6);
			if (a == 1) {
				cout << "Введите название станции:" << endl;
				string fname; // findname
				cin.ignore(1000, '\n');
				cin.clear();
				getline(cin, fname);
				cout << "id найденных КС с введенным названием:" << endl;
				for (const auto& kc : css) {
					if (kc.second.name.find(fname) != string::npos) {
						cout << kc.first << '\n';
						cout << kc.second.name << '\n';
					}
				}
			}

			if (a == 2) {
				cout << "Введите число:" << endl;                            
				int perc,dig;	 // digit, percentage						
				dig = InputCheck(0, 100);
				cout << "id найденных КС с введенным процентом:" << endl;
				for (const auto& kc : css) {
					perc = (((kc.second.quantity - kc.second.work) / float( kc.second.quantity))) * 100;
					if (perc == dig) {
						cout << kc.first << endl;
					}
				}
			}

			if (a == 3) {
				vector <int> vec;
				string id;
				cout << "Введите id KC:" << endl;
				cin.ignore(1000, '\n');                                
				cin.clear();											
				getline(cin, id);
				vec = StringToNum(id);
				for (int i : vec) {
					auto kc = css.find(i);
					if (kc != css.end()) {
						(*kc).second.addwork();
						cout << "Цех КС с id " << i << " запущен" << endl;
					} else {
						cout << "Id " << i << " не найден" << endl;
					}
				}
			}

			if (a == 4) {
				vector <int> vec;
				string id;
				cout << "Введите id KC:" << endl;
				cin.ignore(1000, '\n');
				cin.clear();
				getline(cin, id);
				vec = StringToNum(id);
				for (int i : vec) {
					auto kc = css.find(i);
					if (kc != css.end()) {
						(*kc).second.reducework();
						cout << "Цех КС с id " << i << " остановлен" << endl;
					}
					else {
						cout << "Id " << i << " не найден" << endl;
					}
				}
			}

			if (a == 5) {
				for (auto& kc : css) {
					if (kc.second.work >= kc.second.quantity ) {
						cout << "Все цеха КС с id "<< kc.second.id <<" запущены" << endl;
					} else {
						kc.second.addwork();
						cout << "Цех КС с id " << kc.second.id << " запущен" << endl;
					}
				}
			}

			if (a == 6) {
				for (auto& kc : css) {
					if (kc.second.work <= 0) {
						cout << "Все цеха КС с id "<< kc.second.id<< " остановлены" << endl;
					} else {
						kc.second.reducework();
						cout << "Цех КС с id " << kc.second.id << " остановлен" << endl;
					}
				}
			}

			if (a == 0) {
				break;
			}
		}
		break;
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
	ofile.open(name, ios::out);
	if (ofile.is_open()) {
		ofile << pipe::MaxID - 1 << "\n"; // запись количества труб
		ofile << cs::MaxID - 1 << "\n"; // запись количества КС
		for (const auto& tb : pipes)
			SavePipe(ofile, tb.second);
		for (const auto& kc : css)
			SaveCs(ofile, kc.second);
		ofile.close();
		cout << "Сохранение выполнено." << endl; 
	}
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

	if (ifile.is_open() == 0) {
		cout << "Ошибка открытия файла" << endl;
	} else if (ifile.peek() == EOF) {
		cout << "Ошибка чтения: нет данных в файле." << endl;
	} else {
			pipes.clear();
			css.clear();
			ifile >> pipe::MaxID; // количествo труб
			ifile >> cs::MaxID; //  количествo КС
			
			pipe tb = pipe();
			cs kc = cs();
			do {
				LoadPipe(ifile, tb);
				pipes.emplace( tb.id, tb );
			} while (tb.id < pipe::MaxID - 1);
			
			do {
				LoadCs(ifile, kc);
				css.emplace( kc.id, kc );
			} while (kc.id < cs::MaxID - 1);
			ifile.close();
			cout << "Загрузка выполнена." << endl;
	}
}

void Delete() {
	vector <int> str;
	string s;
	int elem;
	cout << "Введите какой объект вы хотите удалить:" << endl;
	cout << "1. Труба" << endl;
	cout << "2. Компрессорная станция" << endl;
	elem = InputCheck(1, 2);
	if (elem == 1) {
		cout << "Введите id объекта (-ов):" << endl;
		cin.ignore(1000, '\n');
		cin.clear();
		getline(cin, s);
		str = StringToNum(s);
		for (int i : str) {
			auto tb = pipes.find(i);
			if (tb != pipes.end()) {
				pipes.erase(i);
				cout << "Объект " << i << " удален" << endl;
			} else {
				cout << "Id " << i << " не найден" << endl; 
			}
		}
	}

	if (elem == 2) {
		cout << "Введите id объекта (-ов):" << endl;
		cin.ignore(1000, '\n');
		cin.clear();
		getline(cin, s);
		str = StringToNum(s);
		for (int i : str) {
			auto kc = css.find(i);
			if (kc != css.end()) {
				css.erase(i);
				cout << "Объект " << i << " удален" << endl; 
			} else {
				cout << "Id " << i << " не найден" << endl; 
			}
		}
	}
}

int main()  // тело программы
{
	bool saveobj = true;
	menu();
	while (1) {
		cout << "Выберите пункт:" << endl;
		switch (InputCheck(0, 8))
		{
			case 0: {
				if (!saveobj)
				{
					cout << "Параметры не были сохранены, сохранить их?" << endl;
					cout << "1.Да" << endl;
					cout << "2.Нет" << endl;
					int danet;
					while (true) {
						danet = InputCheck(1, 2);
						if (danet == 1) {
							SaveAll();
							exit(0);
							break;
						}
						if (danet == 2) {
							exit(0);
						}
					}
				}
				else exit(0);
			}
			
			case 1: { //ввод трубы и запись в контейнер  ||  "}" - иначе пропуск инициализации, поэтому вручную создается область видимости
				pipe tb = pipe();
				cin >> tb;											
				pipes.insert({ tb.id, tb });
				saveobj = false;
				break; 
			}
			
			case 2: {//ввод КС и запись в контейнер
				cs kc = cs();
				cin >> kc;
				css.insert({ kc.id, kc });
				saveobj = false;
				break; 
			}

			case 3:  // просмотр всех объектов
				PrintAll();
				break; 
			
			case 4: // поиск труб
				Search();
				saveobj = false;
				break; 
			
			case 5: // сохранение
				if (pipes.size() == 0 && css.size() == 0) {
					cout << "Объекты не добавлены" << endl;
					break;
				} else SaveAll();
				saveobj = true;
				break; 
			
			case 6: // загрузка
				LoadAll();
				break;
			
			case 7: //  удаление
				if (pipes.size() == 0 && css.size() == 0) {
					cout << "Объекты не добавлены" << endl;
					break;
				} else Delete();
				saveobj = false;
				break;	
		}
	}
}
