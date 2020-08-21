#include "Huffman.h"
#include "HTree.h"
#include <vector>

std::string Huffman::compress()
{
    std::vector<HTree*> letters;
    for(int i = 0;i<256;i++)
    {
        if(frequencies[i]!=0)
        {
            letters.push_back(new HTree((unsigned char)i,frequencies[i]));
        }
    }

}