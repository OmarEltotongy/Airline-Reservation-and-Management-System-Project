#ifndef __FLIGHT_H__
#define __FLIGHT_H__

#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum flightProcess
{
    FLIGHT_PROCESS_IS_SUCCESSFUL,
    FLIGHT_PROCESS_IS_FAILED
};
enum flightStatus
{
    ON_TIME,
    DELAYED,
    CANCELLED
};

class Flight
{
private:
    std::string flightNumber;      // Unique identifier for the flight.
    std::string departureLocation; // Origin
    std::string arrivalLocation;   // Destination
    std::string departureTime;     // Scheduled departure time.
    std::string arrivalTime;       // Scheduled arrival time.
    flightStatus status;           // Current status of the flight (e.g., "On Time", "Delayed").
    std::string aircraftID;        // ID of the assigned aircraft.

public:
    Flight(const std::string &FN, const std::string &origin, const std::string &destination,
        const std::string &DT, const std::string &AT, const flightStatus &FS,
        const std::string &ACID);
    flightProcess addFlight();
    flightProcess updateFlight();
    flightProcess deleteFlight();
    ~Flight();
};
#endif // __FLIGHT_H__