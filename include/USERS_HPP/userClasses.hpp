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
    virtual json toJson() const = 0; // pure virtual function
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
    double wallet;                                    // wallet balance
    std::map<std::string, std::string> creditCard;    // credit card details
    std::string paypalAccount;                        // PayPal account

public:
    Passenger(const std::string &name, const std::string &pass, const rolesTypes &r,
              const std::string &contactInfo, int &loyaltyPoints, const std::string &id,
              double wallet, const std::map<std::string, std::string> &creditCard,
              const std::string &paypalAccount);
    static void displayMenu();
    virtual json toJson() const;
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
    BookingAgent(const std::string &name, const std::string &pass, const rolesTypes &r,
                 const std::string &contactinfo = "", int loyaltyPoints = 0, const std::string &id = "");
    static void displayMenu(BookingAgent &agent); // if pure virtual function is used, must have prototype in inhereted too
    virtual json toJson() const;

    void searchFlight();
    void modifyReservation();
    void cancelReservation();

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
    Administrator(const std::string &name, const std::string &pass, const rolesTypes &r,
                  const std::string &contactinfo = "", int loyaltyPoints = 0, const std::string &id = "");
    static void mainDisplayMenu();
    static void mangeUsersMenu(Administrator &admin);
    /*****************************Users Functions****************************/
    virtual json toJson() const;
    userState viewAllUsers();
    userState addNewUser();
    userState updateUserInfo();
    userState deleteUser();
    userState searchForUser();

    static void generateReportsMenu(Administrator &admin);
    void operationalReports();
    void maintenanceReports();
    void userActivityReports();

    ~Administrator();
};

/****************************************************************************/

class userFactory
{
public:
    std::unique_ptr<User> createUser(const std::string &name, const std::string &pass, const rolesTypes &role, 
                                     const std::string &contactinfo = "", int loyaltyPoints = 0, 
                                     const std::string &userID = "", double wallet = 0.0, 
                                     const std::map<std::string, std::string> &creditCard = {}, 
                                     const std::string &paypalAccount = "");
};

std::string roleToString(rolesTypes role);
#endif // __USERCLASSES_H__
