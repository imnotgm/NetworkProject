#include <string>
#include <vector>

typedef struct
{
    std::string id;
    int sock_fd;
    int is_available;
    struct sockaddr_in addr;
}User;