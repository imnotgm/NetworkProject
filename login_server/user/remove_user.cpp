#include "../login_server.h"

/* format
"user1":
{
    "host": "192.168.1.2",
    "port": 8080
}, */

void remove_user(std::string id, const std::string& file_path)
{
    user_list.erase(id);

    std::ifstream infile(file_path);
    std::stringstream buffer;
    buffer << infile.rdbuf();
    infile.close();

    std::string content = buffer.str();
    
    // Remove the user information from the content
    std::string::size_type pos = content.find("\"id\": \"" + id + "\"");
    if(pos != std::string::npos)
    {
        std::string::size_type endPos = content.find("},\n", pos);
        if(endPos != std::string::npos)
        {
            content.erase(pos, endPos - pos + 3);
        }
    }

    // Write the updated content back to the file
    std::ofstream out_file(file_path, std::ios_base::trunc);
    out_file << content;
    out_file.close();
}