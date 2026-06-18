#include "airport.h"

void addEquipment() 
{
    cout << "\n--- ADD NEW EQUIPMENT ---\n";
    int equipID;
    while (true) 
    {
        equipID = getValidatedInt("Enter Equipment ID (100-9999): ", 100, 9999);
        
        if (equipmentIDExists(equipID)) {
            cout << " Equipment ID " << equipID << " already exists! Please use a different ID.\n";
        }
         else
        {
            break;
        }
    }
    string equipName = getValidatedString("Enter Equipment Name: ", 1, MAX_NAME - 1);
    char **newEquipmentNames = new char*[equipmentCount + 1];
    int *newEquipmentIDs = new int[equipmentCount + 1];
    bool *newEquipmentAvailable = new bool[equipmentCount + 1];
    for (int i = 0; i < equipmentCount; i++) 
    {
        newEquipmentNames[i] = equipmentNames[i];
        newEquipmentIDs[i] = equipmentIDs[i];
        newEquipmentAvailable[i] = equipmentAvailable[i];
    }
    newEquipmentNames[equipmentCount] = new char[equipName.length() + 1];
    strcpy(newEquipmentNames[equipmentCount], equipName.c_str());
    newEquipmentIDs[equipmentCount] = equipID;
    newEquipmentAvailable[equipmentCount] = true;
    delete[] equipmentNames;
    delete[] equipmentIDs;
    delete[] equipmentAvailable;
    equipmentNames = newEquipmentNames;
    equipmentIDs = newEquipmentIDs;
    equipmentAvailable = newEquipmentAvailable;
    equipmentCount++;
    cout << " Equipment '" << equipName << "' (ID: " << equipID << ") added successfully and marked as Available.\n";
}
void displayEquipment() 
{
    if (equipmentCount == 0) 
    {
        cout << " No equipment registered.\n";
        return;
    }   
    int availableCount = 0;
    for (int i = 0; i < equipmentCount; i++)
    {
        if (equipmentAvailable[i]) availableCount++;
    }
    cout << "\n--- EQUIPMENT (" << equipmentCount << " total, " << availableCount << " available) ---\n";
    line();
    cout << setw(5) << left << "Idx" << setw(10) << "Equip ID" << setw(25) << "Name" << setw(12) << "Available" << "\n";
    line();
    for (int i = 0; i < equipmentCount; i++) 
    {
        cout << setw(5) << left << i 
             << setw(10) << equipmentIDs[i] 
             << setw(25) << equipmentNames[i] 
             << setw(12) << (equipmentAvailable[i] ? "Yes" : " No") << "\n";
    }
    line();
}

void markEquipmentAvailable() 
{
    if (equipmentCount == 0) 
    {
        cout << " No equipment available.\n";
        return;
    }
    displayEquipment();
    int idx = getValidatedInt("Enter Equipment index to mark as AVAILABLE: ", 0, equipmentCount - 1);
    
    if (equipmentAvailable[idx])
    {
        cout << " Equipment ID " << equipmentIDs[idx] << " is already marked as available.\n";
    } else
    {
        equipmentAvailable[idx] = true;
        cout << "Equipment ID " << equipmentIDs[idx] << " (" << equipmentNames[idx] << ") marked as available.\n";
    }
}

void markEquipmentUnavailable() 
{
    if (equipmentCount == 0)
    {
        cout << "No equipment available.\n";
        return;
    }
    displayEquipment();
    int idx = getValidatedInt("Enter Equipment index to mark as UNAVAILABLE: ", 0, equipmentCount - 1);
    
    if (!equipmentAvailable[idx]) {
        cout << " Equipment ID " << equipmentIDs[idx] << " is already marked as unavailable.\n";
    } else {
        equipmentAvailable[idx] = false;
        cout << "Equipment ID " << equipmentIDs[idx] << " (" << equipmentNames[idx] << ") marked as unavailable.\n";
    }
}

void countAvailableEquipment() 
{
    int availableCount = 0;
    for (int i = 0; i < equipmentCount; i++) 
    {
        if (equipmentAvailable[i]) availableCount++;
    }
    cout << "\n--- EQUIPMENT AVAILABILITY SUMMARY ---\n";
    cout << "Total Equipment: " << equipmentCount << "\n";
    cout << "Available Equipment: " << availableCount << "\n";
    cout << "Unavailable Equipment: " << (equipmentCount - availableCount) << "\n";
    cout << "Availability Rate: " << fixed << setprecision(1) 
         << (equipmentCount > 0 ? (availableCount * 100.0 / equipmentCount) : 0) << "%\n";
}

void searchEquipmentByID() 
{
    if (equipmentCount == 0) 
    {
        cout << "No equipment available to search.\n";
        return;
    }
    int searchID = getValidatedInt("Enter Equipment ID to search: ", 0, 9999);
    bool found = false;
    for (int i = 0; i < equipmentCount; i++) 
    {
        if (equipmentIDs[i] == searchID) 
        {
            cout << "\n Equipment Found!\n";
            line();
            cout << "Equipment ID: " << equipmentIDs[i] << "\n";
            cout << "Name: " << equipmentNames[i] << "\n";
            cout << "Available: " << (equipmentAvailable[i] ? "Yes" : "No") << "\n";
            cout << "Index: " << i << "\n";
            line();
            found = true;
            break;
        }
    }
    if (!found) 
    {
        cout << " Equipment ID " << searchID << " not found in the system.\n";
    }
}

void equipmentMenu() 
{
    int ch;
    do {
        clearScreen();
        printTitle("EQUIPMENT MANAGEMENT");
        cout << "[1] Add Equipment\n";
        cout << "[2] Display Equipment\n";
        cout << "[3] Mark Available\n";
        cout << "[4] Mark Unavailable\n";
        cout << "[5] Count Available Equipment\n";
        cout << "[6] Search Equipment by ID\n";
        cout << "[7] Back to Main Menu\n";
        line();
        ch = getValidatedInt("Enter choice (1-7): ", 1, 7);
        switch(ch) {
            case 1: addEquipment(); break;
            case 2: displayEquipment(); break;
            case 3: markEquipmentAvailable(); break;
            case 4: markEquipmentUnavailable(); break;
            case 5: countAvailableEquipment(); break;
            case 6: searchEquipmentByID(); break;
            case 7: break;
        }
        if (ch != 7) { 
            cout << "\nPress Enter to continue..."; 
            cin.get(); 
        }

    } while(ch != 7);
}