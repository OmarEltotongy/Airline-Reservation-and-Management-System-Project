#include "../../include/RESERVATION_HPP/Reservation.hpp"
std::string reservationDB = "data/reservation.json";

Reservation::Reservation(const reservationState &st)
{
    this->status = st;
#if DEBUG
    cout << "Constructor of Reservation is called" << endl;
#endif
}

reservationState Reservation::createReservation(const std::string &reservationID, const std::string &flightNumber,
    const std::string &passengerID,
    const std::string &seatNumber,
    const std::string &origin,
    const std::string &destination,
    const std::string &departureTime)
{
    this->reservationID = reservationID;
    this->flightNumber = flightNumber;
    this->passengerID =passengerID;
    this->seatNumber =seatNumber;
    this->origin = origin;
    this -> destination = destination;
    this->departureTime = departureTime;

    /*Push the reservation in DB*/

    return CREAT_RESERVATION;
}

reservationState Reservation::viewReservation(const std::string& passID)
{
    json reservations = readFromDP(reservationDB);

    // Iterate through the reservations
    for (auto i = 0; i < reservations["reservations"].size(); ++i)
    {
        if (reservations["reservations"][i]["passengerID"] == passID)
        {
            std::cout << "Reservation ID: " << (reservations["reservations"][i]["reservationID"]) << std::endl;
            // print the Reservation data
            std::cout << "Flight " << (reservations["reservations"][i]["flightNumber"]) 
            << " From " << reservations["reservations"][i]["origin"] << " To " <<
            reservations["reservations"][i]["destination"] <<std::endl;
            std::cout << "Departure: " << (reservations["reservations"][i]["departureTime"]) << std::endl;
            std::cout << "Seat Number: " << (reservations["reservations"][i]["seatNumber"]) << std::endl;
            std::cout << "Status: " << (reservations["reservations"][i]["status"]) << std::endl;
        }
    }

    return EXIST_RESERVATION;

}

reservationState Reservation::modifyReservation(const std::string &passID)
{
    /*serach in the container for the reservation id*/

    /*edit in the container */

    return MODIFY_RESERVATION;
}

reservationState Reservation::cancelReservation(const std::string &passID)
{
    /*serach in the container for the reservation id*/

    /*delete the reservation from the container */

    return CANCEL_RESERVATION;
}

json Reservation::toJson() const
{
    return {
        {"reservationID", reservationID},
        {"flightNumber", flightNumber},
        {"passengerID", passengerID},
        {"seatNumber", seatNumber},
        {"origin", origin},
        {"destination", destination},
        {"departureTime", departureTime}
    };
}
