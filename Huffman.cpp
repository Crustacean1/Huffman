#include "Huffman.h"

void debugString(std::string data)
{
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < 8; j++)
        {
            std::cout << ((data[i] >> j) & 1);
        }
        std::cout << " ";
    }
}

std::string serializeSize(unsigned long long int size)
{
    std::string res;
    for (int i = sizeof(unsigned long long int) - 1; i >= 0; i--)
    {
        //std::cout<<"serialization: "<<(int)((size>>i*8)&255)<<std::endl;
        res += (char)((size >> i * 8) & 255);
    }
    return res;
}

unsigned long long int deserializeSize(std::string data)
{
    unsigned long long int sizey = 0;
    for (int i = 0; i < sizeof(unsigned long long int); i++)
    {
        //std::cout<<"sizey: "<<(int)data[i]<<std::endl;
        sizey = sizey << 8;
        sizey += (unsigned char)data[i];
    }
    return sizey;
}

float Huffman::getEntropy()
{
    return entropyPerChar * sum;
}

HTree *Huffman::createTree()
{
    return new HTree(frequencies, 256);
}

void Huffman::createCodes()
{
    HTree *test = createTree();
    std::string temp = test->serialize();
    //std::cout<<"serialized: "<<temp.size()<<std::endl;
    //tree = test;

    tree = new HTree((unsigned char)0, (unsigned long)0);
    //std::cout<<"???"<<std::endl;
    tree->construct(temp);
    //std::cout<<"constructed, coding"<<std::endl;
    codes = new Code[256];
    memset(codes, 0, sizeof(Code) * 256);
    tree->setCodes(codes);
}

std::string Huffman::compress()
{
    createCodes();
    for (int i = 0; i < 256; i++)
    {
        std::cout << (char)i << "\t" << i << "\t" << codes[i].length << "\t";
        for (int j = 0; j < codes[i].length; j++)
        {
            std::cout << ((codes[i].code >> j) & (unsigned int)1);
        }
        std::cout << std::endl;
    }
    std::string res;
    unsigned long int t = 0;

    int length = 0;

    for (int i = 0; i < source->size();)
    {
        for (; length < 9; i++)
        {
            if (!(i < source->size()))
            {
                res += (char)(t & ((unsigned int)pow(2, length) - 1));
                break;
            }
            t += codes[(unsigned char)(*source)[i]].code * pow(2, length);
            length += codes[(unsigned char)(*source)[i]].length;
        }
        res += (unsigned char)(t & 255);
        t = t >> 8;
        length -= 8;
    }

    std::string htree = tree->serialize();
    std::string tSize;
    std::string sSize;

    tSize = serializeSize(htree.size());
    sSize = serializeSize(source->size());

    std::cout << "compressed tree size: " << deserializeSize(tSize) << std::endl;
    std::cout << "pre-compressed text size: " << deserializeSize(sSize) << std::endl;
    std::cout << "compressed to: " << res.size() << std::endl;

    return tSize + htree + sSize + res;
}
///////////////////////////////////////////////////////////////////////////////////
std::string Huffman::decompress()
{
    //std::cout<<"general size: "<<source->size()<<std::endl;
    unsigned long long int tSize, sSize;

    tSize = deserializeSize(*source);
    sSize = deserializeSize(source->substr(8 + tSize, 8));

    tree = new HTree((unsigned char)0, (unsigned int)0);

    std::string treeSource = source->substr(8, tSize);
    tree->construct(treeSource);

    codes = new Code[256];
    memset(codes, 0, sizeof(Code) * 256);

    tree->setCodes(codes);
    if (verbose)
    {
        for (int i = 0; i < 256; i++)
        {
            std::cout << (char)i << "\t" << i << "\t" << codes[i].length << "\t";
            for (int j = 0; j < codes[i].length; j++)
            {
                std::cout << ((codes[i].code >> j) & (unsigned int)1);
            }
            std::cout << std::endl;
        }
    }

    unsigned int pos = 0;
    std::string data = source->substr(16 + tSize, source->size() - 16 - tSize);
    std::string res;

    for (unsigned long long int i = 0; i < sSize; i++)
    {
        res += tree->getCode(data, pos);
    }

    return res;
}