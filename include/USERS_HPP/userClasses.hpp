#ifndef __USERCLASSES_H__
#define __USERCLASSES_H__

#include <iostream>
#include <vector>
#include <string>
#include "../../include/FLIGHT_HPP/Flight.hpp"
#include "../../include/RESERVATION_HPP/Reservation.hpp"
#include <map>

using namespace std;

#define DEBUG 1
enum infoState
{
    INFO_STATE_SUCCESSFUL,
    INFO_STATE_FAILED
};

enum rolesTypes
{
    ADMIN,
    BOOKING_AGENT,
    PASSENGER
};

enum logState
{
    LOG_STATE_SUCCESSFUL,
    LOG_STATE_FAILED
};

class User
{
protected:
    std::string username;
    std::string password;
    enum rolesTypes role;

    enum logState loginState;
    enum logState logoutState;

public:
    User(const std::string &name = " ", const std::string &pass = " ", const rolesTypes &r = PASSENGER);
    logState login();
    logState logout();
    virtual void displayMenu() = 0; // Pure virtual function for role-specific menus

    virtual ~User();
};

/*************************************************************************/
class Passenger : public User
{
private:
    std::string passengerID;
    std::string contactInfo;
    std::map<std::string, std::string> travelHistory; // place, date
    int loyaltyPoints;                                // counter

public:
    Passenger(const std::string &name, const std::string &pass, const rolesTypes &r);
    void displayMenu() override;
    void searchFlight();
    void viewReservation();
    void checkIn();
    ~Passenger();
};

/*************************************************************************/
class BookingAgent : public User
{
private:
    std::string agentID;
    std::vector<Flight> assignedFlights;
    std::vector<Reservation> reservationsHandled; // A list of reservations handled by the booking agent
public:
    BookingAgent(const std::string &name, const std::string &pass, const rolesTypes &r);
    void displayMenu() override; // if pure virtual function is used, must have prototype in inhereted too

    void bookFlight();
    void modifyReservation();
    void cancelReservation();
    void viewAssignedFlights(); // Displays flights assigned to the booking agent.
    void viewReservations();    // Displays all reservations handled by the booking agent.
    ~BookingAgent();
};

/***************************************************************************/
class Administrator : public User
{
private:
    std::string adminId;
    std::vector<Flight> managedFlights;
    std::vector<User> managedUsers;

public:
    Administrator(const std::string &name, const std::string &pass, const rolesTypes &r);
    void displayMenu() override;
    void addFlight();
    void updateFlight();
    void assignCrew();
    void generateReports();

    ~Administrator();
};

/****************************************************************************/

class userFactory
{
public:
    std::unique_ptr<User> createUser(const std::string &name, const std::string &pass, const rolesTypes &role);
};

#endif // __USERCLASSES_H__
