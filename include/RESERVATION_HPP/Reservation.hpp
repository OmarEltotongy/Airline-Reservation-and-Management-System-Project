#ifndef __RESERVATION_H__
#define __RESERVATION_H__

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define DEBUG 1

enum reservationState
{
    CREAT_RESERVATION,
    EXIST_RESERVATION,
    MODIFY_RESERVATION,
    CANCEL_RESERVATION
};

class Reservation
{
private:
    std::string reservationID;
    std::string flightNumber;
    std::string passengerID;
    std::string seatNumber;
    reservationState status;

public:
    Reservation(const reservationState &st = CREAT_RESERVATION);
    reservationState createReservation( const std::string &reservationID = " ",
                                        const std::string &flightNumber = " ",
                                        const std::string &passengerID = " ",
                                        const std::string &seatNumber = " ");

    reservationState modifyReservation(const std::string &reservationID = " ");
    reservationState cancelReservation(const std::string &reservationID = " ");
};

#endif // __RESERVATION_H__