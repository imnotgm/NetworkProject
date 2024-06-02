#include <string>
#include <vector>

typedef struct
{
    std::string id;
    std::string session;
    int is_available;

    int sock;
    struct sockaddr_in addr;
}User;