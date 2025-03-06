#ifndef __RESERVATION_H__
#define __RESERVATION_H__

#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum reservationState
{
    CREATED_RESERVATION,
    EXISTED_RESERVATION,
    MODIFIED_RESERVATION,
    CANCELED_RESERVATION
};

class Reservation
{
    private:
    std::string reservationID;
    std::string flightNumber;
    std::string passengerID; 
    std::string seatNumber; 
    std::string status;
    public:
    Reservation();
    reservationState createReservation();
    reservationState modifyReservation();
    reservationState cancelReservation();
};
#endif // __RESERVATION_H__