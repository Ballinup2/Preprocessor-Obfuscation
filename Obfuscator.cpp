#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

#define ERROR   "[-] :"
#define OK      "[*] :"
#define GOOD    "[+] :"

const std::vector<char> allowedCharacters = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '_', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};


char* to_lower(char* c) {
    for (size_t i = 0; i < strlen(c); i++) {
        if(c[i] >= 65 && c[i] <= 90) {
            c[i] += 32;
        }
    }
    return c;
}

int main(int argc, char* argv[]) {
    if(argc != 1) {
        bool isVerbose = false;
        if(!strcmp(to_lower(argv[1]), "-help")) {
            std::cout << "- How to Use -\n Obfuscator.cpp is a program designed to find #define preprocessors used to function name obfuscation\n and change the value stored in them, IT CHANGES ALL IN THE FILE\n\n - Commands -\n -help : Shows the help menu \n -verbose : shows a more diverse log of what the program is doing\n\n ./Obfuscator <filepath> <verbosity>\n <filepath> is the command to be replaced by the -help command\n";
            return EXIT_SUCCESS;
        }
        if (argc > 2)
        {
            if (!strcmp(to_lower(argv[2]), "-verbose"))
            {
                isVerbose = true;
            }
        }
        std::fstream file(argv[1]);
        if(file.is_open() && file) {
            printf("%s Opened File: %s\n", GOOD, argv[1]);
            int symbolsPatched = 0;
            std::string fileContents;
            srand(std::time(nullptr));
            for (std::string line; std::getline(file, line);)
            {
                if (size_t at = line.find("#define"); at != line.npos)
                {
                    size_t endofdefine = line.find_first_of(' ') + 1;
                    size_t endofsymbol = line.find_first_of(" ", endofdefine, 1);
                    size_t endofwhitespace = line.find_first_not_of(' ', endofsymbol);

                    std::string substr = line.substr(endofdefine, endofsymbol - endofdefine);
                    std::string obfuscationString = line.substr(endofwhitespace);

                    for (size_t i = 0; i < obfuscationString.size(); i++) {
                        obfuscationString[i] = allowedCharacters[rand() % (i != 0 ? allowedCharacters.size() : allowedCharacters.size() - 10)];
                    }

                    line.erase(endofwhitespace, line.npos);
                    line.append(obfuscationString);

                    fileContents += line + '\n';

                    if (isVerbose)
                    {
                        printf("%s Found Symbol: %s\n", OK, substr.c_str());
                        printf("%s Patched %s\n", OK, substr.c_str());
                    }
                    symbolsPatched++;
                } else {
                    fileContents += line + '\n';
                }
            }
            file.clear();
            file.seekp(0);
            file << fileContents.c_str();

            printf("%s Patched %d symbols\n", GOOD, symbolsPatched);
            printf("%s Fully Parsed %s\n", GOOD, argv[1]);
            return EXIT_SUCCESS;
        }
        printf("%s Failed To Open File: %s\n", ERROR, argv[1]);
        return EXIT_SUCCESS;
    }
    printf("%s Invalid Arguments!\n", ERROR);
    return EXIT_SUCCESS;
}