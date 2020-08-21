#include "Parser.h"
void Parser::parse(int argc, char **argv)
{
    auto it = command.begin();

    std::string last = "";
    for (unsigned int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            last = argv[i];
            options[last] = "1";
            continue;
        }
        if (last == "")
        {
            if (command != "")
            {
                std::cout << "command:" << command << std::endl;
                throw "Too many commands";
            }
            command = argv[i];
            continue;
        }
        if (options[last] != "1")
        {
            throw "Too many arguments";
        }
        options[last] = argv[i];
    }
}

void Parser::debug()
{
    std::cout << "command: " << command << std::endl;
    for (auto pair : options)
    {
        std::cout << pair.first << "\t" << pair.second << std::endl;
    }
}
void Parser::execute(std::unordered_map<std::string, void (*)(std::unordered_map<std::string, std::string>)> args)
{
    if (args[command] == NULL)
    {
        throw "Invalid command";
    }
    args[command](options);
}