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
        HASH_INDEX_T w[5] = {0};
        int idxSize = k.size(); //num characters
        int wIdx = 4; //Fills from the right

        //Group into chunks
        while (idxSize > 0 && wIdx >= 0) {
            HASH_INDEX_T chunkIdx = 0;
            HASH_INDEX_T modifier = 1;
            for (int j = 0; (j < 6) && (idxSize > 0); j++) {
                char currChar = std::tolower(k[--idxSize]);

                HASH_INDEX_T idx;
                if (std::isdigit(currChar) == true) {
                    idx = currChar - '0' + 26;
                }
                else {
                    idx = letterDigitToNumber(currChar);
                }
                chunkIdx += idx * modifier;
                modifier = modifier * 36;
            }
            w[wIdx] = chunkIdx;
            wIdx--;
        }
        HASH_INDEX_T out = 0;
        for (int i = 0; i < 5; i++) {
            out += rValues[i] * w[i];
            //std::cout << "w[" << i << "] = " << w[i] << std::endl;
        }
        return out;
        /*HASH_INDEX_T out = 0;
        for (size_t i = 0; i < k.size(); i++) {
            HASH_INDEX_T idx = -1;
            if (std::isdigit(k[i]) == true) {
                idx = k[i] - '0';
                idx = idx + 26;
            }
            else {
                idx = letterDigitToNumber(k[i]);
            }

        }*/

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if (std::isalpha(letter)) {
            letter = std::tolower(letter); //Returns lowercase version of capital
            return letter - 'a';
        }
        else {
            return letter;
        }
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
