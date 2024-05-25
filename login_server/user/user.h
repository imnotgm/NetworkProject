#include <string>
#include <vector>

typedef struct
{
    std::string id;
    int sock_fd;
    struct sockaddr_in addr;
    
    int is_available;
    std::string chat_room;
}User;