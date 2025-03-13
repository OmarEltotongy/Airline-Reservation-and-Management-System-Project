#include "../../include/JSON_HPP/jsonHelperFunctions.hpp"

// Function to read users from a JSON file
json readFromDP(const std::string &filename)
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
void writeToDP(const std::string &filename, const json &data)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    file << data.dump(4); // Pretty-print with 4 spaces indentation
}

void addUserToFile(const std::string &filename, const std::string &username, const std::string &password, const std::string &role)
{
    // Read existing users from the file
    json users = readFromDP(filename);

    // Check if the username already exists
    if (isUsernameExists(users, username))
    {
        std::cout << "Error: Username '" << username << "' already exists. User not added." << std::endl;
        return;
    }

    // Add the new user
    json newUser = {
        {"username", username},
        {"password", password},
        {"role", role}};
    users["users"].push_back(newUser);

    // Write updated users back to the file
    writeToDP(filename, users);
    std::cout << "User '" << username << "' added successfully!" << std::endl;
}

int isUsernameExists(const json &users, const std::string &username)
{
    for(size_t i =0; i < users["users"].size() ; i++)
    {
        if(users["users"][i]["username"] == username)
        {
            return static_cast<int>(i);
        }
    }
    return -1; // Username does not exist
}

int isFlightExists(const json &flights, const std::string &flightNumber)
{
    // Iterate through the "flight" array
    for (size_t i = 0; i < flights["flights"].size(); ++i)
    {
        if (flights["flights"][i]["flightNumber"] == flightNumber)
        {                               // Check the "flightNumber" field
            return static_cast<int>(i); // Return the index if found
        }
    }
    return -1; // Return -1 if not found
}


int isAircraftExist(const json &aircrafts, const std::string &aid)
{
    // Iterate through the "aircraft" array
    for (size_t i = 0; i < aircrafts["aircraft"].size(); ++i)
    {
        if (aircrafts["aircraft"][i]["aircraftID"] == aid)
        {                               // Check the "aircraftID" field
            return static_cast<int>(i); // Return the index if found
        }
    }
    return -1; // Return -1 if not found
}
// Function to add a new flight to the JSON file
void addFlightToDP(const std::string &filename, const std::string &flightNumber, const std::string &origin,
                   const std::string &destination, const std::string &departureTime, const std::string &arrivalTime,
                   const std::string &aircraftType, int totalSeats, const std::string &status)
{
    // Read existing flights from the file
    json flights = readFromDP(filename);

    // Check if the flight already exists
    if (isFlightExists(flights, flightNumber))
    {
        std::cout << "Error: Flight " << flightNumber << " already exists. Cannot add duplicate flight.\n";
        return;
    }

    // Add the new flight to the JSON data
    flights["flights"].push_back({{"flightNumber", flightNumber},
                                  {"origin", origin},
                                  {"destination", destination},
                                  {"departureTime", departureTime},
                                  {"arrivalTime", arrivalTime},
                                  {"aircraftType", aircraftType},
                                  {"totalSeats", totalSeats},
                                  {"status", status}});

    // Write the updated data back to the file
    writeToDP(filename, flights);

    std::cout << "Flight " << flightNumber << " has been successfully added to the schedule.\n";
}

bool isPilotExists(json &pilots, const std::string &ID)
{
    // Loop through the pilots to check if the ID exists
    bool pilotFound = false;

    for (auto &pilot : pilots["pilots"])
    {
        if (pilot["ID"] == ID)
        {
            pilotFound = true;
            if (pilot["status"] == "FREE")
            {
                pilot["status"] = "BUSY"; // Update pilot status to BUSY
                std::cout << "Pilot " << pilot["name"] << " assigned to flight.\n";
            }
            else
            {
                std::cout << "Error: Pilot " << pilot["name"] << " is not available (Status: " << pilot["status"] << ").\n";
                throw std::invalid_argument("Pilot is not free: " + ID);
            }
            break;
        }
    }

    // Throw an exception if the pilot ID is not found
    if (!pilotFound)
    {
        throw std::invalid_argument("Invalid pilot ID: " + ID);
    }

    return pilotFound;
}

bool isFlightAttendantExist(json &flightAttendant, const std::string &ID)
{
    // Loop through the flight attendants to check if the ID exists
    bool flightAttendantFound = false;

    for (auto &fa : flightAttendant["flight_attendants"])
    {
        if (fa["ID"] == ID)
        {
            flightAttendantFound = true;
            if (fa["status"] == "FREE")
            {
                fa["status"] = "BUSY"; // Update flight attendant status to BUSY
                std::cout << "Flight Attendant " << fa["name"] << " assigned to flight.\n";
            }
            else
            {
                std::cout << "Error: Flight Attendant " << fa["name"] << " is not available (Status: " << fa["status"] << ").\n";
                throw std::invalid_argument("Flight Attendant is not free: " + ID);
            }
            break;
        }
    }

    // Throw an exception if the flight attendant ID is not found
    if (!flightAttendantFound)
    {
        throw std::invalid_argument("Invalid flight attendant ID: " + ID);
    }

    return flightAttendantFound;
}