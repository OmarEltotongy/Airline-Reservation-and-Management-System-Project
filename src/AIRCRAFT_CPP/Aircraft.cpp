#include "../../include/AIRCRAFT_HPP/Aircraft.hpp"
#include <iomanip> // For std::setw, std::left, etc.

Aircraft::Aircraft(const std::string &ACID, const std::string &m, const std::string &MS, const bool &AVA)
    : aircraftID(ACID), model(m), maintenanceSchedule(MS), availability(AVA)
{
#if DEBUG
    cout << "Constructor of Aircraft is called" << endl;
#endif
}
Aircraft::Aircraft(Administrator &admin)
{
    cout << "Edits will be done with Admin: " << admin.getName() << endl;
}

json Aircraft::toJson() const
{
    return {
        {"aircraftID", aircraftID},
        {"availability", availability},
        {"maintenanceSchedule", maintenanceSchedule},
        {"model", model},
    };
}

void Aircraft::ManageAircraftMenu(Administrator &Admin)
{
    Aircraft AircraftAdmin(Admin);
    int choice;
    while (true)
    {
        std::cout << "--- Manage Air Crafts ---\n";
        std::cout << "1. View All Aircraft\n";
        std::cout << "2. Add New Aircraft\n";
        std::cout << "3. Update Aircraft Information\n";
        std::cout << "4. Remove Aircraft\n";
        std::cout << "5. Assign Aircraft to Flight\n";
        std::cout << "6. Schedule Maintenance\n";
        std::cout << "7. Check Availability\n";
        std::cout << "8. Back to Main Menu\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            AircraftAdmin.viewAllAircraft();

            break;
        case 2:
            AircraftAdmin.addAircraft();

            break;
        case 3:
            AircraftAdmin.updateAircraft();

            break;
        case 4:
            AircraftAdmin.removeAircraft();
            break;
        case 5:
            AircraftAdmin.assignAircraftToFlight();

            break;
        case 6:
            AircraftAdmin.scheduleMaintenance();

            break;
        case 7:
            AircraftAdmin.checkAvailability();

            break;
        case 8:
            return; // Go back to the main menu
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void Aircraft::viewAllAircraft() // Schedules maintenance for the aircraft.
{
    json aircrafts = readFromDP(AirCraftDB);

    if (aircrafts["aircraft"].empty())
    {
        std::cout << "No aircraft found in the database.\n";
        return;
    }

    // print header
    std::cout << "\n--- List of Aircrafts ---\n";
    std::cout << "+-------------+------------------+-----------------------+---------------------+\n";
    std::cout << "| Aircraft ID | Model            | Maintenance Schedule  | Availability        | \n";
    std::cout << "+-------------+------------------+-----------------------+---------------------+\n";

    // print each aircraft's data
    for (const auto &aircraft : aircrafts["aircraft"])
    {
        std::string availability = aircraft["availability"].get<bool>() ? "true" : "false";
        std::cout << "| "
                  << std::left << std::setw(10) << aircraft["aircraftID"].get<std::string>() << "  | "
                  << std::left << std::setw(17) << aircraft["model"].get<std::string>() << " | "
                  << std::left << std::setw(19) << aircraft["maintenanceSchedule"].get<std::string>() << "  | "
                  << std::left << std::setw(20) << availability << "|\n";

        std::cout << "\n";
        std::cout << "+-------------+------------------+-----------------------+----------------------+\n";
    }
}
/***********************Admin Air Crafts*************************************************/
aircraftProcess Aircraft::addAircraft()
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

    json newAircraftEntry = newAircraft.toJson();
    json aircrafts = readFromDP(AirCraftDB);

    // add the new aircraft
    aircrafts["aircraft"].push_back(newAircraftEntry);
    // Write the updated flights back to the file
    writeToDP(AirCraftDB, aircrafts);
    std::cout << "Aircraft ID " << aircraftID << " has been successfully added to DB.\n";

    return AIRCRAFT_PROCESS_IS_SUCCESSFUL;
}

aircraftProcess Aircraft::updateAircraft()
{
    int choice;
    aircraftProcess ap = AIRCRAFT_PROCESS_IS_NULL;
    std::string aircraftId;
    std::cout << "--- Update Aircraft ---\n";
    std::cout << "Enter Aircraft ID to Update: ";
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

aircraftProcess Aircraft::removeAircraft()
{
    int choice;
    aircraftProcess ap = AIRCRAFT_PROCESS_IS_FAILED;
    std::string aircraftID;
    std::cout << "--- Remove Aircraft Assignment ---\n";
    std::cin.ignore(); // Clear the input buffer
    std::cout << "Enter Aircraft ID to Remove Assignment: ";
    std::getline(std::cin, aircraftID);

    // Read existing aircraft and flights from their files
    json aircrafts = readFromDP(AirCraftDB);
    json flights = readFromDP(flightDP);

    int index = isAircraftExist(aircrafts, aircraftID);

    // Check if the aircraft exists
    if (index == -1)
    {
        std::cout << "Error: Aircraft " << aircraftID << " does not exist.\n";
        ap = AIRCRAFT_PROCESS_IS_FAILED;
        return ap;
    }

    json &aircraft = aircrafts["aircraft"][index];

    // Check if the aircraft is assigned to a flight
    if (!aircraft["assignedFlight"].empty())
    {
        std::string assignedFlight = aircraft["assignedFlight"];
        std::cout << "Aircraft " << aircraftID << " is assigned to flight " << assignedFlight << ".\n";

        // Update the aircraft's availability and clear the assigned flight
        aircraft["availability"] = true;
        aircraft["assignedFlight"] = "";

        // Find and update the corresponding flight
        for (auto &flight : flights["flights"])
        {
            if (flight["flightNumber"] == assignedFlight)
            {
                flight["aircraftID"]=""; // Remove the aircraftID field from the flight
                std::cout << "Aircraft ID removed from flight " << assignedFlight << ".\n";
                break;
            }
        }

        // Notify the user
        std::cout << "Aircraft " << aircraftID << " is now available and no longer assigned to any flight.\n";
    }
    else
    {
        std::cout << "Aircraft " << aircraftID << " is not assigned to any flight.\n";
    }

    // Write the updated data back to the files
    writeToDP(AirCraftDB, aircrafts);
    writeToDP(flightDP, flights);

    ap = AIRCRAFT_PROCESS_IS_SUCCESSFUL;
    return ap;
}
aircraftProcess Aircraft::assignAircraftToFlight()
{
    int choice;
    aircraftProcess aircraft_state = AIRCRAFT_PROCESS_IS_NULL;
    std::string flightNumber;
    std::cout << "--- Assign Aircraft for a flight ---\n";
    std::cout << "Enter Flight Number to assign: ";
    std::cin.ignore(); // Clear the input buffer

    std::getline(std::cin, flightNumber);

    // Read existing flights from the file
    json flights = readFromDP(flightDP);
    json aircrafts = readFromDP(AirCraftDB);

    int index = isFlightExists(flights, flightNumber);
    if (index == -1)
    {
        std::cout << "Error: Flight " << flightNumber << " does not exist.\n";
        aircraft_state = AIRCRAFT_PROCESS_IS_NULL;
        return aircraft_state;
    }
    json &flight = flights["flights"][index];

    std::cout << " --- Updating Existing Flight With New Aircraft ---" << std::endl;
    std::cout << "Please Enter the  Aircraft ID: ";
    std::string newAircraftID;
    std::getline(std::cin, newAircraftID);

    int index_AC = isAircraftExist(aircrafts, newAircraftID);
    if (index_AC == -1)
    {
        std::cout << "Error: Aircraft " << newAircraftID << " does not exist.\n";
        aircraft_state = AIRCRAFT_PROCESS_IS_NULL;
        return aircraft_state;
    }
    json &aircraft = aircrafts["aircraft"][index_AC];

    if (aircraft["availability"] == false)
    {
        std::cout << "Error: Aircraft " << newAircraftID << " is not available.\n";
        aircraft_state = AIRCRAFT_PROCESS_IS_NULL;
        return aircraft_state;
    }

    flight["aircraftID"] = aircraft["aircraftID"];
    aircraft["availability"] = false;
    // Write the updated data back to the file
    writeToDP(flightDP, flights);
    writeToDP(AirCraftDB, aircrafts);
    std::cout << "Flight " << flightNumber << " has been successfully updated.\n";
    aircraft_state = AIRCRAFT_PROCESS_IS_SUCCESSFUL;

    return aircraft_state;
}

aircraftProcess Aircraft::scheduleMaintenance()
{
    int choice;
    aircraftProcess ap = AIRCRAFT_PROCESS_IS_NULL;
    std::string aircraftId;
    std::cout << "--- Update Aircraft ---\n";
    std::cout << "Enter Aircraft ID to Schedule a Maintenance Date: ";
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
    json &aircraft = aircrafts["aircraft"][index];
    std::string maintenanceDate;
    std::cout << " --- Updating Existing aircraft ---" << std::endl;
    std::cout << "Enter a Maintenance Date(DD-MM-YYYY): ";
    std::getline(std::cin, maintenanceDate);

    aircraft["maintenanceSchedule"] = maintenanceDate;

    writeToDP(AirCraftDB, aircrafts);

    ap = AIRCRAFT_PROCESS_IS_SUCCESSFUL;
    return ap;
}

bool Aircraft::checkAvailability()
{
    int choice;
    aircraftProcess ap = AIRCRAFT_PROCESS_IS_NULL;
    std::string aircraftId;
    std::cout << "--- Update Aircraft ---\n";
    std::cout << "Enter Aircraft ID to Check avaliablity: ";
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
    json &aircraft = aircrafts["aircraft"][index];
    if (aircraft["availability"] == true)
    {
        std::cout << "The Aircraft is Available!" << std::endl;
        return true;
    }
    else
    {
        std::cout << "The Aircraft is not Available!" << std::endl;

        return false;
    }
}

Aircraft::~Aircraft()
{
#if DEBUG
    cout << "Deconstructor of Aircraft is called" << endl;
#endif
}