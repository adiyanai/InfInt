#ifndef UNTITLED_LARGEINTEGERS_H
#define UNTITLED_LARGEINTEGERS_H
#include <iostream>
#include <algorithm>
#include <string.h>
#include <cstring>
#include <stdio.h>

using namespace std;

class InfInt {
    string numString;
    bool negative;
    long length;
private:
    string convertToBinary(string s) const;
    string convertToDecimal(string s, bool neg);
    bool isSmallerPositive(InfInt str);
    bool isBiggerPositive(InfInt str);
    bool isSmallerNegative(InfInt str);
    bool isBiggerNegative(InfInt str);
    bool isSmallerNegPos(InfInt str);
    InfInt divide(InfInt n, bool flag);
public:
    InfInt();
    InfInt(const long int num);
    InfInt(const string num);
    InfInt(const char* num);
    InfInt operator+(InfInt n);
    InfInt& operator++();
    InfInt operator++(int n);
    InfInt operator-(InfInt n);
    InfInt& operator--();
    InfInt operator--(int n);
    InfInt operator*(InfInt n);
    InfInt operator/(InfInt n);
    InfInt operator%(InfInt n);
    InfInt& operator+=(InfInt n);
    bool operator==(InfInt n);
    bool operator>(InfInt n);
    bool operator>=(InfInt n);
    bool operator<(InfInt n);
    bool operator<=(InfInt n);
    InfInt operator&(InfInt n);
    InfInt& operator&=(InfInt n);
    InfInt operator|(InfInt n);
    InfInt operator^(InfInt n);
    InfInt operator<<(long x);
    InfInt operator>>(long x);
    InfInt& operator>>=(long x);
    operator int() const;
    friend ostream &operator<<(ostream &out, const InfInt &infInt);
    friend istream &operator>>(istream &in, InfInt &infInt);
};


#endif //UNTITLED_LARGEINTEGERS_H
