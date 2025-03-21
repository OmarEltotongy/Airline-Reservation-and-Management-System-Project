# ✈️ Airline Reservation and Management System

Welcome to the **Airline Reservation and Management System**, a **Modern C++** console-based application designed to simulate the comprehensive operations of an airline. This project leverages **Object-Oriented Programming (OOP)** principles, **Modern C++ features**, and **JSON-based data persistence** to provide a robust and scalable solution for managing flights, aircraft, crew, reservations, and passenger profiles.

---

## 🚀 Key Features

### 1. **User Roles and Authentication**
   - **Roles**: Administrators, Booking Agents, and Passengers.
   - **Authentication**: Secure login system with **role-based access control**.
   - **User Management**: Administrators can create, update, and delete user accounts.

### 2. **Flight Management**
   - **Flight Scheduling**: Add, update, and remove flights with details like flight number, origin, destination, departure/arrival times, aircraft type, and status.
   - **Aircraft Management**: Manage fleet information, including aircraft specifications, maintenance schedules, and availability.
   - **Crew Assignment**: Assign pilots and flight attendants to specific flights while ensuring compliance with regulations (e.g., maximum flight hours).

### 3. **Booking System**
   - **Search Flights**: Allow passengers and booking agents to search for flights based on various criteria (e.g., date, destination, price).
   - **Seat Selection**: Implement seat maps for flights, enabling passengers to select preferred seats.
   - **Booking Management**: Create, modify, and cancel reservations. Handle booking confirmations and waitlists.
   - **Payment Processing**: Simulate payment transactions for bookings, including handling refunds for cancellations.

### 4. **Passenger Management**
   - **Passenger Profiles**: Store and manage passenger information, including contact details, preferences, and travel history.
   - **Loyalty Programs**: Implement a basic loyalty system where passengers earn points for bookings and can redeem them for discounts.

### 5. **Check-In System**
   - **Online Check-In**: Allow passengers to check in online, select seats, and obtain boarding passes.

### 6. **Maintenance Tracking**
   - Schedule and log maintenance activities for aircraft.
   - Ensure compliance with safety and regulatory standards.

### 7. **Reporting and Analytics**
   - Generate reports on flight performance, reservations, financial summaries, and user activities.

---

## 📂 Project Structure

The project is organized into a **modular and scalable structure** to ensure maintainability and ease of development. Below is the detailed file structure:

```
📂 airline-reservation-system/
│── 📂 data/                     # JSON files for data persistence
│   ├── aircraft.json            # Aircraft details (ID, model, availability, etc.)
│   ├── flightAttendant.json     # Flight attendant details (ID, name, status, etc.)
│   ├── flights.json             # Flight details (flight number, origin, destination, etc.)
│   ├── maintenance.json         # Maintenance details (maintenance ID, aircraft ID, etc.)
│   ├── pilots.json              # Pilot details (ID, name, status, etc.)
│   ├── reservation.json         # Reservation details (reservation ID, flight number, etc.)
│   └── users.json               # User details (username, password, role, etc.)
│
│── 📂 docs/                     # Documentation files
│   ├── Airline Reservation and Management System - Project.pdf
│   ├── Input and expected output.md
│   └── organizerHelper.txt
│
│── 📂 include/                  # Header files (HPP)
│   ├── 📂 AIRCRAFT_HPP/
│   │   └── Aircraft.hpp         # Header for the Aircraft class
│   ├── 📂 ENUMS/
│   │   ├── aircraft_enums.hpp   # Enums for aircraft-related processes
│   │   ├── flights_enum.hpp     # Enums for flight-related processes
│   │   └── user_enums.hpp       # Enums for user-related processes
│   ├── 📂 FLIGHT_HPP/
│   │   └── Flight.hpp           # Header for the Flight class
│   ├── 📂 JSON_HPP/
│   │   ├── json.hpp             # JSON library for data handling
│   │   └── jsonHelperFunctions.hpp # Helper functions for JSON operations
│   ├── 📂 RESERVATION_HPP/
│   │   └── Reservation.hpp      # Header for the Reservation class
│   └── 📂 USERS_HPP/
│       └── userClasses.hpp      # Headers for user-related classes (User, Passenger, BookingAgent, Administrator)
│
│── 📂 src/                      # Source files (CPP)
│   ├── 📂 AIRCRAFT_CPP/
│   │   └── Aircraft.cpp         # Implementation of the Aircraft class
│   ├── 📂 FLIGHT_CPP/
│   │   └── Flight.cpp           # Implementation of the Flight class
│   ├── 📂 JSONHELPERFUNCTION_CPP/
│   │   └── jsonHelperFunctions.cpp # Implementation of JSON helper functions
│   ├── 📂 MAIN/
│   │   └── main.cpp             # Main application entry point
│   ├── 📂 RESERVATION_CPP/
│   │   └── Reservation.cpp      # Implementation of the Reservation class
│   └── 📂 USERS_CPP/
│       └── userClasses.cpp      # Implementation of user-related classes
│
│── CMakeLists.txt               # CMake build configuration (optional)
│── README.md                    # Project documentation (this file)
```

---

## 🛠️ How to Build and Run

### Prerequisites
- **C++ Compiler**: Ensure you have a C++17-compatible compiler (e.g., `g++` or `clang++`).
- **CMake** (Optional): For managing the build process.

### Steps to Build and Run
1. **Clone the Repository**:
   ```bash
   git clone <repository-url>
   cd airline-reservation-system
   ```

2. **Compile the Project**:
   - Using `g++`:
     ```bash
     g++ -std=c++17 src/MAIN/main.cpp src/AIRCRAFT_CPP/Aircraft.cpp src/FLIGHT_CPP/Flight.cpp src/JSONHELPERFUNCTION_CPP/jsonHelperFunctions.cpp src/RESERVATION_CPP/Reservation.cpp src/USERS_CPP/userClasses.cpp -o airline_system
     ```
   - Using CMake:
     ```bash
     mkdir build
     cd build
     cmake ..
     make
     ```

3. **Run the Application**:
   ```bash
   ./airline_system
   ```

4. **Login**:
   - Use the following credentials for testing:
     - **Administrator**: Username: `admin1`, Password: `admin123`
     - **Booking Agent**: Username: `agent2`, Password: `agent456`
     - **Passenger**: Username: `passenger2`, Password: `pass456`

---

## 🎯 Example Usage

### 1. **Administrator**
   - Manage flights, aircraft, and users.
   - Generate reports on flight performance and user activity.

### 2. **Booking Agent**
   - Search for flights and create/modify reservations.
   - Process payments and handle cancellations.

### 3. **Passenger**
   - Search for flights, book seats, and check in online.
   - View travel history and loyalty points.

---

## 🔮 Future Enhancements
- **Graphical User Interface (GUI)**: Implement a modern GUI using frameworks like **Qt** or **ImGui**.
- **Real-Time Flight Status Updates**: Integrate with external APIs for real-time flight tracking.
- **Advanced Payment Processing**: Integrate with payment gateways like **Stripe** or **PayPal**.
- **Enhanced Loyalty Program**: Introduce tiered rewards, promotions, and partnerships.
- **Cloud Integration**: Store data in a cloud database (e.g., **Firebase** or **AWS DynamoDB**).

---