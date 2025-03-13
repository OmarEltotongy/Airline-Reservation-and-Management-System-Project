#include "../../include/USERS_HPP/userClasses.hpp"
#include "../../include/FLIGHT_HPP/Flight.hpp"
#include "../../include/AIRCRAFT_HPP/Aircraft.hpp"
// #include "../../include/RESERVATION_HPP/Reservation.hpp"
#include <memory> // for unique ptr

using namespace std;
std::string userDataPath = "data/users.json";
void displayMainMenu();

int main()
{
    int choice;
    std::string username, password;
    userFactory factory;
    std::cout << "Welcome to Airline Reservation and Management System\n";

    while (true)
    {
        // Display the main menu
        displayMainMenu();
        std::cin >> choice;
        std::cin.ignore(); // Clear the input buffer
        std::string vID;
        if (choice == 1)
        { // Administrator
            std::cout << "--- Administrator Login ---\n";
            std::cout << "Username: ";
            std::getline(std::cin, username);
            std::cout << "Password: ";
            std::getline(std::cin, password);

            std::unique_ptr<User> admin = factory.createUser(username, password, rolesTypes::ADMIN,vID);
            // Cast the User pointer to an Administrator pointer
            Administrator *adminPtr = dynamic_cast<Administrator *>(admin.get());

            if (admin->login() == LOG_STATE_SUCCESSFUL)
            {
                std::cout << "Login successful!\n";

                while (true)
                {
                    // Display the Administrator menu
                    Administrator::mainDisplayMenu();
                    std::cin >> choice;
                    std::cin.ignore(); // Clear the input buffer

                    if (choice == 1)
                    { // Manage Flights
                        Flight::ManageFlightsMenu(*adminPtr);
                    }
                    else if (choice == 2)
                    { // Manage Aircraft
                        Aircraft::ManageAircraftMenu(*adminPtr);
                    }
                    else if (choice == 3)
                    { // Manage Users
                        Administrator::mangeUsersMenu(*adminPtr);
                    }
                    else if (choice == 4)
                    { // Generate Reports
                        // Implement Generate Reports functionality
                        std::cout << "Generate Reports functionality not implemented yet.\n";
                    }
                    else if (choice == 5)
                    { // Logout
                        admin->logout();
                        std::cout << "Logging out...\n";
                        break;
                    }
                    else
                    {
                        std::cout << "Invalid choice. Please try again.\n";
                    }
                }
            }
            else
            {
                std::cout << "Login failed! Invalid username or password.\n";
            }
        }
        else if (choice == 2)
        { // Booking Agent
            std::cout << "--- Booking Agent Login ---\n";
            std::cout << "Username: ";
            std::getline(cin, username);
            std::cout << "Password: ";
            std::getline(cin, password);

            std::unique_ptr<User> agent = factory.createUser(username, password, rolesTypes::BOOKING_AGENT, vID);
            if (agent->login() == LOG_STATE_SUCCESSFUL)
            {
                std::cout << "Login successful!\n";

                while (true)
                {
                    // Display the Booking Agent menu
                    BookingAgent::displayMenu();
                    std::cin >> choice;
                    std::cin.ignore(); // Clear the input buffer

                    if (choice == 1)
                    { // Book a Flight
                        // Implement Book a Flight functionality
                        std::cout << "Book a Flight functionality not implemented yet.\n";
                    }
                    else if (choice == 2)
                    { // Modify Reservation
                        // Implement Modify Reservation functionality
                        std::cout << "Modify Reservation functionality not implemented yet.\n";
                    }
                    else if (choice == 3)
                    { // Cancel Reservation
                        // Implement Cancel Reservation functionality
                        std::cout << "Cancel Reservation functionality not implemented yet.\n";
                    }
                    else if (choice == 4)
                    { // Logout
                        agent->logout();
                        std::cout << "Logging out...\n";
                        break;
                    }
                    else
                    {
                        std::cout << "Invalid choice. Please try again.\n";
                    }
                }
            }
            else
            {
                std::cout << "Login failed! Invalid username or password.\n";
            }
        }
        else if (choice == 3)
        { // Passenger
            std::cout << "--- Passenger Login ---\n";
            std::cout << "Username: ";
            std::getline(std::cin, username);
            std::cout << "Password: ";
            std::getline(std::cin, password);

            std::unique_ptr<User> passenger = factory.createUser(username, password, rolesTypes::PASSENGER);
            if (passenger->login() == LOG_STATE_SUCCESSFUL)
            {
                std::cout << "Login successful!\n";

                while (true)
                {
                    // Display the Passenger menu
                    Passenger::displayMenu();
                    std::cin >> choice;
                    std::cin.ignore(); // Clear the input buffer

                    if (choice == 1)
                    { // Search Flights
                        // Implement Search Flights functionality
                        std::cout << "Search Flights functionality not implemented yet.\n";
                    }
                    else if (choice == 2)
                    { // View Reservations
                        // Implement View Reservations functionality
                        std::cout << "View Reservations functionality not implemented yet.\n";
                    }
                    else if (choice == 3)
                    { // Check-In
                        // Implement Check-In functionality
                        std::cout << "Check-In functionality not implemented yet.\n";
                    }
                    else if (choice == 4)
                    { // Logout
                        passenger->logout();
                        std::cout << "Logging out...\n";
                        break;
                    }
                    else
                    {
                        std::cout << "Invalid choice. Please try again.\n";
                    }
                }
            }
            else
            {
                std::cout << "Login failed! Invalid username or password.\n";
            }
        }
        else if (choice == 4)
        { // Exit
            std::cout << "Exiting the program. Goodbye!\n";
            return 0;
        }
        else
        {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

void displayMainMenu()
{
    std::cout << "Please select your role or Exist:\n";
    std::cout << "1. Administrator\n";
    std::cout << "2. Booking Agent\n";
    std::cout << "3. Passenger\n";
    std::cout << "4. Exist\n";
    std::cout << "Enter choice: ";
}