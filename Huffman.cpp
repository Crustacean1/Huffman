#include "Huffman.h"
#include "HTree.h"
#include <vector>

std::vector<HTree *> &merge(std::vector<HTree *> &_a, std::vector<HTree *>& _b)
{
    std::vector<HTree*> & a = (_a.size()>_b.size())?_a:_b;//bigger
    std::vector<HTree*> & b = (_a.size()>_b.size())?_b:_a;//smaller
    std::vector<HTree *> c;

    auto ita = a.begin();
    auto itb = b.begin();

    for (;ita!=a.end();)
    {
        if (itb!=b.end()&&*ita > *itb)
        {
            c.push_back(*(itb++));
            continue;
        }
        c.push_back(*(ita++));
    }
    for(;ita!=a.end();)
    {
        c.push_back(*(ita++));
    }
    return c;
}

std::vector<HTree *> & mergeSort(std::vector<HTree *> &tosort)
{
    if (tosort.size() == 1)
    {
        return tosort;
    }
    return merge(mergeSort(std::vector<HTree*>(tosort.begin(),tosort.begin()+tosort.size()/2)),
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