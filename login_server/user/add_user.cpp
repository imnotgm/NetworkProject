#include "../login_server.h"

/* format
"user1":
{
    "host": "192.168.1.2",
    "port": 8080
}, */

void add_user(std::string id, const std::string& file_path)
{
    User user = tmp_user.back();
    user.id = id;
    printf("[Handler] user %s: (ip: %s, port: %d)\n",
            user.id.c_str(), inet_ntoa(user.addr.sin_addr), ntohs(user.addr.sin_port));

    user_list[id] = user;
    tmp_user.pop_back();

    std::ifstream infile(file_path);
    std::stringstream buffer;
    buffer << infile.rdbuf();
    std::string content = buffer.str();
    infile.close();

    std::stringstream ss;
    ss << "\"" << user.id << "\":\n";
    ss << "{";
    ss << "\t\"host\": \"" << inet_ntoa(user.addr.sin_addr) << "\",\n";
    ss << "\t\"port\": " << ntohs(user.addr.sin_port);
    ss << "\n},\n";

    std::size_t pos = content.rfind('\n');
    if(pos != std::string::npos)
    {
        content.insert(pos, ss.str());
    }

    std::ofstream out_file(file_path, std::ios_base::app);
    if(out_file.is_open())
    {
        out_file << ss.str();
        out_file.close();
    }
}