#ifndef HUFFMAN
#define HUFFMAN

#include <iostream>
#include <cstring>
#include <math.h>
#include "HTree.h"

void debugString(std::string data);

class Huffman
{
    unsigned int frequencies[256];
    std::string *source;

    unsigned long int sum = 0;
    float entropyPerChar = 0;

    Code * codes;
    HTree *tree;

    HTree * createTree();
    void createCodes();
    
    bool verbose = false;

public:
    Huffman(std::string *_source,bool compress = true) : source(_source)
    {
        if(!compress)
        {
            return;
        }
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
    Huffman(){}

    std::string compress();
    std::string decompress();
    
    float getEntropy();
    float getEntropyPerChar() { return entropyPerChar; }

    void debug()
    {
        for (int i = 0; i < 256; i++)
        {
            std::cout << (char)i << "\t" << frequencies[i] << std::endl;
        }
    }

    std::string serialize();
    HTree* load(std::string &data);
};

#endif /*HUFFMAN*/