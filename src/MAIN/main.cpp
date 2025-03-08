#include "../../include/USERS_HPP/userClasses.hpp"
// #include "../../include/FLIGHT_HPP/Flight.hpp"
// #include "../../include/AIRCRAFT_HPP/Aircraft.hpp"
// #include "../../include/RESERVATION_HPP/Reservation.hpp"
#include <memory> // for unique ptr

using namespace std;




int main() {
    // Create a user factory
    userFactory factory;

    // Create users using the factory
    std::unique_ptr<User> admin = factory.createUser("admin", "admin", ADMIN);
    std::unique_ptr<User> agent = factory.createUser("agent", "agentPass", BOOKING_AGENT);
    std::unique_ptr<User> passenger = factory.createUser("passenger", "passenger", PASSENGER);

    // Test login functionality
    if (admin->login() == LOG_STATE_SUCCESSFUL) {
        std::cout << "Admin login successful!" << std::endl;
        admin->displayMenu(); // Display admin menu
    } else {
        std::cout << "Admin login failed!" << std::endl;
    }

    if (agent->login() == LOG_STATE_SUCCESSFUL) {
        std::cout << "Booking Agent login successful!" << std::endl;
        agent->displayMenu(); // Display booking agent menu
    } else {
        std::cout << "Booking Agent login failed!" << std::endl;
    }

    if (passenger->login() == LOG_STATE_SUCCESSFUL) {
        std::cout << "Passenger login successful!" << std::endl;
        passenger->displayMenu(); // Display passenger menu
    } else {
        std::cout << "Passenger login failed!" << std::endl;
    }

    return 0;
}