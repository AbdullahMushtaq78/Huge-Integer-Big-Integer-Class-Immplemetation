pragma once
#include <iostream>
#include <fstream>
using namespace std;

class HI
{
	int* Ds;
	int size;
	bool isNeg;
	void DeAllocate();
	void removeAtEnd(int*&, int&);
	void TRIM();
	const HI ABS()const;

public:
	HI();
	HI(ifstream& rdr);
	HI(const HI&);
	HI(const char* num);
	HI(string num);

	void SetInteger(ifstream&);
	void SetInteger(const HI&);
	void SetInteger(const char* num);
	void SetInteger(string num);
	void SetInteger(istream&);


	friend ifstream& operator>>(ifstream&, HI&);
	friend istream& operator>>(istream&, HI&);
	friend ostream& operator<<(ostream&, const HI&);


	const HI operator=(const HI&);
	const HI operator=(const char* num);
	const HI operator=(string num);

	int& operator[](int);
	int operator[](int)const;

	const HI ADDQWise(const HI& H)const;
	const HI SUBQWise(const HI& H)const;

	bool QWiseGT(const HI& H)const;
	bool QWiseLT(const HI& H)const;
	bool QWiseET(const HI& H)const;


	const HI operator-()const;
	const HI operator++();
	const HI operator++(int);
	const HI operator--();
	const HI operator--(int);


	const HI operator+(const HI&)const;
	const HI operator-(const HI&)const;
	const HI operator*(const HI&)const;
	const HI operator/(const HI&)const;
	const HI operator%(const HI&)const;


	const HI operator+=(const HI&);
	const HI operator-=(const HI&);
	const HI operator*=(const HI&);
	const HI operator/=(const HI&);
	const HI operator%=(const HI&);

	bool operator==(const HI&)const;
	bool operator!=(const HI&)const;

	bool operator<(const HI&)const;
	bool operator>(const HI&)const;

	bool operator<=(const HI&)const;
	bool operator>=(const HI&)const;



	~HI();

};

