#include <stdio.h>

#include "models.h"
#include "fleet.h"

int main(void)
{
    Vehicle vehicles[MAX_VEHICLES];
    Driver drivers[MAX_DRIVERS];

    int vehicleCount = 0;
    int driverCount = 0;

    initializeVehicles(vehicles, &vehicleCount);
    initializeDrivers(drivers, &driverCount);

    assignDriversToVehicles(
        vehicles,
        vehicleCount,
        drivers,
        driverCount
    );

    displayVehicles(vehicles, vehicleCount);
    displayDrivers(drivers, driverCount);

    printf("\nTesting automatic refuelling...\n");

    vehicles[0].fuelLevel = 10.0f;

    updateVehicleFuelState(
        vehicles,
        vehicleCount
    );

    displayVehicles(
        vehicles,
        vehicleCount
    );

    return 0;
}