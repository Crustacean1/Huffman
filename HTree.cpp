#include "HTree.h"

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
        children[0]->setCodes(codes, code << 1, depth + 1);
    }
    if (children[1] != nullptr)
    {
        children[1]->setCodes(codes, (code << 1) + 1, depth + 1);
    }
}