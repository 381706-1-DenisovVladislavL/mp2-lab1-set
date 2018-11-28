#pragma once

#include <iostream>
#include <math.h>
#include <algorithm>
#include <string>

using namespace std;

typedef unsigned int uInt;

class TBitField
{
	friend istream &operator>>(istream &istr, TBitField &bf);
	friend ostream &operator<<(ostream &ostr, const TBitField &bf);
private:
  int  bitLen; // длина битового поля - макс. к-во битов
  uInt *pMem; // память для представления битового поля
  int  memLen; // к-во эл-тов Мем для представления бит.поля

  int   GetMemIndex(const int n) const; // индекс в pМем для бита n       
  uInt GetMemMask (const int n) const; // битовая маска для бита n       
public:
  TBitField(int len);                                               
  TBitField(const TBitField &bf);                                       
  ~TBitField();                                                         

  int GetLength(void) const;      // получить длину (к-во битов)          
  void SetBit(const int n);       // установить бит                       
  void ClrBit(const int n);       // очистить бит                         
  int  GetBit(const int n) const; // получить значение бита               

  int operator==(const TBitField &bf) const; // сравнение                 
  int operator!=(const TBitField &bf) const; // сравнение
  TBitField& operator=(const TBitField &bf); // присваивание              
  TBitField  operator|(const TBitField &bf); // операция "или"           
  TBitField  operator&(const TBitField &bf); // операция "и"           
  TBitField  operator~(void);                // отрицание                
};
// Структура хранения битового поля
//   бит.поле - набор битов с номерами от 0 до BitLen
//   массив pМем рассматривается как последовательность MemLen элементов
//   биты в эл-тах pМем нумеруются справа налево (от младших к старшим)
