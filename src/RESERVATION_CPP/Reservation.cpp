#include "../../include/RESERVATION_HPP/Reservation.hpp"
std::string reservationDB = "data/reservation.json";

Reservation::Reservation(const reservationState &st)
{
    this->status = st;
#if DEBUG
    cout << "Constructor of Reservation is called" << endl;
#endif
}

reservationState Reservation::createReservation(const std::string &rID,
                                                const std::string &fn,
                                                const std::string &pID,
                                                const std::string &sn)
{
    this->reservationID = rID;
    this->flightNumber = fn;
    this->passengerID = pID;
    this->seatNumber = sn;
    /*Push the reservation in container*/

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
            std::cout << "Reservation NO " << i << " :" << std::endl;
            // print the Reservation data
            std::cout << "Flight Number: " << (reservations["reservations"][i]["flightNumber"]) << std::endl;
            std::cout << "Reservation ID: " << (reservations["reservations"][i]["reservationID"]) << std::endl;
            std::cout << "Passenger ID: " << (reservations["reservations"][i]["passengerID"]) << std::endl;
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
