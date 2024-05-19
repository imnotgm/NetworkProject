#include "utils.h"

std::map<std::string, std::string> parseHeaders(const char* msg)
{
    std::map<std::string, std::string> headers;
    const char* delimiter = "\r\n";
    char* msg_copy = strdup(msg);
    char* line = strtok(msg_copy, delimiter);

    while (line != nullptr)
    {
        // Find the position of the colon
        char* pos = strchr(line, ':');
        if(pos != nullptr)
        {
            // Extract the key and value
            std::string key(line, pos);
            std::string value(pos + 1);

            // Trim leading and trailing whitespace from key and value
            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);

            // Insert into map
            headers[key] = value;
        }

        // Get the next line
        line = strtok(nullptr, delimiter);
    }

    free(msg_copy);
    return headers;
}

// int main()
// {
//     char msg[] =
//         "method: %s\r\n"
//         "authentication: %s\r\n"
//         "fin: %d\r\n"
//         "\r\n";

//     char buf[BUFSIZ];
//     snprintf(buf, BUFSIZ, msg, "login", "success", 1);
//     std::map<std::string, std::string> headers = parseHeaders(buf);

//     printf("%s\n", buf);
//     std::string str = headers["method"];
//     printf("%s\n", str.c_str());

//     for (const auto& pair : headers) {
//         std::cout << pair.first << ":" << pair.second << std::endl;
//     }

//     return 0;
// }
