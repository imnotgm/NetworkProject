#include "../login_server.h"

void remove_user(int sock, const std::string &file_path)
{
    if(users.find(sock) == users.end())
        return;
    std::string id = users[sock].id;
    users.erase(sock);
    
    // Read the existing JSON file
    std::ifstream in_file(file_path);
    rapidjson::Document doc;

    if (in_file.is_open())
    {
        std::string content((std::istreambuf_iterator<char>(in_file)), (std::istreambuf_iterator<char>()));
        in_file.close();
        if (doc.Parse(content.c_str()).HasParseError())
        {
            std::cerr << "[remove_user] error: Failed to parse JSON file: " << file_path << std::endl;
            return;
        }
    }
    else
    {
        std::cerr << "[remove_user] error: Failed to open file for reading: " << file_path << std::endl;
        return;
    }

    // Remove the user with the specified ID
    if (doc.HasMember(id.c_str()))
    {
        doc.RemoveMember(id.c_str());
    }
    else
    {
        std::cerr << "[remove_user] error: User ID not found in JSON: " << id << std::endl;
        return;
    }

    // Write the updated JSON back to the file
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    std::ofstream out_file(file_path);
    if (!out_file.is_open())
    {
        std::cerr << "[remove_user] error: Failed to open file for writing: " << file_path << std::endl;
        return;
    }

    out_file << buffer.GetString();
    out_file.close();
}