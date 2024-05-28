#ifndef LOGIN_SERVER_H
#define LOGIN_SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cerrno>
#include <cstring>
#include <string>
#include <map>
#include <vector>
#include "./user/user.h"
#include "../include/utils/utils.h"
#include "../include/rapidjson/document.h"
#include "../include/rapidjson/writer.h"
#include "../include/rapidjson/stringbuffer.h"
#include "../include/rapidjson/prettywriter.h"

extern std::vector<User> tmp_user;
extern std::map<int, User> users;

int server_socket();
void server_bind(int sock, int port);
void server_listen(int sock, int backlog);
int server_accept(int sock);
bool authenticate(std::string id, const std::string &file_path);

void add_user(int sock, std::string id, const std::string &file_path);
void remove_user(int sock, const std::string &file_path);
std::string online_users();

int msg_handler(int sock, std::string status, std::string body, std::string method);
int conn_handler(int server_sock, const std::string &file_path);

#endif