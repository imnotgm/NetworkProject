#include <string>
#include <vector>

typedef struct
{
    std::string id;
    std::string host;
    int port;
    int sock_fd;
}User;