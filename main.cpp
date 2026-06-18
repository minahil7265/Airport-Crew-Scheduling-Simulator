#include "airport.h"

int main() 
{
    int choice;
    do 
    {
        clearScreen();
        printTitle("AIRPORT GROUND CREW SCHEDULING SYSTEM");
        cout << "[1] Flight Management\n";
        cout << "[2] Crew Management\n";
        cout << "[3] Equipment Management\n";
        cout << "[4] Task Management\n";
        cout << "[5] File Management\n";
        cout << "[6] Exit Program\n";
        line();
        choice = getValidatedInt("Enter your choice (1-6): ", 1, 6);
        switch(choice) {
            case 1: flightMenu(); break;
            case 2: crewMenu(); break;
            case 3: equipmentMenu(); break;
            case 4: taskMenu(); break;
            case 5: fileMenu(); break;
            case 6: 
                exitProgram();
                cout << "\n Program terminated successfully\n";
                break;
        }
    } while(choice != 6);
    return 0;
}