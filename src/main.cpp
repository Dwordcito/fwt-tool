#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <map>

std::vector<std::string> split(const std::string& s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if (from.empty())
        return;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

std::map<std::string, std::vector<std::string>> loadData(const std::string& filename)
{
    std::map<std::string, std::vector<std::string>> file;
    std::ifstream fileStream(filename);
    std::string line;
    while (std::getline(fileStream, line))
    {
        replaceAll(line, " ", "");
        std::vector<std::string> tokens = split(line, ':');
        std::vector<std::string> subTokens = split(tokens.at(1), ',');
        file[tokens.at(0)] = subTokens;
    }
    return file;
}


void printResultValues(const std::string &filePath1, const std::string &filePath2)
{
    // Load data
    const auto file1 = loadData(filePath1);
    const auto file2 = loadData(filePath2);

    // Check intersection of values
    for (const auto& [key, value] : file1)
    {
        if (file2.find(key) != file2.end())
        {
            std::vector<std::string> intersection;
            std::set_intersection(value.begin(), value.end(), file2.at(key).begin(), file2.at(key).end(), std::back_inserter(intersection));
            if (!intersection.empty())
            {
                std::cout << key << ": ";
                for (const auto& item : intersection)
                {
                    std::cout << item << " ";
                }
                std::cout << std::endl;
            }
        }
    }
}

int main(int argc, char** argv)
{
    // Argument parsing
    if (argc != 3 || (argc > 1 && std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help"))
    {
        std::cout << "Usage: " << argv[0] << " <file1> <file2>" << std::endl;
        std::cout << "Repetidas -> Me faltan == Me faltan -> Repetidas" << std::endl;
        return 1;
    }

    printResultValues(argv[1], argv[2]);

    return 0;
}
