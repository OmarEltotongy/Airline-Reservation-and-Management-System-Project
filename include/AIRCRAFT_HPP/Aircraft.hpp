#ifndef __AIRCRAFT_H__
#define __AIRCRAFT_H__

#include "../../include/USERS_HPP/userClasses.hpp"
#include "../ENUMS/aircraft_enums.hpp"

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Aircraft
{
private:
    std::string aircraftID;          // Unique identifier for the aircraft.
    std::string model;               // Model of the aircraft.
    std::string maintenanceSchedule; // Scheduled maintenance dates.
    bool availability;

public:
    Aircraft(const std::string &aircraftID, const std::string &model, const std::string &maintenanceSchedule, const bool &availability);
    Aircraft(Administrator &admin);
    static void ManageAircraftMenu(Administrator &admin);

    /***********************************Air Crafts Functions***********************************/
    aircraftProcess addAircraft();
    aircraftProcess removeAircraft();
    aircraftProcess updateAircraft();
    aircraftProcess assignAircraftToFlight();
    aircraftProcess scheduleMaintenance(); // Schedules maintenance for the aircraft.
    bool checkAvailability();   // Checks if the aircraft is available.
    /*********************************************************************************************/

    void viewAllAircraft();
    ~Aircraft();
};

#endif // __AIRCRAFT_H__