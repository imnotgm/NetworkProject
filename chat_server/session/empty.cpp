#include "./session.h"

bool Session::empty()
{
    if(members.empty())
        return true;
    return false;
}