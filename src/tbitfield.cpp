#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len <= 0) throw - 1;
	bitLen = len;
	//memLen = int(ceil(double(bitLen) / double(sizeof(uInt))));
	memLen = (len + 31) >> 5;
	pMem = new uInt[memLen];
	for (int i = 0; i < memLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	bitLen = bf.bitLen;
	memLen = bf.memLen;
	pMem = new uInt[memLen];
	for (int i = 0; i < memLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField() //Деструктор
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	//return int(ceil(double(n) / double(sizeof(uInt))));
	return n >> 5;
}

uInt TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n & 31);
	//return 1 << int(n - sizeof(uInt)*GetMemIndex(n));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return bitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n >= bitLen) throw - 1;
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n >= bitLen) throw - 1;
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & (~GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n >= bitLen) throw - 1;
	return (pMem[GetMemIndex(n)] & GetMemMask(n));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf)
	{
		delete[]pMem;
		bitLen = bf.bitLen;
		memLen = bf.memLen;
		pMem = new uInt[memLen];
		for (int i = 0; i < memLen; i++)
		{
			pMem[i] = bf.pMem[i];
		}
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int res = 1;
	if (bitLen != bf.bitLen)
		res = 0;
	else
		for (int i = 0; i < memLen; i++)
			if (pMem[i] != bf.pMem[i])
			{
				res = 0;
				break;
			}
	return res;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField tmp(max(bitLen, bf.bitLen)); //новое поле создаем таким, чтоб уместить туда наибольшее из 2х битовых полей
	for (int i = 0; i < memLen; i++)
		tmp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.memLen; i++)
		tmp.pMem[i] |= bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField tmp(max(bitLen, bf.bitLen)); //новое поле создаем таким, чтоб уместить туда наибольшее из 2х битовых полей
	for (int i = 0; i < memLen; i++)
		tmp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.memLen; i++)
		tmp.pMem[i] &= bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(bitLen);
	for (int i = 0; i < bitLen; i++) {
		if (this->GetBit(i) == 0)
			tmp.SetBit(i);
	}
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	string temp;
	istr >> temp;
	if (temp.size() != bf.GetLength())
		throw "Incorrect length";
	for (int i = 0; i < bf.bitLen; i++)
	{
	  if (temp[i] == '0')
			bf.ClrBit(i);
		else if (temp[i] == '1')
			bf.SetBit(i);
		else
			throw "Incorrect input";
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.bitLen; i++)
	{
		if (bf.GetBit(i))
			ostr << 1;
		else
			ostr << 0;
	}
	return ostr;
}
