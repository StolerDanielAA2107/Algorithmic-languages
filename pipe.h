#include <iostream> 

class pipe
{
	double length;
public:
	static int MaxID;
	int id, diameter;
	bool priznak, connect;	
	pipe();	
	pipe(int value);
	void changesign(); // редактирование трубы
	void connect1();   // труба в графе
	friend void SavePipe(std::ofstream& fout, const pipe& p);
	friend void LoadPipe(std::ifstream& fin, pipe& p);
	friend std::istream& operator >> (std::istream& in, pipe& p); // Ввод трубы
	friend std::ostream& operator << (std::ostream& in, const pipe& p); // Вывод трубы
};

