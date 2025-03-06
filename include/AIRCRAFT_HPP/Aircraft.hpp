#ifndef __AIRCRAFT_H__
#define __AIRCRAFT_H__

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
    void scheduleMaintenance(); // Schedules maintenance for the aircraft.
    bool checkAvailability();   // Checks if the aircraft is available.
    ~Aircraft();
};

#endif // __AIRCRAFT_H__