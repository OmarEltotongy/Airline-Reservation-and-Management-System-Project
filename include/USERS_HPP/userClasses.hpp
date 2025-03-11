#ifndef __USERCLASSES_H__
#define __USERCLASSES_H__

#include "../RESERVATION_HPP/Reservation.hpp"
#include "../JSON_HPP/jsonHelperFunctions.hpp"
#include "../ENUMS/flights_enum.hpp"
#include "../ENUMS/user_enums.hpp"
#include "../ENUMS/aircraft_enums.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>
using namespace std;

// Forward declaration and Externs
class Flight;
class Aircraft;
extern std::string flightDP;
extern std::string UserDP;
extern std::string flightDP;
extern std::string pilotDP;
extern std::string flightAttendantDB;
extern std::string AirCraftDB;

#define DEBUG 1

class User
{
protected:
    std::string username;
    std::string password;
    rolesTypes role;

    enum logState loginState;
    enum logState logoutState;

public:
    User(const std::string &name = " ", const std::string &pass = " ", const rolesTypes &r = rolesTypes::PASSENGER);
    bool validateCredentials(const std::string &username, const std::string &password, const rolesTypes &role);
    logState login();
    logState logout();
    std::string getName();
    // virtual void displayMenu() = 0 ; //pure virtual function

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
    static void displayMenu();
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
    static void displayMenu(); // if pure virtual function is used, must have prototype in inhereted too

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
    static void mainDisplayMenu();
    void generateReports();

    ~Administrator();
};

/****************************************************************************/

class userFactory
{
public:
    std::unique_ptr<User> createUser(const std::string &name, const std::string &pass, const rolesTypes &role);
};

std::string roleToString(rolesTypes role);
#endif // __USERCLASSES_H__
