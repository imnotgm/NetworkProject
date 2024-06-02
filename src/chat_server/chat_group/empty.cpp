#include "./ChatGroup.h"

// std::map<std::string, User> members;

bool ChatGroup::empty()
{
    if(members.empty())
        return true;
    return false;
}