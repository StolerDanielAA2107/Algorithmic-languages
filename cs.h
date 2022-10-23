#pragma once
#include <iostream>

class cs
{
public:
	int id;
	static int MaxID;
	std::string name;	// ��� �������
	int quantity ;	// ���������� �����
	int work;		// ���������� ����� � ������
	double effect; // �������������
	cs();
	void EditCs();
	friend void SaveCs(std::ofstream& fout, const cs& s);
	friend std::istream& operator >> (std::istream& in, cs& s); // ���� ��
	friend std::ostream& operator << (std::ostream& in, cs& s); // ����� ��
};

