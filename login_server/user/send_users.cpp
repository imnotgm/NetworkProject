#include "../login_server.h"

void send_userList(int sock_fd, const std::string& file_path)
{
    std::ifstream file(file_path, std::ios::in | std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << file_path << std::endl;
        return;
    }

    char buf[BUFSIZ];
    while(file.read(buf, sizeof(buf)))
    {
        if(send(sock_fd, buf, file.gcount(), 0) < 0)
        {
            std::cerr << "Failed to send file data to client." << std::endl;
            file.close();
            return;
        }
    }

    // Send any remaining bytes in the buffer
    if(file.gcount() > 0)
    {
        if(send(sock_fd, buf, file.gcount(), 0) < 0)
        {
            std::cerr << "Failed to send remaining file data to client." << std::endl;
        }
    }

    file.close();
    std::cout << "File sent successfully to client." << std::endl;
}