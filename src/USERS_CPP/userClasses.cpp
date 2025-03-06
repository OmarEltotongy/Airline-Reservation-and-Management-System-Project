#include "../../include/USERS_HPP/userClasses.hpp"

User::User(const std::string &name, const std::string &pass, const rolesTypes &r)
{
#if DEBUG
    cout << "Constructor of User is called" << endl;
#endif
}

logState User::login()
{
    switch (role)
    {
    case ADMIN:
    {
        if (username == "Passenger" && password == "Passenger")
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
    case BOOKING_AGENT:
    {
        if (username == "agent" && password == "agent")
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

    case PASSENGER:
    {

        if (username == "Passenger" && password == "Passenger")
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
    case ADMIN:
    {
        if (username == "Passenger" && password == "Passenger")
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
            logoutState = LOG_STATE_FAILED;
        }
        return logoutState;
    }
    case BOOKING_AGENT:
    {
        if (username == "agent" && password == "agent")
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

    case PASSENGER:
    {

        if (username == "Passenger" && password == "Passenger")
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

infoState setInfo(const std::string &passengerID, const std::string &contactInfo)
{
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
    case ADMIN:
        return std::make_unique<Administrator>(name, pass, role);
    case BOOKING_AGENT:
        return std::make_unique<BookingAgent>(name, pass, role);
    case PASSENGER:
        return std::make_unique<Passenger>(name, pass, role);
    default:
        throw std::invalid_argument("Invalid role type");
        ;
    }
}