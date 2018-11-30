#include "tset.h"

TSet::TSet(int mp) : bitField(mp)
{
	maxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : bitField(s.bitField)
{
	maxPower = s.maxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : bitField(bf)
{
	maxPower = bf.GetLength();
}

TSet::operator TBitField()
{
	TBitField tmp(bitField);
	return tmp;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return maxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if (Elem < 0 || Elem >= maxPower) throw -1;
    return bitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if (Elem < 0 || Elem >= maxPower) throw - 1;
	bitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if (Elem < 0 || Elem >= maxPower) throw - 1;
	bitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	if (this != &s)
	{
		maxPower = s.maxPower;
		bitField = s.bitField;
	}
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return (bitField == s.bitField);
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return (bitField != s.bitField);
}

TSet TSet::operator+(const TSet &s) // объединение
{
	int len = maxPower;
	if (s.maxPower > maxPower)
		len = s.maxPower;
	TSet tmp(len);
	tmp.bitField = bitField | s.bitField;
	return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem < 0 || Elem >= maxPower) throw -1;
	TSet tmp(*this);
	tmp.InsElem(Elem);
	return tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if (Elem < 0 || Elem >= maxPower) throw -1;
	TSet tmp(*this);
	tmp.bitField.ClrBit(Elem);
	return tmp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	int len = maxPower;
	if (s.maxPower > maxPower)
		len = s.maxPower;
	TSet tmp(len);
	tmp = bitField & s.bitField;
	return tmp;
}

TSet TSet::operator~(void) // дополнение
{
	TSet tmp(*this);
	tmp.bitField = ~tmp.bitField;
	return tmp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int i;
	cin >> i;
	for (; ((i > -1) && (i < s.maxPower)); cin >> i)
	  s.bitField.SetBit(i);
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << s.bitField << ' ';
	return ostr;
}
