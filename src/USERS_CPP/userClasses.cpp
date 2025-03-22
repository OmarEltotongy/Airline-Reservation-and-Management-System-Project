#include "../../include/USERS_HPP/userClasses.hpp"
#include "../../include/FLIGHT_HPP/Flight.hpp" // Including the full definition of Flight in cpp
#include "../../include/AIRCRAFT_HPP/AirCraft.hpp"
#include "../../include/JSON_HPP/jsonHelperFunctions.hpp"

std::string UserDP = "data/users.json";
std::string flightDP = "data/flights.json";
std::string pilotDP = "data/pilots.json";
std::string flightAttendantDB = "data/flightAttendant.json";
std::string AirCraftDB = "data/aircraft.json";
std::string ReservationDP = "data/reservation.json";

User::User(const std::string &name, const std::string &pass, const rolesTypes &r)
    : username(name), password(pass), role(r)

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

/*************************************************************************************************************/
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

void Administrator::generateReportsMenu(Administrator &admin)
{
std::cout << "Reports will be Viewed by: " << admin.getName() << std::endl;
/*already validated the username and the password in the main*/
int choice;
while (true)
{
std::cout << "--- Generate Reports ---\n";
std::cout << "1. Operational Reports\n";
std::cout << "2. Maintenance Reports\n";
std::cout << "3. User Activity Reports\n";
std::cout << "4. Back to Main Menu\n";
std::cout << "Enter choice: ";
std::cin >> choice;

switch (choice)
{
case 1:
admin.operationalReports();
break;
case 2:
admin.maintenanceReports();
break;
case 3:
admin.userActivityReports();
break;
case 4:
return; // Go back to the previous menu
default:
std::cout << "Invalid choice. Please try again.\n";
}
}
}

/************************************ User Function***************************************/
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
double wallet;
std::string cardNumber, expiryDate, cvv, paypalAccount;
userFactory factory;

std::cout << "--- Add New User ---\n";
std::cout << "Enter User Name (Spaces will be removed): ";
std::cin.ignore(); // Clear the input buffer
std::getline(std::cin, username);
// Remove spaces from the username
username.erase(std::remove_if(username.begin(), username.end(), ::isspace), username.end());

// Check if the username already exists
int usernameIndex = isUsernameExists(users, username);
if (usernameIndex != -1)
{
std::cout << "Sorry, but this username is already used.\n";
return FAILED_OPERATION;
}

std::cout << "Enter Password: ";
std::getline(std::cin, password);
std::cout << "Enter User ID: ";
std::getline(std::cin, userID);

// Check if the user ID already exists
int userIDIndex = isUserIDExists(users, userID);
if (userIDIndex != -1)
{
std::cout << "Sorry, but this user ID is already used.\n";
return FAILED_OPERATION;
}

std::cout << "Enter Role (ADMIN, BOOKING_AGENT, PASSENGER): ";
std::getline(std::cin, role);

// Convert role to uppercase for consistency
std::transform(role.begin(), role.end(), role.begin(), ::toupper);

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
else if (role == "PASSENGER")
{
std::cout << "Enter Contact Info: ";
std::getline(std::cin, contactInfo);
std::cout << "Enter Loyalty Points: ";
std::cin >> LP;
std::cout << "Enter Wallet Balance: ";
std::cin >> wallet;
std::cin.ignore(); // Clear the input buffer after reading the wallet balance
std::cout << "Enter Credit Card Number: ";
std::getline(std::cin, cardNumber);
std::cout << "Enter Credit Card Expiry Date (MM/YY): ";
std::getline(std::cin, expiryDate);
std::cout << "Enter Credit Card CVV: ";
std::getline(std::cin, cvv);
std::cout << "Enter PayPal Account: ";
std::getline(std::cin, paypalAccount);

std::unique_ptr<User> user = factory.createUser(username, password, rolesTypes::PASSENGER, contactInfo, LP, userID);
newUserEntry = user->toJson();

// Add additional fields for passengers
newUserEntry["wallet"] = wallet;
newUserEntry["creditCard"] = {
{"cardNumber", cardNumber},
{"expiryDate", expiryDate},
{"cvv", cvv}};
newUserEntry["paypalAccount"] = paypalAccount;
}
else
{
std::cout << "Invalid role. Please enter ADMIN, BOOKING_AGENT, or PASSENGER.\n";
return FAILED_OPERATION;
}

// Add the new user to the users list
users["users"].push_back(newUserEntry);

// Write the updated data back to the file
writeToDP(UserDP, users);
std::cout << "User ID " << userID << " has been successfully added to the database.\n";

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

/************************************* Reports Function **********************************/

void Administrator::operationalReports() {
    std::string monthYear;
    std::cout << "--- Operational Reports ---\n";
    std::cout << "Enter Month and Year for Report (MM-YYYY): ";
    std::cin >> monthYear;

    // Read flights and reservations from JSON files
    json flights = readFromDP(flightDP);
    json reservations = readFromDP(ReservationDP);

    int totalFlightsScheduled = 0;
    int flightsCompleted = 0;
    int flightsDelayed = 0;
    int flightsCanceled = 0;
    int totalReservations = 0;
    double totalRevenue = 0.0;

    // Filter flights for the specified month and year
    for (const auto &flight : flights["flights"]) {
        std::string departureTime = flight["departureTime"];
        if (departureTime.substr(3, 7) == monthYear) { // Check if the month and year match
            totalFlightsScheduled++;
            std::string status = flight["status"];
            if (status == "ON_TIME" || status == "DELAYED") {
                flightsCompleted++;
                if (status == "DELAYED") {
                    flightsDelayed++;
                }
            } else if (status == "CANCELED") {
                flightsCanceled++;
            }

            // Calculate revenue for the flight
            double price = flight["price"];
            int availableSeats = flight["availableSeats"];
            int maxSeats = flight["maxSeats"];
            int bookings = maxSeats - availableSeats;
            totalReservations += bookings;
            totalRevenue += bookings * price;
        }
    }

    // Round total revenue to 2 decimal places
    totalRevenue = round(totalRevenue * 100) / 100;

    // Generate the report
    std::cout << "\nGenerating Operational Report for " << monthYear << "...\n\n";
    std::cout << "Report Summary:\n";
    std::cout << "- Total Flights Scheduled: " << totalFlightsScheduled << "\n";
    std::cout << "- Flights Completed: " << flightsCompleted << "\n";
    std::cout << "- Flights Delayed: " << flightsDelayed << "\n";
    std::cout << "- Flights Canceled: " << flightsCanceled << "\n";
    std::cout << "- Total Reservations Made: " << totalReservations << "\n";
    std::cout << "- Total Revenue: $" << std::fixed << std::setprecision(2) << totalRevenue << "\n\n";

    std::cout << "Detailed Flight Performance:\n";
    for (const auto &flight : flights["flights"]) {
        std::string departureTime = flight["departureTime"];
        if (departureTime.substr(3, 7) == monthYear) {
            std::string flightNumber = flight["flightNumber"];
            std::string status = flight["status"];
            double price = flight["price"];
            int availableSeats = flight["availableSeats"];
            int maxSeats = flight["maxSeats"];
            int bookings = maxSeats - availableSeats;
            double revenue = bookings * price;

            std::cout << "Flight " << flightNumber << ": " << status
                      << " (" << bookings << " Bookings, $" << std::fixed << std::setprecision(2) << revenue << ")\n";
        }
    }
}

void Administrator::maintenanceReports() {
    std::string monthYear;
    std::cout << "--- Maintenance Reports ---\n";
    std::cout << "Enter Month and Year for Report (MM-YYYY): ";
    std::cin >> monthYear;

    // Read maintenance data from JSON file
    json maintenance = readFromDP("data/maintenance.json");

    int totalMaintenanceTasks = 0;
    int tasksCompleted = 0;
    int tasksScheduled = 0;
    int tasksInProgress = 0;

    // Filter maintenance tasks for the specified month and year
    for (const auto &task : maintenance["maintenance"]) {
        std::string maintenanceDate = task["maintenanceDate"];
        if (maintenanceDate.substr(3, 7) == monthYear) { // Check if the month and year match
            totalMaintenanceTasks++;
            std::string status = task["status"];
            if (status == "COMPLETED") {
                tasksCompleted++;
            } else if (status == "SCHEDULED") {
                tasksScheduled++;
            } else if (status == "IN_PROGRESS") {
                tasksInProgress++;
            }
        }
    }

    // Generate the report
    std::cout << "\nGenerating Maintenance Report for " << monthYear << "...\n\n";
    std::cout << "Report Summary:\n";
    std::cout << "- Total Maintenance Tasks: " << totalMaintenanceTasks << "\n";
    std::cout << "- Tasks Completed: " << tasksCompleted << "\n";
    std::cout << "- Tasks Scheduled: " << tasksScheduled << "\n";
    std::cout << "- Tasks In Progress: " << tasksInProgress << "\n\n";

    std::cout << "Detailed Maintenance Tasks:\n";
    for (const auto &task : maintenance["maintenance"]) {
        std::string maintenanceDate = task["maintenanceDate"];
        if (maintenanceDate.substr(3, 7) == monthYear) {
            std::string maintenanceID = task["maintenanceID"];
            std::string aircraftID = task["aircraftID"];
            std::string description = task["description"];
            std::string status = task["status"];

            std::cout << "Task " << maintenanceID << ": " << description
                      << " (Aircraft: " << aircraftID << ", Status: " << status << ")\n";
        }
    }
}

void Administrator::userActivityReports() {
    std::string monthYear;
    std::cout << "--- User Activity Reports ---\n";
    std::cout << "Enter Month and Year for Report (MM-YYYY): ";
    std::cin >> monthYear;

    // Read users and reservations from JSON files
    json users = readFromDP(UserDP);
    json reservations = readFromDP(ReservationDP);

    int totalUsers = 0;
    int totalReservations = 0;
    double totalRevenue = 0.0;

    // Filter reservations for the specified month and year
    for (const auto &reservation : reservations["reservations"]) {
        std::string departureTime = reservation["departureTime"];
        if (departureTime.substr(3, 7) == monthYear) { // Check if the month and year match
            totalReservations++;
            double price = 250.0; // Assuming a fixed price for simplicity
            totalRevenue += price;
        }
    }

    // Count total users
    totalUsers = users["users"].size();

    // Round total revenue to 2 decimal places
    totalRevenue = round(totalRevenue * 100) / 100;

    // Generate the report
    std::cout << "\nGenerating User Activity Report for " << monthYear << "...\n\n";
    std::cout << "Report Summary:\n";
    std::cout << "- Total Users: " << totalUsers << "\n";
    std::cout << "- Total Reservations Made: " << totalReservations << "\n";
    std::cout << "- Total Revenue: $" << std::fixed << std::setprecision(2) << totalRevenue << "\n\n";

    std::cout << "Detailed User Activity:\n";
    for (const auto &user : users["users"]) {
        std::string userID = user["userID"];
        std::string username = user["username"];
        std::string role = user["role"];
        int reservationsCount = 0;

        // Count reservations for the user
        for (const auto &reservation : reservations["reservations"]) {
            if (reservation["passengerID"] == userID) {
                reservationsCount++;
            }
        }

        std::cout << "User " << username << " (" << role << "): "
                  << reservationsCount << " Reservations\n";
    }
}
/******************************************************************************************/
Administrator::~Administrator()
{
#if DEBUG
cout << "Destructor of Administrator is called" << endl;
#endif // 1
}

/******************************************************************************************/

Passenger::Passenger(const std::string &name, const std::string &pass, const rolesTypes &r,
                     const std::string &contactInfo, int &loyaltyPoints, const std::string &id,
                     double wallet, const std::map<std::string, std::string> &creditCard,
                     const std::string &paypalAccount)
    : User(name, pass, r), passengerID(id), contactInfo(contactInfo), loyaltyPoints(loyaltyPoints),
      wallet(wallet), creditCard(creditCard), paypalAccount(paypalAccount)
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
    std::cout << "Enter choice: ";
}

void Passenger::searchFlight()
{
    std::string flightNum;
    std::string flightDate;
    std::string origin;
    std::string destination;
    std::string seatNumber;
    std::string paymentMethod;
    std::string paymentDetails;

    std::vector<int> avaFlightsIndex;
    json flights = readFromDP(flightDP);
    json users = readFromDP(UserDP);
    json reservations = readFromDP(ReservationDP);
    std::string choice;

    std::cout << "--- Searching Flights ---\n"
              << std::endl;
    std::cout << "Enter Origin: ";
    std::getline(std::cin, origin);

    std::cout << "Enter Destination: ";
    std::getline(std::cin, destination);

    std::cout << "Please enter a date in this format (YYYY-MM-DD HH:MM): ";
    std::getline(std::cin, flightDate);

    // Find available flights
    for (size_t i = 0; i < flights["flights"].size(); ++i)
    {
        if ((flights["flights"][i]["departureTime"] == flightDate) &&
            (flights["flights"][i]["origin"] == origin) &&
            (flights["flights"][i]["destination"] == destination))
        {
            std::cout << "Available Flight " << i + 1 << ":\n";
            std::cout << "Flight Number: " << flights["flights"][i]["flightNumber"] << "\n";
            std::cout << "Origin: " << flights["flights"][i]["origin"] << "\n";
            std::cout << "Destination: " << flights["flights"][i]["destination"] << "\n";
            std::cout << "Departure Time: " << flights["flights"][i]["departureTime"] << "\n";
            std::cout << "Arrival Time: " << flights["flights"][i]["arrivalTime"] << "\n";
            std::cout << "Status: " << flights["flights"][i]["status"] << "\n";
            std::cout << "Price: $" << flights["flights"][i]["price"] << "\n";
            std::cout << "Available Seats: " << flights["flights"][i]["availableSeats"] << "\n";
            std::cout << "-------------------------\n";

            avaFlightsIndex.push_back(i);
        }
    }

    if (!avaFlightsIndex.empty())
    {
        std::cout << "Do you want to book a flight? (y/n): ";
        std::cin >> choice;
        std::cin.ignore(); // Clear the input buffer

        if (choice == "y" || choice == "Y")
        {
            std::cout << "Enter the Flight Number you wish to book: ";
            std::getline(std::cin, flightNum);

            int index = isFlightExists(flights, flightNum);
            if (index == -1)
            {
                std::cout << "Error: Flight " << flightNum << " does not exist.\n";
                return;
            }

            // Check if there are available seats
            if (flights["flights"][index]["availableSeats"] <= 0)
            {
                std::cout << "Error: No available seats for flight " << flightNum << ".\n";
                return;
            }

            // Get seat number
            std::cout << "Enter Seat Number (e.g., 14C): ";
            std::getline(std::cin, seatNumber);

            // Get passenger's loyalty points
            int loyaltyPoints = 0;
            for (auto &user : users["users"])
            {
                if (user["userID"] == passengerID)
                {
                    loyaltyPoints = user["loyaltyPoints"];
                    break;
                }
            }

            // Calculate discount based on loyalty points
            double price = flights["flights"][index]["price"];
            double discount = 0.0;
            if (loyaltyPoints >= 100)
            {
                discount = 0.10; // 10% discount for every 100 loyalty points
                int discountMultiplier = loyaltyPoints / 100;
                discount = discount * discountMultiplier;
                if (discount > 0.50) // Cap discount at 50%
                {
                    discount = 0.50;
                }
            }

            double discountedPrice = price * (1 - discount);

            // Display old and new prices
            std::cout << "Original Price: $" << price << "\n";
            std::cout << "Discounted Price: $" << discountedPrice << " (Discount: " << (discount * 100) << "%)\n";

            // Get payment method
            std::cout << "Enter Payment Method (Credit Card/Wallet/PayPal): ";
            std::getline(std::cin, paymentMethod);

            // Get payment details
            if (paymentMethod == "Credit Card" || paymentMethod == "credit card")
            {
                std::cout << "Enter Credit Card Number: ";
                std::getline(std::cin, paymentDetails);
            }
            else if (paymentMethod == "Wallet" || paymentMethod == "wallet")
            {
                // Check wallet balance
                if (wallet < discountedPrice)
                {
                    std::cout << "Error: Insufficient wallet balance.\n";
                    return;
                }
                wallet -= discountedPrice; // Deduct from wallet
                paymentDetails = "Wallet";
            }
            else if (paymentMethod == "PayPal" || paymentMethod == "paypal")
            {
                std::cout << "Enter PayPal Account: ";
                std::getline(std::cin, paymentDetails);
            }
            else
            {
                std::cout << "Error: Invalid payment method.\n";
                return;
            }

            // Deduct loyalty points used for discount
            if (discount > 0)
            {
                int pointsUsed = (discount / 0.10) * 100; // 100 points per 10% discount
                for (auto &user : users["users"])
                {
                    if (user["userID"] == passengerID)
                    {
                        user["loyaltyPoints"] = user["loyaltyPoints"].get<int>() - pointsUsed;
                        break;
                    }
                }
            }

            // Create reservation
            std::string reservationID = "R" + std::to_string(reservations["reservations"].size() + 1);
            Reservation reservation;
            reservation.createReservation(reservationID, flightNum, passengerID, seatNumber, origin, destination, flightDate);

            // Add reservation to database
            reservations["reservations"].push_back(reservation.toJson());

            // Update flight available seats
            flights["flights"][index]["availableSeats"] = flights["flights"][index]["availableSeats"].get<int>() - 1;

            // Update user wallet (if payment was from wallet)
            if (paymentMethod == "Wallet" || paymentMethod == "wallet")
            {
                for (auto &user : users["users"])
                {
                    if (user["userID"] == passengerID)
                    {
                        user["wallet"] = wallet;
                        break;
                    }
                }
            }

            // Write updated data back to files
            writeToDP(flightDP, flights);
            writeToDP(UserDP, users);
            writeToDP(ReservationDP, reservations);

            // Print confirmation
            std::cout << "\nBooking successful!\n";
            std::cout << "Reservation ID: " << reservationID << "\n";
            std::cout << "Flight: " << flightNum << " from " << origin << " to " << destination << "\n";
            std::cout << "Seat: " << seatNumber << "\n";
            std::cout << "Total Cost: $" << discountedPrice << " (Original Price: $" << price << ")\n";
        }
        else
        {
            std::cout << "Thank you for your visit.\n";
        }
    }
    else
    {
        std::cout << "No available flights found for the given criteria.\n";
    }
}

void Passenger::viewReservation()
{
    std::string username;
    std::cout << "--- View Reservations ---\n";
    std::cout << "Enter your username: ";
    std::cin >> username;

    // Read users and reservations from their files
    json users = readFromDP(UserDP);
    json reservations = readFromDP(ReservationDP);

    // Find the passenger's user ID
    std::string passengerID;
    bool passengerFound = false;
    for (const auto &user : users["users"])
    {
        if (user["username"] == username)
        {
            passengerID = user["userID"];
            passengerFound = true;
            break;
        }
    }

    if (!passengerFound)
    {
        std::cout << "Error: Passenger with username " << username << " not found.\n";
        return;
    }

    // Fetch reservations for the passenger
    std::vector<json> passengerReservations;
    for (const auto &reservation : reservations["reservations"])
    {
        if (reservation["passengerID"] == passengerID)
        {
            passengerReservations.push_back(reservation);
        }
    }

    if (passengerReservations.empty())
    {
        std::cout << "No reservations found for passenger " << username << ".\n";
        return;
    }

    // Display reservations
    std::cout << "\nFetching reservations for Passenger " << username << "...\n";
    for (size_t i = 0; i < passengerReservations.size(); ++i)
    {
        const auto &reservation = passengerReservations[i];
        std::cout << i + 1 << ". Reservation ID: " << reservation["reservationID"] << "\n";
        std::cout << "   Flight: " << reservation["flightNumber"] << " from " << reservation["origin"] << " to " << reservation["destination"] << "\n";
        std::cout << "   Departure: " << reservation["departureTime"] << "\n";
        std::cout << "   Seat: " << reservation["seatNumber"] << "\n";
        std::cout << "   Status: Confirmed\n"; // Assuming all reservations are confirmed
        std::cout << "-------------------------\n";
    }
}
void Passenger::checkIn()
{
    std::string reservationID;
    std::cout << "--- Check-In ---\n";
    std::cout << "Enter Reservation ID: ";
    std::cin >> reservationID;

    // Read reservations, flights, and users from their files
    json reservations = readFromDP(ReservationDP);
    json flights = readFromDP(flightDP);
    json users = readFromDP(UserDP);

    // Find the reservation
    bool reservationFound = false;
    json *reservation = nullptr;
    for (auto &res : reservations["reservations"])
    {
        if (res["reservationID"] == reservationID)
        {
            reservation = &res;
            reservationFound = true;
            break;
        }
    }

    if (!reservationFound)
    {
        std::cout << "Error: Reservation with ID " << reservationID << " not found.\n";
        return;
    }

    // Check if the reservation is already confirmed
    if ((*reservation)["status"] == "Confirmed")
    {
        std::cout << "Reservation is already confirmed.\n";
        return;
    }

    // Update the reservation status to "Confirmed"
    (*reservation)["status"] = "Confirmed";

    // Fetch flight details to get the gate
    std::string flightNumber = (*reservation)["flightNumber"];
    std::string gate;
    for (const auto &flight : flights["flights"])
    {
        if (flight["flightNumber"] == flightNumber)
        {
            gate = flight["gate"];
            break;
        }
    }

    // Fetch passenger details
    std::string passengerID = (*reservation)["passengerID"];
    std::string passengerName;
    for (const auto &user : users["users"])
    {
        if (user["userID"] == passengerID)
        {
            passengerName = user["username"];
            break;
        }
    }

    // Generate boarding pass
    std::cout << "\nCheck-In Successful!\n";
    std::cout << "Boarding Pass:\n";
    std::cout << "-----------------------------\n";
    std::cout << "Reservation ID: " << (*reservation)["reservationID"] << "\n";
    std::cout << "Passenger: " << passengerName << "\n";
    std::cout << "Flight: " << (*reservation)["flightNumber"] << "\n";
    std::cout << "Origin: " << (*reservation)["origin"] << "\n";
    std::cout << "Destination: " << (*reservation)["destination"] << "\n";
    std::cout << "Departure: " << (*reservation)["departureTime"] << "\n";
    std::cout << "Seat: " << (*reservation)["seatNumber"] << "\n";
    std::cout << "Gate: " << gate << "\n"; // Fetch gate from flight data
    std::cout << "-----------------------------\n";

    // Write the updated reservations back to the file
    writeToDP(ReservationDP, reservations);
}

json Passenger::toJson() const
{
    return {
        {"username", username},
        {"password", password},
        {"role", role},
        {"userID", passengerID},
        {"contactInfo", contactInfo},
        {"loyaltyPoints", loyaltyPoints},
        {"wallet", wallet},
        {"creditCard", creditCard},
        {"paypalAccount", paypalAccount}};
}

Passenger::~Passenger()
{
#if DEBUG
    cout << "Destructor of Passenger is called" << endl;
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
void BookingAgent::displayMenu(BookingAgent &agent)
{
    std::cout << "Actions will be done by: " << agent.getName() << std::endl;

    // Display booking agent-specific menu options
    std::cout << ("1. Search a Flight to Book") << endl;
    std::cout << ("2. Modify Reservation") << endl;
    std::cout << ("3. Cancel Reservation") << endl;
    std::cout << ("4. Logout") << endl;
    std::cout << ("Enter Choice: ");
}

/************************************ Agent Functionality ************************************/
void BookingAgent::searchFlight()
{
    std::string flightNum;
    std::string flightDate;
    std::string origin;
    std::string destination;
    std::string seatNumber;
    std::string paymentMethod;
    std::string paymentDetails;
    std::string passengerID;

    std::vector<int> avaFlightsIndex;
    json flights = readFromDP(flightDP);
    json users = readFromDP(UserDP);
    json reservations = readFromDP(ReservationDP);
    std::string choice;

    std::cout << "--- Searching Flights ---\n"
              << std::endl;
    std::cout << "Enter Origin: ";
    std::getline(std::cin, origin);

    std::cout << "Enter Destination: ";
    std::getline(std::cin, destination);

    std::cout << "Please enter a date in this format (YYYY-MM-DD HH:MM): ";
    std::getline(std::cin, flightDate);

    // Find available flights
    for (size_t i = 0; i < flights["flights"].size(); ++i)
    {
        if ((flights["flights"][i]["departureTime"] == flightDate) &&
            (flights["flights"][i]["origin"] == origin) &&
            (flights["flights"][i]["destination"] == destination))
        {
            std::cout << "Available Flight " << i + 1 << ":\n";
            std::cout << "Flight Number: " << flights["flights"][i]["flightNumber"] << "\n";
            std::cout << "Origin: " << flights["flights"][i]["origin"] << "\n";
            std::cout << "Destination: " << flights["flights"][i]["destination"] << "\n";
            std::cout << "Departure Time: " << flights["flights"][i]["departureTime"] << "\n";
            std::cout << "Arrival Time: " << flights["flights"][i]["arrivalTime"] << "\n";
            std::cout << "Status: " << flights["flights"][i]["status"] << "\n";
            std::cout << "Price: $" << flights["flights"][i]["price"] << "\n";
            std::cout << "Available Seats: " << flights["flights"][i]["availableSeats"] << "\n";
            std::cout << "-------------------------\n";

            avaFlightsIndex.push_back(i);
        }
    }

    if (!avaFlightsIndex.empty())
    {
        std::cout << "Do you want to book a flight? (y/n): ";
        std::cin >> choice;
        std::cin.ignore(); // Clear the input buffer

        if (choice == "y" || choice == "Y")
        {
            std::cout << "Enter the Flight Number you wish to book: ";
            std::getline(std::cin, flightNum);

            int index = isFlightExists(flights, flightNum);
            if (index == -1)
            {
                std::cout << "Error: Flight " << flightNum << " does not exist.\n";
                return;
            }

            // Check if there are available seats
            if (flights["flights"][index]["availableSeats"] <= 0)
            {
                std::cout << "Error: No available seats for flight " << flightNum << ".\n";
                return;
            }

            // Get passenger ID
            std::cout << "Enter Passenger ID: ";
            std::getline(std::cin, passengerID);

            // Get seat number
            std::cout << "Enter Seat Number (e.g., 14C): ";
            std::getline(std::cin, seatNumber);

            // Get passenger's loyalty points
            int loyaltyPoints = 0;
            double wallet = 0.0;
            for (auto &user : users["users"])
            {
                if (user["userID"] == passengerID)
                {
                    loyaltyPoints = user["loyaltyPoints"];
                    wallet = user["wallet"];
                    break;
                }
            }

            // Calculate discount based on loyalty points
            double price = flights["flights"][index]["price"];
            double discount = 0.0;
            if (loyaltyPoints >= 100)
            {
                discount = 0.10; // 10% discount for every 100 loyalty points
                int discountMultiplier = loyaltyPoints / 100;
                discount = discount * discountMultiplier;
                if (discount > 0.50) // Cap discount at 50%
                {
                    discount = 0.50;
                }
            }

            double discountedPrice = price * (1 - discount);

            // Display old and new prices
            std::cout << "Original Price: $" << price << "\n";
            std::cout << "Discounted Price: $" << discountedPrice << " (Discount: " << (discount * 100) << "%)\n";

            // Get payment method
            std::cout << "Enter Payment Method (Credit Card/Wallet/PayPal): ";
            std::getline(std::cin, paymentMethod);

            // Get payment details
            if (paymentMethod == "Credit Card" || paymentMethod == "credit card")
            {
                std::cout << "Enter Credit Card Number: ";
                std::getline(std::cin, paymentDetails);
            }
            else if (paymentMethod == "Wallet" || paymentMethod == "wallet")
            {
                // Check wallet balance
                if (wallet < discountedPrice)
                {
                    std::cout << "Error: Insufficient wallet balance.\n";
                    return;
                }
                wallet -= discountedPrice; // Deduct from wallet
                paymentDetails = "Wallet";
            }
            else if (paymentMethod == "PayPal" || paymentMethod == "paypal")
            {
                std::cout << "Enter PayPal Account: ";
                std::getline(std::cin, paymentDetails);
            }
            else
            {
                std::cout << "Error: Invalid payment method.\n";
                return;
            }

            // Deduct loyalty points used for discount
            if (discount > 0)
            {
                int pointsUsed = (discount / 0.10) * 100; // 100 points per 10% discount
                for (auto &user : users["users"])
                {
                    if (user["userID"] == passengerID)
                    {
                        user["loyaltyPoints"] = user["loyaltyPoints"].get<int>() - pointsUsed;
                        break;
                    }
                }
            }

            // Create reservation
            std::string reservationID = "R" + std::to_string(reservations["reservations"].size() + 1);
            Reservation reservation;
            reservation.createReservation(reservationID, flightNum, passengerID, seatNumber, origin, destination, flightDate);

            // Add reservation to database
            reservations["reservations"].push_back(reservation.toJson());

            // Update flight available seats
            flights["flights"][index]["availableSeats"] = flights["flights"][index]["availableSeats"].get<int>() - 1;

            // Update user wallet (if payment was from wallet)
            if (paymentMethod == "Wallet" || paymentMethod == "wallet")
            {
                for (auto &user : users["users"])
                {
                    if (user["userID"] == passengerID)
                    {
                        user["wallet"] = wallet;
                        break;
                    }
                }
            }

            // Write updated data back to files
            writeToDP(flightDP, flights);
            writeToDP(UserDP, users);
            writeToDP(ReservationDP, reservations);

            // Print confirmation
            std::cout << "\nBooking successful!\n";
            std::cout << "Reservation ID: " << reservationID << "\n";
            std::cout << "Flight: " << flightNum << " from " << origin << " to " << destination << "\n";
            std::cout << "Seat: " << seatNumber << "\n";
            std::cout << "Total Cost: $" << discountedPrice << " (Original Price: $" << price << ")\n";
        }
        else
        {
            std::cout << "Thank you for your visit.\n";
        }
    }
    else
    {
        std::cout << "No available flights found for the given criteria.\n";
    }
}

void BookingAgent::modifyReservation()
{
    cout << "M" << endl;
}
void BookingAgent::cancelReservation()
{
    cout << "C" << endl;
}
/*********************************************************************************************/

BookingAgent::~BookingAgent()
{
#if DEBUG
    cout << "Destructor of BookingAgent is called" << endl;
#endif // 1
}

/*****************************************************************/

std::unique_ptr<User> userFactory::createUser(const std::string &name, const std::string &pass,
                                              const rolesTypes &role, const std::string &contactinfo,
                                              int loyaltyPoints, const std::string &userID,
                                              double wallet,
                                              const std::map<std::string, std::string> &creditCard,
                                              const std::string &paypalAccount)
{
    switch (role)
    {
    case rolesTypes::ADMIN:
        return std::make_unique<Administrator>(name, pass, role, userID);
    case rolesTypes::BOOKING_AGENT:
        return std::make_unique<BookingAgent>(name, pass, role, userID);
    case rolesTypes::PASSENGER:
        return std::make_unique<Passenger>(name, pass, role, contactinfo, loyaltyPoints, userID,
                                           wallet, creditCard, paypalAccount);
    default:
        throw std::invalid_argument("Invalid role type");
    }
}