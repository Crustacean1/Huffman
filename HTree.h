#ifndef HTREE
#define HTREE

#include <string>
#include <iostream>

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
    HTree(unsigned char _me, unsigned int _freq) : frequency(_freq), me(_me) {}
    HTree(unsigned int * _freq, int _size){construct(_freq,_size);}

    void construct(unsigned int * frequency, int size);
    int construct(std::string &data,int pos = 0);
    std::string serialize();

    unsigned int getFrequency(){return frequency;}
    char getChar(){return (char)me;}

    void setCodes(Code *codes, unsigned long code = 0, unsigned short depth = 0);
    unsigned char getCode(std::string & data,unsigned int & pos);
    void Debug()
    {
        if(children[0]!=nullptr)
        {
            children[0]->Debug();
        }
        std::cout<<" "<<(char)me<<" ";
        if(children[1]!=nullptr)
        {
            children[1]->Debug();
        }
    }
};
#endif /*HTREE*/