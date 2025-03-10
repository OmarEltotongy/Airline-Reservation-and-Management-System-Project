#include "../../include/AIRCRAFT_HPP/Aircraft.hpp"
#include <iomanip> // For std::setw, std::left, etc.

Aircraft::Aircraft(const std::string &ACID, const std::string &m, const std::string &MS, const bool &AVA)
    : aircraftID(ACID), model(m), maintenanceSchedule(MS), availability(AVA)
{
#if DEBUG
    cout << "Constructor of Aircraft is called" << endl;
#endif
}
void Aircraft::ManageAircraftMenu(const std::string &username, const std::string &password, const rolesTypes &r)
{
    Administrator admin(username, password, r);
    int choice;
    std::cout << "--- Manage Air Crafts ---\n";
    std::cout << "1. View All Aircraft\n";
    std::cout << "2. Search Aircraft\n";
    std::cout << "3. Add New Aircraft\n";
    std::cout << "4. Update Aircraft Information\n";
    std::cout << "5. Remove Aircraft\n";
    std::cout << "6. Assign Aircraft to Flight\n";
    std::cout << "7. Schedule Maintenance\n";
    std::cout << "8. Check Availability\n";
    std::cout << "9. Back to Main Menu\n";
    std::cout << "Enter choice: ";
    std::cin >> choice;

    switch (choice)
    {
    case 1:
        Aircraft::viewAllAircraft();

        break;
    case 2:
        admin.searchAircraft();

        break;
    case 3:
        admin.addAircraft();

        break;
    case 4:
        admin.updateAircraft();

        break;
    case 5:
        admin.removeAircraft();
        break;
    case 6:
        admin.assignAircraftToFlight();

        break;
    case 7:
        admin.scheduleMaintenance();

        break;
    case 8:
        admin.checkAvailability();

        break;
    case 9:
        return; // Go back to the main menu
        break;
    default:
        std::cout << "Invalid choice. Please try again.\n";
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
        std::cout << "| "
                  << std::left << std::setw(10) << aircraft["aircraftID"].get<std::string>() << "  | "
                  << std::left << std::setw(17) << aircraft["model"].get<std::string>() << " | "
                  << std::left << std::setw(19) << aircraft["maintenanceSchedule"].get<std::string>() << "  | "
                  << std::left << std::setw(20) << aircraft["availability"].get<bool>() << "|\n";

        std::cout << "\n";
        std::cout << "+-------------+------------------+-----------------------+----------------------+\n";
    }
}

Aircraft::~Aircraft()
{
#if DEBUG
    cout << "Deconstructor of Aircraft is called" << endl;
#endif
}