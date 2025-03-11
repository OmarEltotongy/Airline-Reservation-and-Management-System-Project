#include "../../include/USERS_HPP/userClasses.hpp"
#include "../../include/FLIGHT_HPP/Flight.hpp" // Including the full definition of Flight in cpp
#include "../../include/AIRCRAFT_HPP/AirCraft.hpp"
#include "../../include/JSON_HPP/jsonHelperFunctions.hpp"

std::string UserDP = "data/users.json";
std::string flightDP = "data/flights.json";
std::string pilotDP = "data/pilots.json";
std::string flightAttendantDB = "data/flightAttendant.json";
std::string AirCraftDB = "data/aircraft.json";


User::User(const std::string &name, const std::string &pass, const rolesTypes &r)
{
#if DEBUG
    cout << "Constructor of User is called" << endl;
#endif
}
std::string User::getName()
{
    return username;
}

bool User::validateCredentials(const std::string &username, const std::string &password, const rolesTypes &role)
{
    json users = readFromDP(UserDP);

    // Convert the role enum to a string
    std::string roleStr = roleToString(role);

    for (const auto &user : users["users"])
    {
        if (user["username"] == username && user["password"] == password && user["role"] == roleStr)
        {
            return true; // Credentials are valid
        }
    }
    return false; // Credentials are invalid
}

logState User::login()
{
    switch (role)
    {
    case rolesTypes::ADMIN:
    {
        if (validateCredentials(username, password, role))
        {
#if DEBUG
            cout << "admin login succeed" << endl;
#endif
            loginState = LOG_STATE_SUCCESSFUL;
        }
        else
        {
#if DEBUG
            cout << "admin login failed" << endl;
#endif
            loginState = LOG_STATE_FAILED;
        }
        return loginState;
    }
    case rolesTypes::BOOKING_AGENT:
    {
        if (validateCredentials(username, password, role))
        {
#if DEBUG
            cout << "BookingAgent login succeed" << endl;
#endif
            loginState = LOG_STATE_SUCCESSFUL;
        }
        else
        {
#if DEBUG
            cout << "BookingAgent login failed" << endl;
#endif
            loginState = LOG_STATE_FAILED;
        }
        return loginState;
    }

    case rolesTypes::PASSENGER:
    {

        if (validateCredentials(username, password, role))
        {
#if DEBUG
            cout << "Passenger login succeed" << endl;
#endif
            loginState = LOG_STATE_SUCCESSFUL;
        }
        else
        {
#if DEBUG
            cout << "Passenger login failed" << endl;
#endif
            loginState = LOG_STATE_FAILED;
        }
        return loginState;
    }

    default:
        return LOG_STATE_FAILED;
    };
}

logState User::logout()
{
    switch (role)
    {
    case rolesTypes::ADMIN:
    {
        if (loginState == LOG_STATE_SUCCESSFUL)
        {
#if DEBUG
            cout << "admin logout succeed" << endl;
#endif
            logoutState = LOG_STATE_SUCCESSFUL;
        }
        else
        {
#if DEBUG
            cout << "admin logout failed" << endl;
#endif
            logoutState = LOG_STATE_FAILED;
        }
        return logoutState;
    }
    case rolesTypes::BOOKING_AGENT:
    {
        if (loginState == LOG_STATE_SUCCESSFUL)
        {
#if DEBUG
            cout << "BookingAgent logout succeed" << endl;
#endif
            logoutState = LOG_STATE_SUCCESSFUL;
        }
        else
        {
#if DEBUG
            cout << "BookingAgent logout failed" << endl;
#endif
            logoutState = LOG_STATE_FAILED;
        }
        return logoutState;
    }

    case rolesTypes::PASSENGER:
    {

        if (loginState == LOG_STATE_SUCCESSFUL)
        {
#if DEBUG
            cout << "Passenger logout succeed" << endl;
#endif
            logoutState = LOG_STATE_SUCCESSFUL;
        }
        else
        {
#if DEBUG
            cout << "Passenger logout failed" << endl;
#endif
            loginState = LOG_STATE_FAILED;
        }
        return loginState;
    }

    default:
        return LOG_STATE_FAILED;
    };
}

User::~User()
{
#if DEBUG
    cout << "Destructor of User is called" << endl;
#endif // 1
}

/********************************************************************/

Passenger::Passenger(const std::string &name, const std::string &pass, const rolesTypes &r)
{
    this->username = name;
    this->password = pass;
    this->role = r;

#if DEBUG
    cout << "Constructor of Passenger is called" << endl;
#endif
}

void Passenger::displayMenu()
{
    // Display passenger-specific menu options
    std::cout << ("1. Search Flights") << endl;
    std::cout << ("2. View Reservations") << endl;
    std::cout << ("3. Check-In") << endl;
    std::cout << ("4. Logout") << endl;
}

Passenger::~Passenger()
{
#if DEBUG
    cout << "Destructor of Passenger is called" << endl;
#endif // 1
}

/************************************************************************/

Administrator::Administrator(const std::string &name, const std::string &pass, const rolesTypes &r)
{
    this->username = name;
    this->password = pass;
    this->role = r;

#if DEBUG
    cout << "Constructor of Administrator is called" << endl;
#endif
}

void Administrator::mainDisplayMenu()
{
    // Display admin-specific menu options
    std::cout << "--- Administrator Menu ---\n";
    std::cout << ("1. Manage Flights") << endl;
    std::cout << ("2. Manage Aircraft") << endl;
    std::cout << ("3. Manage Users") << endl;
    std::cout << ("4. Generate Reports") << endl;
    std::cout << ("5. Logout") << endl;
    std::cout << "Enter choice: ";
}


Administrator::~Administrator()
{
#if DEBUG
    cout << "Destructor of Administrator is called" << endl;
#endif // 1
}

/************************************************************************/

BookingAgent::BookingAgent(const std::string &name, const std::string &pass, const rolesTypes &r)
{
    this->username = name;
    this->password = pass;
    this->role = r;

#if DEBUG
    cout << "Constructor of BookingAgent is called" << endl;
#endif
}

void BookingAgent::displayMenu()
{
    // Display booking agent-specific menu options
    std::cout << ("1. Book a Flight") << endl;
    std::cout << ("2. Modify Reservation") << endl;
    std::cout << ("3. Cancel Reservation") << endl;
    std::cout << ("4. Logout") << endl;
}

BookingAgent::~BookingAgent()
{
#if DEBUG
    cout << "Destructor of BookingAgent is called" << endl;
#endif // 1
}

/*****************************************************************/

std::unique_ptr<User> userFactory::createUser(const std::string &name, const std::string &pass, const rolesTypes &role)
{
    switch (role)
    {
    case rolesTypes::ADMIN:
        return std::make_unique<Administrator>(name, pass, role);
    case rolesTypes::BOOKING_AGENT:
        return std::make_unique<BookingAgent>(name, pass, role);
    case rolesTypes::PASSENGER:
        return std::make_unique<Passenger>(name, pass, role);
    default:
        throw std::invalid_argument("Invalid role type");
        ;
    }
}