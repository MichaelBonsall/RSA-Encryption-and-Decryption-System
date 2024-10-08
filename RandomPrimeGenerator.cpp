#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <random>
#include "StringMath.cpp"
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <functional>


using namespace std;

//num of times for Miller-Rabin to choose a new a. 20 means chance of composite sneaking through is (1/3)^20 or 1/3486784401
static int MillerRabinChecks = 20;

//num of threads you want to use for computation. 
static int THREAD_COUNT = 4;


/** 
 * @brief Miller-Rabin Test. Probabilistic primality test. About 1/3 chance of random number chosen to be a strong liar, so looping is recommended.
 * A false return means the number is guaranteed a composite, however a true return means the number is LIKELY prime. 
 * 
 * 
 * @param num The number for the Miller-Rabin test to be ran on. 
 * @return True/False
 */
bool millerRabinTest(uint64_t num){
    uint64_t d = num - 1; //d s.t. n = 2^d * r + 1 for some r >=1
        while (d % 2 == 0)
            d /= 2;
    uint64_t a = 2 + rand() % (num - 4); 
    string xs = stringPowerMod(to_string(a), to_string(d), to_string(num));
    uint64_t x = stoull(xs);

    if (x == 1  || x == num - 1)    return true;
    //keep squaring until one of these doesnt happen
    //d not n - 1
    //(x^2 % n not 1
    //(iii) x^2 % n not n - 1
    while (d != num - 1){
            xs = stringPowerMod(xs, "2", to_string(num));
            x = stoull(xs);
            d *= 2;
 
            if (x == 1)      return false; //composite
            if (x == num - 1)    return true;
        }
    return false;
    
}

/**
 * @brief Generates a random odd num between 3 - 64_INT_MAX
 * π(N) ≈ n/lg(n) so 20 digit number means about a 4.62% chance of a prime
 * @return uint64_t A 64bit even num
 */
uint64_t possiblyPrimeNum(){
    random_device rd;
    uniform_int_distribution<uint64_t> randomDist(3, UINT64_MAX - 2); 
    uint64_t result = randomDist(rd);
    if (! (result & 1)){
        result += 1;
    }

    return result;

}


mutex mtx;
condition_variable cv;
atomic<bool> foundPrime(false); 
atomic<uint64_t> resultPrime(0);
/**
 * @brief A helper method for randomPrime() that allows for multi threading. DO NOT USE THIS!! 
 * 
 * @param k DONT USE THIS FUNCTION!!
 * @return uint64_t 
 */
uint64_t static randomPrimeThreadRunner(int k){
    uint64_t num = 0;
    int firstTwentyPrimes[20] = {3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73}; 
    bool prime = false;
    for(int i = 0; i < k; i++){
        do{
            num = possiblyPrimeNum();
            bool initialFail = false;

            for (int j: firstTwentyPrimes){ //Checks first couple primes before Miller Rabin for efficiency
                if (num % j == 0){
                    initialFail = true;
                    break;
                }
            }
            if (initialFail == true){
                continue;
            }
            if (!millerRabinTest(num)){
                continue;
            }
            else break;
        }
        while (!prime);
    }
    unique_lock<mutex> lock(mtx);
    cv.notify_all(); //First thread to find a solution tells all other threads to give up
    resultPrime = num;
    return 0;
}

/**
 * @brief Generates a random 64 bit prime number from range 3-18,446,744,073,709,551,614
 * Uses the Miller-Rabin test for primality checking. Recommended to run with at least 20 tests.
 * 
 * @param k The desired number of times for the Miller-Rabin test to be run.
 * @return uint64_t A random 64 bit prime
 */
uint64_t static randomPrime(int k){
    vector<thread> threads;
    for (int i = 0; i < THREAD_COUNT; i++){
        threads.push_back(thread(randomPrimeThreadRunner, k));
    }
    for (thread &th : threads) {
        if (th.joinable()) {
            th.join();
        }
    }

    return resultPrime; 
}
