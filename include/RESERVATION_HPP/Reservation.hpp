#ifndef __RESERVATION_H__
#define __RESERVATION_H__

#include <iostream>
#include <vector>
#include <string>
#include "../JSON_HPP/jsonHelperFunctions.hpp"

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
    std::string origin;
    std::string destination;
    std::string departureTime;

public:
    Reservation(const reservationState &st = CREAT_RESERVATION);
    reservationState createReservation(const std::string &reservationID = " ",
                                       const std::string &flightNumber = " ",
                                       const std::string &passengerID = " ",
                                       const std::string &seatNumber = " ",
                                       const std::string &origin =" ",
                                       const std::string &destination= " ",
                                       const std::string &departureTime = " ");

    reservationState viewReservation(const std::string &passID = "");
    reservationState modifyReservation(const std::string &passID = " ");
    reservationState cancelReservation(const std::string &passID = " ");
    json toJson() const; // Method to convert Reservation object to JSON

};

#endif // __RESERVATION_H__