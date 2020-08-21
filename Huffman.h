#ifndef HUFFMAN
#define HUFFMAN

#include <iostream>
#include <cstring>
#include <math.h>

class Huffman
{
    unsigned int frequencies[256];
    std::string *source;

    unsigned long int sum = 0;
    float entropyPerChar = 0;

public:
    Huffman(std::string *_source) : source(_source)
    {
        memset(frequencies, 0, 256 * sizeof(unsigned int));
        for (auto a : *_source)
        {
            frequencies[(unsigned char)a]++;
            sum++;
        }
        float entropy = 0;

        for (auto i : frequencies)
        {
            if (i == 0)
            {
                continue;
            }
            entropy += ((double)i / (double)sum) * log2((double)i / (double)sum);
        }
        entropyPerChar = -entropy;
    }

    std::string compress();
    float getEntropy();
    float getEntropyPerChar() { return entropyPerChar; }

    void debug()
    {
        for (int i = 0; i < 256; i++)
        {
            std::cout << (char)i << "\t" << frequencies[i] << std::endl;
        }
    }
};

#endif /*HUFFMAN*/