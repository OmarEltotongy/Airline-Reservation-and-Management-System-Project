#include "../../include/FLIGHT_HPP/Flight.hpp"
#include "../../include/USERS_HPP/userClasses.hpp"
#include <iomanip> // For std::setw, std::left, etc.

Flight::Flight(const std::string &FN, const std::string &origin, const std::string &destination,
               const std::string &DT, const std::string &AT, const flightStatus &FS,
               const std::string &ACID, const AssignedCrew &assignedCrew)
    : flightNumber(FN), departureLocation(origin), arrivalLocation(destination),
      departureTime(DT), arrivalTime(AT), status(FS), aircraftID(ACID), assignedCrew(assignedCrew)
{
#if DEBUG
    cout << "Constructor of Flight is called" << endl;
#endif
}
// Function to display the Flight Management menu

void Flight::ManageFlightsMenu(const std::string &username, const std::string &password, const rolesTypes &r)
{
    /*already validated the username and the password in the main*/
    Administrator admin(username, password, r);

    int choice;
    while (true)
    {
        std::cout << "--- Manage Flights ---\n";
        std::cout << "1. Add New Flight\n";
        std::cout << "2. Update Existing Flight\n";
        std::cout << "3. Remove Flight\n";
        std::cout << "4. View All Flights\n";
        std::cout << "5. Back to Main Menu\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            admin.addFlight();
            break;
        case 2:
            admin.updateFlight();
            break;
        case 3:
            admin.deleteFlight();
            break;
        case 4:
            Flight::viewAllFlights();
            break;
        case 5:
            return; // Go back to the previous menu
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void Flight::viewAllFlights()
{
    json flights = readFromDP(flightDP);

    // Check if there are any flights
    if (flights["flights"].empty())
    {
        std::cout << "No flights found in the database.\n";
        return;
    }

    // Print header
    std::cout << "\n--- List of Flights ---\n";
    std::cout << "+------------+------------------+------------------+---------------------+---------------------+------------------+------------------+\n";
    std::cout << "| Flight No. | Origin           | Destination      | Departure Time      | Arrival Time        | Aircraft ID      | Status           |\n";
    std::cout << "+------------+------------------+------------------+---------------------+---------------------+------------------+------------------+\n";

    // Print each flight's data
    /*using printf for */
    for (const auto &flight : flights["flights"])
    {
        std::cout << "| "
                  << std::left << std::setw(10) << flight["flightNumber"].get<std::string>() << " | "
                  << std::left << std::setw(16) << flight["origin"].get<std::string>() << " | "
                  << std::left << std::setw(16) << flight["destination"].get<std::string>() << " | "
                  << std::left << std::setw(19) << flight["departureTime"].get<std::string>() << " | "
                  << std::left << std::setw(19) << flight["arrivalTime"].get<std::string>() << " | "
                  << std::left << std::setw(16) << flight["aircraftID"].get<std::string>() << " | "
                  << std::left << std::setw(16) << flight["status"].get<std::string>() << " |\n";
        // Display assigned crew
        std::cout << "+------------+------------------+------------------+---------------------+---------------------+------------------+------------------+\n";
        std::cout << "| Assigned Crew:                                                                                                                         |\n";
        std::cout << "|   Pilot ID: " << flight["assignedCrew"]["pilotID"].get<std::string>() << "\n";
        std::cout << "|   Flight Attendant IDs: ";
        for (const auto &faID : flight["assignedCrew"]["flightAttendantIDs"])
        {
            std::cout << faID.get<std::string>() << " ";
        }
        std::cout << "\n";
        std::cout << "+------------+------------------+------------------+---------------------+---------------------+------------------+------------------+\n";
    }
}

Flight::~Flight()
{
#if DEBUG
    cout << "Deconstructor of Flight is called" << endl;
#endif
}