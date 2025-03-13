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

Passenger::Passenger(const std::string &name, const std::string &pass, const rolesTypes &r, const std::string &contactInfo, int &loyaltyPoints,const std::string &id )
: User(name, pass, r), passengerID(id), contactInfo(contactInfo), loyaltyPoints(loyaltyPoints)
{


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

json Passenger::toJson() const
{
    return {
        {"username", username},
        {"password", password},
        {"role", role},
        {"userID", passengerID},
        {"contactInfo", contactInfo},
        {"loyaltyPoints", loyaltyPoints}};
}

Passenger::~Passenger()
{
#if DEBUG
    cout << "Destructor of Passenger is called" << endl;
#endif // 1
}

/************************************************************************/

Administrator::Administrator(const std::string &name, const std::string &pass, const rolesTypes &r,
                             const std::string &contactinfo, int loyaltyPoints, const std::string &id)
    : User(name, pass, r), adminId(id)
{
#if DEBUG
    cout << "Constructor of Administrator is called" << endl;
#endif
}
json Administrator::toJson() const
{
    return {
        {"username", username},
        {"password", password},
        {"role", role},
        {"userID", adminId},
    };
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

void Administrator::mangeUsersMenu(Administrator &admin)
{
    std::cout << "Edited will be done by: " << admin.getName() << std::endl;
    /*already validated the username and the password in the main*/
    int choice;
    while (true)
    {
        std::cout << "--- Manage Users ---\n";
        std::cout << "1. View All Users\n";
        std::cout << "2. Add a New User\n";
        std::cout << "3. Update User Information\n";
        std::cout << "4. Delete a User\n";
        std::cout << "5. Search for a User\n";
        std::cout << "6. Back to Administrator Menu\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            admin.viewAllUsers();
            break;
        case 2:
            admin.addNewUser();
            break;
        case 3:
            admin.updateUserInfo();
            break;
        case 4:
            admin.deleteUser();
            break;
        case 5:
            admin.searchForUser();
            break;
        case 6:
            return; // Go back to the previous menu
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

userState Administrator::viewAllUsers()
{
    json users = readFromDP(UserDP);

    if (users["users"].empty())
    {
        std::cout << "No users found in the database" << std::endl;
        return FAILED_OPERATION;
    }
    // Print header
    std::cout << "\n--- List of Users ---\n";
    std::cout << "+------------+------------------+------------------+---------------------+---------------------+------------------+\n";
    std::cout << "| User Name  | Password         | User ID          | Role                | Contact Info        | Loyalty Points   |\n";
    std::cout << "+------------+------------------+------------------+---------------------+---------------------+------------------+\n";

    for (const auto &user : users["users"])
    {
        std::cout << "| "
                  << std::left << std::setw(10) << user["username"].get<std::string>() << " | "
                  << std::left << std::setw(16) << user["password"].get<std::string>() << " | "
                  << std::left << std::setw(16) << user["userID"].get<std::string>() << " | "
                  << std::left << std::setw(19) << user["role"].get<std::string>() << " | ";

        if (user["role"] == "PASSENGER")
        {
            std::cout << std::left << std::setw(19) << user["contactInfo"].get<std::string>() << " | "
                      << std::left << std::setw(16) << user["loyaltyPoints"].get<int>() << " |\n";
        }
        else
        {
            // Leave contact info and loyalty points blank for non-passengers
            std::cout << std::left << std::setw(19) << "N/A" << " | "
                      << std::left << std::setw(16) << "N/A" << " |\n";
        }
        std::cout << "\n";
        std::cout << "+------------+------------------+------------------+---------------------+---------------------+------------------+\n";
    }

    return USER_VIEWED;
}
userState Administrator::addNewUser()
{
    json users = readFromDP(UserDP);
    std::string username, password, role, userID, contactInfo;
    int LP;
    userFactory factory;

    std::cout << "--- Add New user ---\n";
    std::cout << "Enter User Name(Spaces will be removed): ";
    std::cin.ignore(); // Clear the input buffer
    std::getline(std::cin, username);
    // Remove spaces from the username
    username.erase(std::remove_if(username.begin(), username.end(), ::isspace), username.end());

    int index = isUsernameExists(users, username);
    if (index != -1)
    {
        cout << "Sorry, but this username is used" << endl;
        return FAILED_OPERATION;
    }

    std::cout << "Enter Password: ";
    std::getline(std::cin, password);
    std::cout << "Enter User ID: ";
    std::getline(std::cin, userID);
    std::cout << "Enter Role: ";
    std::getline(std::cin, role);

    json newUserEntry;
    if (role == "BOOKING_AGENT")
    {
        std::unique_ptr<User> user = factory.createUser(username, password, rolesTypes::BOOKING_AGENT, userID);
        newUserEntry = user->toJson();
    }
    else if (role == "ADMIN")
    {
        std::unique_ptr<User> user = factory.createUser(username, password, rolesTypes::ADMIN, userID);
        newUserEntry = user->toJson();
    }
    else
    {
        std::cout << "Enter Contact Info: ";
        std::getline(std::cin, contactInfo);
        std::cout << "Enter Loyalty Points: ";
        std::cin >> LP;
        std::cin.ignore(); // Clear the input buffer after reading the status
        std::unique_ptr<User> user = factory.createUser(username, password, rolesTypes::PASSENGER, contactInfo, LP, userID);
        newUserEntry = user->toJson();
    }

    users["users"].push_back(newUserEntry);
    writeToDP(UserDP, users);
    std::cout << "User ID " << userID << " has been successfully added to DB.\n";

    return USER_ADDED;
}
userState Administrator::updateUserInfo()
{
    int choice;
    userState state = FAILED_OPERATION;
    std::string un;
    json users = readFromDP(UserDP);
    int index = 0;

    std::cout << "--- Update User ---\n";
    std::cout << "Enter Username to Update: ";
    std::cin.ignore(); // Clear the input buffer

    std::getline(std::cin, un);
    // Remove spaces from the username
    un.erase(std::remove_if(un.begin(), un.end(), ::isspace), un.end());

    index = isUsernameExists(users, un);
    if (index == -1)
    {
        cout << "Sorry, but this username is not found" << endl;
        return state;
    }
    // Access the user using the index
    json &user = users["users"][index];

    if (user["role"] == "PASSENGER")
    {
        std::cout << " --- Updating Existing User ---" << std::endl;
        std::cout << "Select information to update:" << std::endl;
        std::cout << "1. Username" << std::endl;
        std::cout << "2. User ID" << std::endl;
        std::cout << "3. Password" << std::endl;
        std::cout << "4. Role" << std::endl;
        std::cout << "5. Contact Info" << std::endl;
        std::cout << "6. Loyalty Points" << std::endl;
        std::cout << "7. Back to Manage Flights" << std::endl;
        std::cout << "Enter choice: ";
        cin >> choice;
    }
    else
    {
        std::cout << " --- Updating Existing User ---" << std::endl;
        std::cout << "Select information to update:" << std::endl;
        std::cout << "1. Username" << std::endl;
        std::cout << "2. User ID" << std::endl;
        std::cout << "3. Password" << std::endl;
        std::cout << "4. Role" << std::endl;
        std::cout << "5. Back to Manage Flights" << std::endl;
        std::cout << "Enter choice: ";
        cin >> choice;
    }
    std::string newValue;
    int newPoints;

    switch (choice)
    {
    case 1: // Update Username
        std::cout << "Enter new username: ";
        std::cin.ignore(); // Clear the input buffer
        std::getline(std::cin, newValue);
        user["username"] = newValue;
        std::cout << "Username updated successfully.\n";
        state = UPDATED_USER;
        break;

    case 2: // Update User ID
        std::cout << "Enter new user ID: ";
        std::cin.ignore(); // Clear the input buffer
        std::getline(std::cin, newValue);
        user["userID"] = newValue;
        std::cout << "User ID updated successfully.\n";
        state = UPDATED_USER;
        break;

    case 3: // Update Password
        std::cout << "Enter new password: ";
        std::cin.ignore(); // Clear the input buffer
        std::getline(std::cin, newValue);
        user["password"] = newValue;
        std::cout << "Password updated successfully.\n";
        state = UPDATED_USER;
        break;

    case 4: // Update Role
        std::cout << "Enter new role (ADMIN, BOOKING_AGENT, PASSENGER): ";
        std::cin.ignore(); // Clear the input buffer
        std::getline(std::cin, newValue);
        user["role"] = newValue;
        std::cout << "Role updated successfully.\n";
        state = UPDATED_USER;
        break;

    case 5: // Update Contact Info (Only for PASSENGER)
        if (user["role"] == "PASSENGER")
        {
            std::cout << "Enter new contact info: ";
            std::cin.ignore(); // Clear the input buffer
            std::getline(std::cin, newValue);
            user["contactInfo"] = newValue;
            std::cout << "Contact info updated successfully.\n";
            state = UPDATED_USER;
        }
        else
        {
            std::cout << "Only for Passenger, Returning to the main menu.\n";
            state = FAILED_OPERATION;
        }
        break;

    case 6: // Update Loyalty Points (Only for PASSENGER)
        if (user["role"] == "PASSENGER")
        {
            std::cout << "Enter new loyalty points: ";
            std::cin >> newPoints;
            user["loyaltyPoints"] = newPoints;
            std::cout << "Loyalty points updated successfully.\n";
            state = UPDATED_USER;
        }
        else
        {
            std::cout << "Only for Passenger, Returning to the main menu.\n";
            state = FAILED_OPERATION;
        }
        break;

    case 7: // Back to Manage Users (Only for PASSENGER)
        if (user["role"] == "PASSENGER")
        {
            std::cout << "Returning to the main menu.\n";
            state = FAILED_OPERATION;
        }
        else
        {
            std::cout << "Invalid choice. Please try again.\n";
            state = FAILED_OPERATION;
        }
        break;

    default:
        std::cout << "Invalid choice. Please try again.\n";
        state = FAILED_OPERATION;
        break;
    }

    // Write the updated users back to the file
    if (state == UPDATED_USER)
    {
        writeToDP(UserDP, users);
    }

    return state;
}
userState Administrator::deleteUser()
{
    userState state = FAILED_OPERATION;
    std::string un;
    json users = readFromDP(UserDP);
    int index = 0;
    std::cout << "--- Search for User ---\n";
    std::cout << "Enter Username to Delete: ";
    std::cin.ignore(); // Clear the input buffer

    std::getline(std::cin, un);
    // Remove spaces from the username
    un.erase(std::remove_if(un.begin(), un.end(), ::isspace), un.end());

    index = isUsernameExists(users, un);
    if (index == -1)
    {
        cout << "Sorry, but this username is not found" << std::endl;
        return state;
    }

    json &user = users["users"][index];

    users["users"].erase(users["users"].begin() + index);
    std::cout << "username: " << un << " has been successfully deleted.\n";

    writeToDP(UserDP, users);
    return DELETED_USER;
}
userState Administrator::searchForUser()
{
    userState state = FAILED_OPERATION;
    std::string un;
    json users = readFromDP(UserDP);
    int index = 0;
    std::cout << "--- Search for User ---\n";
    std::cout << "Enter Username to Search on: ";
    std::cin.ignore(); // Clear the input buffer

    std::getline(std::cin, un);
    // Remove spaces from the username
    un.erase(std::remove_if(un.begin(), un.end(), ::isspace), un.end());

    index = isUsernameExists(users, un);
    if (index == -1)
    {
        cout << "Sorry, but this username is not found" << std::endl;
    }
    else
    {
        std::cout << "Username is found at index: " << index << std::endl;
        state = USER_VIEWED;
    }
    return state;
}

Administrator::~Administrator()
{
#if DEBUG
    cout << "Destructor of Administrator is called" << endl;
#endif // 1
}

/************************************************************************/

BookingAgent::BookingAgent(const std::string &name, const std::string &pass, const rolesTypes &r,
                           const std::string &contactinfo, int loyaltyPoints, const std::string &id)
    : User(name, pass, r), agentID(id)
{
#if DEBUG
    cout << "Constructor of BookingAgent is called" << endl;
#endif
}
json BookingAgent::toJson() const
{
    return {
        {"username", username},
        {"password", password},
        {"role", role},
        {"userID", agentID},
    };
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

std::unique_ptr<User> userFactory::createUser(const std::string &name, const std::string &pass, const rolesTypes &role, const std::string &contactinfo, int loyaltyPoints, const std::string &userID)
{
    switch (role)
    {
    case rolesTypes::ADMIN:
        return std::make_unique<Administrator>(name, pass, role,userID);
    case rolesTypes::BOOKING_AGENT:
        return std::make_unique<BookingAgent>(name, pass, role, userID);
    case rolesTypes::PASSENGER:
        return std::make_unique<Passenger>(name, pass, role, contactinfo, loyaltyPoints, userID);
    default:
        throw std::invalid_argument("Invalid role type");
        ;
    }
}