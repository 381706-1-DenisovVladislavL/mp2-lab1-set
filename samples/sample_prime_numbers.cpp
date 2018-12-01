// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// sample_prime_numbers.cpp - Copyright (c) Гергель В.П. 20.08.2000
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Тестирование битового поля и множества

#include <iomanip>

 #define USE_SET // Использовать класс TSet,
                // закоментировать, чтобы использовать битовое поле

#ifndef USE_SET // Использовать класс TBitField

#include "tbitfield.h"

int main()
{
  int n, m, k, count, sizeBit;

  setlocale(LC_ALL, "Russian");
  cout << "Тестирование программ поддержки битового поля" << endl;
  cout << "             Решето Эратосфена" << endl;
  cout << "Введите верхнюю границу целых значений - ";
  cin  >> n;
  TBitField s(n + 1);
  // заполнение множества
  for (m = 2; m <= n; m++)
		s.SetBit(m);
  // проверка до sqrt(n) и удаление кратных
  for (m = 2; m * m <= n; m++)
    // если m в s, удаление кратных
    if (s.GetBit(m))
      for (k = 2 * m; k <= n; k += m)
        if (s.GetBit(k))
          s.ClrBit(k);
  // оставшиеся в s элементы - простые числа
  cout << endl << "Печать множества некратных чисел" << endl << s << endl;
  cout << endl << "Печать простых чисел" << endl;
  count = 0;
  k = 1;
  for (m = 2; m <= n; m++)
    if (s.GetBit(m))
    {
      count++;
      cout << setw(3) << m << " ";
      if (k++ % 10 == 0)
        cout << endl;
    }
  cout << endl;
  cout << "В первых " << n << " числах " << count << " простых" << endl;

  cout << "\n\n\tВвод битовой строки\n";
  cout << "Введите размер битовой строки\n";
  cin >> sizeBit;
  TBitField bit(sizeBit);
  cout << "Введите битовую строку длинной " << sizeBit << "\n";
  cin >> bit;
  cout << "\nВаша битовая строка\n";
  cout << bit;
  cout << "\n\nМножество чисел битовой строки\n";
  for (m = 0; m < sizeBit; m++)
    if (bit.GetBit(m))
      cout << setw(3) << m << " ";
  cout << endl;
}
#else

#include "tset.h"

int main()
{
  int n, m, k, count, maxElem;

  setlocale(LC_ALL, "Russian");
  cout << "Тестирование программ поддержки множества" << endl;
  cout << "              Решето Эратосфена" << endl;
  cout << "Введите верхнюю границу целых значений - ";
  cin  >> n;
  TSet s(n + 1);
  // заполнение множества
  for (m = 2; m <= n; m++)
    s.InsElem(m);
  // проверка до sqrt(n) и удаление кратных
  for (m = 2; m * m <= n; m++)
    // если м в s, удаление кратных
    if (s.IsMember(m))
      for (k = 2 * m; k <= n; k += m)
       if (s.IsMember(k))
         s.DelElem(k);
  // оставшиеся в s элементы - простые числа
  cout << endl << "Печать множества некратных чисел" << endl << s << endl;
  cout << endl << "Печать простых чисел" << endl;
  count = 0;
  k = 1;
  for (m = 2; m <= n; m++)
    if (s.IsMember(m))
    {
      count++;
      cout << setw(3) << m << " ";
      if (k++ % 10 == 0)
        cout << endl;
    }
  cout << endl;
  cout << "В первых " << n << " числах " << count << " простых" << endl;

  cout << "\n\n\tВвод множества целых чисел\n";
  cout << "Введите наибольший элемент множества\n";
  cin >> maxElem;
  TSet bit(maxElem + 1);
  cout << "Введите элементы множества (-1 или число >" << maxElem <<" для завершения ввода)\n";
  cin >> bit;
  cout << "\nВведенное множество в виде битовой строки\n";
  cout << bit;
  cout << "\n\nВведенное множество в виде хранимых в нем целых чисел\n";
  for (m = 0; m <= maxElem; m++)
    if (bit.IsMember(m))
      cout << setw(3) << m << " ";
  cout << endl;
}

#endif