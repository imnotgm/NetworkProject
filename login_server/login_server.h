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

extern std::map<int, User> users;
extern std::vector<User> tmp_user;

// extern std::string response_form;

int server_socket();
void server_bind(int sock_fd, int port);
void server_listen(int sock_fd, int backlog);
int server_accept(int sock_fd);
bool authenticate(std::string id, const std::string &file_path);

void add_user(int sock_fd, std::string id, const std::string &file_path);
void remove_user(int sock_fd, const std::string &file_path);
std::string online_users();

int message_handler(int sock_fd, char buf[], int buf_size,
                    int status, std::string body, std::string method, std::string detail);
int connection_handler(int sock_fd, const std::string &file_path);

#endif