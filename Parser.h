#ifndef PARSER
#define PARSER

#include <iostream>
#include <vector>
#include <unordered_map>

class Parser
{
    std::string command ="";
    std::unordered_map<std::string,std::string> options;

    public:

    void parse(int argc,char ** argv);
    
    void execute(std::unordered_map<std::string,void(*)(std::unordered_map<std::string,std::string>)> fmap);
    void debug();

};

#endif /*PARSER*/