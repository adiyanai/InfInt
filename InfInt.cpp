#include <iostream>
#include <algorithm>
#include <string.h>
#include <cstring>
#include <stdio.h>
#include "LargeIntegers.h"
using namespace std;

/**
 * convert the decimal number to binary number
 * @param s - a string number
 * @return a string of the binary number
 */
string InfInt::convertToBinary(string s) const{
    string numberTempString="";
    string afterDiv = "";
    int digit = 0;
    long i = 0;
    int tempDiv = 0;
    string binaryNum = "";
    // if the number is negative
    if(s[0]=='-'){
        i++;
    }

    while (s.compare("0")){
        if(s[0]-48==0){
            i++;
        }
        for(i ; i <s.size();i++){
            if((s[i]>='0')&&(s[i]<='9')){
                digit = s[i]-'0';
                if(i==s.size()-1){
                    if(digit%2){
                        binaryNum+='1';
                    } else{
                        binaryNum+='0';
                    }
                }

                if(digit%2 == 0){
                    digit = digit/2+tempDiv+48;
                    afterDiv+=digit;
                    tempDiv = 0;
                } else{
                    digit = digit/2+tempDiv+48;
                    afterDiv+=digit;
                    tempDiv = 5;
                }
            }else{
                return NULL;
            }
        }
        s=afterDiv;
        tempDiv = 0;
        afterDiv = "";
        i =0;
    }
    std::reverse(binaryNum.begin(),binaryNum.end());
    return binaryNum;
}

/**
 * convert the binary number to decimal number
 * @param s - a binary string number
 * @param neg - true, if the number is negative, false if he is positive
 * @return a string of decimal number
 */
string InfInt::convertToDecimal(string s, bool neg) {
    string str;
    InfInt sum = InfInt("0");
    InfInt two = InfInt("2");

    for (int i = 0; i < s.length(); i++) {
        str = s[i];
        sum = (sum * two) + InfInt(str);
    }

    // if the number is negative add minus to the number
    if (neg && sum.numString != "0") {
        sum = InfInt('-' + sum.numString);
    }

    return sum.numString;
}

/**
 * check between two positive numbers if the first one is smaller
 * @param str - an InfInt number
 * @return true if the first number smaller than the second one,
 *         false if the first number bigger or equals to the second number
 */
bool InfInt::isSmallerPositive(InfInt str) {
    if (this->length < str.length) {
        return true;
    }
    if (str.length < this->length) {
        return false;
    }

    // pass over the digits of the two numbers and compare between them
    for (int i = 0; i < this->length; i++) {
        if (this->numString[i] < str.numString[i]) {
            return true;
        } else if (this->numString[i] > str.numString[i]) {
            return false;
        }
    }
    return false;
}

/**
 * check between two positive numbers if the first one is bigger
 * @param str - an InfInt number
 * @return true if the first number bigger than the second one,
 *         false if the first number smaller or equals to the second number
 */
bool InfInt::isBiggerPositive(InfInt str) {
    if (this->length > str.length) {
        return true;
    }
    if (str.length > this->length) {
        return false;
    }

    // pass over the digits of the two numbers and compare between them
    for (int i = 0; i < this->length; i++) {
        if (this->numString[i] > str.numString[i]) {
            return true;
        } else if (this->numString[i] < str.numString[i]) {
            return false;
        }
    }
    return false;
}

/**
 * check between two negative numbers if the first one is smaller
 * @param str - an InfInt number
 * @return true if the first number smaller than the second one,
 *         false if the first number bigger or equals to the second number
 */
bool InfInt::isSmallerNegative(InfInt str) {
    if (this->length > str.length) {
        return true;
    }
    if (str.length > this->length) {
        return false;
    }

    // start the loop from 1 so the minus: '-' won't bother us
    // pass over the digits of the two numbers and compare between them
    for (int i = 1; i < this->length; i++) {
        if (this->numString[i] > str.numString[i]) {
            return true;
        } else if (this->numString[i] < str.numString[i]) {
            return false;
        }
    }
    return false;
}

/**
 * check between two negative numbers if the first one is bigger
 * @param str - an InfInt number
 * @return true if the first number bigger than the second one,
 *         false if the first number smaller or equals to the second number
 */
bool InfInt::isBiggerNegative(InfInt str) {
    if (this->length < str.length) {
        return true;
    }
    if (str.length < this->length) {
        return false;
    }

    // start the loop from 1 so the minus: '-' won't bother us
    // pass over the digits of the two numbers and compare between them
    for (int i = 1; i < this->length; i++) {
        if (this->numString[i] < str.numString[i]) {
            return true;
        } else if (this->numString[i] > str.numString[i]) {
            return false;
        }
    }
    return false;
}

/**
 * check between two numbers, one negative and the other positive,
 * if the first one is smaller
 * @param str - an InfInt number
 * @return true if the first number is negative, false if he is positive
 */
bool InfInt::isSmallerNegPos(InfInt str) {
    return (this->numString[0] == '-');
}

/**
 * divide two InfInt numbers and return the a/b or a%b
 * according to the boolean flag
 * @param n - an InfInt number
 * @param flag - true if we want to return a/b
 *               false if we want to return a%b
 * @return a/b or a%b, acocording to the boolean flag
 */
InfInt InfInt::divide (InfInt n, bool flag) {
    long size = 0;
    bool negR, negQ;
    InfInt numR, numN, result;
    string r, q, b1, b2;

    negR = false;
    negQ = false;

    // if just one of 'this' and 'n' is negative, the result of this/n will be negative
    if ((this->negative && !n.negative) || (!this->negative && n.negative)) {
        negQ = true;
    }

    // convert the two numbers from decimal to binary
    b1 = this->convertToBinary(this->numString);
    b2 = n.convertToBinary(n.numString);

    if (b2 == "0")
        throw "Cannot divide by zero";


    size = max(b1.size(), b2.size());

    // make a string of zeros in a length of the longer number between b1 and b2
    for (long i = 0; i < size; i++) {
        q += '0';
    }

    for (long i = 0; i < b1.size(); i++) {
        r += '0';
        r[r.size() - 1] = b1[i];
        numR = InfInt(convertToDecimal(r, false));
        numN = InfInt(convertToDecimal(b2, false));
        if (numR >= numN) {
            result = numR - numN;
            r = convertToBinary(result.numString);
            q[i] = '1';
        }
    }
    // if the flag is false return the result of 'this'%'n'
    if (!flag) {
        return InfInt(convertToDecimal(r, negR));
    }

    // if the flag is true return the result of 'this'/'n'
    return InfInt(convertToDecimal(q, negQ));
}


/**
 * default constructor
 * the number is zero
 */
InfInt::InfInt() {
    this->numString = "0";
    this->length = 1;
    this->negative = false;
}

/**
 * constructor
 * @param num - an long int number
 */
InfInt::InfInt(const long int num) {
    // convert the long int num to be in type of string
    string s = to_string(num);
    this->numString = s;
    this->length = this->numString.length();
    this->negative = (s[0] == '-');
}

/**
 * constructor
 * @param num - a string number
 */
InfInt::InfInt(const string num) {
    this->numString = num;
    this->length = this->numString.length();
    negative = (num[0] == '-');
}

/**
 * constructor
 * @param num - a char* number
 */
InfInt::InfInt(const char* num) {
    this->numString = num;
    this->length = this->numString.length();
    this->negative = (num[0] == '-');
}

/**
 * do addition between two InfInt numbers and return their sum
 * (as InfInt number)
 * @param n - an InfInt number
 * @return - the sum after addition two InfInt number
 */
InfInt InfInt::operator+(InfInt n) {

    int digit, carry;
    carry = 0;
    // a boolean variable that represent if the two numbers
    // we want to sum are negative
    bool neg = false;
    // take an empty string for storing result
    string newNum;
    InfInt newInf1, newInf2;

    // check if the two numbers we want to sum are negative
    if ((this->numString[0] == '-') && (n.numString[0] == '-')) {
        neg = true;
        // erase the '-' from the two numbers so we can sum them like two
        // positive number (we return the '-' later)
        newInf1 = InfInt(this->numString.substr(1, this->length -1));
        newInf2 = InfInt(n.numString.substr(1, n.length -1));

        // if just one of the numbers negative
    } else if ((this->numString[0] == '-') || (n.numString[0] == '-')) {
        if (this->numString[0] == '-') {
            newInf1 = InfInt(this->numString.substr(1, this->length -1));
            return n.operator-(newInf1);
        } else {
            newInf2 = InfInt(n.numString.substr(1, n.length -1));
            return this->operator-(newInf2);
        }
    } else {
        newInf1 = *this;
        newInf2 = n;
    }

    // reverse both of strings
    reverse(newInf1.numString.begin(), newInf1.numString.end());
    reverse(newInf2.numString.begin(), newInf2.numString.end());

    if (newInf1.length <= newInf2.length) {
        for (int i = 0; i < newInf2.length; i++) {
            // if we finish to pass over all the digits in the first number
            // but not finish to pass over all the digits in the second number
            if (newInf1.length <= i) {
                // add the digits that left in the second number to our sum
                digit = (newInf2.numString[i] - '0') + carry;
                newNum.push_back((char)(digit % 10 + '0'));
                carry = digit / 10;
            } else {
                // add one digit from the first number with one digit from the second number
                digit = (newInf1.numString[i] - '0') + (newInf2.numString[i] - '0') + carry;
                newNum.push_back((char)(digit % 10 + '0'));
                carry = digit / 10;
            }
        }
    } else {
        for (int i = 0; i < newInf1.length; i++) {
            // if we finish to pass over all the digits in the second number
            // but not finish to pass over all the digits in the first number
            if (newInf2.length <= i) {
                // add the digits that left in the first number to our sum
                digit = (newInf1.numString[i] -'0') + carry;
                newNum.push_back((char)(digit % 10 + '0'));
                carry = digit / 10;
            } else {
                // add one digit from the first number with one digit from the second number
                digit = (newInf1.numString[i] - '0') + (newInf2.numString[i] - '0') + carry;
                newNum.push_back((char)(digit % 10 + '0'));
                carry = digit/ 10;
            }
        }
    }

    if (carry != 0) {
        newNum.push_back((char)(carry + '0'));
    }
    // if the two numbers we sum were negative, add '-' (the minus)
    // to the string result
    if (neg) {
        newNum.push_back('-');
    }
    // reverse resulted string
    reverse(newNum.begin(), newNum.end());
    return InfInt(newNum);
}

/**
 * prefix ++ on number
 * Increases the number by 1
 * @return the InfInt number after the ++
 */
InfInt& InfInt::operator++() {
    string one = "1";
    InfInt newInf = InfInt(one);
    // Increases the number by 1
    *this = *this + newInf;
    return *this;
}

/**
 * postfix ++ on number
 * Increases the number by 1
 * @return the InfInt number before the ++
 */
InfInt InfInt::operator++(int n) {
    InfInt temp = *this;
    // Increases the number by 1
    ++(*this);
    return temp;
}

/**
 * do subtraction between two InfInt numbers and return their difference
 * (as InfInt number)
 * @param n - an InfInt number
 * @return - the subtraction between two InfInt numbers
 */
InfInt InfInt::operator-(InfInt n) {
    // take an empty string for storing result
    string newNum;
    InfInt newInf;
    bool smaller;
    int carry = 0;
    int sub = 0;
    // flag if the first number smaller then the second one
    smaller = this->isSmallerPositive(n);

    // if the two numbers are negative
    if ((this->numString[0] == '-') && (n.numString[0] == '-')) {
        // -- = + so we remove the '-'
        // (-A)-(-B) its like (-A)+B
        newInf = InfInt(n.numString.substr(1, n.length-1));
        // (-A)+B
        return this->operator+(newInf);
        // if just the second number is negative
    } else if (n.numString[0] == '-') {
        // -- = + so we remove the '-'
        // (A)-(-B) its like A+B
        newInf = InfInt(n.numString.substr(1, n.length-1));
        // A+B
        return this->operator+(newInf);
        // if just the first number is negative
    } else if (this->numString[0] == '-') {
        // (-A)-(B) its like (-A)+(-B)
        newInf = InfInt('-' + n.numString);
        // (-A)+(-B)
        return this->operator+(newInf);
        // if the two numbers are positive
    } else {
        // reverse both of strings
        reverse(this->numString.begin(), this->numString.end());
        reverse(n.numString.begin(), n.numString.end());

        // if the first number bigger then the second one
        if (!smaller) {
            // run loop till small string length
            // and subtract digit of 'this' to n
            for (int i = 0; i < this->length; i++) {
                // subtract remaining digits, if we finished to go over 'n'
                if (n.length <= i) {
                    sub = (this->numString[i] - '0') - carry;
                    // if subtraction is less then zero, we add then 10 into sub
                    // and take carry as 1 for calculating next step
                    if (sub < 0) {
                        sub = sub + 10;
                        carry = 1;
                    } else {
                        carry = 0;
                    }
                    if ((sub != 0) || (sub == 0 && i != this->length - 1)) {
                        newNum.push_back(sub + '0');
                    }
                    // subtract digit of 'this' to 'n', while we not finish
                    // to go over 'n'
                } else {
                    // do school mathematics, compute difference of current digit
                    sub = (this->numString[i] - '0') - (n.numString[i] - '0') - carry;
                    // if subtraction is less then zero, we add then 10 into sub
                    // and take carry as 1 for calculating next step
                    if (sub < 0) {
                        sub = sub + 10;
                        carry = 1;
                    } else {
                        carry = 0;
                    }
                    newNum.push_back(sub + '0');
                }
            }
            // if the second number bigger then the second one
        } else {
            for (int i = 0; i < n.length; i++) {
                if (this->length <= i) {
                    sub = (n.numString[i] - '0') - carry;
                    // if subtraction is less then zero, we add then 10 into sub
                    // and take carry as 1 for calculating next step
                    if (sub < 0) {
                        sub = sub + 10;
                        carry = 1;
                    } else {
                        carry = 0;
                    }
                    if ((sub != 0) || (sub == 0 && i != n.length - 1)) {
                        newNum.push_back(sub + '0');
                    }
                } else {
                    // do school mathematics, compute difference of current digit
                    sub = (n.numString[i] - '0') - (this->numString[i] - '0') - carry;
                    // if subtraction is less then zero, we add then 10 into sub
                    // and take carry as 1 for calculating next step
                    if (sub < 0) {
                        sub = sub + 10;
                        carry = 1;
                    } else {
                        carry = 0;
                    }
                    newNum.push_back(sub + '0');
                }
            }
            newNum.push_back('-');
        }
    }
    // reverse both of strings back
    reverse(this->numString.begin(), this->numString.end());
    reverse(n.numString.begin(), n.numString.end());

    // reverse resulted string
    reverse(newNum.begin(), newNum.end());

    // if the number is string of zeros, return just one zero
    for (int i = 0; i < newNum.length(); i++) {
        if (newNum[i] != '0') {
            break;
        }
        if ((newNum[i] == '0') && (i == newNum.length() - 1)) {
            return InfInt("0");
        }
    }

    return InfInt(newNum);
}

/**
 * prefix -- on number
 * reduce the number by 1
 * @return the InfInt number after the --
 */
InfInt& InfInt::operator--() {
    string one = "1";
    InfInt newInf = InfInt(one);
    // decreases the number by 1
    *this = *this - newInf;
    return *this;
}

/**
 * postfix -- on number
 * reduce the number by 1
 *  @return the InfInt number before the --
 */
InfInt InfInt::operator--(int n) {
    InfInt temp = *this;
    // decreases the number by 1
    --(*this);
    return temp;
}

/**
 * Multiplies two InfInt numbers
 * @param n - an InfInt number
 * @return the product of the two InfInt numbers
 */
InfInt InfInt::operator*(InfInt n) {
    // take an empty string for storing result
    string newNum;
    long carry = 0;
    // a boolean variable that represent if one of the numbers
    // we want to multiplies are negative
    bool oneNeg = false;
    InfInt newInf1, newInf2;

    // if one of the numbers are zero, return 0
    if ((this->numString[0] == '0') || (n.numString[0] == '0')) {
        newNum = '0';
        return newNum;
    }

    // if the two numbers are both negative
    if ((this->numString[0] == '-') && (n.numString[0] == '-')) {
        newInf1 = InfInt(this->numString.substr(1, this->length-1));
        newInf2 = InfInt(n.numString.substr(1, n.length-1));
        // if just one of the numbers are negative
    } else if ((this->numString[0] == '-') && (n.numString[0] != '-')) {
        oneNeg = true;
        newInf1 = InfInt(this->numString.substr(1, this->length-1));
        newInf2 = InfInt(n);
        // if just one of the numbers are negative
    } else if ((this->numString[0] != '-') && (n.numString[0] == '-')) {
        oneNeg = true;
        newInf1 = InfInt(*this);
        newInf2 = InfInt(n.numString.substr(1, n.length-1));
        // if the two numbers are both positive
    } else {
        newInf1 = InfInt(*this);
        newInf2 = InfInt(n);
    }

    // will keep the result number in vector, in reverse order
    vector <long> result(newInf1.numString.size() + newInf2.numString.size(), 0);
    //two indexes are used to find positions in result
    int i_inf1 = 0;
    int i_inf2 = 0;
    long n1, n2, sum;

    // go from right to left in newInf1
    for (long i = newInf1.numString.size() - 1; i >= 0; i--) {
        carry = 0;
        n1 = newInf1.numString[i] - '0';

        // to shift position to left after every multiplication
        // of a digit in newInf2
        i_inf2 = 0;

        // go from right to left in newInf2
        for (long j = newInf2.numString.size() - 1; j >= 0; j--) {
            // take the current digit of the second number
            n2 = newInf2.numString[j] - '0';

            // multiply with current digit of the first number and
            // add result to previously stored result at current position
            sum = (n1 * n2) + result[i_inf1 + i_inf2] + carry;

            // carry for next iteration
            carry = sum / 10;
            // store result
            result[i_inf1 + i_inf2] = sum % 10;
            i_inf2++;
        }

        // store carry in next cell
        if (carry > 0) {
            result[i_inf1 + i_inf2] += carry;
        }

        //to shift position to left after every multiplication
        // of a digit in newInt1
        i_inf1++;
    }

    // ignore '0's from the right
    long s = result.size() - 1;
    while ((s >= 0) && (result[s] == 0)) {
        s--;
    }

    while (s >= 0) {
        newNum += std::to_string(result[s--]);
    }

    // if just one of the numbers were negative add minus to the result
    if (oneNeg) {
        // reverse the result so we can add the minus: '-'
        reverse(newNum.begin(), newNum.end());
        // add minus to the result
        newNum.push_back('-');
        // reverse the result back
        reverse(newNum.begin(), newNum.end());
    }

    return InfInt(newNum);
}

/**
 * do division(/) between two InfInt numbers and return the quotient (A/B)
 * (as InfInt number)
 * @param n - an InfInt number
 * @return the quotient(A/B) after division two InfInt numbers
 */
InfInt InfInt::operator/(InfInt n) {
    return this->divide(n, true);
}

/**
 * do division(%) between two InfInt numbers and return the quotient (A%B)
 * (as InfInt number)
 * @param n - an InfInt number
 * @return the quotient(A%B) after division two InfInt numbers
 */
InfInt InfInt::operator%(InfInt n) {
    return this->divide(n, false);
}

/**
 * do addition between two InfInt numbers,
 * and push this result(the sum) to the 'this' InfInt number
 * @param n - an InfInt number
 * @return 'this' after we changed him to be the addition between him
 *         and other InfInt number
 */
InfInt& InfInt::operator+=(InfInt n) {
    *this = *this + n;
    return *this;
}

/**
 * checks if the two numbers are equal
 * @param n - an InfInt number
 * @return true if the two numbers are equal, else false
 */
bool InfInt::operator==(InfInt n) {
    // to represent if the two numbers are equal
    bool flag = false;
    // if the two numbers are negative
    if ((this->numString[0] == '-') && (n.numString[0] == '-')) {
        if (!this->isSmallerNegative(n) && !this->isBiggerNegative(n)) {
            flag = true;
        }
        // if the two numbers are positive
    } else if ((this->numString[0] != '-') && (n.numString[0] != '-')) {
        if (!this->isSmallerPositive(n) && !this->isBiggerPositive(n)) {
            flag = true;
        }
    }

    if (this->numString == "0" && n.numString == "0") {
        flag = true;
    }
    return flag;
}

/**
 * checks if the first number is bigger than the second number
 * @param n - an InfInt number
 * @return true if the first number is bigger than the second number,
 *         else false
 */
bool InfInt::operator>(InfInt n) {
    // to represent if the first number is bigger than the second number
    bool flag = false;
    // if the two numbers are negative
    if ((this->numString[0] == '-') && (n.numString[0] == '-')) {
        if (this->isBiggerNegative(n)) {
            flag = true;
        }
        // if the two numbers are positive
    } else if ((this->numString[0] != '-') && (n.numString[0] != '-')) {
        if (this->isBiggerPositive(n)) {
            flag = true;
        }
        // if one of the numbers negative and the other positive
    } else {
        if (!this->isSmallerNegPos(n)) {
            flag = true;
        }
    }
    return flag;
}

/**
* checks if the first number is bigger than the second number
* or equals to him
* @param n - an InfInt number
* @return true if the first number is bigger than the second number
*         or equals to him, else false
*/
bool InfInt::operator>=(InfInt n) {
    return ((*this > n) || *this == n);
}

/**
 * checks if the first number is smaller than the second number
 * @param n - an InfInt number
 * @return true if the first number is smaller than the second number,
 *         else false
 */
bool InfInt::operator<(InfInt n) {
    // to represent if the first number is smaller than the second number
    bool flag = false;
    // if the two numbers are negative
    if ((this->numString[0] == '-') && (n.numString[0] == '-')) {
        if (this->isSmallerNegative(n)) {
            flag = true;
        }
        // if the two numbers are positive
    } else if ((this->numString[0] != '-') && (n.numString[0] != '-')) {
        if (this->isSmallerPositive(n)) {
            flag = true;
        }
        // if one of the numbers negative and the other positive
    } else {
        if (this->isSmallerNegPos(n)) {
            flag = true;
        }
    }
    return flag;
}

/**
* checks if the first number is smaller than the second number
* or equals to him
* @param n - an InfInt number
* @return true if the first number is smaller than the second number
*         or equals to him, else false
*/
bool InfInt::operator<=(InfInt n) {
    return ((*this < n) || *this == n);
}

/**
 * do AND between two InfInt numbers
 * @param n - an InfInt number
 * @return - the result of the AND between two InfInt numbers
 */
InfInt InfInt::operator&(InfInt n) {
    InfInt newInf;
    long n1, n2;
    string binaryS,b1, b2, inf1, inf2;
    bool neg = false;
    binaryS = "";

    // convert the two numbers from decimal to binary
    b1 = this->convertToBinary(this->numString);
    b2 = n.convertToBinary(n.numString);

    // the length of the two binary strings
    n1 = b1.length();
    n2 = b2.length();

    // just if the two numbers are negative
    // the new number will remain negative
    if (this->negative && n.negative) {
        neg = true;
    }

    // push zeros on the left side of the shorter number
    // so now the two binary numbers will be in the same length
    if (n1 > n2) {
        for (int i = 1; i <= n1 - n2; i++) {
            inf2 += '0';
        }
        inf2 += b2;
        inf1 = b1;
    } else if (n1 < n2){
        for (int i = 1; i <= n2 - n1; i++) {
            inf1 += '0';
        }
        inf1 += b1;
        inf2 = b2;
        // if the two binary numbers have the same size
    } else {
        inf1 = b1;
        inf2 = b2;
    }

    // pass on any bit of the two numbers ant do AND between them
    for (int i = 0; i < inf1.length(); i++) {
        if ((inf1[i] == '1') && (inf2[i] == '1')) {
            binaryS += '1';
        } else {
            binaryS += '0';
        }
    }
    newInf = InfInt(convertToDecimal(binaryS, neg));
    // return the new InfInt
    return newInf;
}

/**
 * do AND between two InfInt numbers
 * and push this result to the 'this' InfInt number
 * @param n - an InfInt number
 * @return 'this' after we changed him to be the AND between him
 *         and other InfInt number
 */
InfInt& InfInt::operator&=(InfInt n) {
    // call to the function &
    *this = *this & n;
    return *this;
}

/**
 * do OR between two InfInt numbers
 * @param n - an InfInt number
 * @return - the result of the OR between two InfInt numbers
 */
InfInt InfInt::operator|(InfInt n) {
    InfInt newInf;
    long n1, n2;
    string binaryS, b1, b2, inf1, inf2;
    bool neg = false;
    binaryS = "";

    // convert the two numbers from decimal to binary
    b1 = this->convertToBinary(this->numString);
    b2 = n.convertToBinary(n.numString);

    // the length of the two binary strings
    n1 = b1.length();
    n2 = b2.length();

    // if one of the numbers are negative or both of them
    // the new number will be negative, else he will be positive
    if (this->negative || n.negative) {
        neg = true;
    }

    // push zeros on the left side of the shorter number
    // so now the two binary numbers will be in the same length
    if (n1 > n2) {
        for (int i = 1; i <= n1 - n2; i++) {
            inf2 += '0';
        }
        inf2 += b2;
        inf1 = b1;
    } else if (n1 < n2){
        for (int i = 1; i <= n2 - n1; i++) {
            inf1 += '0';
        }
        inf1 += b1;
        inf2 = b2;
        // if the two binary numbers have the same size
    } else {
        inf1 = b1;
        inf2 = b2;
    }

    // pass on any bit of the two numbers ant do OR between them
    for (int i = 0; i < inf1.length(); i++) {
        if ((inf1[i] == '0') && (inf2[i] == '0')) {
            binaryS += '0';
        } else {
            binaryS += '1';
        }
    }
    newInf = InfInt(convertToDecimal(binaryS, neg));
    // return the new InfInt
    return newInf;
}

/**
 * do XOR between two InfInt numbers
 * @param n - an InfInt number
 * @return - the result of the XOR between two InfInt numbers
 */
InfInt InfInt::operator^(InfInt n) {
    InfInt newInf;
    long n1, n2;
    string binaryS, b1, b2, inf1, inf2;
    bool neg = false;
    binaryS = "";

    // convert the two numbers from decimal to binary
    b1 = this->convertToBinary(this->numString);
    b2 = n.convertToBinary(n.numString);

    // the length of the two binary strings
    n1 = b1.length();
    n2 = b2.length();

    // just if one of the numbers are negative and the other is positive
    // the new number will be negative, else he will be positive
    if ((this->negative && !n.negative) || (!this->negative && n.negative)) {
        neg = true;
    }

    // push zeros on the left side of the shorter number
    // so now the two binary numbers will be in the same length
    if (n1 > n2) {
        for (int i = 1; i <= n1 - n2; i++) {
            inf2 += '0';
        }
        inf2 += b2;
        inf1 = b1;
    } else if (n1 < n2){
        for (int i = 1; i <= n2 - n1; i++) {
            inf1 += '0';
        }
        inf1 += b1;
        inf2 = b2;
        // if the two binary numbers have the same size
    } else {
        inf1 = b1;
        inf2 = b2;
    }

    // pass on any bit of the two numbers ant do Xor between them
    for (int i = 0; i < inf1.length(); i++) {
        if (((inf1[i] == '0') && (inf2[i] == '1')) || ((inf1[i] == '1') && (inf2[i] == '0'))) {
            binaryS += '1';
        } else {
            binaryS += '0';
        }
    }
    newInf = InfInt(convertToDecimal(binaryS, neg));
    // return the new InfInt number
    return newInf;
}

/**
 * increases the number by 2^x
 * @param x - a long number
 * @return - the result of the increases of the number by 2^x
 */
InfInt InfInt::operator<<(long x) {
    InfInt newInf;
    string binaryStr, numStr;
    binaryStr = "";
    // convert the number from decimal to binary
    binaryStr = this->convertToBinary(this->numString);
    // increases the number by 2^x
    for (int i = 1; i <= x; i++) {
        binaryStr += '0';
    }
    numStr = convertToDecimal(binaryStr, this->negative);
    newInf = InfInt(numStr);
    return newInf;
}

/**
* decreases the number by 2^x
* @param x - a long number
* @return - the result of the decreases of the number by 2^x
*/
InfInt InfInt::operator>>(long x) {
    InfInt newInf;
    string binaryStr, numStr;
    // convert the number from decimal to binary
    numStr = this->convertToBinary(this->numString);

    if (x >= numStr.length()) {
        return InfInt();
    }
    // decreases the number by 2^x
    binaryStr = numStr.substr(0, numStr.length() - x);

    numStr = convertToDecimal(binaryStr, this->negative);
    newInf = InfInt(numStr);
    return newInf;
}

/**
* decreases the number by 2^x
* @param x - a long number
* @return - the result of the decreases of the number by 2^x
*/
InfInt& InfInt::operator>>=(long x) {
    *this = *this >> x;
    return *this;
}

/**
 * convert he InfInt number to int number
 * if the InfInt number bigger than the size of int,
 * cut the extra bits from the InfInt number
 * @return - an int number
 */
InfInt:: operator int() const {
    int sum, digit, count;
    string number;
    long n;
    sum = 0;
    count = 0;
    // convert the string number to binary number
    number = this->convertToBinary(this->numString);

    // if the InfInt number bigger than the size of int
    if (number.length() > 31) {
        n = number.length() - 31;
    } else {
        n = 0;
    }

    for (long i =  number.length() - 1; i >= n; i--) {
        digit = number[i] - '0';
        if (digit == 1) {
            sum += 1 * pow(2, count);
        }
        count++;
    }

    // if the number was negative, also the new number be negative
    if (this->negative) {
        sum *= -1;
    }

    return sum;
}

/**
 * output operator
 * @param out - ostream
 * @param infInt - an InfInt number
 * @return out
 */
ostream &operator<<(ostream &out, const InfInt &infInt) {
    out << infInt.numString;
    return out;
}

/**
 * input operator
 * @param in - istream
 * @param infInt - an InfInt number
 * @return in
 */
istream &operator>>(istream &in, InfInt &infInt) {
    in >> infInt.numString;
    infInt = InfInt(infInt.numString);
    return in;
}
