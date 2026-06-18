# Airport-Crew-Scheduling-Simulator


A fully dynamic, pointer-based C++ console application that manages Flights, Crew, and Equipment with complete binary file saving/loading, flexible data entry, and robust memory management using Object-Oriented Programming (OOP) principles.

This comprehensive C++ application is designed to manage airport ground operations, including flight scheduling, crew management, equipment tracking, and task assignments.

---

 Features

- Flight Managemen: Add, display, update status, and search flights.
- Crew Management: Register crew members, track availability, and assign to tasks.
-Equipment Management**: Maintain equipment inventory with availability status.
-Task Management: Create tasks, assign crew and equipment, track completion.
-File Operations: Save/load data in both text and binary formats.
- Input Validation: Robust error handling and user input validation.

---

 Requirements

- C++ Compiler (GCC, Clang, or MSVC)
- Standard C++ Library
- Compatible with Windows, Linux, and macOS

---

 Compilation

Using g++:
```bash
g++ -o airport_system main.cpp flight.cpp crew.cpp equipment.cpp task.cpp utilities.cpp globals.cpp

Usage

Compile the program using the instructions above.

Run the executable:
./airport_system

Using Makefile:
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
TARGET = airport_system
SOURCES = main.cpp flight.cpp crew.cpp equipment.cpp task.cpp utilities.cpp globals.cpp



Navigate through the menu-driven interface:

Flight Management: Add and manage flights.
Crew Management: Handle crew members and availability.
Equipment Management: Track equipment inventory.
Task Management: Assign and complete tasks
File Management: Save and load system data.


airport-system/
├── README.md          
├── main.cpp           
├── flight.cpp          
├── crew.cpp          
├── equipment.cpp       
├── task.cpp           
├── utilities.cpp       
├── globals.cpp        
├── airport_data.txt    
├── airport_data.bin    
└── airport.h           


 Input Validation

Integer input validation with range checking.
String input validation with length limits.
Duplicate ID prevention.
Yes/No input handling.

Dynamic Memory Management

The system uses dynamic memory allocation for:
Flight information arrays.
Crew member data.
Equipment inventory.
Task assignments.
Automatic memory cleanup on program exit.

Sample Data

Flight Status Options:
SCHEDULED
DEPARTED
LANDED
CANCELLED
DELAYED

ID Ranges:

Crew IDs: 100–999
Equipment IDs: 100–9999
Task IDs: 1–9999
Flight IDs: Exactly 6 characters

 Error Handling

Input validation for all user interactions.
File operation error checking.
Memory allocation safety.
Graceful program termination.

 License

Academic Project – Educational Use.
