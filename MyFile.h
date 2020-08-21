#ifndef MYFILE
#define MYFILE

#include <iostream>
#include <fstream>
#include <sstream>

class MyFile
{
    std::string path;
    std::string getLocalPath();

    public:
    MyFile(std::string _path);

    std::string read();
    void write(std::string _content,bool override=false);
};

#endif /*MYFILE*/