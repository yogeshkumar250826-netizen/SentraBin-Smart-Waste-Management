#include <stdio.h>

#include "models.h"
#include "bin.h"
#include "fleet.h"
#include "distance.h"

int main(void)
{
    Bin bins[MAX_BINS];
    Vehicle vehicles[MAX_VEHICLES];
    Driver drivers[MAX_DRIVERS];

    int binCount = 0;
    int vehicleCount = 0;
    int driverCount = 0;

    float distanceMatrix[MAX_BINS][MAX_BINS];

    initializeBins(bins, &binCount);

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

    generateBinDistanceMatrix(
        bins,
        binCount,
        distanceMatrix
    );

    displayDistanceMatrix(
        bins,
        binCount,
        distanceMatrix
    );

    int binIndex = 3;

    int vehicleIndex =
        findNearestAvailableVehicle(
            vehicles,
            vehicleCount,
            &bins[binIndex]
        );

    printf(
        "\nTarget Bin: B%d (%s)\n",
        bins[binIndex].id,
        bins[binIndex].location
    );

    if (vehicleIndex != -1)
    {
        printf(
            "Nearest Available Vehicle: V%d\n",
            vehicles[vehicleIndex].id
        );
    }
    else
    {
        printf(
            "No suitable vehicle available.\n"
        );
    }

    return 0;
}