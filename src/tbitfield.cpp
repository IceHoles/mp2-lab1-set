// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len) : BitLen(len)
{   if (len < 0) {
        throw std::invalid_argument("Negative length");
    }
    MemLen = (len / (sizeof(TELEM) * 8)) + 1;
    pMem = new TELEM[MemLen];
    memset(pMem, 0, MemLen * sizeof(TELEM));
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[bf.MemLen];
    memcpy(pMem, bf.pMem, MemLen * sizeof(TELEM));
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return (n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return (TELEM)1 << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0 || n > BitLen) {
        throw std::invalid_argument("Negative bit");
    }
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0 || n > BitLen) {
        throw std::invalid_argument("Negative bit");
    }
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0 || n > BitLen) {
        throw std::invalid_argument("Negative bit");
    }
    return pMem[GetMemIndex(n)] & GetMemMask(n);;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this == &bf)
        return *this;
    TBitField temp(bf);
    swap(*this, temp);
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen ||  MemLen != bf.MemLen) {
        return 0;
    }
    for (int i = 0; i < MemLen; i++) {
        if (pMem[i] != bf.pMem[i]) {
            return 0;
        }
    }
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return ~(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int max = BitLen > bf.BitLen ? BitLen : bf.BitLen;
    TBitField temp(max);
    for (int i = 0; i < MemLen; i++) {
        temp.pMem[i] = pMem[i];
    }
    for (int i = 0; i < bf.MemLen; i++) {
        temp.pMem[i] |= bf.pMem[i];
    }
    return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int max = BitLen > bf.BitLen ? BitLen : bf.BitLen;
    TBitField temp(max);
    for (int i = 0; i < MemLen; i++) {
        temp.pMem[i] = pMem[i];
    }
    for (int i = 0; i < bf.MemLen; i++) {
        temp.pMem[i] &= bf.pMem[i];
    }
    return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField temp(BitLen);
    for (int i = 0; i < MemLen; i++) {
        temp.pMem[i] = ~pMem[i];
    }
    for (int i = BitLen; i < (sizeof(TELEM) * 8) * MemLen; i++) {
        temp.pMem[GetMemIndex(i)] &= ~GetMemMask(i);
    }
    return temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    int len = bf.GetLength();
    for (int i = 0; i < len; i++) {
        if (bf.GetBit(i)) {
            ostr << '1';
        }
        else {
            ostr << '0';
        }
    }
    return ostr;
}


void swap(TBitField& Left, TBitField& Right)
{
    std::swap(Left.BitLen, Right.BitLen);
    std::swap(Left.MemLen, Right.MemLen);
    std::swap(Left.pMem, Right.pMem);
}