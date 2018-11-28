#pragma once

#include "tbitfield.h"
#include <math.h>

class TSet
{
	friend istream &operator>>(istream &istr, TSet &bf);
	friend ostream &operator<<(ostream &ostr, const TSet &bf);
private:
  int maxPower;       // максимальная мощность множества
  TBitField bitField; // битовое поле для хранения характеристического вектора
public:
  TSet(int mp);
  TSet(const TSet &s);       // конструктор копирования
  TSet(const TBitField &bf); // конструктор преобразования типа
  operator TBitField();      // преобразование типа к битовому полю
  // доступ к битам
  int GetMaxPower(void) const;     // максимальная мощность множества
  void InsElem(const int elem);       // включить элемент в множество
  void DelElem(const int elem);       // удалить элемент из множества
  int IsMember(const int elem) const; // проверить наличие элемента в множестве
  // теоретико-множественные операции
  int operator== (const TSet &s) const; // сравнение
  int operator!= (const TSet &s) const; // сравнение
  TSet& operator=(const TSet &s);  // присваивание
  TSet operator+ (const int elem); // объединение с элементом
                                   // элемент должен быть из того же универса
  TSet operator- (const int elem); // разность с элементом
                                   // элемент должен быть из того же универса
  TSet operator+ (const TSet &s);  // объединение
  TSet operator* (const TSet &s);  // пересечение
  TSet operator~ (void);           // дополнение
};