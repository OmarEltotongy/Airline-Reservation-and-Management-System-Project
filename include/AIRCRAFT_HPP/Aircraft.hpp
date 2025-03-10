#ifndef __AIRCRAFT_H__
#define __AIRCRAFT_H__

#include "../../include/USERS_HPP/userClasses.hpp"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class AirCraft
{
private:
    std::string aircraftID;          // Unique identifier for the aircraft.
    std::string model;               // Model of the aircraft.
    std::string maintenanceSchedule; // Scheduled maintenance dates.
    bool availability;

public:
    AirCraft(const std::string &aircraftID, const std::string &model, const std::string &maintenanceSchedule, const bool &availability);
    static void ManageAirCraftMenu(const std::string& username, const std::string& password,const rolesTypes& r);
    static void viewAllAircraft();
    ~AirCraft();
};

#endif // __AIRCRAFT_H__