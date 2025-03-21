#include "../../include/RESERVATION_HPP/Reservation.hpp"
std::string reservationDP = "data/reservation.json";
std::string flightDP_R = "data/flights.json";

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
    json reservations = readFromDP(reservationDP);

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
    // Read reservations from the file
    json reservations = readFromDP(reservationDP);

    // Find the most recent reservation for the passenger
    json *mostRecentReservation = nullptr;
    std::string mostRecentDepartureTime;
    for (auto &res : reservations["reservations"])
    {
        if (res["passengerID"] == passID)
        {
            // Check if this reservation is more recent than the current most recent
            if (mostRecentReservation == nullptr || res["departureTime"] > mostRecentDepartureTime)
            {
                mostRecentReservation = &res;
                mostRecentDepartureTime = res["departureTime"];
            }
        }
    }

    if (mostRecentReservation == nullptr)
    {
        std::cout << "Error: No reservations found for passenger ID " << passID << ".\n";
        return MODIFY_RESERVATION;
    }

    // Display current reservation details
    std::cout << "\nMost Recent Reservation Details:\n";
    std::cout << "Reservation ID: " << (*mostRecentReservation)["reservationID"] << "\n";
    std::cout << "Flight: " << (*mostRecentReservation)["flightNumber"] << "\n";
    std::cout << "Seat: " << (*mostRecentReservation)["seatNumber"] << "\n";
    std::cout << "Origin: " << (*mostRecentReservation)["origin"] << "\n";
    std::cout << "Destination: " << (*mostRecentReservation)["destination"] << "\n";
    std::cout << "Departure: " << (*mostRecentReservation)["departureTime"] << "\n";

    // Prompt for new seat number
    std::string newSeatNumber;
    std::cout << "\nEnter New Seat Number (or press Enter to keep current): ";
    std::cin.ignore(); // Clear the input buffer
    std::getline(std::cin, newSeatNumber);

    if (!newSeatNumber.empty())
    {
        (*mostRecentReservation)["seatNumber"] = newSeatNumber;
    }

    // Write the updated reservations back to the file
    writeToDP(reservationDP, reservations);
    std::cout << "Most recent reservation for passenger ID " << passID << " has been successfully modified.\n";

    return MODIFY_RESERVATION;
}

reservationState Reservation::cancelReservation(const std::string &passID)
{
    // Read reservations and flights from their files
    json reservations = readFromDP(reservationDP);
    json flights = readFromDP(flightDP_R);

    // Find the most recent reservation for the passenger
    json *mostRecentReservation = nullptr;
    std::string mostRecentDepartureTime;
    size_t mostRecentIndex = 0;
    for (size_t i = 0; i < reservations["reservations"].size(); ++i)
    {
        if (reservations["reservations"][i]["passengerID"] == passID)
        {
            // Check if this reservation is more recent than the current most recent
            if (mostRecentReservation == nullptr || reservations["reservations"][i]["departureTime"] > mostRecentDepartureTime)
            {
                mostRecentReservation = &reservations["reservations"][i];
                mostRecentDepartureTime = reservations["reservations"][i]["departureTime"];
                mostRecentIndex = i;
            }
        }
    }

    if (mostRecentReservation == nullptr)
    {
        std::cout << "Error: No reservations found for passenger ID " << passID << ".\n";
        return CANCEL_RESERVATION;
    }

    // Fetch flight number from the reservation
    std::string flightNumber = (*mostRecentReservation)["flightNumber"];

    // Find the flight and increment available seats
    for (auto &flight : flights["flights"])
    {
        if (flight["flightNumber"] == flightNumber)
        {
            flight["availableSeats"] = flight["availableSeats"].get<int>() + 1;
            break;
        }
    }

    // Remove the most recent reservation
    reservations["reservations"].erase(reservations["reservations"].begin() + mostRecentIndex);

    // Write the updated data back to the files
    writeToDP(reservationDP, reservations);
    writeToDP(flightDP_R, flights);

    std::cout << "Most recent reservation for passenger ID " << passID << " has been successfully canceled.\n";

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
