#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <unordered_map>
#include "pipe.h"
#include "cs.h"
#include "utils.h"

using namespace std;

unordered_map <int, pipe> pipes;
unordered_map <int, cs> css;
map <int, vector<int>> gts;
map <int, vector<int> >::iterator itrCode;

void menu() 
{ 
	setlocale(LC_ALL, "Russian");
	cout << " 1. Добавить трубу" << endl;
	cout << " 2. Добавить КС" << endl;
	cout << " 3. Просмотр всех объектов" << endl;
	cout << " 4. Поиск объектов" << endl;
	cout << " 5. Создать газотранспортную сеть" << endl;
	cout << " 6. Показать соединения" << endl;
	cout << " 7. Отсортировать граф" << endl;
	cout << " 8. Сохранить в файл" << endl;
	cout << " 9. Загрузить из файла" << endl;
	cout << " 10. Удалить объекты" << endl;
	cout << " 0. Выход" << "\n" << endl; 
}

vector <int> StringToNum(string& str) 
{
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

void InputPipe() 
{
	pipe tb = pipe();
	cin >> tb;
	pipes.insert({ tb.id, tb });
}

void InputKS() 
{
	cs kc = cs();
	cin >> kc;
	css.insert({ kc.id, kc });
}

void PrintAll() 
{
	if (pipes.size() == 0 && css.size() == 0) {
		cout << "Объекты не добавлены" << endl;
	}

	for (auto& key_value : pipes) {
		int key = key_value.first;
		pipe value = key_value.second;
		cout << "ID трубы:" << key << endl;
		cout << value << endl; 
	}

	for (const auto& key_value : css) {
		int key = key_value.first;
		cs value = key_value.second;
		cout << "ID КС:" << key << endl;
		cout << value << endl; 
	}
}

void menupipe()
{
	cout << "1. Показать трубы в ремонте" << endl;
	cout << "2. Показать трубы не в ремонте" << endl;
	cout << "3. Поменять состояние только введенных труб" << endl;
	cout << "4. Отправить все трубы в ремонт" << endl;
	cout << "5. Вернуть трубы из ремонта" << endl;
	cout << "0. Выход" << endl;
}

void menucs()
{
	cout << "Выберите параметр поиска:" << endl;
	cout << "1. По названию" << endl;
	cout << "2. По проценту незадействованных цехов" << endl;
	cout << "3. Запустить  1 цех только указанным КС" << endl;
	cout << "4. Остановить 1 цех только указанным КС" << endl;
	cout << "5. Запустить всем КС 1 цех" << endl;
	cout << "6. Остановить у всех КС 1 цех" << endl;
	cout << "0. Выход" << endl;
}

int ChoiceOrInputNewPipe(int val)
{
	int available = 0, id{};
	auto it = find_if(pipes.begin(), pipes.end(),
	[&val](const pair<int, pipe>& p) { return p.second.diameter == val;});
	
	if (it == pipes.end()) {
		cout << "Труба с введенными диаметром не нашлась, создать ее?" << endl;
		cout << "1. Да" << endl;
		cout << "2. Нет" << endl;
		switch (InputCheck(1, 2)) {
			case 1: {
				pipe tb = pipe(val);
				pipes.insert({ tb.id, tb });
				return tb.id;
			}
			case 2: {
				return int(); 
			}
		}
	} else {
	cout << "Доступны трубы с ID:" << endl;
		for (const auto& tb : pipes) {
			if ((tb.second.diameter == val) && (tb.second.connect == 0)) {
				cout << tb.first << endl;
			}
		}
		available = InputCheck(1, pipe::MaxID - 1);
		auto tb = pipes.find(available);
		(*tb).second.connect1();
		id = available;
	}
	return id;
}

void newgraph()
{
	vector <int> output_input;
	int input, output, id{};
	if (css.size() >= 2) {
		cout << " Выберите ID КС выхода:" << endl;
		output = InputCheck(1, cs::MaxID - 1);
		auto kc = css.find(output);
		cout << " Выберите ID КС входа:" << endl;
		input = InputCheck(1, cs::MaxID - 1);
		kc = css.find(input);
		if (output == input) {
			cout << "Начало и конец не должны совпадать, попробуйте еще раз" << endl;
			return void();			// завершаем выполнение функции если условие подтвердилось
		}
		cout << "Выберите диаметр трубы:" << endl;
		cout << "1. 500mm" << endl;
		cout << "2. 700mm" << endl;
		cout << "3. 1400mm" << endl;
		switch (InputCheck(1, 3)) {
		case 1: id = ChoiceOrInputNewPipe(500); break;
		case 2: id = ChoiceOrInputNewPipe(700); break;
		case 3: id = ChoiceOrInputNewPipe(1400); break;}
		output_input.push_back(output);
		output_input.push_back(input);
		if (id == 0) {                 // в функции ChoiceOrInputNewPipe при отмене создания трубы возвращается ID = 0,
			void();					   // поэтому чтобы не создавалось соединение пишется проверка
		} else {
			gts.insert({ id ,output_input });
			cout << "Соединение создано" << endl;
		}
	} else {
		cout << "КС не существует, либо добавьте еще 1" << endl;
	}
}

void printgraph()
{
	for (itrCode = gts.begin(); itrCode != gts.end(); itrCode++)
	{
		cout << " ( ID трубы: " << itrCode->first;
		vector<int>& vec = itrCode->second;
		for (vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			if (it == vec.end() - 1)
				cout << "КС " << *it << " )" << '\n';
			else
				cout << " = КС " << *it << " -> ";
		}
	}
}

void Search() 
{
	if (pipes.size() == 0 && css.size() == 0) {
		cout << "Объекты не добавлены" << endl;
	} else {
		while (1) {
			cout << "Введите по какому объекту сделать поиск:" << endl;
			cout << "1. Труба" << endl;
			cout << "2. Компрессорная станция" << endl;
			cout << "0. Выход" << endl;
			switch (InputCheck(0, 2)) {
			case 1:
				menupipe();
				switch (InputCheck(0, 5)) {
				case 1: {
					cout << "id найденных труб с признаком <в ремонте>:" << endl;
					for (const auto& tb : pipes) {
						if (tb.second.priznak == 1) {
							cout << tb.first << endl;
						}
					} continue;
				}

				case 2: {
					cout << "id найденных труб с признаком <не в ремонте>:" << endl;
					for (const auto& tb : pipes) {
						if (tb.second.priznak == 0) {
							cout << tb.first << endl;
						}
					} continue;
				}

				case 3: {
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
							(*tb).second.changesign();
							cout << "Состояние трубы с ID " << i << " изменено" << endl;
						}
						else {
							cout << "Id " << i << " не найден" << endl;
						}
					} continue;
				}
				case 4: {
					for (auto& tb : pipes) {
						tb.second.priznak = 1;
					}
					cout << "Все трубы отправлены в ремонт" << endl;
					continue;
				}

				case 5: {
					for (auto& tb : pipes) {
						tb.second.priznak = 0;
					}
					cout << "Все трубы вернулись из ремонта" << endl;
					continue;
				}
				case 0: {
					break;
				}
					  break;
				}
			case 2: {
				menucs();
				switch (InputCheck(0, 6)) {
				case 1: {
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
					} continue;
				}
				case 2: {
					cout << "Введите число:" << endl;
					int perc, dig;	 // digit, percentage						
					dig = InputCheck(0, 100);
					cout << "id найденных КС с введенным процентом:" << endl;
					for (const auto& kc : css) {
						perc = (((kc.second.quantity - kc.second.work) / float(kc.second.quantity))) * 100;
						if (perc == dig) {
							cout << kc.first << endl;
						}
					} continue;
				}

				case 3: {
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
						}
						else {
							cout << "Id " << i << " не найден" << endl;
						}
					} continue;
				}

				case 4: {
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
					} continue;
				}

				case 5: {
					for (auto& kc : css) {
						if (kc.second.work >= kc.second.quantity) {
							cout << "Все цеха КС с id " << kc.second.id << " запущены" << endl;
						}
						else {
							kc.second.addwork();
							cout << "Цех КС с id " << kc.second.id << " запущен" << endl;
						}
					} continue;
				}

				case 6: {
					for (auto& kc : css) {
						if (kc.second.work <= 0) {
							cout << "Все цеха КС с id " << kc.second.id << " остановлены" << endl;
						}
						else {
							kc.second.reducework();
							cout << "Цех КС с id " << kc.second.id << " остановлен" << endl;
						}
					} continue;
				}

				case 0: {
					break;
				}
				}
				break;
			}
			}
			break;
		}
	}
}

void SaveAll()
{
	if (pipes.size() == 0 && css.size() == 0) {
		cout << "Объекты не добавлены" << endl;
	} else {
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

void Delete() 
{
	if (pipes.size() == 0 && css.size() == 0) {
		cout << "Объекты не добавлены" << endl;
	} else {
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
				}
				else {
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
				}
				else {
					cout << "Id " << i << " не найден" << endl;
				}
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
		switch (InputCheck(0, 10))
		{
			case 0: {
				if (!saveobj) {
					cout << "Параметры не были сохранены, сохранить их?" << endl;
					cout << "1.Да" << endl;
					cout << "2.Нет" << endl;
					while (1) {
						switch (InputCheck(1, 2)) {
						case 1:
							SaveAll();
							exit(0);
						case 2: exit(0);
						}
					}
				}
				else exit(0);
			}

			case 1: 
				InputPipe();
				saveobj = false;
				break; 

			case 2: 		
				InputKS();
				saveobj = false;
				break; 

			case 3: 
				PrintAll();
				break; 
			
			case 4: 
				Search();
				saveobj = false;
				break; 
			case 5: 
				newgraph();
				break;
	
			case 6: 
				printgraph();
				break;

			case 8: 
				SaveAll();
				saveobj = true;
				break; 
			
			case 9: 
				LoadAll();
				break;
			
			case 10:
				 Delete();
				saveobj = false;
				break;	
		}
	}
}
