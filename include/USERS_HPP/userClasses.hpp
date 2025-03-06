#ifndef __USERCLASSES_H__
#define __USERCLASSES_H__

#include <iostream>
#include <vector>
#include <string>

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

    //for passenger
    std::string passengerID;
    std::string contactInfo;
    std::string travelHistory; //vector will be implemented
    std::string loyaltyPoints;  //counter will be implemented

    //for bookingAgent


    //for administrator



public:
    User(const std::string &name = " ", const std::string &pass = " ", const rolesTypes &r = PASSENGER);
    logState login();
    logState logout();

    //for passenger , i think will be moved to passenger class
    infoState setInfo(const std::string& passengerID, const std::string& contactInfo);
    
    virtual ~User();
};


/*************************************************************************/
class Passenger : public User
{

public:
    Passenger(const std::string &name, const std::string &pass, const rolesTypes &r);
    ~Passenger();
};

/*************************************************************************/
class BookingAgent : public User
{    
public:
    BookingAgent(const std::string &name, const std::string &pass, const rolesTypes &r);
    ~BookingAgent();
};

/***************************************************************************/
class Administrator : public User
{
private:

public:
    Administrator(const std::string &name, const std::string &pass, const rolesTypes &r);
    ~Administrator();
};


/****************************************************************************/

class userFactory
{
    public:
    std::unique_ptr<User> createUser(const std::string &name, const std::string &pass, const rolesTypes& role);

};

#endif // __USERCLASSES_H__
