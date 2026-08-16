#ifndef FLEET_H
#define FLEET_H

#include "models.h"

void initializeVehicles(Vehicle vehicles[], int *vehicleCount);
void initializeDrivers(Driver drivers[], int *driverCount);

void displayVehicles(const Vehicle vehicles[], int vehicleCount);
void displayDrivers(const Driver drivers[], int driverCount);

void assignDriversToVehicles(
    Vehicle vehicles[],
    int vehicleCount,
    Driver drivers[],
    int driverCount
);

void updateVehicleFuelState(Vehicle vehicles[], int vehicleCount);

void returnVehicleToDepot(
    Vehicle *vehicle,
    SimulationStats *stats
);

#endif