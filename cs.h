#pragma once
#include <iostream>
#include <string>

class cs
{
private:
	//int id_s; // идентификатор компрессорной станции
	std::string name{""};	// имя станции
	int quantity {0};	// количество цехов
	double effect {0.0}; // эффективность

public:
	cs() {};
	int work {0};		// количество цехов в работе
	void EditCs(cs& s);
	friend std::istream& operator >> (std::istream& in, cs& s); // Ввод КС
	friend std::ostream& operator << (std::ostream& in, cs& s); // Вывод КС
};

