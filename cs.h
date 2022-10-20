#pragma once
#include <iostream>
#include <string>

class cs
{
private:
	//int id_s; // ������������� ������������� �������
	std::string name{""};	// ��� �������
	int quantity {0};	// ���������� �����
	double effect {0.0}; // �������������

public:
	cs() {};
	int work {0};		// ���������� ����� � ������
	void EditCs(cs& s);
	friend std::istream& operator >> (std::istream& in, cs& s); // ���� ��
	friend std::ostream& operator << (std::ostream& in, cs& s); // ����� ��
};

