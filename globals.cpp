#include "airport.h"


char **flightIDs = nullptr;
char **flightStatus = nullptr;
int flightCount = 0;
char **crewNames = nullptr;
int *crewIDs = nullptr;
bool *crewAvailable = nullptr;
int crewCount = 0;
char **equipmentNames = nullptr;
int *equipmentIDs = nullptr;
bool *equipmentAvailable = nullptr;
int equipmentCount = 0;
char ***taskNames = nullptr;
int **taskIDs = nullptr;
int **taskAssignedCrew = nullptr;
int **taskRequiredEquipment = nullptr;
int *taskCountPerFlight = nullptr;