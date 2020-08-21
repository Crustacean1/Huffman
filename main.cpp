#include <iostream>
#include "Parser.h"
#include "Huffman.h"
#include "MyFile.h"

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