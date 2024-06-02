#include "./ChatGroup.h"

bool ChatGroup::isMember(const std::string &id)
{
    if(members.find(id) == members.end())
        return false;
    return true;
}