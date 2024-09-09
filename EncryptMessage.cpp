#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <random>
#include "RSA.cpp"

//MUST BE A MULTIPLE OF 3. HIGHER IS BETTER FOR LONGER MESSAGES
static const int BLOCKSIZE = 9;

/**
 * @brief Encrypts a message in blocks. Blocks are from size BLOCKSIZE. 
 * BLOCKSIZE must be a multiple of 3. Higher values are better for longer messages. 
 * 
 * @param message The message you want to encrypt
 * @param encryptionKey The encryption key given by the receiver of the message. 
 * @param modulus The modulus given by the receiver of the message.
 * 
 * @return The encrypted message, or ciphertext. 
 */
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
        cipherText += RSAEncryption(encryptionKey, modulus, partition);
        cipherText += " ";
    }

    if (i < ascii.length()){
        string remaining = ascii.substr(i);
        cipherText += RSAEncryption(encryptionKey, modulus, remaining);

    }
    return cipherText;
}

