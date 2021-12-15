#include "HTree.h"
#include <vector>
#include <iostream>
#include <math.h>

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

void vectorInsert(std::vector<HTree *> *vec, HTree **el) //TODO fix to be log(n) instead of n
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

////////////////////////////////////////////////////////////////////////////

void HTree::setCodes(Code *codes, unsigned long code, unsigned short depth)
{
    if (children[0] == nullptr && children[1] == nullptr)
    {
        codes[(unsigned short)me].code = code;
        codes[(unsigned short)me].length = depth;
        return;
    }
    if (children[0] != nullptr)
    {
        children[0]->setCodes(codes, code, depth + 1);
    }
    if (children[1] != nullptr)
    {
        children[1]->setCodes(codes, code + pow(2, depth), depth + 1);
    }
}

void HTree::construct(unsigned int *_frequency, int _size)
{
    std::vector<HTree *> letters;
    for (int i = 0; i < _size; i++)
    {
        if (_frequency[i] != 0)
        {
            letters.push_back(new HTree((unsigned char)i, _frequency[i]));
        }
    }
    letters = *mergeSort(&letters);

    while (letters.size() != 1)
    {
        HTree *ptr = new HTree(letters[0], letters[1]);
        letters.erase(letters.begin());
        letters.erase(letters.begin());
        vectorInsert(&letters, &ptr);
    }
    *this = *letters[0];
}

std::string HTree::serialize()
{
    std::string ret = "";
    if (children[0] == nullptr && children[1] == nullptr)
    {
        ret += (char)1;
        ret += me;
        return ret;
    }
    ret += (char)0;

    return ret + children[0]->serialize() + children[1]->serialize();
}
int HTree::construct(std::string &data, int pos)
{
    if((unsigned int)pos>=data.size()){throw "Size exceeded";}
    
    if (data[pos] == (char)1)
    {
        me = data[pos + 1];
        return pos + 1;
    }
    children[0] = new HTree((unsigned char)0, (unsigned int)0);
    pos = children[0]->construct(data, pos + 1);
    children[1] = new HTree((unsigned char)0, (unsigned int)0);
    pos = children[1]->construct(data, pos + 1);
    return pos;
}
unsigned char HTree::getCode(std::string &data, unsigned int &pos)
{
    if (children[0] == nullptr && children[1] == nullptr)
    {
        return me;
    }
    if ((((unsigned char)data[pos / 8] >> (pos % 8)) & (unsigned char)1) == 0)
    {
        pos++;
        return children[0]->getCode(data, pos);
    }
    pos++;
    return children[1]->getCode(data, pos);
}