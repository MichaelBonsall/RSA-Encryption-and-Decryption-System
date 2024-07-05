#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <tuple>
#include "RandomPrimeGenerator.cpp"

using namespace std;

//CHANGE THIS TO CHANGE ENCRYPTION KEY. MUST BE A PRIME NUMBER
string e = "65537"; //commonly chosen e. short bit length and small hamming weight == efficient encryption (also public key)

/**
 * @brief Regular Euclidean Algorithm
 * 
 * @param a string representation of number
 * @param b string representation of number
 * @return string the common factor between a and b
 */
string stringEuclideanAlgo(string a, string b){
    if (a == b) return a;
    if (stringGreaterThan(b,a)) swap(b,a);
    string remainder = "1";
    while (remainder != "0"){
        string c = stringDivide(a, b);
        remainder = stringSubtract(a, stringMul(b, c));

        if (remainder == "0"){return b;}

        a = b;
        b = remainder;
        
    }
    return b;
}

/**
 * @brief struct used in modularMultiplicativeInverse to simulate negative numbers
 * 
 */
typedef struct tag_stringAndSign{
    string value;
    bool isNegative;
}   stringAndSign;


/**
 * @brief Finds the modular multiplicative inverse of a mod b using enhanced euclidean algorithm since a and b are co-prime
 * 
 * @param a num
 * @param b modulo
 * @return string x such that ax = 1 mod b
 */
string modularMultiplicativeInverse(string a, string b){ 

    if (b == "0") throw invalid_argument("No modular multiplicative inverse exists since b = 0"); //these errors shouldnt throw unless another method messes up

    string b0 = b;
    tag_stringAndSign x0 = { "0", false }; // b = 1*b + 0*a
    tag_stringAndSign x1 = { "1", false }; // a = 0*b + 1*a

    while (stringGreaterThan(a, "1")){
        if (b == "0") // means original A and B were not co-prime so there is no answer
            throw invalid_argument("No modular multiplicative inverse exists because a and b are not co-prime");
        string q = stringDivide(a, b);
        string t = b; b = stringMod(a, b); a = t;
        
        tag_stringAndSign t2 = x0;
        string qx0 = stringMul(q, x0.value);
        if (x0.isNegative != x1.isNegative)
        {
            x0.value = stringAdd(x1.value, qx0);
            x0.isNegative = x1.isNegative;
        }
        else
        {
            x0.value = (stringGreaterThan(x1.value, qx0)) ? stringSubtract(x1.value, qx0) : stringSubtract(qx0, x1.value);
            x0.isNegative = (stringGreaterThan(x1.value, qx0)) ? x1.isNegative: !x0.isNegative;
        }
        x1 = t2;
    }

    return x1.isNegative ? (stringSubtract(b0, x1.value)) : x1.value;
}

/**
 * @brief Euler totient function for strings. Sometimes results in d > lambdaN which is larger (and thus slower) than necessary, but still works
 * 
 * @param p First prime p
 * @param q Second prime q
 * @return string phi(n)
 */
string stringEulerTotientFunction(string p, string q){
    return stringMul(stringSubtract(p, "1"), stringSubtract(q, "1"));
}

/**
 * @brief Generates RSA keys. Returns a tuple of key strings. e = encryption key, n = modulus / key length , d = decryption key. 
 * e and n should be public, and d should remain private.
 * 
 * @return tuple <string, string, string>  <encryption key, modulus, decryption key>
 */
tuple <string, string, string> RSAKeyGenerator(){ 
    string p = to_string(randomPrime(MillerRabinChecks));
    string q = to_string(randomPrime(MillerRabinChecks));
    string n = stringMul(p, q);

    string phiN = stringEulerTotientFunction(p, q); //secret
    string d = modularMultiplicativeInverse(e, phiN); //private key
    return tuple<string, string, string>(e, n, d);
}


/**
 * @brief Encrypts message M using keys generated by RSAKeyGenerator(). 
 * 
 * c = m^e mod n
 * 
 * @param e The encryption key
 * @param n The modulus from RSAKeyGenerator()
 * @param m The message represented as a number to be encrypted
 * @return Ciphertext
 */
string RSAEncryption(string e, string n, string m){ 
    return stringPowerMod(m, e, n);
}

/**
 * @brief Decrypts ciphertext C using keys generated by RSAKeyGenerator().
 * 
 * m = c^d mod n
 * 
 * @param d The decryption key
 * @param n The modulus from RSAKeyGenerator()
 * @param c The ciphertext from RSAEncryption() to be decrypted
 * @return The original plaintext
 */
string RSADecryption(string c, string d, string n){
    return stringPowerMod(c, d, n);
}


int main(){
    tuple<string, string, string> a = RSAKeyGenerator(); 
    
    string e, n, d;
    tie(e, n, d) = a;
    cout<<"encryption key e: "<<e<<" modulus n: "<<n<<" decryption key d: "<<d<<"\n";
    string m = "69";
    string c = RSAEncryption(e, n, m);
    cout<<"message: "<<m<<"\n";
    cout<<"cipher text: "<<c<<"\n";
    string m2 = RSADecryption(c, d, n);
    cout<<"decrypted message: "<<m2;
}



