#include "airport.h"

void addTaskToFlight() 
{
    if (flightCount == 0) 
    {
        cout << "No flights available to assign tasks.\n";
        return;
    }
    displayFlights();
    int flightIdx = getValidatedInt("Enter Flight index to add task: ", 0, flightCount - 1);
    cout << "\nAdding task to Flight: " << flightIDs[flightIdx] << "\n";
    int taskID;
    while (true) 
    {
        taskID = getValidatedInt("Enter Task ID (1-9999): ", 1, 9999);
        bool taskExists = false;
        for (int t = 0; t < taskCountPerFlight[flightIdx]; t++) 
        {
            if (taskIDs[flightIdx][t] == taskID) 
            {
                taskExists = true;
                break;
            }
        }
        if (taskExists) 
        {
            cout << "Task ID " << taskID << " already exists for this flight! Please use a different ID.\n";
        } else 
        {
            break;
        }
    }
    string taskName = getValidatedString("Enter Task Name: ", 1, MAX_NAME - 1);
    if (equipmentCount == 0) 
    {
        cout << "No equipment registered. Please add equipment first.\n";
        return;
    }
    displayEquipment();
    int requiredEquip = getValidatedInt("Enter Required Equipment ID: ", 0, 9999);
    bool equipFound = false;
    for (int i = 0; i < equipmentCount; i++) 
    {
        if (equipmentIDs[i] == requiredEquip) 
        {
            equipFound = true;
            if (!equipmentAvailable[i]) 
            {
                cout << "Warning: Equipment ID " << requiredEquip << " is currently unavailable!\n";
            }
            break;
        }
    }
    if (!equipFound) {
        if (!getYesNoInput("Equipment ID not found. Do you want to continue anyway?")) {
            cout << "Task creation cancelled.\n";
            return;
        }
    }
    int newTaskCount = taskCountPerFlight[flightIdx] + 1;
    char **newTaskNames = new char*[newTaskCount];
    int *newTaskIDs = new int[newTaskCount];
    int *newTaskAssignedCrew = new int[newTaskCount];
    int *newTaskRequiredEquipment = new int[newTaskCount];
    for (int i = 0; i < taskCountPerFlight[flightIdx]; i++) 
    {
        newTaskNames[i] = taskNames[flightIdx][i];
        newTaskIDs[i] = taskIDs[flightIdx][i];
        newTaskAssignedCrew[i] = taskAssignedCrew[flightIdx][i];
        newTaskRequiredEquipment[i] = taskRequiredEquipment[flightIdx][i];
    }
    newTaskNames[newTaskCount - 1] = new char[taskName.length() + 1];
    strcpy(newTaskNames[newTaskCount - 1], taskName.c_str());
    newTaskIDs[newTaskCount - 1] = taskID;
    newTaskAssignedCrew[newTaskCount - 1] = -1; 
    newTaskRequiredEquipment[newTaskCount - 1] = requiredEquip;
    delete[] taskNames[flightIdx];
    delete[] taskIDs[flightIdx];
    delete[] taskAssignedCrew[flightIdx];
    delete[] taskRequiredEquipment[flightIdx];
    taskNames[flightIdx] = newTaskNames;
    taskIDs[flightIdx] = newTaskIDs;
    taskAssignedCrew[flightIdx] = newTaskAssignedCrew;
    taskRequiredEquipment[flightIdx] = newTaskRequiredEquipment;
    taskCountPerFlight[flightIdx] = newTaskCount;
    cout << "Task '" << taskName << "' (ID: " << taskID << ") added to Flight " << flightIDs[flightIdx] << ".\n";
}

void displayTasks() 
{
    if (flightCount == 0) 
    {
        cout << "No flights available to display tasks for.\n";
        return;
    }
    int totalTasks = 0;
    for (int f = 0; f < flightCount; f++)
    {
        totalTasks += taskCountPerFlight[f];
    }
    if (totalTasks == 0) 
    {
        cout << "No tasks assigned to any flight.\n";
        return;
    }
    cout << "\n--- ALL TASKS ACROSS ALL FLIGHTS (" << totalTasks << " tasks total) ---\n";
    for (int f = 0; f < flightCount; f++) 
    {
        if (taskCountPerFlight[f] > 0) 
        {
            cout << "\n--- Flight: " << flightIDs[f] << " (" << taskCountPerFlight[f] << " tasks) ---\n";
            line();
            cout << setw(5) << "Idx" << setw(10) << "Task ID" << setw(25) << "Task Name" 
                 << setw(15) << "Assigned Crew" << setw(15) << "Required Equip" << "\n";
            line();
            
            for (int t = 0; t < taskCountPerFlight[f]; t++) 
            {
                cout << setw(5) << t 
                     << setw(10) << taskIDs[f][t] 
                     << setw(25) << taskNames[f][t] 
                     << setw(15) << (taskAssignedCrew[f][t] == -1 ? "N/A" : to_string(taskAssignedCrew[f][t]))
                     << setw(15) << taskRequiredEquipment[f][t] << "\n";
            }
            line();
        }
    }
}

void assignCrewToTask() 
{
    if (flightCount == 0 || crewCount == 0) 
    {
        cout << "No flights or crew members available for assignment.\n";
        return;
    }
    displayFlights();
    int flightIdx = getValidatedInt("Enter Flight index: ", 0, flightCount - 1);

    if (taskCountPerFlight[flightIdx] == 0) 
    {
        cout << "No tasks available for Flight " << flightIDs[flightIdx] << "\n";
        return;
    }
    listFlightTasks();
    int taskIdx = getValidatedInt("Enter Task index: ", 0, taskCountPerFlight[flightIdx] - 1);
    if (taskAssignedCrew[flightIdx][taskIdx] != -1) 
    {
        cout << "This task is already assigned to Crew ID: " << taskAssignedCrew[flightIdx][taskIdx] << "\n";
        if (!getYesNoInput("Do you want to reassign it?"))
        {
            return;
        }
    }
    cout << "\n--- AVAILABLE CREW MEMBERS ---\n";
    bool hasAvailableCrew = false;
    line();
    cout << setw(5) << "Idx" << setw(10) << "Crew ID" << setw(25) << "Name" << "\n";
    line();
    
    for (int i = 0; i < crewCount; i++) 
    {
        if (crewAvailable[i]) 
        {
            cout << setw(5) << i << setw(10) << crewIDs[i] << setw(25) << crewNames[i] << "\n";
            hasAvailableCrew = true;
        }
    }
    line();

    if (!hasAvailableCrew) 
    {
        cout << "No available crew members to assign!\n";
        return;
    }
    int crewIdx = getValidatedInt("Enter Crew index to assign: ", 0, crewCount - 1);
    if (!crewAvailable[crewIdx])
    {
        cout << "Crew member is not available for assignment!\n";
        return;
    }
    taskAssignedCrew[flightIdx][taskIdx] = crewIDs[crewIdx];
    crewAvailable[crewIdx] = false;

    cout << "Crew ID " << crewIDs[crewIdx] << " (" << crewNames[crewIdx] 
         << ") assigned to Task '" << taskNames[flightIdx][taskIdx] 
         << "' for Flight " << flightIDs[flightIdx] << ".\n";
}

void startService() 
{
    cout << "\n=== SERVICE INITIATION ===\n";
    
    int assignedTasks = 0;
    for (int f = 0; f < flightCount; f++) 
    {
        for (int t = 0; t < taskCountPerFlight[f]; t++) 
        {
            if (taskAssignedCrew[f][t] != -1) 
            {
                assignedTasks++;
            }
        }
    }
    cout << " Service started for all flights.\n";
    cout << " " << assignedTasks << " tasks have crew assignments.\n";
    cout << "Crew and equipment allocations are now active.\n";
    cout << "=== SERVICE INITIATION COMPLETE ===\n";
}

void completeTask() 
{
    if (flightCount == 0) 
    {
        cout << "No flights available.\n";
        return;
    }
    displayFlights();
    int flightIdx = getValidatedInt("Enter Flight index: ", 0, flightCount - 1);

    if (taskCountPerFlight[flightIdx] == 0) 
    {
        cout << "No tasks available for Flight " << flightIDs[flightIdx] << "\n";
        return;
    }
    listFlightTasks();
    int taskIdx = getValidatedInt("Enter Task index to COMPLETE: ", 0, taskCountPerFlight[flightIdx] - 1);

    int assignedCrewID = taskAssignedCrew[flightIdx][taskIdx];
    
    if (assignedCrewID == -1) 
    {
        cout << "Task '" << taskNames[flightIdx][taskIdx] << "' completed (was not assigned to any crew).\n";
    } else 
    {
        for (int i = 0; i < crewCount; i++) 
        {
            if (crewIDs[i] == assignedCrewID) 
            {
                crewAvailable[i] = true;
                cout << "Task '" << taskNames[flightIdx][taskIdx] << "' completed.\n";
                cout << "Crew ID " << assignedCrewID << " (" << crewNames[i] << ") released and marked available.\n";
                break;
            }
        }
    }
    taskAssignedCrew[flightIdx][taskIdx] = -1;
}

void taskMenu() 
{
    int ch;
    do {
        clearScreen();
        printTitle("TASK MANAGEMENT");
        cout << "[1] Add Task to Flight\n";
        cout << "[2] Display All Tasks (by Flight)\n";
        cout << "[3] Assign Crew to Task\n";
        cout << "[4] Start Service (System Message)\n";
        cout << "[5] Complete Task\n";
        cout << "[6] Back to Main Menu\n";
        line();
        ch = getValidatedInt("Enter choice (1-6): ", 1, 6);
        switch(ch) {
            case 1: addTaskToFlight(); break;
            case 2: displayTasks(); break;
            case 3: assignCrewToTask(); break;
            case 4: startService(); break;
            case 5: completeTask(); break;
            case 6: break;
        }
        if (ch != 6) { 
            cout << "\nPress Enter to continue..."; 
            cin.get(); 
        }

    } while(ch != 6);
}