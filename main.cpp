#include <iostream>
#include "Parser.h"
#include "Huffman.h"
#include "MyFile.h"
#include "HTree.h"

//Entropy above 7.5 is inefficient

void Compress(std::unordered_map<std::string, std::string> args)
{
    if (args["-input"] == "")
    {
        throw "Input path required";
    }
    if (args["-output"] == "")
    {
        throw "Output path required";
    }

    MyFile input(args["-input"]);
    std::string inp = input.read();

    Huffman huf(&inp);
    huf.setVerbose(args["-v"] == "1");
    std::string comp = huf.compress();
    if (args["-v"] == "1")
    {
        std::cout << "Computed entropy: " << huf.getEntropy() << "\t Entropy per character: " << huf.getEntropyPerChar() << "\t optimization: " << huf.getEntropyPerChar() / 8.f << std::endl;
        std::cout << "before compression: " << inp.size() << std::endl;
        std::cout << "compressed to: " << comp.size() << std::endl;
    }

    MyFile output(args["-output"]);
    output.write(comp, true);
}
void Decompress(std::unordered_map<std::string, std::string> args)
{
    if (args["-input"] == "")
    {
        throw "Input path required";
    }
    if (args["-output"] == "")
    {
        throw "Output path required";
    }

    MyFile input(args["-input"]);
    std::string inp;
    inp = input.read();

    Huffman huf(&inp, false);
    huf.setVerbose(args["-v"] == "1");
    std::string data = huf.decompress();
    MyFile output(args["-output"]);
    output.write(data, true);
}
void Entropy(std::unordered_map<std::string, std::string> args)
{
    if (args["-input"] == "")
    {
        throw "Input path required";
    }

    MyFile input(args["-input"]);
    std::string inp = input.read();

    Huffman huf(&inp);
    std::cout << "Computed entropy: " << huf.getEntropy() << "\t Entropy per character: " << huf.getEntropyPerChar() << "\t optimization: " << huf.getEntropyPerChar() / 8.f << std::endl;
}

void IdentityCheck(std::string _a, std::string _b)
{
    MyFile a(_a);
    MyFile b(_b);

    std::string sa = a.read();
    std::string sb = b.read();
    if (sa.size() != sb.size())
    {
        std::cout << "different sizes" << std::endl;
    }
    for (unsigned int i = 0; i < sa.size(); i++)
    {
        if (sa[i] != sb[i])
        {
            std::cout << (int)(unsigned char)sa[i - 2] << "\t" << (int)(unsigned char)sb[i - 2] << std::endl;
            std::cout << (int)(unsigned char)sa[i - 1] << "\t" << (int)(unsigned char)sb[i - 1] << std::endl;
            std::cout << (int)(unsigned char)sa[i] << "\t" << (int)(unsigned char)sb[i] << std::endl;
            std::cout << "line: " << i << std::endl;
            std::cin.get();
        }
    }
    std::cout << sa.size() << "\t" << sb.size() << std::endl;
}

int main(int argc, char **argv)
{
    //if(argc<3){return -1;}
    //IdentityCheck(argv[1],argv[2]);
    //return 0;
    std::unordered_map<std::string, void (*)(std::unordered_map<std::string, std::string>)> commands;
    commands["compress"] = Compress;
    commands["decompress"] = Decompress;
    commands["entropy"] = Entropy;

    try
    {
        Parser parser;
        parser.parse(argc, argv);
        parser.execute(commands);
    }
    catch (const char *msg)
    {
        std::cout << "Invalid syntax: " << msg << std::endl;
    }
    return 0;
}