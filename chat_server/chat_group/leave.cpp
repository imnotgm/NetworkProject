#include "./ChatGroup.h"

// std::map<std::string, User> members;

bool ChatGroup::leave(const std::string &id)
{
    if(members.find(id) == members.end())
        return false;

    members.erase(id);
    return true;
}