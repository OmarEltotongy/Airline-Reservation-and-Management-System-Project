#include "../../include/AIRCRAFT_HPP/AirCraft.hpp"

AirCraft::AirCraft(const std::string &ACID, const std::string &m, const std::string &MS, const bool &AVA)
    : aircraftID(ACID), model(m), maintenanceSchedule(MS), availability(AVA)
{
#if DEBUG
    cout << "Constructor of Aircraft is called" << endl;
#endif
}
void AirCraft::ManageAirCraftMenu(const std::string &username, const std::string &password, const rolesTypes &r)
{
    Administrator admin(username, password, r);
    int choice;
    std::cout << "--- Manage Air Crafts ---\n";
    std::cout << "1. Assign Aircraft to Flight\n";
    std::cout << "2. Schedule Maintenance\n";
    std::cout << "3. Check Availability\n";
    std::cout << "4. Add New Aircraft\n";
    std::cout << "5. Remove Aircraft\n";
    std::cout << "6. Update Aircraft Information\n";
    std::cout << "7. View All Aircraft\n";
    std::cout << "8. Search Aircraft\n";
    std::cout << "9. Back to Main Menu\n";
    std::cout << "Enter choice: ";
    std::cin >> choice;

    switch (choice)
    {
    case 1:
        admin.assignAircraftToFlight();

        break;
    case 2:
        admin.scheduleMaintenance();

        break;
    case 3:
        admin.checkAvailability();

        break;
    case 4:
        admin.addAircraft();

        break;
    case 5:
        admin.removeAircraft();
        break;
    case 6:
        admin.updateAircraft();
        break;
    case 7:
        AirCraft::viewAllAircraft();

        break;
    case 8:
        admin.searchAircraft();
        break;
    case 9:
        return; // Go back to the main menu
        break;
    default:
        std::cout << "Invalid choice. Please try again.\n";
    }
}

void AirCraft::viewAllAircraft() // Schedules maintenance for the aircraft.
{
}

AirCraft::~AirCraft()
{
#if DEBUG
    cout << "Deconstructor of Aircraft is called" << endl;
#endif
}