#ifndef __FLIGHT_H__
#define __FLIGHT_H__
#include "../USERS_HPP/userClasses.hpp"
#include "../ENUMS/flights_enum.hpp"
#include "../ENUMS/user_enums.hpp"

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define DEBUG 1

// Forward declaration of Administrator class
class User;
class Administrator;

class Flight
{
private:
    std::string flightNumber;      // Unique identifier for the flight.
    std::string departureLocation; // Origin
    std::string arrivalLocation;   // Destination
    std::string departureTime;     // Scheduled departure time.
    std::string arrivalTime;       // Scheduled arrival time.
    std::string aircraftID;        // ID of the assigned aircraft.
    flightStatus status;           // Current status of the flight (e.g., "On Time", "Delayed").
    AssignedCrew assignedCrew;     // Nested struct for assigned crew

public:
    Flight(const std::string &FN, const std::string &origin, const std::string &destination,
           const std::string &DT, const std::string &AT, const flightStatus &FS,
           const std::string &ACID, const AssignedCrew &assignedCrew);
    Flight(Administrator &admin);
    static void ManageFlightsMenu(Administrator &admin);
    // Method to convert Flight object to JSON
    json toJson() const;

    /************************************Flights Functions*************************************/
    AssignedCrew assignCrewToFlight(const std::string &flightNumber, json &pilots, json &Flight_Attendant);
    flightProcess addFlight(Flight &flight_admin);
    flightProcess updateFlight(Flight &flight_admin);
    flightProcess deleteFlight();
    /******************************************************************************************/

    void viewAllFlights(); // print the database

    ~Flight();
};
#endif // __FLIGHT_H__