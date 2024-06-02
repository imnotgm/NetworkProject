#include "utils.h"

int countSubstr(const std::string& str, const std::string& sub)
{
    if(sub.empty())
    {
        return 0;
    }

    int cnt = 0;
    for(size_t offset = str.find(sub); offset != std::string::npos; offset = str.find(sub, offset + sub.length()))
    {
        cnt++;
    }
    return cnt;
}