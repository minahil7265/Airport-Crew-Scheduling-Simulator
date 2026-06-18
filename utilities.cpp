#include "airport.h"

int getValidatedInt(const string& prompt, int minVal, int maxVal) 
{
    int value;
    while (true)
    {
        cout << prompt;
        if (cin >> value) 
        {
            if (value >= minVal && value <= maxVal) 
            {
                cin.ignore();
                return value;
            } 
            else 
            {
                cout << " Error: Value must be between " << minVal << " and " << maxVal << ". Please try again.\n";
                clearScreen();
            }
        } 
        else 
        {
            cout << " Error: Invalid input. Please enter a valid number.\n";
            cin.clear();
            cin.ignore();
        }
    }
}

string getValidatedString(const string& prompt, int minLength, int maxLength) 
{
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        
        if (input.length() < minLength || input.length() > maxLength)
        {
            cout << " Error: Input must be between " << minLength << " and " << maxLength 
                 << " characters. Please try again.\n";
        } 
        else 
        {
            bool valid = true;
            for (char c : input) 
            {
                if (c < 32 || c > 126) 
                {
                    valid = false;
                    break;
                }
            }
            if (valid)   return input; 
            else     cout << " Error: Input contains invalid characters.\n";    
        }
    }
}

bool getYesNoInput(const string& prompt) 
{
    string input;
    while (true)
   {
        cout << prompt << " (y/n): ";
        getline(cin, input);
        
        if (input == "y" || input == "Y" || input == "yes" || input == "YES")  return true;
        else if (input == "n" || input == "N" || input == "no" || input == "NO")   return false;
        else     cout << " Error: Please enter 'y' for yes or 'n' for no.\n";
    }
}

bool crewIDExists(int id) 
{
    for (int i = 0; i < crewCount; i++) 
    {
        if (crewIDs[i] == id) return true;
    }
    return false;
}

bool equipmentIDExists(int id) 
{
    for (int i = 0; i < equipmentCount; i++) 
    {
        if (equipmentIDs[i] == id) return true;
    }
    return false;
}

bool flightIDExists(const char* id) 
{
    for (int i = 0; i < flightCount; i++) 
    {
        if (strcmp(flightIDs[i], id) == 0) return true;
    }
    return false;
}

void clearScreen() 
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void printTitle(const char *title) 
{
    cout << "\n===============================================================\n";
    cout << "                         " << title << "\n";
    cout << "===============================================================\n";
}

void line()
{
    cout << "---------------------------------------------------------------\n";
}

void saveDataToText() 
{
    char choice;
    cout << "Do you want to append to the file or overwrite it? (A = Append, T = Truncate): ";
    cin >> choice;

    ofstream fout;
    if (choice == 'A' || choice == 'a') 
    {
        fout.open("airport_data.txt", ios::app);  
    } else {
        fout.open("airport_data.txt", ios::trunc);
    }

    if (!fout) 
    {
        cout << "Error opening file for saving!\n";
        return;
    }

    fout << "===============================================================\n";
    fout << "                   AIRPORT MANAGEMENT SYSTEM DATA\n";
    fout << "===============================================================\n";
    fout << "Generated on: " << __DATE__ << " at " << __TIME__ << "\n\n";
    fout << "FLIGHTS (" << flightCount << " total)\n";
    fout << "---------------------------------------------------------------\n";
    fout << "Index | Flight ID | Status     | Task Count\n";
    fout << "---------------------------------------------------------------\n";
    
    for (int i = 0; i < flightCount; i++) 
    {
        fout << setw(5) << i << " | " 
             << setw(9) << flightIDs[i] << " | " 
             << setw(10) << flightStatus[i] << " | " 
             << setw(10) << taskCountPerFlight[i] << "\n";
    }
    fout << "---------------------------------------------------------------\n\n";

    fout << "TASKS (Detailed by Flight)\n";
    fout << "===============================================================\n";
    
    for (int i = 0; i < flightCount; i++) 
    {
        if (taskCountPerFlight[i] > 0) 
        {
            fout << "\nFlight: " << flightIDs[i] << " - " << taskCountPerFlight[i] << " tasks\n";
            fout << "---------------------------------------------------------------\n";
            fout << "TaskID | Task Name               | Assigned Crew | Required Equip\n";
            fout << "---------------------------------------------------------------\n";
            
            for (int t = 0; t < taskCountPerFlight[i]; t++) 
            {
                fout << setw(6) << taskIDs[i][t] << " | " 
                     << setw(23) << taskNames[i][t] << " | " 
                     << setw(13) << (taskAssignedCrew[i][t] == -1 ? "N/A" : to_string(taskAssignedCrew[i][t])) << " | " 
                     << setw(14) << taskRequiredEquipment[i][t] << "\n";
            }
            fout << "---------------------------------------------------------------\n";
        }
    }
    fout << "\n";

    fout << "CREW MEMBERS (" << crewCount << " total)\n";
    fout << "---------------------------------------------------------------\n";
    fout << "CrewID | Name                     | Available\n";
    fout << "---------------------------------------------------------------\n";
    
    for (int i = 0; i < crewCount; i++)
    {
        fout << setw(6) << crewIDs[i] << " | " 
             << setw(24) << crewNames[i] << " | " 
             << setw(8) << (crewAvailable[i] ? "Yes" : "No") << "\n";
    }
    fout << "---------------------------------------------------------------\n\n";

    fout << "EQUIPMENT (" << equipmentCount << " total)\n";
    fout << "---------------------------------------------------------------\n";
    fout << "EquipID | Name                     | Available\n";
    fout << "---------------------------------------------------------------\n";
    
    for (int i = 0; i < equipmentCount; i++)
    {
        fout << setw(7) << equipmentIDs[i] << " | " 
             << setw(24) << equipmentNames[i] << " | " 
             << setw(8) << (equipmentAvailable[i] ? "Yes" : "No") << "\n";
    }
    fout << "---------------------------------------------------------------\n";

    fout << "\nSUMMARY\n";
    fout << "===============================================================\n";
    fout << "Total Flights:        " << flightCount << "\n";
    
    int totalTasks = 0;
    for (int i = 0; i < flightCount; i++) {
        totalTasks += taskCountPerFlight[i];
    }
    fout << "Total Tasks:          " << totalTasks << "\n";
    
    int availableCrew = 0;
    for (int i = 0; i < crewCount; i++) {
        if (crewAvailable[i]) availableCrew++;
    }
    fout << "Available Crew:       " << availableCrew << "/" << crewCount << "\n";
    
    int availableEquipment = 0;
    for (int i = 0; i < equipmentCount; i++) {
        if (equipmentAvailable[i]) availableEquipment++;
    }
    fout << "Available Equipment:  " << availableEquipment << "/" << equipmentCount << "\n";
    fout << "===============================================================\n";

    fout.close();
    cout << "Data saved to airport_data.txt with professional formatting.\n";
}


void loadDataFromText()
{
    ifstream fin("airport_data.txt");
    if (!fin) 
    {
        cout << "Text file not found! (airport_data.txt)\n";
        return;
    }
    clearScreen();
    string line;
    cout << "========== AIRPORT DATA FROM FILE ==========\n\n";

    while (getline(fin, line))
    {
        cout << line << "\n";
    }

    fin.close();
    cout << "\nData displayed from airport_data.txt successfully.\n";
}


void loadDataFromBinary()
{
    ifstream fin("airport_data.bin", ios::binary);
    if (!fin)
    {
        cout << "Binary file not found! (airport_data.bin)\n";
        return;
    }

  
    exitProgram();

    
    fin.read((char*)&flightCount, sizeof(flightCount));
    
    if (flightCount > 0) 
    {
        flightIDs = new char*[flightCount];
        flightStatus = new char*[flightCount];
        taskCountPerFlight = new int[flightCount];
        taskNames = new char**[flightCount];
        taskIDs = new int*[flightCount];
        taskAssignedCrew = new int*[flightCount];
        taskRequiredEquipment = new int*[flightCount];

        for (int i = 0; i < flightCount; i++) 
        {
            int len;
            fin.read((char*)&len, sizeof(len));
            flightIDs[i] = new char[len];
            fin.read(flightIDs[i], len);

            fin.read((char*)&len, sizeof(len));
            flightStatus[i] = new char[len];
            fin.read(flightStatus[i], len);

            fin.read((char*)&taskCountPerFlight[i], sizeof(taskCountPerFlight[i]));

            taskNames[i] = new char*[taskCountPerFlight[i]];
            taskIDs[i] = new int[taskCountPerFlight[i]];
            taskAssignedCrew[i] = new int[taskCountPerFlight[i]];
            taskRequiredEquipment[i] = new int[taskCountPerFlight[i]];

            for (int t = 0; t < taskCountPerFlight[i]; t++) 
            {
                fin.read((char*)&taskIDs[i][t], sizeof(int));

                fin.read((char*)&len, sizeof(len));
                taskNames[i][t] = new char[len];
                fin.read(taskNames[i][t], len);

                fin.read((char*)&taskAssignedCrew[i][t], sizeof(int));
                fin.read((char*)&taskRequiredEquipment[i][t], sizeof(int));
            }
        }
    }

    fin.read((char*)&crewCount, sizeof(crewCount));
    
    if (crewCount > 0) 
    {
        crewIDs = new int[crewCount];
        crewNames = new char*[crewCount];
        crewAvailable = new bool[crewCount];

        for (int i = 0; i < crewCount; i++) 
        {
            fin.read((char*)&crewIDs[i], sizeof(int));

            int len;
            fin.read((char*)&len, sizeof(len));
            crewNames[i] = new char[len];
            fin.read(crewNames[i], len);

            fin.read((char*)&crewAvailable[i], sizeof(bool));
        }
    }

    fin.read((char*)&equipmentCount, sizeof(equipmentCount));
    
    if (equipmentCount > 0) 
    {
        equipmentIDs = new int[equipmentCount];
        equipmentNames = new char*[equipmentCount];
        equipmentAvailable = new bool[equipmentCount];

        for (int i = 0; i < equipmentCount; i++) 
        {
            fin.read((char*)&equipmentIDs[i], sizeof(int));

            int len;
            fin.read((char*)&len, sizeof(len));
            equipmentNames[i] = new char[len];
            fin.read(equipmentNames[i], len);

            fin.read((char*)&equipmentAvailable[i], sizeof(bool));
        }
    }

    fin.close();
    
    clearScreen();
    cout << "========== DATA LOADED FROM BINARY FILE ==========\n\n";
    
    cout << "FLIGHTS (" << flightCount << " total)\n";
    cout << "---------------------------------------------------------------\n";
    cout << "Index | Flight ID | Status     | Task Count\n";
    cout << "---------------------------------------------------------------\n";
    
    for (int i = 0; i < flightCount; i++) 
    {
        cout << setw(5) << i << " | " 
             << setw(9) << flightIDs[i] << " | " 
             << setw(10) << flightStatus[i] << " | " 
             << setw(10) << taskCountPerFlight[i] << "\n";
    }
    cout << "---------------------------------------------------------------\n\n";

    cout << "TASKS (Detailed by Flight)\n";
    cout << "===============================================================\n";
    
    for (int i = 0; i < flightCount; i++) 
    {
        if (taskCountPerFlight[i] > 0) 
        {
            cout << "\nFlight: " << flightIDs[i] << " - " << taskCountPerFlight[i] << " tasks\n";
            cout << "---------------------------------------------------------------\n";
            cout << "TaskID | Task Name               | Assigned Crew | Required Equip\n";
            cout << "---------------------------------------------------------------\n";
            
            for (int t = 0; t < taskCountPerFlight[i]; t++) 
            {
                cout << setw(6) << taskIDs[i][t] << " | " 
                     << setw(23) << taskNames[i][t] << " | " 
                     << setw(13) << (taskAssignedCrew[i][t] == -1 ? "N/A" : to_string(taskAssignedCrew[i][t])) << " | " 
                     << setw(14) << taskRequiredEquipment[i][t] << "\n";
            }
            cout << "---------------------------------------------------------------\n";
        }
    }
    cout << "\n";
    cout << "CREW MEMBERS (" << crewCount << " total)\n";
    cout << "---------------------------------------------------------------\n";
    cout << "CrewID | Name                     | Available\n";
    cout << "---------------------------------------------------------------\n";
    
    for (int i = 0; i < crewCount; i++)
    {
        cout << setw(6) << crewIDs[i] << " | " 
             << setw(24) << crewNames[i] << " | " 
             << setw(8) << (crewAvailable[i] ? "Yes" : "No") << "\n";
    }
    cout << "---------------------------------------------------------------\n\n";

    cout << "EQUIPMENT (" << equipmentCount << " total)\n";
    cout << "---------------------------------------------------------------\n";
    cout << "EquipID | Name                     | Available\n";
    cout << "---------------------------------------------------------------\n";
    
    for (int i = 0; i < equipmentCount; i++)
    {
        cout << setw(7) << equipmentIDs[i] << " | " 
             << setw(24) << equipmentNames[i] << " | " 
             << setw(8) << (equipmentAvailable[i] ? "Yes" : "No") << "\n";
    }
    cout << "---------------------------------------------------------------\n";

    cout << "\nData loaded from binary file and displayed successfully.\n";
}

void saveDataToBinary()
{
    char choice;
    cout << "Do you want to append to the binary file or overwrite it? (A = Append, T = Truncate): ";
    cin >> choice;

    ofstream fout;

    if (choice == 'A' || choice == 'a')
        fout.open("airport_data.bin", ios::binary | ios::app);   
    else
        fout.open("airport_data.bin", ios::binary | ios::trunc);

    if (!fout) 
    {
        cout << "Error opening binary file for saving\n";
        return;
    }

    fout.write((char*)&flightCount, sizeof(flightCount));

    for (int i = 0; i < flightCount; i++) 
    {
        int len = strlen(flightIDs[i]) + 1;
        fout.write((char*)&len, sizeof(len));
        fout.write(flightIDs[i], len);

        len = strlen(flightStatus[i]) + 1;
        fout.write((char*)&len, sizeof(len));
        fout.write(flightStatus[i], len);

        fout.write((char*)&taskCountPerFlight[i], sizeof(taskCountPerFlight[i]));

        for (int t = 0; t < taskCountPerFlight[i]; t++) 
        {
            fout.write((char*)&taskIDs[i][t], sizeof(int));

            len = strlen(taskNames[i][t]) + 1;
            fout.write((char*)&len, sizeof(len));
            fout.write(taskNames[i][t], len);

            fout.write((char*)&taskAssignedCrew[i][t], sizeof(int));
            fout.write((char*)&taskRequiredEquipment[i][t], sizeof(int));
        }
    }

    fout.write((char*)&crewCount, sizeof(crewCount));

    for (int i = 0; i < crewCount; i++) 
    {
        fout.write((char*)&crewIDs[i], sizeof(int));

        int len = strlen(crewNames[i]) + 1;
        fout.write((char*)&len, sizeof(len));
        fout.write(crewNames[i], len);

        fout.write((char*)&crewAvailable[i], sizeof(bool));
    }

    fout.write((char*)&equipmentCount, sizeof(equipmentCount));

    for (int i = 0; i < equipmentCount; i++) 
    {
        fout.write((char*)&equipmentIDs[i], sizeof(int));

        int len = strlen(equipmentNames[i]) + 1;
        fout.write((char*)&len, sizeof(len));
        fout.write(equipmentNames[i], len);

        fout.write((char*)&equipmentAvailable[i], sizeof(bool));
    }

    fout.close();
    cout << "Data saved to binary file (airport_data.bin) successfully.\n";
}

void fileMenu() 
{
    int ch;
    do {
        clearScreen();
        printTitle("FILE MANAGEMENT");
        cout << "[1] Save Data to Text (airport_data.txt)\n";
        cout << "[2] Load Data from Text (airport_data.txt)\n";
        cout << "[3] Save Data to Binary (airport_data.bin)\n";
        cout << "[4] Load Data from Binary (airport_data.bin)\n";
        cout << "[5] Back to Main Menu\n";
        line();
        ch = getValidatedInt("Enter choice (1-5): ", 1, 5);

        switch(ch) {
            case 1: saveDataToText(); break;
            case 2: loadDataFromText(); break;
            case 3: saveDataToBinary(); break;
            case 4: loadDataFromBinary(); break;
            case 5: break;
        }
        if (ch != 5) { 
            cout << "\nPress Enter to continue..."; 
            cin.get(); 
        }

    } while(ch != 5);
}


void exitProgram()
{
    for(int i=0;i<flightCount;i++)
    {
        delete[] flightIDs[i];
        delete[] flightStatus[i];
        for(int t=0;t<taskCountPerFlight[i];t++)
        {
            delete[] taskNames[i][t];
        }
        delete[] taskNames[i];
        delete[] taskIDs[i];
        delete[] taskAssignedCrew[i];
        delete[] taskRequiredEquipment[i];
    }
    if (flightCount > 0)
    {
        delete[] flightIDs;
        delete[] flightStatus;
        delete[] taskNames;
        delete[] taskIDs;
        delete[] taskAssignedCrew;
        delete[] taskRequiredEquipment;
        delete[] taskCountPerFlight;
    }
    for(int i=0;i<crewCount;i++) 
    {
        delete[] crewNames[i];
    }
    if (crewCount > 0)
    {
        delete[] crewNames;
        delete[] crewIDs;
        delete[] crewAvailable;
    }
    for(int i=0;i<equipmentCount;i++) 
    {
        delete[] equipmentNames[i];
    }
    if (equipmentCount > 0) 
    {
        delete[] equipmentNames;
        delete[] equipmentIDs;
        delete[] equipmentAvailable;
    }
    flightIDs = nullptr;
    flightStatus = nullptr;
    taskNames = nullptr;
    taskIDs = nullptr;
    taskAssignedCrew = nullptr;
    taskRequiredEquipment = nullptr;
    taskCountPerFlight = nullptr;
    crewNames = nullptr;
    crewIDs = nullptr;
    crewAvailable = nullptr;
    equipmentNames = nullptr;
    equipmentIDs = nullptr;
    equipmentAvailable = nullptr;

    flightCount = crewCount = equipmentCount = 0;
    cout << "All dynamic memory freed successfully.\n";
}