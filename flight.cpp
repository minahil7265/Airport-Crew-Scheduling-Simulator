#include "airport.h"

void addFlight() 
{
    cout << "\n--- ADD NEW FLIGHT ---\n";
    
    string flightID;
    while (true) 
    {
        flightID = getValidatedString("Enter Flight ID (exactly 6 characters): ", 6, 6);
        
        if (flightIDExists(flightID.c_str()))
        {
            cout << " Error: Flight ID '" << flightID << "' already exists. Please use a different ID.\n";
        } 
        else 
            break;
    }
    int choice;
    const char* status;
    cout << "\nSelect Flight Status:\n";
    cout << "1. SCHEDULED\n";
    cout << "2. DEPARTED\n";
    cout << "3. LANDED\n";
    cout << "4. CANCELLED\n";
    cout << "5. DELAYED\n";
    choice = getValidatedInt("Enter choice (1-5): ", 1, 5);
    switch(choice)
    {
        case 1: status = "SCHEDULED"; break;
        case 2: status = "DEPARTED"; break;
        case 3: status = "LANDED"; break;
        case 4: status = "CANCELLED"; break;
        case 5: status = "DELAYED"; break;
    }
    char **newFlightIDs = new char*[flightCount + 1];
    char **newFlightStatus = new char*[flightCount + 1];
    char ***newTaskNames = new char**[flightCount + 1];
    int **newTaskIDs = new int*[flightCount + 1];
    int **newTaskAssignedCrew = new int*[flightCount + 1];
    int **newTaskRequiredEquipment = new int*[flightCount + 1];
    int *newTaskCountPerFlight = new int[flightCount + 1];
    for(int i = 0; i < flightCount; i++) 
    {
        newFlightIDs[i] = flightIDs[i];
        newFlightStatus[i] = flightStatus[i];
        newTaskNames[i] = taskNames[i];
        newTaskIDs[i] = taskIDs[i];
        newTaskAssignedCrew[i] = taskAssignedCrew[i];
        newTaskRequiredEquipment[i] = taskRequiredEquipment[i];
        newTaskCountPerFlight[i] = taskCountPerFlight[i];
    }
    newFlightIDs[flightCount] = new char[flightID.length() + 1];
    strcpy(newFlightIDs[flightCount], flightID.c_str());
    newFlightStatus[flightCount] = new char[strlen(status) + 1];
    strcpy(newFlightStatus[flightCount], status);
    newTaskNames[flightCount] = nullptr;
    newTaskIDs[flightCount] = nullptr;
    newTaskAssignedCrew[flightCount] = nullptr;
    newTaskRequiredEquipment[flightCount] = nullptr;
    newTaskCountPerFlight[flightCount] = 0;
    delete[] flightIDs;
    delete[] flightStatus;
    delete[] taskNames;
    delete[] taskIDs;
    delete[] taskAssignedCrew;
    delete[] taskRequiredEquipment;
    delete[] taskCountPerFlight;
    flightIDs = newFlightIDs;
    flightStatus = newFlightStatus;
    taskNames = newTaskNames;
    taskIDs = newTaskIDs;
    taskAssignedCrew = newTaskAssignedCrew;
    taskRequiredEquipment = newTaskRequiredEquipment;
    taskCountPerFlight = newTaskCountPerFlight;
    flightCount++;
    cout << " Flight '" << flightID << "' added successfully with status: " << status << "\n";
}

void displayFlights() 
{
    if (flightCount == 0) 
    {
        cout << " No flights registered in the system.\n";
        return;
    }
    
    cout << "\n--- REGISTERED FLIGHTS (" << flightCount << " flights) ---\n";
    line();
    cout << setw(5) << left << "Idx" << setw(12) << "Flight ID" << setw(15) << "Status" << setw(10) << "Tasks" << "\n";
    line();
    
    for(int i = 0; i < flightCount; i++) 
    {
        cout << setw(5) << left << i 
             << setw(12) << flightIDs[i] 
             << setw(15) << flightStatus[i] 
             << setw(10) << taskCountPerFlight[i] << "\n";
    }
    line();
}
void updateFlightStatus() 
{
    if (flightCount == 0) 
    {
        cout << " No flights available to update.\n";
        return;
    }
    displayFlights();
    int choice = getValidatedInt("\nUpdate flight by:\n1. Index\n2. Flight ID\nEnter choice (1-2): ", 1, 2);
    int flightIndex = -1;
    if (choice == 1) 
    {
        flightIndex = getValidatedInt("Enter Flight Index: ", 0, flightCount - 1);
    }
     else 
    {
        string flightID = getValidatedString("Enter Flight ID: ", 1, MAX_NAME - 1);
        bool found = false;
        for (int i = 0; i < flightCount; i++) 
        {
            if (strcmp(flightIDs[i], flightID.c_str()) == 0) 
            {
                flightIndex = i;
                found = true;
                break;
            }
        }
        if (!found) 
        {
            cout << " Flight ID '" << flightID << "' not found!\n";
            return;
        }
    }
    cout << "\nCurrent status of Flight " << flightIDs[flightIndex] << ": " << flightStatus[flightIndex] << "\n";
    cout << "\nSelect new status:\n";
    cout << "1. SCHEDULED\n";
    cout << "2. DEPARTED\n";
    cout << "3. LANDED\n";
    cout << "4. CANCELLED\n";
    cout << "5. DELAYED\n";
    int statusChoice = getValidatedInt("Enter new status (1-5): ", 1, 5);
    const char* newStatus;
    switch(statusChoice) {
        case 1: newStatus = "SCHEDULED"; break;
        case 2: newStatus = "DEPARTED"; break;
        case 3: newStatus = "LANDED"; break;
        case 4: newStatus = "CANCELLED"; break;
        case 5: newStatus = "DELAYED"; break;
    }
    delete[] flightStatus[flightIndex];
    flightStatus[flightIndex] = new char[strlen(newStatus) + 1];
    strcpy(flightStatus[flightIndex], newStatus);
    cout << " Status updated for Flight " << flightIDs[flightIndex] << " to: " << newStatus << "\n";
}
void listFlightTasks() 
{
    if (flightCount == 0)
    {
        cout << "No flights available.\n";
        return;
    }
    displayFlights();
    int choice = getValidatedInt("\nSelect flight by:\n1. Index\n2. Flight ID\nEnter choice (1-2): ", 1, 2);
    int flightIndex = -1;
    if (choice == 1)
    {
        flightIndex = getValidatedInt("Enter Flight Index: ", 0, flightCount - 1);
    } 
    else
    {
        string flightID = getValidatedString("Enter Flight ID: ", 1, MAX_NAME - 1);
        bool found = false;
        for (int i = 0; i < flightCount; i++) 
        {
            if (strcmp(flightIDs[i], flightID.c_str()) == 0)
            {
                flightIndex = i;
                found = true;
                break;
            }
        }
        if (!found) 
        {
            cout << " Flight ID '" << flightID << "' not found!\n";
            return;
        }
    }
    cout << "\n--- TASKS FOR FLIGHT " << flightIDs[flightIndex] << " ---\n";
    if (taskCountPerFlight[flightIndex] == 0) 
    {
        cout << "No tasks assigned to this flight.\n";
        return;
    }
    line();
    cout << setw(5) << "Idx" 
         << setw(10) << "Task ID" 
         << setw(25) << "Task Name" 
         << setw(15) << "Assigned Crew" 
         << setw(15) << "Required Equip" << "\n";
    line();
    for (int t = 0; t < taskCountPerFlight[flightIndex]; t++) 
    {
        cout << setw(5) << t 
             << setw(10) << taskIDs[flightIndex][t] 
             << setw(25) << taskNames[flightIndex][t] 
             << setw(15);
        
        if (taskAssignedCrew[flightIndex][t] == -1)
            cout << "N A";
        else
            cout << taskAssignedCrew[flightIndex][t];

        cout << setw(15) << taskRequiredEquipment[flightIndex][t] << "\n";
    }
    line();
    cout << "Total tasks: " << taskCountPerFlight[flightIndex] << "\n";
}
void searchFlightByID() {
    if (flightCount == 0) 
    {
        cout << " No flights available to search.\n";
        return;
    }
    string searchID = getValidatedString("Enter Flight ID to search: ", 1, MAX_NAME - 1);
    bool found = false;
    for (int i = 0; i < flightCount; i++) 
    {
        if (strcmp(flightIDs[i], searchID.c_str()) == 0) {
            cout << "\n✓ Flight Found!\n";
            line();
            cout << "Flight ID: " << flightIDs[i] << "\n";
            cout << "Status: " << flightStatus[i] << "\n";
            cout << "Total Tasks: " << taskCountPerFlight[i] << "\n";
            cout << "Index: " << i << "\n";
            line();
            found = true;
            break;
        }
    }
    if (!found) {
        cout << " Flight ID '" << searchID << "' not found in the system.\n";
    }
}
void flightMenu() {
    int ch;
    do {
        clearScreen();
        printTitle("FLIGHT MANAGEMENT");
        cout << "[1] Add Flight\n";
        cout << "[2] Display Flights\n";
        cout << "[3] Update Flight Status\n";
        cout << "[4] List Flight Tasks\n";
        cout << "[5] Search Flight by ID\n";
        cout << "[6] Back to Main Menu\n";
        line();
        ch = getValidatedInt("Enter choice (1-6): ", 1, 6);
        switch(ch) {
            case 1: addFlight(); break;
            case 2: displayFlights(); break;
            case 3: updateFlightStatus(); break;
            case 4: listFlightTasks(); break;
            case 5: searchFlightByID(); break;
            case 6: break;
        }
        if (ch != 6) { 
            cout << "\nPress Enter to continue..."; 
            cin.get(); 
        }

    } while(ch != 6);
}