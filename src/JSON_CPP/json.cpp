#include "../../include/JSON_HPP/jsonHelperFunctions.hpp"

// Function to read users from a JSON file
json readUsersFromFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    json data;
    file >> data;
    return data;
}
// Function to write users to a JSON file
void writeUsersToFile(const std::string &filename, const json &data)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    file << data.dump(4); // Pretty-print with 4 spaces indentation
}

void addUserToFile(const std::string &filename, const std::string &username, const std::string &password, const std::string &role) {
    // Read existing users from the file
    json users = readUsersFromFile(filename);

    // Check if the username already exists
    if (isUsernameExists(users, username)) {
        std::cout << "Error: Username '" << username << "' already exists. User not added." << std::endl;
        return;
    }

    // Add the new user
    json newUser = {
        {"username", username},
        {"password", password},
        {"role", role}
    };
    users["users"].push_back(newUser);

    // Write updated users back to the file
    writeUsersToFile(filename, users);
    std::cout << "User '" << username << "' added successfully!" << std::endl;
}

bool isUsernameExists(const json &users, const std::string &username) {
    for (const auto &user : users["users"]) {
        if (user["username"] == username) {
            return true; // Username already exists
        }
    }
    return false; // Username does not exist
}