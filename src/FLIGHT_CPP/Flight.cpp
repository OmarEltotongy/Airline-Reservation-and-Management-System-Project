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
Flight::Flight(Administrator &admin)
{
    cout << "Edits will be done with Admin: " << admin.getName() << endl;
}
// Function to display the Flight Management menu

void Flight::ManageFlightsMenu(Administrator &admin)
{
    Flight FlightAdmin(admin);
    /*already validated the username and the password in the main*/
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
            FlightAdmin.addFlight(FlightAdmin);
            break;
        case 2:
            FlightAdmin.updateFlight(FlightAdmin);
            break;
        case 3:
            FlightAdmin.deleteFlight();
            break;
        case 4:
            FlightAdmin.viewAllFlights();
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

flightStatus intStatusToflightStatus(int s)
{
    switch (s)
    {
    case 0:
        return ON_TIME;
    case 1:
        return DELAYED;
    case 2:
        return CANCELLED;
    default:
        throw std::invalid_argument("Invalid status type");
    }
}

std::string intStatusToStringStatus(int s)
{
    switch (s)
    {
    case 0:
        return "ON_TIME";
    case 1:
        return "DELAYED";
    case 2:
        return "CANCELLED";
    default:
        throw std::invalid_argument("Invalid status type");
    }
}

std::string roleToString(rolesTypes role)
{
    switch (role)
    {
    case rolesTypes::ADMIN:
        return "ADMIN";
    case rolesTypes::BOOKING_AGENT:
        return "BOOKING_AGENT";
    case rolesTypes::PASSENGER:
        return "PASSENGER";
    default:
        throw std::invalid_argument("Invalid role type");
    }
}

/**************************Admin Flights*******************************************/
AssignedCrew Flight::assignCrewToFlight(const std::string &flightNumber, json &pilots, json &flightAttendant)
{
    AssignedCrew crew;

    // Assign Pilot
    std::cout << "--- List of Pilots ---\n";
    for (auto &pilot : pilots["pilots"])
    {
        std::cout << "ID: " << pilot["ID"] << ", Name: " << pilot["name"]
                  << ", Status: " << pilot["status"] << "\n";
    }
    while (true)
    {
        std::string pilotID;
        std::cout << "Select Pilot by ID (or type 'done' to skip): ";
        std::cin >> pilotID;

        if (pilotID == "done")
        {
            break; // Exit the loop
        }

        if (isPilotExists(pilots, pilotID))
        {
            crew.pilotID.push_back(pilotID); // Store the flight attendant ID
            std::cout << "Pilot " << pilotID << " assigned to flight.\n";
        }
        else
        {
            std::cout << "Error: Pilot " << pilotID << " does not exist.\n";
        }
    }
    // Assign Flight Attendants
    std::cout << "--- List of Flight Attendants ---\n";
    for (auto &fa : flightAttendant["flight_attendants"])
    {
        std::cout << "ID: " << fa["ID"] << ", Name: " << fa["name"]
                  << ", Status: " << fa["status"] << "\n";
    }

    std::cout << "Enter Flight Attendant IDs (one at a time, type 'done' to finish):\n";
    while (true)
    {
        std::string faID;
        std::cout << "Enter Flight Attendant ID: ";
        std::cin >> faID;

        if (faID == "done")
        {
            break; // Exit the loop
        }

        if (isFlightAttendantExist(flightAttendant, faID))
        {
            crew.flightAttendantIDs.push_back(faID); // Store the flight attendant ID
            std::cout << "Flight Attendant " << faID << " assigned to flight.\n";
        }
        else
        {
            std::cout << "Error: Flight Attendant " << faID << " does not exist.\n";
        }
    }
    return crew;
}

flightProcess Flight::addFlight(Flight &flight_admin)
{
    int s;
    flightStatus status;
    std::string flightNumber, origin, destination, departureTime, arrivalTime, aircraftID;
    AssignedCrew ac;

    std::cout << "--- Add New Flight ---\n";
    std::cout << "Enter Flight Number: ";
    std::cin.ignore(); // Clear the input buffer
    std::getline(std::cin, flightNumber);
    std::cout << "Enter Origin: ";
    std::getline(std::cin, origin);
    std::cout << "Enter Destination: ";
    std::getline(std::cin, destination);
    std::cout << "Enter Departure Date and Time (DD-MM-YYYY HH:MM): ";
    std::getline(std::cin, departureTime);
    std::cout << "Enter Arrival Date and Time (DD-MM-YYYY HH:MM): ";
    std::getline(std::cin, arrivalTime);
    std::cout << "Enter Aircraft ID: ";
    std::getline(std::cin, aircraftID);
    std::cout << "Enter Status (Scheduled:0 /Delayed: 1 /Canceled: 2): ";
    std::cin >> s;
    std::cin.ignore(); // Clear the input buffer after reading the status
    status = intStatusToflightStatus(s);

    // Read existing pilots from the file
    json pilots = readFromDP(pilotDP);
    // Read existing Flight Attendant from the file
    json Flight_Attendant = readFromDP(flightAttendantDB);

    auto crew = flight_admin.assignCrewToFlight(flightNumber, pilots, Flight_Attendant);

    // Create a new Flight object
    Flight newFlight(flightNumber, origin, destination, departureTime, arrivalTime, status, aircraftID, crew);

    // Add the flight to the JSON file
    json flights = readFromDP(flightDP);
    // Create a JSON object for the new flight, including the assigned crew
    json newFlightEntry = {
        {"flightNumber", flightNumber},
        {"origin", origin},
        {"destination", destination},
        {"departureTime", departureTime},
        {"arrivalTime", arrivalTime},
        {"aircraftID", aircraftID},
        {"status", status},
        {"assignedCrew", {{"pilotID", crew.pilotID}, {"flightAttendantIDs", crew.flightAttendantIDs}}}};

    // Add the new flight to the flights array
    flights["flights"].push_back(newFlightEntry);

    // Write the updated flights back to the file
    writeToDP(flightDP, flights);
    std::cout << "Flight " << flightNumber << " has been successfully added with assigned crew.\n";

    return FLIGHT_PROCESS_IS_SUCCESSFUL;
}

flightProcess Flight::updateFlight(Flight &flight_admin)
{
    int choice;
    flightProcess fp = FLIGHT_PROCESS_IS_NULL;
    std::string flightNumber;
    std::cout << "--- Update Flight ---\n";
    std::cout << "Enter Flight Number to Update: ";
    std::cin.ignore(); // Clear the input buffer

    std::getline(std::cin, flightNumber);

    // Read existing flights from the file
    json flights = readFromDP(flightDP);

    int index = isFlightExists(flights, flightNumber);

    // Check if the flight exists
    if (index == -1)
    {
        std::cout << "Error: Flight " << flightNumber << " does not exist.\n";
        fp = FLIGHT_PROCESS_IS_FAILED;
        return fp;
    }

    std::cout << " --- Updating Existing Flight ---" << std::endl;
    std::cout << "Select information to update:" << std::endl;
    std::cout << "1. Flight Details" << std::endl;
    std::cout << "2. Crew Assignments" << std::endl;
    std::cout << "3. Status" << std::endl;
    std::cout << "4. Back to Manage Flights" << std::endl;
    std::cout << "Enter choice: ";
    cin >> choice;

    json &flight = flights["flights"][index];

    switch (choice)
    {

    case 1:
    {
        // Update Flight Details
        std::cout << "Select detail to update:" << std::endl;
        std::cout << "1. Flight Number" << std::endl;
        std::cout << "2. Origin" << std::endl;
        std::cout << "3. Destination" << std::endl;
        std::cout << "4. Departure Time" << std::endl;
        std::cout << "5. Arrival Time" << std::endl;
        std::cout << "6. Aircraft ID" << std::endl;
        std::cout << "Enter choice: ";
        int detailChoice;
        std::cin >> detailChoice;
        std::cin.ignore(); // Clear the input buffer

        switch (detailChoice)
        {

        case 1:
        {
            std::string newFlightNumber;
            std::cout << "Enter new Flight Number: ";
            std::getline(std::cin, newFlightNumber);
            flight["flightNumber"] = newFlightNumber;
            break;
        }
        case 2:
        {
            std::string newOrigin;
            std::cout << "Enter new Origin: ";
            std::getline(std::cin, newOrigin);
            flight["origin"] = newOrigin;
            break;
        }
        case 3:
        {
            std::string newDestination;
            std::cout << "Enter new Destination: ";
            std::getline(std::cin, newDestination);
            flight["destination"] = newDestination;
            break;
        }
        case 4:
        {
            std::string newDepartureTime;
            std::cout << "Enter new Departure Time (DD-MM-YYYY HH:MM): ";
            std::getline(std::cin, newDepartureTime);
            flight["departureTime"] = newDepartureTime;
            break;
        }
        case 5:
        {
            std::string newArrivalTime;
            std::cout << "Enter new Arrival Time (DD-MM-YYYY HH:MM): ";
            std::getline(std::cin, newArrivalTime);
            flight["arrivalTime"] = newArrivalTime;
            break;
        }
        case 6:
        {
            std::string newAircraftID;
            std::cout << "Enter new Aircraft ID: ";
            std::getline(std::cin, newAircraftID);
            flight["aircraftID"] = newAircraftID;
            break;
        }
        default:
        {
            std::cout << "Invalid choice. No changes made.\n";
            fp = FLIGHT_PROCESS_IS_FAILED;
            return fp;
        }
        }

        // Write the updated data back to the file
        writeToDP(flightDP, flights);
        std::cout << "Flight " << flightNumber << " has been successfully updated.\n";
        fp = FLIGHT_PROCESS_IS_SUCCESSFUL;
        break;
    }
    case 2:
    {

        // Read existing pilots and flight attendants from their files
        json pilots = readFromDP(pilotDP);
        json flightAttendant = readFromDP(flightAttendantDB);

        // Assign new crew to the flight
        auto newCrew = flight_admin.assignCrewToFlight(flightNumber, pilots, flightAttendant);

        flight["assignedCrew"]["pilotID"] = newCrew.pilotID;
        flight["assignedCrew"]["flightAttendantIDs"] = newCrew.flightAttendantIDs;


        std::cout << "Crew for flight " << flightNumber << " has been updated.\n";

        // Write the updated flights back to the file
        writeToDP(flightDP, flights);
        writeToDP(pilotDP,pilots);
        writeToDP(flightAttendantDB,flightAttendant);

        break;
    }

    case 3:
    {
        int newStatus;
        std::cout << "Enter New Status (ON_TIME: 0 /DELAYED: 1 /CANCELED: 2): ";
        std::cin >> newStatus;
        std::string state;
        state = intStatusToStringStatus(newStatus);
        flight["status"] = state;

        // Write the updated data back to the file
        writeToDP(flightDP, flights);

        std::cout << "Flight " << flightNumber << " has been successfully updated.\n";
        fp = FLIGHT_PROCESS_IS_SUCCESSFUL;
        break;
    }
    case 4:
    {
        std::cout << "Backing to Manage Flights menu" << std::endl;
        break;
    }
    default:
        throw invalid_argument("incorrect choice");
    }
    return fp;
}

flightProcess Flight::deleteFlight()
{
    int choice;
    flightProcess fp = FLIGHT_PROCESS_IS_FAILED;
    std::string flightNumber;
    std::cout << "--- Delete Flight ---\n";
    std::cin.ignore(); // Clear the input buffer
    std::cout << "Enter Flight Number to Delete: ";
    std::getline(std::cin, flightNumber);

    // Read existing flights from the file
    json flights = readFromDP(flightDP);
    int index = isFlightExists(flights, flightNumber);

    // Check if the flight exists
    if (index == -1)
    {
        std::cout << "Error: Flight " << flightNumber << " does not exist already.\n";
        return FLIGHT_PROCESS_IS_FAILED;
    }

    json &flight = flights["flights"][index];

    flights["flights"].erase(flights["flights"].begin() + index);
    std::cout << "Flight with number " << flightNumber << " has been successfully deleted.\n";

    // Write the updated data back to the file
    writeToDP(flightDP, flights);
    return FLIGHT_PROCESS_IS_SUCCESSFUL;
}

/*********************************************************************************/

Flight::~Flight()
{
#if DEBUG
    cout << "Deconstructor of Flight is called" << endl;
#endif
}