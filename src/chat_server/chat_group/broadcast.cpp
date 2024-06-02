#include "./ChatGroup.h"

/*
std::map<std::string, User> members;
std::string resoponse_form = 
            "status: %s\r\n"
            "content-length: %d\r\n"
            "\r\n"
            "%s";
*/

void ChatGroup::broadcast(std::string msg_type, std::string id, std::string body)
{
    std::string resoponse_msg =
                "status-code: %s\r\n"
                "sender: %s\r\n"
                "content-type: %s\r\n"
                "content-length: %d\r\n"
                "\r\n"
                "%s";

    char tmp[BUFSIZ];
    memset(tmp, 0, BUFSIZ);
    memset(this->buf, 0, BUFSIZ);

    if(msg_type != "chat")
        snprintf(tmp, BUFSIZ, "system: %s", body.c_str());
    else
        snprintf(tmp, BUFSIZ, "@%s: %s", id.c_str(), body.c_str());
    snprintf(this->buf, BUFSIZ, resoponse_msg.c_str(), "OK", id.c_str(), "msg", strlen(tmp), tmp);

    int cnt = 0;
    for(auto &member : members)
    {
        std::string member_id = member.first;
        int sock = member.second.sock;

        if(member_id == id) continue;

        if(send(sock, this->buf, strlen(this->buf), 0) < 0)
        {
            printf("[broadcast(%s)] Failed to send msg to member '%s'.\n", name.c_str(), member_id.c_str());
            continue;
        }
        cnt++;
    }
    printf("[braodcast(%s)] Sent msg to (%d/%d) members\n", name.c_str(), cnt, (int) members.size() - 1);
}