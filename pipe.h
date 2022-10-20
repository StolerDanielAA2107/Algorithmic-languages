#pragma once
#include <iostream> 

class pipe
{
private:
	//int id_p = 1; // ������������� �����
	double length {0.0}, diameter {0.0};	// �����, �������

public:
	pipe() {};
	bool priznak{ 0 };	// ������� "� ������"
	//UniqueID();
	void EditPipe(pipe& p);
	pipe(double length, double diameter, bool priznak);

	friend std::istream& operator >> (std::istream& in, pipe& p); // ���� �����
	friend std::ostream& operator << (std::ostream& in, pipe& p); // ����� �����

};

