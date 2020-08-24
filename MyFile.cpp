#include "MyFile.h"

MyFile::MyFile(std::string _path)
{
    path = _path;
}
std::string MyFile::read()
{
    std::string content;

    std::ifstream file(path, std::ios::binary);
    if(!file.is_open()){throw ("Unable to open file");}
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}
void MyFile::write(std::string _content, bool override)
{
    std::ofstream file;
    if (override)
    {
        file.open(path, std::ios::binary);
    }
    else
    {
        file.open(path, std::ios::app | std::ios::binary);
    }
    if(!file.is_open()){throw "Unable to open file: "+path;}
    file << _content;
}