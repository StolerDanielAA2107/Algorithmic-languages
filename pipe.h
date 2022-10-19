#pragma once
#include <iostream>
#include "Utils.h"  

class pipe
{
	double length, diameter;	// �����, �������
	bool priznak;	// ������� "� ������"

public:
	/*pipe();
	pipe(double length);
	pipe(double diameter);
	pipe(bool priznak);
	pipe(const pipe& p);*/
	double GetLength() const;
	double GetDiameter() const;
	void SetLength(double);
	void SetDiameter(double);
	void SetPriznak(bool);
	void EditPipe();
	friend std::istream& operator >> (std::istream& in, pipe& p); // ���� �����
	friend std::ostream& operator << (std::ostream& in, pipe& p); // ����� �����

};

