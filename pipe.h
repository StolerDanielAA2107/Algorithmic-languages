#include <iostream> 

class pipe
{
	double length, diameter;
public:
	static int MaxID;
	int id;
	bool priznak;	
	pipe();	
	void changesign(); // �������������� �����
	friend void SavePipe(std::ofstream& fout, const pipe& p);
	friend void LoadPipe(std::ifstream& fin, pipe& p);
	friend std::istream& operator >> (std::istream& in, pipe& p); // ���� �����
	friend std::ostream& operator << (std::ostream& in, const pipe& p); // ����� �����
};

