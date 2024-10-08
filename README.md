# RSA-Key-Generator
Choose an encryption key, and generate a random decryption key for use in the RSA algorithm. 

To run, run RSA.cpp. If you would like to change your public key, change e to any number greater than 3. Expected output below
![image](https://github.com/MichaelBonsall/RSA-Key-Generator/assets/104641118/60739140-9945-47a3-ac97-5065518ac1fd)


# Encrpyt and Decrypt Messages

Generate keys from RSAKeyGenerator() as described above. Then, create a message and use encryptMessage() and decryptMessage() as described by the documentation.
![image](https://github.com/user-attachments/assets/1971401f-cdbb-4cad-99e1-b8f60ed3959e)

![image](https://github.com/user-attachments/assets/f48de0eb-98ed-4c5a-9c03-8821da7ecb2a)

This is done using a block cipher. To change the size of each block, change BLOCKSIZE in EncrpytMessage.cpp.
It must be a multiple of 3. A higher block size will be more secure, but it will have preformance losses.


In RandomPrimeGenerator.cpp, there are two static ints you can change if you want.
MillerRabinChecks is the number of times the Miller-Rabin primality test is ran. The more iterations, the more likely the number is to be prime, but the default of 20 should suffice (9.09494701×10−13 chance of false prime). 

THREAD_COUNT is the number of threads you wish to compute the RSA keys with. If you want to use all the threads on your machine, use thread::hardware_concurrency() (c++ 11+) to find the number of threads you have. 
