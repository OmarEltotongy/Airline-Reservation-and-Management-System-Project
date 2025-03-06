#include "../../include/AIRCRAFT_HPP/Aircraft.hpp"

Aircraft::Aircraft(const std::string &ACID, const std::string &m, const std::string &MS, const bool &AVA)
: aircraftID(ACID), model(m), maintenanceSchedule(MS),availability(AVA)
{
#if DEBUG
    cout << "Constructor of Aircraft is called" << endl;
#endif
}
void Aircraft::scheduleMaintenance() // Schedules maintenance for the aircraft.
{
}
bool Aircraft::checkAvailability() // Checks if the aircraft is available.
{
    return true;
}
Aircraft::~Aircraft()
{
#if DEBUG
    cout << "Deconstructor of Aircraft is called" << endl;
#endif
}