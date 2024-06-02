#include "./ChatGroup.h"

ChatGroup::ChatGroup(std::string name, std::string id, User user) : name(name)
{
    members[id] = user;

    // TODO: 비동기식으로 초대 수락/거절 기능 구현
}

ChatGroup::~ChatGroup()
{
    
}