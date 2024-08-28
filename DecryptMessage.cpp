#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include "RSA.cpp"


static const string cipherText = "22573068466540092756306013238544216912 10321392066240359832073445998216514622 4566514889366191369752423369763713611 4450519335398492259715717342376536982 4450519335398492259715717342376536982 15054423825242970548392889601717131632 22397307351322846527199535759111205228 18109120169981032842842605665273815525" ;
static const string decryptionKey = "9595502799659191645956353566665847089";
static const string modulo = "23503530684005996531166929758775217061";

string removeSpaces(const string& input) {
    std::string result;
    for (char c : input) {
        if (!std::isspace(c)) {
            result += c;
        }
    }
    return result;
}


string decryptMessage(string cipherText, string modulo, string decryptionKey){
    string ascii = "";
    string message = "";
    vector<string> blocks;
    stringstream ss(cipherText);
    string block;

    while (ss >> block) {
        blocks.push_back(block);
    }

    for (const auto& block : blocks) {
        string messageBlock = RSADecryption(decryptionKey, modulo, block);
        /*
        Since leading zeroes are stripped in string math, sometimes they needed to be added back to convert back to ASCII properly.

        126 is the highest ASCII code that can be used, so anything higher must be another character thats missing a 0.  
        */
        if (stoi(messageBlock.substr(0, 3)) > 126 ) messageBlock = "0" + messageBlock; 
        ascii = ascii + messageBlock + " ";
        
    }
    
    //cout<<ascii<<endl;
    ascii = removeSpaces(ascii);
    for (int i = 0; i < ascii.length(); i += 3) {  // Assuming ASCII values are 3 digits long
        string asciiValue = ascii.substr(i, 3);
        message += (char)stoi(asciiValue);
    }
    
    return message;
}

int main(){

    cout<<decryptMessage(cipherText, modulo,  decryptionKey);
}
