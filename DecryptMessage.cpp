#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include "RSA.cpp"


/**
 * @brief Removes spaces from input string
 * 
 * @param input The string you want to remove spaces from
 * @return string with no spaces
 */
string removeSpaces(const string& input) {
    std::string result;
    for (char c : input) {
        if (!std::isspace(c)) {
            result += c;
        }
    }
    return result;
}

/**
 * @brief Decrypt an encrypted message. Give the other party the encryption key and the modulus. No need to worry about BLOCKSIZE since the spaces are the blocks.  
 * 
 * @param cipherText The ciphertext you want to decrypt
 * @param modulo The modulo given by RSAKeyGenerator()
 * @param decryptionKey  The decryption key given by RSAKeyGenerator()
 * @return The decrypted message
 */
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

        126 is the highest ASCII code that is a normal character, so anything higher must be another character thats missing a 0. Thus, we add it back
        */
        if (stoi(messageBlock.substr(0, 3)) > 126 ) messageBlock = "0" + messageBlock; 
        ascii = ascii + messageBlock + " ";
        
    }
    

    ascii = removeSpaces(ascii);
    for (int i = 0; i < ascii.length(); i += 3) {  // Assuming ASCII values are 3 digits long, which they should be thanks to step above
        string asciiValue = ascii.substr(i, 3);
        message += (char)stoi(asciiValue);
    }
    
    return message;
}


