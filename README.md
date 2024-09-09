# RSA-Key-Generator
Choose an encryption key, and generate a random decryption key for use in the RSA algorithm. 

To run, run change e on line 10 to another prime number if desired, and run RSA.cpp. Expected output below
![image](https://github.com/MichaelBonsall/RSA-Key-Generator/assets/104641118/60739140-9945-47a3-ac97-5065518ac1fd)


# Encrpyt and Decrypt Messages

Generate keys from RSAKeyGenerator() as described above. Then, create a message and use encryptMessage() and decryptMessage() as described by the documentation.
![image](https://github.com/user-attachments/assets/1971401f-cdbb-4cad-99e1-b8f60ed3959e)

![image](https://github.com/user-attachments/assets/f48de0eb-98ed-4c5a-9c03-8821da7ecb2a)

The encryption is done in blocks. To change the size, change BLOCKSIZE in EncrpytMessage.cpp.
It must be a multiple of 3. A higher block size will be more secure, but it will have preformance losses. 
