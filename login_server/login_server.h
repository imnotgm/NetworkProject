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
#include "./user.h"
#include "../utils/utils.h"

extern std::map<std::string, User> user_list;
extern std::vector<User> tmp_user;

extern std::string response_form;

int server_socket();
void server_bind(int sock_fd, int port);
void server_listen(int sock_fd, int backlog);
int server_accept(int sock_fd);
bool authenticate(std::string id);

void add_user(std::string id, const std::string& file_path);
void remove_user(std::string id, const std::string& file_path);
void send_userList(int sock_fd, const std::string& file_path);

int connection_handler(int sock_fd, const std::string& file_path);

#endif