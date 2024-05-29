#ifndef UTILS_H
#define UTILS_H

#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <iostream>

int countSubstr(const std::string &str, const std::string &sub);
std::vector<std::string> split(std::string str, std::string delim, int limit = 2);
std::map<std::string, std::string> parseHeaders(const char* msg);

#endif