#include "Huffman.h"
#include <vector>
#include "HTree.h"

std::vector<HTree *> *merge(std::vector<HTree *> *a, std::vector<HTree *> *b)
{
    std::vector<HTree *> *c = new std::vector<HTree *>();

    auto ita = a->begin();
    auto itb = b->begin();

    for (; ita != a->end() && itb != b->end();)
    {
        if (itb != b->end() && (*ita)->getFrequency() > (*itb)->getFrequency())
        {
            (*c).push_back(*(itb++));
            continue;
        }
        (*c).push_back(*(ita++));
    }

    for (; ita != a->end();)
    {
        (*c).push_back(*(ita++));
    }
    for (; itb != b->end();)
    {
        (*c).push_back(*(itb++));
    }

    delete a;
    delete b;

    return c;
}

std::vector<HTree *> *mergeSort(std::vector<HTree *> *tosort)
{
    if (tosort->size() == 1)
    {
        return tosort;
    }
    return merge(mergeSort(new std::vector<HTree *>(tosort->begin(), tosort->begin() + tosort->size() / 2)),
                 mergeSort(new std::vector<HTree *>(tosort->begin() + tosort->size() / 2, tosort->end())));
}

void vectorInsert(std::vector<HTree *> *vec, HTree **el)
{
    auto it = vec->begin();
    for (; it != vec->end(); it++)
    {
        if ((*el)->getFrequency() < (*it)->getFrequency())
        {
            break;
        }
    }
    vec->insert(it, *el);
}

float Huffman::getEntropy()
{
    return entropyPerChar * sum;
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
    letters = *mergeSort(&letters);
    for (auto i : letters)
    {
        std::cout << i->getChar() << "\t" << i->getFrequency() << std::endl;
    }
    std::cout<<"break;"<<std::endl;
    while (letters.size() != 1)
    {
        HTree *ptr = new HTree(letters[0], letters[1]);
        letters.erase(letters.begin());
        letters.erase(letters.begin());

        vectorInsert(&letters, &ptr);
        /*for (auto i : letters)
        {
            std::cout << (int)i->getChar() << "\t" << i->getFrequency() << std::endl;
        }
        break;*/
    }
    Code * codes = new Code[256];
    letters[0]->setCodes(codes);
    for(int i = 0;i<256;i++)
    {
        std::cout<<(char)i<<"\t"<<i<<"\t"<<codes[i].length<<std::endl;
    }
}