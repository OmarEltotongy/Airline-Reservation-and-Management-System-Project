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
│── CMakeLists.txt               # CMake build configuration 
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

## **Test Cases**

This section outlines the test cases for the **Airline Reservation and Management System**. These test cases cover all functionalities for the **Administrator**, **Booking Agent**, and **Passenger** roles.

---

### **1. Administrator Test Cases**

#### **1.1. Manage Flights**
- **Test Case 1.1.1: Add a New Flight**
  - **Input**: Flight Number: `AA123`, Origin: `New York (JFK)`, Destination: `Los Angeles (LAX)`, Departure Time: `2023-12-15 08:30`, Arrival Time: `2023-12-15 12:30`, Aircraft ID: `B737`, Status: `ON_TIME`, Max Seats: `150`, Price: `250.00`, Gate: `A1`
  - **Expected Output**: Flight `AA123` is added to the `flights.json` file. Success message: `Flight AA123 has been successfully added.`

- **Test Case 1.1.2: Update an Existing Flight**
  - **Input**: Flight Number: `AA123`, Field to Update: `Status`, New Status: `DELAYED`
  - **Expected Output**: Flight `AA123` status is updated to `DELAYED`. Success message: `Flight AA123 has been successfully updated.`

- **Test Case 1.1.3: Delete a Flight**
  - **Input**: Flight Number: `AA123`
  - **Expected Output**: Flight `AA123` is removed. Success message: `Flight AA123 has been successfully deleted.`

- **Test Case 1.1.4: View All Flights**
  - **Input**: None
  - **Expected Output**: A list of all flights is displayed.

---

#### **1.2. Manage Aircraft**
- **Test Case 1.2.1: Add a New Aircraft**
  - **Input**: Aircraft ID: `B787`, Model: `Boeing 787`, Maintenance Schedule: `2024-01-15`, Availability: `true`
  - **Expected Output**: Aircraft `B787` is added. Success message: `Aircraft B787 has been successfully added.`

- **Test Case 1.2.2: Update an Existing Aircraft**
  - **Input**: Aircraft ID: `B787`, Field to Update: `Availability`, New Availability: `false`
  - **Expected Output**: Aircraft `B787` availability is updated. Success message: `Aircraft B787 has been successfully updated.`

- **Test Case 1.2.3: Remove an Aircraft**
  - **Input**: Aircraft ID: `B787`
  - **Expected Output**: Aircraft `B787` is removed. Success message: `Aircraft B787 has been successfully removed.`

- **Test Case 1.2.4: View All Aircraft**
  - **Input**: None
  - **Expected Output**: A list of all aircraft is displayed.

---

#### **1.3. Manage Users**
- **Test Case 1.3.1: Add a New User**
  - **Input**: Username: `newuser`, Password: `newpass`, Role: `PASSENGER`, User ID: `U011`
  - **Expected Output**: User `newuser` is added. Success message: `User newuser has been successfully added.`

- **Test Case 1.3.2: Update User Information**
  - **Input**: Username: `newuser`, Field to Update: `Password`, New Password: `updatedpass`
  - **Expected Output**: User `newuser` password is updated. Success message: `User newuser has been successfully updated.`

- **Test Case 1.3.3: Delete a User**
  - **Input**: Username: `newuser`
  - **Expected Output**: User `newuser` is removed. Success message: `User newuser has been successfully deleted.`

- **Test Case 1.3.4: View All Users**
  - **Input**: None
  - **Expected Output**: A list of all users is displayed.

---

#### **1.4. Generate Reports**
- **Test Case 1.4.1: Operational Reports**
  - **Input**: Month and Year: `12-2023`
  - **Expected Output**: A summary of flights, reservations, and revenue for December 2023.

- **Test Case 1.4.2: Maintenance Reports**
  - **Input**: Month and Year: `01-2024`
  - **Expected Output**: A summary of maintenance tasks for January 2024.

- **Test Case 1.4.3: User Activity Reports**
  - **Input**: Month and Year: `12-2023`
  - **Expected Output**: A summary of user activity and reservations for December 2023.

---

### **2. Booking Agent Test Cases**

#### **2.1. Search Flights**
- **Test Case 2.1.1: Search for Flights**
  - **Input**: Origin: `New York (JFK)`, Destination: `Los Angeles (LAX)`, Date: `2023-12-15`
  - **Expected Output**: A list of available flights matching the criteria.

---

#### **2.2. Modify Reservation**
- **Test Case 2.2.1: Modify a Reservation**
  - **Input**: Reservation ID: `R001`, New Seat Number: `14B`
  - **Expected Output**: Reservation `R001` is updated. Success message: `Reservation R001 has been successfully modified.`

---

#### **2.3. Cancel Reservation**
- **Test Case 2.3.1: Cancel a Reservation**
  - **Input**: Reservation ID: `R001`
  - **Expected Output**: Reservation `R001` is canceled. Success message: `Reservation R001 has been successfully canceled.`

---

### **3. Passenger Test Cases**

#### **3.1. Search Flights**
- **Test Case 3.1.1: Search for Flights**
  - **Input**: Origin: `New York (JFK)`, Destination: `Los Angeles (LAX)`, Date: `2023-12-15`
  - **Expected Output**: A list of available flights matching the criteria.

---

#### **3.2. View Reservations**
- **Test Case 3.2.1: View Reservations**
  - **Input**: Passenger ID: `U003`
  - **Expected Output**: A list of reservations for passenger `U003`.

---

#### **3.3. Check-In**
- **Test Case 3.3.1: Check-In for a Flight**
  - **Input**: Reservation ID: `R001`
  - **Expected Output**: Check-in is successful. Boarding pass is generated.

---

#### **3.4. Loyalty Program**
- **Test Case 3.4.1: View Loyalty Points**
  - **Input**: Passenger ID: `U003`
  - **Expected Output**: Loyalty points for passenger `U003` are displayed.

---

### **4. General Test Cases**

#### **4.1. Login**
- **Test Case 4.1.1: Valid Login**
  - **Input**: Username: `admin1`, Password: `admin123`, Role: `ADMIN`
  - **Expected Output**: Login successful.

- **Test Case 4.1.2: Invalid Login**
  - **Input**: Username: `admin1`, Password: `wrongpass`, Role: `ADMIN`
  - **Expected Output**: Login failed.

---

#### **4.2. Logout**
- **Test Case 4.2.1: Logout**
  - **Input**: None
  - **Expected Output**: Logout successful.

---
## 🔮 Future Enhancements
- **Graphical User Interface (GUI)**: Implement a modern GUI using frameworks like **Qt** or **ImGui**.
- **Real-Time Flight Status Updates**: Integrate with external APIs for real-time flight tracking.
- **Advanced Payment Processing**: Integrate with payment gateways like **Stripe** or **PayPal**.
- **Enhanced Loyalty Program**: Introduce tiered rewards, promotions, and partnerships.
- **Cloud Integration**: Store data in a cloud database (e.g., **Firebase** or **AWS DynamoDB**).

---
