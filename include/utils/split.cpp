#include "utils.h"

std::vector<std::string> split(std::string str, std::string delim, const int limit = 2)
{
    std::vector<std::string> tokens;
    size_t start = 0, pos = 0;
    int found = 0;
    int n = limit;

    if(limit == 0)
        n = countSubstr(str, delim);

    while(start < str.length())
    {
        pos = str.find(delim, start);
        if(pos == std::string::npos || found == limit - 1)
            pos = str.length();

        std::string token = str.substr(start, pos - start);

        if(!token.empty())
            tokens.push_back(token);
        start = pos + delim.length();
        found++;
    }
    return tokens;
}
