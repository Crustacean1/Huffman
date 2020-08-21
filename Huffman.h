#ifndef HUFFMAN
#define HUFFMAN

#include <iostream>
#include <cstring>
#include <vector>
#include "HTree.h"

std::vector<HTree *> mergeSort(std::vector<HTree *> tosort);

class Huffman
{
    unsigned int frequencies[256];
    std::string * source;

    public:

    Huffman(std::string * _source) : source(_source)
    {
        memset(frequencies,0,256*sizeof(unsigned int));
        for(char a : *_source)
        {
            frequencies[(unsigned char)a]++;
        }
    }

    std::string compress();
    float getEntropy();

    void debug()
    {
        for(int i = 0;i<256;i++)
        {
            std::cout<<(char)i<<"\t"<<frequencies[i]<<std::endl;
        }
    }
};

#endif /*HUFFMAN*/