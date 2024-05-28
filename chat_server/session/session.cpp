#include "./session.h"

Session::Session(std::string name, std::string id, User user) : name(name)
{
    memset(buf, 0, BUFSIZ);
    members[id] = user;

    // TODO: 비동기식으로 초대 수락/거절 기능 구현
}

Session::~Session()
{
    
}