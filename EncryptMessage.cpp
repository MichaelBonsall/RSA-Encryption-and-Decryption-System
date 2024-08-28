#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <random>
#include "RSA.cpp"

//MUST BE A MULTIPLE OF 3. HIGHER IS BETTER FOR LONGER VALUES
static const int BLOCKSIZE = 9;


string encryptMessage(string message, string encryptionKey, string modulus){
    string ascii = "";
    string cipherText = "";
    int i = 0;

    for (i = 0; i < message.length(); i++){
        string character = to_string((int)message[i]);
        if (character.length() < 3) character = "0" + character;
        ascii += character;
    }

    for (i = 0; i <= ascii.length() - BLOCKSIZE; i += BLOCKSIZE){
        string partition = ascii.substr(i, BLOCKSIZE);
        //cout << partition << " ";
        cipherText += RSAEncryption(encryptionKey, modulus, partition);
        cipherText += " ";
    }

    if (i < ascii.length()){
        string remaining = ascii.substr(i);
        cipherText += RSAEncryption(encryptionKey, modulus, remaining);
        //cout<<remaining<<endl;
    }
    return cipherText;
}

//d 9595502799659191645956353566665847089
//n 23503530684005996531166929758775217061
int main(){
    //cout<<RSAEncryption("65537", "23503530684005996531166929758775217061", "7210110810811133")<<endl;
    //cout<<RSADecryption("9112779443813110842972144341729453505", "9595502799659191645956353566665847089", "23503530684005996531166929758775217061");
    cout<<encryptMessage("Hello! This is a message", "65537", "23503530684005996531166929758775217061")<<endl;
    
}