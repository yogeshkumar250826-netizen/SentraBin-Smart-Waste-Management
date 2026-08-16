#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "models.h"
#include "bin.h"
#include "fleet.h"
#include "routing.h"

int main(void)
{
    Bin bins[MAX_BINS];
    Vehicle vehicles[MAX_VEHICLES];
    Driver drivers[MAX_DRIVERS];

    int binCount = 0;
    int vehicleCount = 0;
    int driverCount = 0;

    srand((unsigned int)time(NULL));

    initializeBins(
        bins,
        &binCount
    );

    initializeVehicles(
        vehicles,
        &vehicleCount
    );

    initializeDrivers(
        drivers,
        &driverCount
    );

    assignDriversToVehicles(
        vehicles,
        vehicleCount,
        drivers,
        driverCount
    );

    displayBins(
        bins,
        binCount
    );

    Route route = generateRoute(
        bins,
        binCount,
        &vehicles[2]
    );

    displayRoute(
        &route,
        bins,
        binCount
    );

    return 0;
}