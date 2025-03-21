#ifndef __JSONHELPERFUNCTIONS_H__
#define __JSONHELPERFUNCTIONS_H__

#include <iostream>
#include <fstream>
#include "json.hpp"
using json = nlohmann::json; // must be before the #include to see json

// Forward declaration of Flight class
class Flight;

// Function to read users from a JSON file
json readFromDP(const std::string &filename);

// Function to write users to a JSON file
void writeToDP(const std::string &filename, const json &data);

void addUserToFile(const std::string &filename, const std::string &username, const std::string &password, const std::string &role);

int isUsernameExists(const json &users, const std::string &username);

void addFlightToDP(const std::string &filename, const std::string &flightNumber, const std::string &origin,
                   const std::string &destination, const std::string &departureTime, const std::string &arrivalTime,
                   const std::string &aircraftType, int totalSeats, const std::string &status);

bool isPilotExists(json &pilots, const std::string &ID);
bool isFlightAttendantExist(json &flightAttendant, const std::string &ID);

int isFlightExists(const json &flights, const std::string &flightNumber);
int isAircraftExist(const json &aircrafts, const std::string &aid);

#endif // __JSONHELPERFUNCTIONS_H__