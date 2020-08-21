#include "Huffman.h"

std::vector<HTree *> * merge(std::vector<HTree *> a, std::vector<HTree *> b)
{
    std::vector<HTree *> * c = new std::vector<HTree*>();

    auto ita = a.begin();
    auto itb = b.begin();
    
    for (;ita!=a.end()&&itb!=b.end();)
    {
        if (itb!=b.end()&& (*ita)->getFrequency() > (*itb)->getFrequency())
        {
            (*c).push_back(*(itb++));
            continue;
        }
        (*c).push_back(*(ita++));
    }

    for(;ita!=a.end();)
    {
        (*c).push_back(*(ita++));
    }
    for(;itb!=b.end();)
    {
        (*c).push_back(*(itb++));
    }

    std::cout<<"after"<<c->size()<<std::endl;
    return c;
}

std::vector<HTree *> mergeSort(std::vector<HTree *> tosort)
{
    if (tosort.size() == 1)
    {
        return tosort;
    }
    return *merge(mergeSort(std::vector<HTree*>(tosort.begin(),tosort.begin()+tosort.size()/2)),
     mergeSort(std::vector<HTree*>(tosort.begin()+tosort.size()/2,tosort.end())));
}

std::string Huffman::compress()
{
    std::vector<HTree *> letters;
    for (int i = 0; i < 256; i++)
    {
        if (frequencies[i] != 0)
        {
            letters.push_back(new HTree((unsigned char)i, frequencies[i]));
        }
    }
}