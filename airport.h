#ifndef AIRPORT_H
#define AIRPORT_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include <limits>
#include <climits>
#include <string>
using namespace std;
#define MAX_NAME 50

extern char **flightIDs;
extern char **flightStatus;
extern int flightCount;
extern char **crewNames;
extern int *crewIDs;
extern bool *crewAvailable;
extern int crewCount;
extern char **equipmentNames;
extern int *equipmentIDs;
extern bool *equipmentAvailable;
extern int equipmentCount;
extern char ***taskNames;
extern int **taskIDs;
extern int **taskAssignedCrew;
extern int **taskRequiredEquipment;
extern int *taskCountPerFlight;
int getValidatedInt(const string& prompt, int minVal = INT_MIN, int maxVal = INT_MAX);
string getValidatedString(const string& prompt, int minLength = 1, int maxLength = MAX_NAME-1);
bool getYesNoInput(const string& prompt);
bool crewIDExists(int id);
bool equipmentIDExists(int id);
bool flightIDExists(const char* id);
void clearScreen();
void printTitle(const char *title);
void line();
void addFlight();
void displayFlights();
void updateFlightStatus();
void listFlightTasks();
void searchFlightByID();
void addCrew();
void displayCrew();
void markCrewAvailable();
void markCrewUnavailable();
void countAvailableCrew();
void searchCrewByID();
void addEquipment();
void displayEquipment();
void markEquipmentAvailable();
void markEquipmentUnavailable();
void countAvailableEquipment();
void searchEquipmentByID();
void addTaskToFlight();
void displayTasks();
void assignCrewToTask();
void startService();
void completeTask();
void saveDataToText();
void loadDataFromText();
void saveDataToBinary();
void loadDataFromBinary();
void exitProgram();
void flightMenu();
void crewMenu();
void equipmentMenu();
void taskMenu();
void fileMenu();

#endif