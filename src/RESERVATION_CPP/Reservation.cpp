#include "../../include/RESERVATION_HPP/Reservation.hpp"

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

reservationState Reservation::modifyReservation(const std::string &reservationID)
{
    /*serach in the container for the reservation id*/

    /*edit in the container */

    return MODIFY_RESERVATION;
}

reservationState Reservation::cancelReservation(const std::string &reservationID)
{
    /*serach in the container for the reservation id*/

    /*delete the reservation from the container */

    return CANCEL_RESERVATION;
}
