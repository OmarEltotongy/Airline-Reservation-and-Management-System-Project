#include "../../include/USERS_HPP/userClasses.hpp"
#include "../../include/FLIGHT_HPP/Flight.hpp" // Including the full definition of Flight in cpp
#include "../../include/AIRCRAFT_HPP/AirCraft.hpp"
#include "../../include/JSON_HPP/jsonHelperFunctions.hpp"

std::string UserDP = "data/users.json";
std::string flightDP = "data/flights.json";
std::string pilotDP = "data/pilots.json";
std::string flightAttendantDB = "data/flightAttendant.json";
std::string AirCraftDB = "data/aircraft.json";

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

User::User(const std::string &name, const std::string &pass, const rolesTypes &r)
{
#if DEBUG
    cout << "Constructor of User is called" << endl;
#endif
}
bool User::validateCredentials(const std::string &username, const std::string &password, const rolesTypes &role)
{
    json users = readFromDP(UserDP);

    // Convert the role enum to a string
    std::string roleStr = roleToString(role);

    for (const auto &user : users["users"])
    {
        if (user["username"] == username && user["password"] == password && user["role"] == roleStr)
        {
            return true; // Credentials are valid
        }
    }
    return false; // Credentials are invalid
}

logState User::login()
{
    switch (role)
    {
    case rolesTypes::ADMIN:
    {
        if (validateCredentials(username, password, role))
        {
#if DEBUG
            cout << "admin login succeed" << endl;
#endif
            loginState = LOG_STATE_SUCCESSFUL;
        }
        else
        {
#if DEBUG
            cout << "admin login failed" << endl;
#endif
            loginState = LOG_STATE_FAILED;
        }
        return loginState;
    }
    case rolesTypes::BOOKING_AGENT:
    {
        if (validateCredentials(username, password, role))
        {
#if DEBUG
            cout << "BookingAgent login succeed" << endl;
#endif
            loginState = LOG_STATE_SUCCESSFUL;
        }
        else
        {
#if DEBUG
            cout << "BookingAgent login failed" << endl;
#endif
            loginState = LOG_STATE_FAILED;
        }
        return loginState;
    }

    case rolesTypes::PASSENGER:
    {

        if (validateCredentials(username, password, role))
        {
#if DEBUG
            cout << "Passenger login succeed" << endl;
#endif
            loginState = LOG_STATE_SUCCESSFUL;
        }
        else
        {
#if DEBUG
            cout << "Passenger login failed" << endl;
#endif
            loginState = LOG_STATE_FAILED;
        }
        return loginState;
    }

    default:
        return LOG_STATE_FAILED;
    };
}

logState User::logout()
{
    switch (role)
    {
    case rolesTypes::ADMIN:
    {
        if (loginState == LOG_STATE_SUCCESSFUL)
        {
#if DEBUG
            cout << "admin logout succeed" << endl;
#endif
            logoutState = LOG_STATE_SUCCESSFUL;
        }
        else
        {
#if DEBUG
            cout << "admin logout failed" << endl;
#endif
            logoutState = LOG_STATE_FAILED;
        }
        return logoutState;
    }
    case rolesTypes::BOOKING_AGENT:
    {
        if (loginState == LOG_STATE_SUCCESSFUL)
        {
#if DEBUG
            cout << "BookingAgent logout succeed" << endl;
#endif
            logoutState = LOG_STATE_SUCCESSFUL;
        }
        else
        {
#if DEBUG
            cout << "BookingAgent logout failed" << endl;
#endif
            logoutState = LOG_STATE_FAILED;
        }
        return logoutState;
    }

    case rolesTypes::PASSENGER:
    {

        if (loginState == LOG_STATE_SUCCESSFUL)
        {
#if DEBUG
            cout << "Passenger logout succeed" << endl;
#endif
            logoutState = LOG_STATE_SUCCESSFUL;
        }
        else
        {
#if DEBUG
            cout << "Passenger logout failed" << endl;
#endif
            loginState = LOG_STATE_FAILED;
        }
        return loginState;
    }

    default:
        return LOG_STATE_FAILED;
    };
}

User::~User()
{
#if DEBUG
    cout << "Destructor of User is called" << endl;
#endif // 1
}

/********************************************************************/

Passenger::Passenger(const std::string &name, const std::string &pass, const rolesTypes &r)
{
    this->username = name;
    this->password = pass;
    this->role = r;

#if DEBUG
    cout << "Constructor of Passenger is called" << endl;
#endif
}

void Passenger::displayMenu()
{
    // Display passenger-specific menu options
    std::cout << ("1. Search Flights") << endl;
    std::cout << ("2. View Reservations") << endl;
    std::cout << ("3. Check-In") << endl;
    std::cout << ("4. Logout") << endl;
}

Passenger::~Passenger()
{
#if DEBUG
    cout << "Destructor of Passenger is called" << endl;
#endif // 1
}

/************************************************************************/

Administrator::Administrator(const std::string &name, const std::string &pass, const rolesTypes &r)
{
    this->username = name;
    this->password = pass;
    this->role = r;

#if DEBUG
    cout << "Constructor of Administrator is called" << endl;
#endif
}

void Administrator::mainDisplayMenu()
{
    // Display admin-specific menu options
    std::cout << "--- Administrator Menu ---\n";
    std::cout << ("1. Manage Flights") << endl;
    std::cout << ("2. Manage Aircraft") << endl;
    std::cout << ("3. Manage Users") << endl;
    std::cout << ("4. Generate Reports") << endl;
    std::cout << ("5. Logout") << endl;
    std::cout << "Enter choice: ";
}

/**************************Admin Flights*******************************************/
AssignedCrew Administrator::assignCrewToFlight(const std::string &flightNumber, json &pilots, json &flightAttendant)
{
    AssignedCrew crew;

    // Assign Pilot
    std::cout << "--- List of Pilots ---\n";
    for (auto &pilot : pilots["pilots"])
    {
        std::cout << "ID: " << pilot["ID"] << ", Name: " << pilot["name"]
                  << ", Status: " << pilot["status"] << "\n";
    }
    std::cout << "Select Pilot by ID (or type 'done' to skip): ";
    std::string pilotID;
    std::cin >> pilotID;

    if (pilotID != "done" && isPilotExists(pilots, pilotID))
    {
        crew.pilotID = pilotID; // Store the pilot ID
        std::cout << "Pilot " << pilotID << " assigned to flight.\n";
    }
    else
    {
        std::cout << "No pilot assigned.\n";
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

flightProcess Administrator::addFlight()
{
    std::string flightNumber, origin, destination, departureTime, arrivalTime, aircraftID;
    AssignedCrew ac;
    int s;
    flightStatus status;

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

    auto crew = Administrator::assignCrewToFlight(flightNumber, pilots, Flight_Attendant);

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

flightProcess Administrator::updateFlight()
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
        auto newCrew = Administrator::assignCrewToFlight(flightNumber, pilots, flightAttendant);

        flight["assignedCrew"]["pilotID"] = newCrew.pilotID;
        flight["assignedCrew"]["flightAttendantIDs"] = newCrew.flightAttendantIDs;

        std::cout << "Crew for flight " << flightNumber << " has been updated.\n";

        // Write the updated flights back to the file
        writeToDP(flightDP, flights);

        break;
    }

    case 3:
    {
        int newStatus;
        std::cout << "Enter New Status (Scheduled: 0 /Delayed: 1 /Canceled: 2): ";
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

flightProcess Administrator::deleteFlight()
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

    flights["flights"].erase(flights["flights"].begin()+index);
    std::cout << "Flight with number " << flightNumber << " has been successfully deleted.\n";

    // Write the updated data back to the file
    writeToDP(flightDP, flights);
    return FLIGHT_PROCESS_IS_SUCCESSFUL;
}

/****************************************************************************************/

/***********************Admin Air Crafts*************************************************/
aircraftProcess Administrator::addAircraft()
{
    std::string aircraftID, model, maintenanceSchedule;
    int a;
    bool availability;
    std::cout << "--- Add New Aircraft ---\n";
    std::cout << "Enter Aircraft ID: ";
    std::cin.ignore(); // Clear the input buffer
    std::getline(std::cin, aircraftID);
    std::cout << "Enter Model: ";
    std::getline(std::cin, model);
    std::cout << "Enter maintenanceSchedule Date (DD-MM-YYYY): ";
    std::getline(std::cin, maintenanceSchedule);

    std::cout << "Enter availability (0: Not Available, 1: Available): ";
    cin >> a;
    if (a == 0)
        availability = false;
    else if (a == 1)
        availability = true;
    else
    {
        return AIRCRAFT_PROCESS_IS_FAILED; // MAKE IT CATCH
        throw invalid_argument("Invalid Available State");
    }

    // Create a new aircraft object
    Aircraft newAircraft(aircraftID, model, maintenanceSchedule, availability);

    // read the database to add to it
    json aircrafts = readFromDP(AirCraftDB);

    // Create a JSON object for the new aircraft
    json newAircraftEntry = {
        {"aircraftID", aircraftID},
        {"model", model},
        {"maintenanceSchedule", maintenanceSchedule},
        {"availability", availability}};

    // add the new aircraft
    aircrafts["aircraft"].push_back(newAircraftEntry);
    // Write the updated flights back to the file
    writeToDP(AirCraftDB, aircrafts);
    std::cout << "Aircraft ID " << aircraftID << " has been successfully added to DB.\n";

    return AIRCRAFT_PROCESS_IS_SUCCESSFUL;
}

aircraftProcess Administrator::updateAircraft()
{
    int choice;
    aircraftProcess ap = AIRCRAFT_PROCESS_IS_NULL;
    std::string aircraftId;
    std::cout << "--- Update Aircraft ---\n";
    std::cout << "Enter Flight Number to Update: ";
    std::cin.ignore(); // Clear the input buffer

    std::getline(std::cin, aircraftId);
    json aircrafts = readFromDP(AirCraftDB);
    int index = isAircraftExist(aircrafts, aircraftId);
    if (index == -1)
    {
        std::cout << "Error: Aircraft " << aircraftId << " does not exist.\n";
        ap = AIRCRAFT_PROCESS_IS_FAILED;
        return ap;
    }

    std::cout << " --- Updating Existing aircraft ---" << std::endl;
    std::cout << "Select information to update:" << std::endl;
    std::cout << "1. Aircraft ID" << std::endl;
    std::cout << "2. Aircraft Availability" << std::endl;
    std::cout << "3. Aircraft Maintenance Schedule" << std::endl;
    std::cout << "4. Aircraft Model" << std::endl;
    std::cout << "5. Back to Manage Flights" << std::endl;
    std::cout << "Enter choice: ";
    cin >> choice;

    // Access the aircraft using the index
    json &aircraft = aircrafts["aircraft"][index];

    switch (choice)
    {
    case 1:
    {
        std::string newID;

        std::cout << "Enter new Aircraft ID: ";
        std::cin.ignore();
        std::getline(cin, newID);
        aircraft["aircraftID"] = newID;
        break;
    }
    case 2:
    {
        int availability;
        bool ava;
        std::cout << "Enter new Aircraft availability (0: false, 1: true) ";
        cin >> availability;

        if (availability == 0)
            aircraft["availability"] = false;
        else
            aircraft["availability"] = true;

        break;
    }
    case 3:
    {
        std::string newMaintenanceSchedule;

        std::cout << "Enter new Aircraft Maintenance Schedule(DD-MM-YYYY): ";
        std::cin.ignore();
        std::getline(cin, newMaintenanceSchedule);
        aircraft["maintenanceSchedule"] = newMaintenanceSchedule;
        break;
    }
    case 4:
    {
        std::string newModel;

        std::cout << "Enter new Aircraft Model: ";
        std::cin.ignore();
        std::getline(cin, newModel);
        aircraft["model"] = newModel;
        break;
    }
    default:
        throw invalid_argument("incorrect choice");
    }
    // Write the updated data back to the file
    writeToDP(AirCraftDB, aircrafts);
    std::cout << "Aircraft " << aircraftId << " has been successfully updated.\n";
    ap = AIRCRAFT_PROCESS_IS_SUCCESSFUL;

    return ap;
}

aircraftProcess Administrator::removeAircraft()
{
    int choice;
    aircraftProcess ap = AIRCRAFT_PROCESS_IS_FAILED;
    std::string aircraftID;
    std::cout << "--- Delete Aircraft ---\n";
    std::cin.ignore(); // Clear the input buffer
    std::cout << "Enter Flight Number to Delete: ";
    std::getline(std::cin, aircraftID);

    // Read existing flights from the file
    json aircrafts = readFromDP(AirCraftDB);
    int index = isAircraftExist(aircrafts, aircraftID);
    if (index == -1)
    {
        std::cout << "Error: Aircraft " << aircraftID << " does not exist.\n";
        ap = AIRCRAFT_PROCESS_IS_FAILED;
        return ap;
    }

    json &aircraft = aircrafts["aircraft"][index];

    // Remove the aircraft at the found index
    aircrafts["aircraft"].erase(aircrafts["aircraft"].begin() + index);
    std::cout << "Aircraft with ID " << aircraftID << " has been successfully deleted.\n";

    // Write the updated data back to the file
    writeToDP(AirCraftDB, aircrafts);
    return AIRCRAFT_PROCESS_IS_SUCCESSFUL;
}

void Administrator::assignAircraftToFlight()
{
}

void Administrator::scheduleMaintenance()
{
}

bool Administrator::checkAvailability()
{
    return true;
}

/*********************************************************************************/

Administrator::~Administrator()
{
#if DEBUG
    cout << "Destructor of Administrator is called" << endl;
#endif // 1
}

/************************************************************************/

BookingAgent::BookingAgent(const std::string &name, const std::string &pass, const rolesTypes &r)
{
    this->username = name;
    this->password = pass;
    this->role = r;

#if DEBUG
    cout << "Constructor of BookingAgent is called" << endl;
#endif
}

void BookingAgent::displayMenu()
{
    // Display booking agent-specific menu options
    std::cout << ("1. Book a Flight") << endl;
    std::cout << ("2. Modify Reservation") << endl;
    std::cout << ("3. Cancel Reservation") << endl;
    std::cout << ("4. Logout") << endl;
}

BookingAgent::~BookingAgent()
{
#if DEBUG
    cout << "Destructor of BookingAgent is called" << endl;
#endif // 1
}

/*****************************************************************/

std::unique_ptr<User> userFactory::createUser(const std::string &name, const std::string &pass, const rolesTypes &role)
{
    switch (role)
    {
    case rolesTypes::ADMIN:
        return std::make_unique<Administrator>(name, pass, role);
    case rolesTypes::BOOKING_AGENT:
        return std::make_unique<BookingAgent>(name, pass, role);
    case rolesTypes::PASSENGER:
        return std::make_unique<Passenger>(name, pass, role);
    default:
        throw std::invalid_argument("Invalid role type");
        ;
    }
}