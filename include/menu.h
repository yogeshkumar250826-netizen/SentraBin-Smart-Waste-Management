#ifndef MENU_H
#define MENU_H

#include "models.h"

void runMainMenu(
    Bin bins[],
    int *binCount,
    Vehicle vehicles[],
    int *vehicleCount,
    Driver drivers[],
    int *driverCount,
    Complaint complaints[],
    int *complaintCount,
    SimulationStats *stats
);

#endif