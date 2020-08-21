#ifndef HTREE
#define HTREE

struct Code
{
    unsigned short length;
    unsigned long code;
}; //Throws exception >32

class HTree
{
    unsigned int frequency;
    HTree *children[2] = {nullptr, nullptr};
    unsigned char me;

public:

    HTree(HTree *a, HTree *b)
    {
        children[0] = a;
        children[1] = b;
        frequency = children[0]->frequency + children[1]->frequency;
        me = 0;
    }
    HTree(unsigned char _me, unsigned int _freq) : me(_me), frequency(_freq) {}
    unsigned int getFrequency(){return frequency;}

    void setCodes(Code *codes, unsigned long code = 0, unsigned short depth = 0);
};
#endif /*HTREE*/