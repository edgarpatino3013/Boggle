#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
				//size 5
        unsigned long long w[5] = {0,0,0,0,0};
        std::string copy = k;

        for (int i = 4; i >= 0; i--){
            for (int j = copy.size() - 1; j >= 0; j--){
                if (j < 6 && j < copy.size()){
                    w[i] += pow(36, j)*letterDigitToNumber(copy[abs(j - copy.size() + 1)]);
                }
            }

            for (int i = 0; i < 6; i++){
                if (copy.size() != 0){
                    copy.pop_back();
                }
            }
        }

        HASH_INDEX_T func = 0;

        for (int i = 0; i < 5; i++){
            func += w[i] * rValues[i];
        }
        
        return func;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        
        //ensure letter is lowercase
        if (letter >= 'A' && letter <= 'Z'){
            letter = tolower(letter);
        }
        
        //if number 0-9
        if (letter >= '0' && letter <= '9'){
            return letter - 22;
        }

        //if lowercase letter
        if (letter >= 'a' && letter <= 'z'){
            return letter - 97;
        }
        
        //else
        return -1;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
