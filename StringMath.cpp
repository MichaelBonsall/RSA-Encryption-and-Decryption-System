#include <iostream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

/**
 * @brief Strips leading zeroes of a string number
 * 
 * @param num the number to be stripped of leading zeroes
 * @return the string with no leading zeroes
 */
string stripLeadingZeroes(string num){
    return num.erase(0, min(num.find_first_not_of('0'), num.size() - 1));
}

/**
 * @brief string equivalent of >=.  num1 >= num2
 * 
 * @param num1 
 * @param num2 
 * @return true if num1 >= num2
 * @return false if num1 < num2
 */
bool stringGreaterThanEqualTo(string num1, string num2){
    num1 = stripLeadingZeroes(num1);
    num2= stripLeadingZeroes(num2);

    if (num1.length() > num2.length()) return true; 
    else if (num1.length() < num2.length()) return false;

    //same length strings
    for (int i = 0; i < num1.length(); i++){ //fine to use num1 length() because both strings are the same length
        if (num1[i] == num2[i]) continue;
        else if ((num1[i] - '0') > (num2[i] - '0')) return true; // - '0' returns char to int. ascii shenanigans
        else return false;
    }
    return true; 
}

/**
 * @brief string equivalent to >. num1 > num2
 * 
 * @param num1 
 * @param num2 
 * @return true if num1 > num2
 * @return false if num1 <= num2
 */
bool stringGreaterThan(string num1, string num2){
    num1 = stripLeadingZeroes(num1);
    num2 = stripLeadingZeroes(num2);

    if (num1.length() > num2.length()) return true;
    else if (num1.length() < num2.length()) return false;

    for (int i = 0; i < num1.length(); i++){ //fine to use num1 length() because both strings are the same length
        if (num1[i] == num2[i]) continue;
        else if ((num1[i] - '0') > (num2[i] - '0')) return true; 
        else return false;
    }
    return false; //numbers are equal
}

/**
 * @brief Multiplication between two strings
 * 
 * @param num1 First string to be multiplied
 * @param num2 Second string to be multiplied
 * @return string product
 */
string stringMul(string num1, string num2){ 
    int num1Length = num1.size();
    int num2Length = num2.size();
    string result(num1Length + num2Length, '0');
    for (int i = num1Length - 1; i >= 0; i--){
        for (int j = num2Length - 1; j >= 0; j--){
            int p = (num1[i] - '0') * (num2[j] - '0') + (result[i + j + 1] - '0');
            result[i + j + 1] = p % 10 + '0';
            result[i + j] += p / 10;
      }
    }
    if (result[0] == '0'){
        return result.substr(1, result.length());
    }
    return stripLeadingZeroes(result);
}

/**
 * @brief Subtracts two strings. num1 - num2. Does NOT account for negative values.
 * 
 * @param num1 The minuend (number started with)
 * @param num2 The subtrahend (number to be subtracted)
 * @return string difference
 */
string stringSubtract(string num1, string num2){
    
    string result = "";

    int num1Length = num1.length();
    int num2Length = num2.length();
    int diff = num1Length - num2Length;
    if (num1 == num2) return "0";
    else if (stringGreaterThan(num2, num1)) throw invalid_argument("StringSubstract: num2 is greater than num1");

    int carry = 0;
 
    for (int i = num2Length - 1; i >= 0; i--) {
        int sub = ((num1[i + diff] - '0') - (num2[i] - '0') - carry);
        if (sub < 0) {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;
 
        result.push_back(sub + '0');
    }
 
    //subtract remaining digits of num1
    for (int i = num1Length - num2Length - 1; i >= 0; i--) {
        if (num1[i] == '0' && carry) {
            result.push_back('9');
            continue;
        }
        int sub = ((num1[i] - '0') - carry);
        if (i > 0 || sub > 0) // remove leading 0s
            result.push_back(sub + '0');
        carry = 0;
    }
    reverse(result.begin(), result.end());
    
    return stripLeadingZeroes(result);
}

/**
 * @brief  Adds two string values
 * 
 * @param num1 The first value to be added
 * @param num2 The second value to be added
 * @return string sum
 */
string stringAdd(string num1, string num2){ 
    if (num1.length() > num2.length()) swap(num1, num2);

    string result = "";

    int num1Length = num1.length();
    int num2Length = num2.length();
    int digitDiff = num2Length - num1Length;
    int carry = 0;
    int intSum;

    for (int i = num1Length - 1; i >= 0; i--) {
        intSum = ((num1[i] - '0') + (num2[i + digitDiff]- '0') + carry);
        result.push_back(intSum % 10 + '0');
        carry = intSum / 10;
    }

    for (int i = digitDiff - 1; i >= 0; i--) {
        intSum = ((num2[i] - '0') + carry);
        result.push_back(intSum % 10 + '0');
        carry = intSum / 10;
    }

    if (carry){
        result.push_back(carry + '0');
    }

    reverse(result.begin(), result.end());
    return stripLeadingZeroes(result);
}

/**
 * @brief string version of base ^ power, int power
 * 
 * @param base STRING base
 * @param power INT power
 * @return string 
 */
string stringPower(string base, int power){
    if (power == 0){
        return "1";
    }
    string result = base;
    for (int i = 1; i < power; i++){
        result = stringMul(result, base);
    }
    return stripLeadingZeroes(result);
}

/**
 * @brief Modulo for string num and integer mod
 * 
 * @param num STRING num
 * @param mod INTEGER modulo
 * @return int n
 */
int intMod(string num, int mod)
{
    int result = 0;
    for (int i = 0; i < num.length(); i++)
        result = (result * 10 + num[i] - '0') % mod;
 
    return result;
}

/**
 * @brief Divide two string numbers. Does not give remainders or fractions. 
 * 
 * @param dividend The dividend you wish to divide from
 * @param divisor The divisor to divide from the dividend
 * @return string quotient
 */
string stringDivide(string dividend, string divisor) {
    string result = "0";
    if (dividend == divisor) return "1";
    if (stringGreaterThan(divisor, dividend)) return "0";

    string currentDividend = dividend.substr(0, divisor.length() - 1);
    dividend = dividend.substr(divisor.length() - 1); 

    while (!dividend.empty()) {
        currentDividend += dividend[0];
        dividend.erase(0, 1);

        currentDividend = stripLeadingZeroes(currentDividend);
        if (currentDividend == "0") {
            result += "0";
            currentDividend = "";
            continue;
        }

        if (stringGreaterThan(divisor, currentDividend)) {
            result += "0";
            continue;
        }

        for (int i = 9; i >= 0; --i) {
            string temp = stringMul(to_string(i), divisor);
            if (!stringGreaterThan(temp, currentDividend)) {
                result += to_string(i);
                currentDividend = stringSubtract(currentDividend, temp);
                break;
            }
        }
    }

    return stripLeadingZeroes(result);
}

/**
 * @brief  num % modulo for string num and string mod
 * 
 * @param num 
 * @param mod modulo
 * @return string num % modulo
 */
string stringMod(string num, string mod){ 
    if (stringGreaterThan(mod, num)) return num;
    if (num == mod) return 0;
    //a - (b * int(a/b))
    string div = stringDivide(num, mod);
    string mul = stringMul(mod, div);
    return stringSubtract(num, mul);
}

/**
 * @brief decimal number stored as string to binary
 * 
 * @param num number stored as string
 * @return string binary
 */
string stringToBinary(string num){
    int i = 0;
    string binary = "";
    while (stringGreaterThan(num, "0")){

        int bit = intMod(num, 2); 
        binary.append(to_string(bit)); 
        num = stringDivide(num, "2");
    }

    reverse(binary.begin(), binary.end());
    return binary;
}

/**
 * @brief binary to number string
 * 
 * @param num binary string
 * @return string number
 */
string binaryToString(string num){
    string result = "0";
    for (int j = num.length() - 1; j > 0; j--){ 
        if (num[j] == '1'){
            result = stringAdd(result, stringPower("2", num.length() - j - 1));
        }
    }
    return stripLeadingZeroes(result);
}

/**
 * @brief string equivalent to built in >> 1 operator. Shifts bits one to the right
 * 
 * @param num The number you wish to bit shift
 * @return string number in decimal after the bit shift
 */
string stringBitShiftRight(string num){
    if (num == "1") return "0";

    string binary = stringToBinary(num);


    for (int i = binary.length(); i >= 0; i--){
        binary[i + 1] = binary[i]; 
    }
    binary[0] = '0';
    
    return binaryToString(binary);
}

/**
 * @brief (x^y) % m for strings. (modular exponentiation)
 * 
 * @param base The desired base
 * @param power The exponent
 * @param mod modulo
 * @return string (x^y) % m
 */
string stringPowerMod(string base, string power, string mod){ 
    string result = "1";
    if (base == "0") return 0;

    base = stringMod(base, mod);

    while (stringGreaterThan(power, "0")){

        if (power.back() % 2 == 1){
            result = stringMod(stringMul(result, base), mod);  
            
        }
        base = stringMod(stringMul(base, base), mod); 
        power = stringBitShiftRight(power);
    }
    return stripLeadingZeroes(result);
}











