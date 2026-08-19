#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "models.h"
#include "bin.h"
#include "fleet.h"
#include "storage.h"
#include "menu.h"

int main(void)
{
    Bin bins[MAX_BINS];
    Vehicle vehicles[MAX_VEHICLES];
    Driver drivers[MAX_DRIVERS];
    Complaint complaints[MAX_COMPLAINTS];

    int binCount = 0;
    int vehicleCount = 0;
    int driverCount = 0;
    int complaintCount = 0;

    SimulationStats stats = {0};

    srand((unsigned int)time(NULL));

    printf("\nStarting SentraBin...\n");

    int binsLoaded =
        loadBins(
            bins,
            &binCount
        );

    int vehiclesLoaded =
        loadVehicles(
            vehicles,
            &vehicleCount
        );

    int driversLoaded =
        loadDrivers(
            drivers,
            &driverCount
        );

    loadComplaints(
        complaints,
        &complaintCount
    );

    if (!binsLoaded ||
        !vehiclesLoaded ||
        !driversLoaded)
    {
        printf(
            "No complete saved state found.\n"
        );

        printf(
            "Initializing default system data...\n"
        );

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

        complaintCount = 0;

        saveBins(
            bins,
            binCount
        );

        saveVehicles(
            vehicles,
            vehicleCount
        );

        saveDrivers(
            drivers,
            driverCount
        );

        saveComplaints(
            complaints,
            complaintCount
        );

        printf(
            "Default system initialized successfully.\n"
        );
    }
    else
    {
        printf(
            "Previous system state loaded successfully.\n"
        );
    }

    runMainMenu(
        bins,
        &binCount,
        vehicles,
        &vehicleCount,
        drivers,
        &driverCount,
        complaints,
        &complaintCount,
        &stats
    );

    return 0;
}