// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"


// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.MaxPower)
{
    MaxPower = s.MaxPower;
    BitField = s.BitField;
}

TSet::operator TBitField()
{
    TBitField temp(BitField);
    return temp;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return BitField.test(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if (Elem >= MaxPower)
        throw out_of_range("Out of range");
    BitField.set(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if (Elem >= MaxPower)
        throw out_of_range("Out of range");
    BitField.reset(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    if (*this == s)
        return *this;
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return !(*this == s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
    if (MaxPower != s.MaxPower)
        throw length_error("Length error");
    TSet temp(BitField | s.BitField);
    return temp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet temp(BitField);
    temp.InsElem(Elem);
    return temp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet temp(BitField);
    temp.DelElem(Elem);
    return temp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    if (MaxPower != s.MaxPower)
        throw length_error("Length error");
    TSet temp(BitField & s.BitField);
    return temp;
}

TSet TSet::operator~(void) // дополнение
{
    TSet temp(MaxPower);
    temp.BitField = ~BitField;
    return temp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    char ch = '{';
    int n = s.GetMaxPower();
    for (int i = 0; i < n; i++) {
        if (s.IsMember(i)) {
            ostr << ch << ' ' << i;
            ch = ',';
        }
    }
    ostr << " }";
    return ostr;
}
