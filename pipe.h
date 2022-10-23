#pragma once
#include <iostream> 

class pipe
{
public:
	int id;
	static int MaxID;
	double length;	// длина
	double diameter; // диаметр
	bool priznak;	// признак "в работе"
	pipe();		
	void EditPipe();
	friend void SavePipe(std::ofstream& fout, const pipe& p);
	friend std::istream& operator >> (std::istream& in, pipe& p); // Ввод трубы
	friend std::ostream& operator << (std::ostream& in, const pipe& p); // Вывод трубы
};

