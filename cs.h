#pragma once
#include <iostream>

class cs
{
public:
	int id;
	static int MaxID;
	std::string name;
	int quantity;	
	int work;	
	double effect; 
	cs();
	void EditCs();
	friend void SaveCs(std::ofstream& fout, const cs& s);
	friend void LoadCs(std::ifstream& fin, cs& s);
	friend std::istream& operator >> (std::istream& in, cs& s); // Ввод КС
	friend std::ostream& operator << (std::ostream& in, cs& s); // Вывод КС
};

