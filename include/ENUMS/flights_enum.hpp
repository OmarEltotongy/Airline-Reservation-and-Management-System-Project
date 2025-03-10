#ifndef __FLIGHTS_ENUM_H__
#define __FLIGHTS_ENUM_H__

#include <string>
#include <vector>

enum flightProcess
{
    FLIGHT_PROCESS_IS_SUCCESSFUL,
    FLIGHT_PROCESS_IS_FAILED,
    FLIGHT_PROCESS_IS_NULL
};

enum flightStatus
{
    ON_TIME,
    DELAYED,
    CANCELLED
};

struct AssignedCrew
{
    std::string pilotID;                         // ID of the assigned pilot
    std::vector<std::string> flightAttendantIDs; // IDs of the assigned flight attendants
};

#endif // __FLIGHTS_ENUM_H__