cmake_minimum_required(VERSION 3.10)
project(AirlineReservationSystem)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories (adjust paths if needed)
include_directories(
    include
    include/JSON_HPP  # Path to your downloaded json.hpp
)

# CMakeLists.txt
file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})

# Add executable
add_executable(airline_system
    src/MAIN/main.cpp
    src/AIRCRAFT_CPP/Aircraft.cpp
    src/FLIGHT_CPP/Flight.cpp
    src/JSONHELPERFUNCTION_CPP/jsonHelperFunctions.cpp
    src/RESERVATION_CPP/Reservation.cpp
    src/USERS_CPP/userClasses.cpp
)
