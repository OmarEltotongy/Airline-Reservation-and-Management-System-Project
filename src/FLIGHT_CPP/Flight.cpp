#include "../../include/FLIGHT_HPP/Flight.hpp"

Flight::Flight(const std::string &FN, const std::string &origin, const std::string &destination,
               const std::string &DT, const std::string &AT, const flightStatus &FS,
               const std::string &ACID)
    : flightNumber(FN), departureLocation(origin), arrivalLocation(destination),
      departureTime(DT), arrivalTime(AT), status(FS), aircraftID(ACID)
{
#if DEBUG
    cout << "Constructor of Flight is called" << endl;
#endif
}

flightProcess Flight::addFlight()
{
    return FLIGHT_PROCESS_IS_SUCCESSFUL;
}
flightProcess Flight::updateFlight()
{
    return FLIGHT_PROCESS_IS_SUCCESSFUL;
}
flightProcess Flight::deleteFlight()
{
    return FLIGHT_PROCESS_IS_SUCCESSFUL;
}

Flight::~Flight()
{
#if DEBUG
    cout << "Deconstructor of Flight is called" << endl;
#endif
}