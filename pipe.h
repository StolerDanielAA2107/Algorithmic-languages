#pragma once
#include <iostream> 

class pipe
{
public:
	int id;
	static int MaxID;
	double length;	// �����
	double diameter; // �������
	bool priznak;	// ������� "� ������"
	pipe();		
	void EditPipe();
	friend void SavePipe(std::ofstream& fout, const pipe& p);
	friend std::istream& operator >> (std::istream& in, pipe& p); // ���� �����
	friend std::ostream& operator << (std::ostream& in, const pipe& p); // ����� �����
};

