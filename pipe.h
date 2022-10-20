#pragma once
#include <iostream> 

class pipe
{
private:
	//int id_p = 1; // идентификатор трубы
	double length {0.0}, diameter {0.0};	// длина, диаметр

public:
	pipe() {};
	bool priznak{ 0 };	// признак "в работе"
	//UniqueID();
	void EditPipe(pipe& p);
	pipe(double length, double diameter, bool priznak);

	friend std::istream& operator >> (std::istream& in, pipe& p); // Ввод трубы
	friend std::ostream& operator << (std::ostream& in, pipe& p); // Вывод трубы

};

