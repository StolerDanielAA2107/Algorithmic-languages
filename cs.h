#include <iostream>

class cs
{
public:
	static int MaxID;
	int id;
	std::string name;
	int quantity;
	int work;	
	double effect; 
	cs();
	void addwork();
	void reducework();
	friend void SaveCs(std::ofstream& fout, const cs& s);
	friend void LoadCs(std::ifstream& fin, cs& s);
	friend std::istream& operator >> (std::istream& in, cs& s); // Ввод КС
	friend std::ostream& operator << (std::ostream& in, cs& s); // Вывод КС
};

