#ifndef LOGIN_SERVER_H
#define LOGIN_SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
#include <iostream>
#include <stdexcept>
#include <cerrno>
#include <cstring>
#include <string>
#include <map>
#include <vector>
#include "./user.h"
#include "../utils/utils.h"

extern std::map<std::string, User> user_list;
extern std::vector<User> user_tmp;

extern std::string response_form;

int server_socket();
void server_bind(int sock_fd, int port);
void server_listen(int sock_fd, int backlog);
int server_accept(int sock_fd);
bool id_check(std::string id);
int authenticate(int sock_fd);

#endif