#include "./ChatGroup.h"

// std::map<std::string, User> members;

bool ChatGroup::join(const std::string &id, User &user)
{
    if(members.find(id) == members.end())
    {
        members[id] = user;
        return true;
    }
    return false;
}