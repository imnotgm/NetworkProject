#ifndef CHAT_SERVER_H
#define CHAT_SERVER_H

#include "./chat_group/ChatGroup.h"
#include "../include/utils/utils.h"
#include "../include/rapidjson/document.h"
#include "../include/rapidjson/writer.h"
#include "../include/rapidjson/stringbuffer.h"
#include "../include/rapidjson/prettywriter.h"

extern std::vector<User> tmp_user;
extern std::map<std::string, User> users;
extern std::map<std::string, ChatGroup *> chat_groups;

int server_socket();
void server_bind(int sock, int port);
void server_listen(int sock, int backlog);
int server_accept(int sock);

std::string user_list(std::string id);
std::string live_chat_list();
int msg_handler(User &user, std::string request, std::string status_code, std::string session, std::string content_type, std::string body);
int conn_handler(int server_sock);

#endif