#ifndef __JSONHELPERFUNCTIONS_H__
#define __JSONHELPERFUNCTIONS_H__

#include "json.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

// Function to read users from a JSON file
json readUsersFromFile(const std::string &filename);

// Function to write users to a JSON file
void writeUsersToFile(const std::string &filename, const json &data);
void addUserToFile(const std::string &filename, const std::string &username, const std::string &password, const std::string &role);

bool isUsernameExists(const json &users, const std::string &username);

#endif // __JSONHELPERFUNCTIONS_H__