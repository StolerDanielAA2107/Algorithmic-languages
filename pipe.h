#include <iostream> 

class pipe
{
public:
	static int MaxID;
	int id;
	double length;
	double diameter;
	bool priznak;	
	pipe();		
	void EditPipe();
	friend void SavePipe(std::ofstream& fout, const pipe& p);
	friend void LoadPipe(std::ifstream& fin, pipe& p);
	friend std::istream& operator >> (std::istream& in, pipe& p); // Ввод трубы
	friend std::ostream& operator << (std::ostream& in, const pipe& p); // Вывод трубы
};

