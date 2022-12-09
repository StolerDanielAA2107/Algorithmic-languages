#include <iostream> 

class pipe
{
public:
	static int MaxID;
	double length;
	int id, diameter, outCsId, inCsId;
	bool priznak, connect, used;	
	pipe();	
	pipe(int value);
	void changesign(); // �������������� �����
	void connect1();   // ����� � �����
	void use();
	friend void SavePipe(std::ofstream& fout, const pipe& p);
	friend void LoadPipe(std::ifstream& fin, pipe& p);
	friend std::istream& operator >> (std::istream& in, pipe& p); // ���� �����
	friend std::ostream& operator << (std::ostream& in, const pipe& p); // ����� �����
};

