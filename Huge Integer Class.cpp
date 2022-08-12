#include "HI.h"
//UTILITY FUNCs
void HI::DeAllocate()
{
	delete[]Ds;
	size = 0;
	isNeg = false;
}
void HI::removeAtEnd(int*& D, int& size)
{
	size--;
	int* NH = new int[size];
	for (int i = 0; i < size; i++)
		NH[i] = D[i];

	delete[]D;
	D = NH;
}
void HI::TRIM()
{
	while (Ds[size - 1] == 0 && size > 1)
		removeAtEnd(Ds, size);
}
const HI HI::ABS()const
{
	HI R = *this;
	R.isNeg = false;
	return R;
}

//CONSTRUCTORS
HI::HI()
{
	this->Ds = nullptr;
	this->size = 0;
	this->isNeg = false;
}
HI::HI(ifstream& rdr)
{
	SetInteger(rdr);
}
HI::HI(const HI& H)
{
	SetInteger(H);
}
HI::HI(const char* num)
{
	SetInteger(num);
}
HI::HI(string num)
{
	SetInteger(num);
}


//SET INTEGER FUNCs (INITIALIZERS)
void HI::SetInteger(ifstream& rdr)
{
	string aline;
	char sign;

	rdr >> sign >> aline;

	if (sign == '-')
		this->isNeg = true;
	else
		this->isNeg = false;

	this->size = aline.size();
	this->Ds = new int[size];
	for (int i = 0; i < this->size; i++)
		this->Ds[this->size - 1 - i] = aline[i] - '0';

	TRIM();
}
void HI::SetInteger(const HI& H)
{
	this->size = H.size;
	this->isNeg = H.isNeg;

	this->Ds = new int[this->size];
	for (int i = 0; i < this->size; i++)
	{
		this->Ds[i] = H.Ds[i];
	}
	TRIM();
}
void HI::SetInteger(const char* num)
{
	int signDif = 0;
	if (num[0] == '-')
	{
		this->isNeg = true;
		this->size = strlen(num) - 1;
		signDif = 1;
	}
	else if (num[0] == '+')
	{
		this->isNeg = false;
		this->size = strlen(num) - 1;
		signDif = 1;
	}
	else
	{
		this->isNeg = false;
		this->size = strlen(num);

		signDif = 0;
	}


	this->Ds = new int[this->size];
	for (int i = 0; i < this->size; i++)
	{
		this->Ds[size - i - 1] = num[i + signDif] - '0';
	}
	TRIM();
}

void HI::SetInteger(string num)
{
	int signDif = 0;
	if (num[0] == '-')
	{
		this->isNeg = true;
		this->size = num.length() - 1;
		signDif = 1;
	}
	else if (num[0] == '+')
	{
		this->isNeg = false;
		this->size = num.length() - 1;
		signDif = 1;
	}
	else
	{
		this->isNeg = false;
		this->size = num.length();
		signDif = 0;
	}

	this->Ds = new int[this->size];
	for (int i = 0; i < this->size; i++)
	{
		this->Ds[size - i - 1] = num[i + signDif] - '0';
	}
	TRIM();
}

void HI::SetInteger(istream&)
{
	string aline;
	cin >> aline;

	if (aline[0] == '-')
		this->isNeg = true;
	else
		this->isNeg = false;

	this->size = aline.size() - 1;
	this->Ds = new int[size];
	for (int i = 0; i < this->size; i++)
		this->Ds[this->size - 1 - i] = aline[i + 1] - '0';
	TRIM();
}

//SUBSCRIPT OPERATORS
int& HI::operator[](int i)
{
	return this->Ds[i];
}
int HI::operator[](int i) const
{
	if (i >= this->size)
		return 0;

	return this->Ds[i];
}

//QTY WISE OPERATIONS
const HI HI::ADDQWise(const HI& H)const
{
	HI NH;
	NH.size = this->size + 1;
	NH.Ds = new int[NH.size];
	int carry = 0;
	for (int i = 0; i < NH.size; i++)
	{
		NH[i] = ((*this)[i] + H[i] + carry) % 10;
		carry = ((*this)[i] + H[i] + carry) / 10;
	}
	NH.TRIM();
	return NH;
}
const HI HI::SUBQWise(const HI& H)const
{
	HI NH;
	NH.size = this->size;
	NH.Ds = new int[NH.size];
	int carry = 0;
	for (int i = 0; i < NH.size; i++)
	{
		NH[i] = ((*this)[i] - H[i] - carry);
		if (NH[i] < 0)
		{
			carry = 1;
			NH[i] += 10;
		}
		else
			carry = 0;
	}
	NH.TRIM();
	return NH;
}
//booleans
bool HI::QWiseGT(const HI& H) const
{
	if (this->size < H.size)
		return false;
	else if (this->size > H.size)
		return true;
	else
		for (int i = size - 1; i >= 0; i--)
		{
			if (this->Ds[i] > H.Ds[i])
				return true;
			else if (this->Ds[i] < H.Ds[i])
				return false;
		}
	return false;
}
bool HI::QWiseLT(const HI& H) const
{
	return H.QWiseGT(*this);
}
bool HI::QWiseET(const HI& H) const
{
	return (!this->QWiseGT(H) && !this->QWiseLT(H));
}

//SIGN CHANGE
const HI HI::operator-()const
{

	HI R = *this;
	if (!this->QWiseET("0"))
		R.isNeg = !isNeg;

	return R;
}

//INCREMENT/DECREMENT
const HI HI::operator++()
{
	*this = *this + "1";
	return *this;
}
const HI HI::operator++(int)
{
	HI R = *this;
	*this += "1";
	return R;
}
const HI HI::operator--()
{
	*this = *this - "1";
	return *this;
}
const HI HI::operator--(int)
{
	HI R = *this;
	*this = *this - "1";
	return R;
}

//ARITHMETIC
const HI HI::operator+(const HI& H) const
{
	HI R = "0";
	if (isNeg == H.isNeg)
	{
		if (this->QWiseGT(H))
			R = this->ADDQWise(H);
		else
			R = H.ADDQWise(*this);
		R.isNeg = this->isNeg;
	}
	else
	{

		if (this->QWiseGT(H))
		{
			R = this->SUBQWise(H);
			R.isNeg = this->isNeg;
		}
		else
		{
			R = H.SUBQWise(*this);
			R.isNeg = H.isNeg;
		}
	}
	if (R.QWiseET("0"))
		R.isNeg = false;
	return R;
}
const HI HI::operator-(const HI& H) const
{
	return *this + (-H);
}
//slow multiply
/*
const HugeInt HugeInt::operator*(const HugeInt&H) const
{
	HugeInt R,
	for(HugeInt i = "+0"; i <= H; i++)
	{
		R += *this;
	}

	return R;
}
*/
const HI HI::operator*(const HI& H) const
{
	if (*this == "0" || H == "0")
		return "0";

	HI R = this->ABS();
	HI C = "1", B = H.ABS();
	HI Total = "0";

	do
	{
		while (C + C <= B)
		{
			R += R;
			C += C;
		}
		B -= C;
		Total += R;
		R = this->ABS();
		C = "1";

	} while (B != "0");


	if (isNeg == H.isNeg)
		Total.isNeg = false;
	else
		Total.isNeg = true;

	if (R.QWiseET("0"))
		R.isNeg = false;
	return Total;

}
const HI HI::operator/(const HI& H)const
{
	if (H == "+0" || H == "0")
	{
		system("cls");
		cout << "DIVISION BY ZERO\n\n Program Ended";
		int i = 1;
		i--;
		i /= i;
	}
	else if (*this == "0" || *this == "+0")
	{
		return "0";
	}
	else if (*this < H)
		return "0";
	else if (*this == H)
		return "1";

	HI R = H.ABS();
	HI C = "1";
	HI Remainder = this->ABS(), Quotient = "+0";


	do
	{
		while (R + R <= Remainder)
		{
			R += R;
			C += C;
		}
		Remainder -= R;
		Quotient += C;
		C = "1";
		R = H.ABS();
	} while (Remainder >= H.ABS());

	if (isNeg == H.isNeg)
		Quotient.isNeg = false;
	else
		Quotient.isNeg = true;

	if (R.QWiseET("0"))
		R.isNeg = false;
	return Quotient;
}

const HI HI::operator%(const HI& H)const
{
	if (this->ABS() < H.ABS())
		return "0";

	HI R = H.ABS();
	HI C = "1";
	HI Remainder = this->ABS(), Quotient = "+0";

	do
	{
		while (R + R <= Remainder)
		{
			R += R;
			C += C;
		}
		Remainder -= R;
		Quotient += C;
		C = "1";
		R = H.ABS();
	} while (Remainder >= H.ABS());

	//HugeInt Div = *this / H;
	//HugeInt Remainder = (*this - (Div * H));

	if (isNeg)
		Remainder.isNeg = true;
	else
		Remainder.isNeg = false;

	if (R.QWiseET("0"))
		R.isNeg = false;
	return Remainder;

}

//ASSIGN ACCUMULATE
const HI HI::operator+=(const HI& H)
{
	*this = *this + H;
	return *this;
}
const HI HI::operator-=(const HI& H)
{
	*this = *this - H;
	return *this;
}
const HI HI::operator*=(const HI& H)
{
	*this = *this * H;
	return *this;
}
const HI HI::operator/=(const HI& H)
{
	*this = *this / H;
	return *this;
}
const HI HI::operator%=(const HI& H)
{
	*this = *this % H;
	return *this;
}

//COMPARISON OPERATORs
bool HI::operator==(const HI& H) const
{
	if (isNeg != H.isNeg)
		return false;
	else
		return this->QWiseET(H);
}
bool HI::operator!=(const HI& H) const
{
	return !(*this == H);
}

bool HI::operator<(const HI& H) const
{
	if (isNeg && !H.isNeg)
		return true;
	else if (!isNeg && H.isNeg)
		return false;
	else
	{
		if (isNeg == false)
			return this->QWiseLT(H);
		else
			return H.QWiseLT(*this);
	}
}
bool HI::operator>(const HI& H) const
{
	return H < *this;
}
bool HI::operator<=(const HI& H) const
{
	return (*this < H || *this == H);
}
bool HI::operator>=(const HI& H) const
{
	return H <= *this;
}

//ASSIGNMENT OPERATORS
const HI HI::operator=(const HI& H)
{
	this->DeAllocate();
	this->SetInteger(H);
	return *this;
}
const HI HI::operator=(const char* num)
{
	this->DeAllocate();
	this->SetInteger(num);
	return *this;
}

// I/O FUNCs
ifstream& operator>>(ifstream& rdr, HI& H)
{
	H.SetInteger(rdr);
	return rdr;
}
istream& operator>>(istream& cin, HI& H)
{
	H.SetInteger(cin);
	return cin;
}
ostream& operator<<(ostream&, const HI& H)
{
	if (!H.QWiseET("0"))
		cout << (H.isNeg ? '-' : '+');

	for (int i = 0; i < H.size; i++)
		cout << H.Ds[H.size - 1 - i];
	return cout;
}

HI::~HI()
{
	DeAllocate();
}
