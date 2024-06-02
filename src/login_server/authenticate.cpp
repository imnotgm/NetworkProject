#include "./login_server.h"

bool authenticate(std::string id, const std::string &file_path)
{
    // Read the existing JSON file
    std::ifstream in_file(file_path);
    rapidjson::Document doc;

    if (in_file.is_open())
    {
        std::string content((std::istreambuf_iterator<char>(in_file)), (std::istreambuf_iterator<char>()));
        in_file.close();
        if (doc.Parse(content.c_str()).HasParseError())
        {
            std::cerr << "[authenticate] error: Cannot parse JSON file: " << file_path << std::endl;
            return false;
        }
    }
    else
    {
        std::cerr << "[authenticate] error: Cannot open file for reading: " << file_path << std::endl;
        return false;
    }

    if (doc.HasMember(id.c_str()))
        return false;
    return true;
}