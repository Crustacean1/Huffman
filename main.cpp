#include <iostream>
#include "Parser.h"
#include "Huffman.h"
#include "MyFile.h"
#include "HTree.h"

void Compress(std::unordered_map<std::string,std::string> args)
{
    if(args["-input"]==""){throw "Input path required";}
    if(args["-output"]==""){throw "Output path required";}

    MyFile input(args["-input"]);
    std::string inp = input.read();
    
    Huffman huf(&inp);
}
void Decompress(std::unordered_map<std::string,std::string> args)
{
    if(args["-input"]==""){throw "Input path required";}
    if(args["-output"]==""){throw "Output path required";}
}

int main(int argc,char ** argv)
{
    std::unordered_map<std::string, void (*)(std::unordered_map<std::string,std::string>)> commands;
    commands["compress"] = Compress;
    commands["decompress"] = Decompress;

    std::vector<HTree*> test;
    test.push_back(new HTree('a',2));
    test.push_back(new HTree('a',23));
    test.push_back(new HTree('a',111));
    test.push_back(new HTree('a',13));
    test.push_back(new HTree('a',17));
    test.push_back(new HTree('a',0));

    for(auto t:test)
    {
        std::cout<<t->getFrequency()<<std::endl;
    }
    std::cout<<"after sort: "<<std::endl;

    auto result = mergeSort(test);
    for(auto t:result)
    {
        std::cout<<t->getFrequency()<<std::endl;
    }

    try{
    Parser parser;
    parser.parse(argc,argv);
    parser.execute(commands);
    }
    catch (const char *msg)
    {
        std::cout << "Invalid syntax: " << msg << std::endl;
    }
    return 0;
}