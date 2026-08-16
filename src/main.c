#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "models.h"
#include "bin.h"
#include "fleet.h"
#include "simulation.h"
#include "complaint.h"

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

    /* Initialize system data */
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

    printf("\nINITIAL SYSTEM STATE\n");

    displayBins(
        bins,
        binCount
    );

    displayVehicles(
        vehicles,
        vehicleCount
    );

    /*
     * Run first two normal simulation cycles.
     */
    for (int i = 0; i < 2; i++)
    {
        runSimulationCycle(
            bins,
            binCount,
            vehicles,
            vehicleCount,
            complaints,
            complaintCount,
            &stats
        );
    }

    /*
     * Simulate a citizen complaint arriving
     * after two cycles.
     */
    printf("\n");
    printf("=====================================================\n");
    printf("                 NEW COMPLAINT\n");
    printf("=====================================================\n");

    submitComplaint(
        complaints,
        &complaintCount,
        bins,
        binCount,
        "Near Perambur bus stand",
        "Garbage is overflowing and there is a bad smell"
    );

    displayComplaints(
        complaints,
        complaintCount
    );

    printf("\nBIN STATE AFTER COMPLAINT\n");

    displayBins(
        bins,
        binCount
    );

    /*
     * Run next cycle.
     * The complaint should influence priority and routing.
     */
    runSimulationCycle(
        bins,
        binCount,
        vehicles,
        vehicleCount,
        complaints,
        complaintCount,
        &stats
    );

    /*
     * Complaint should now be resolved
     * if the corresponding bin was serviced.
     */
    printf("\nCOMPLAINT STATUS AFTER COLLECTION\n");

    displayComplaints(
        complaints,
        complaintCount
    );

    /*
     * Run two more cycles so total cycles = 5.
     */
    for (int i = 0; i < 2; i++)
    {
        runSimulationCycle(
            bins,
            binCount,
            vehicles,
            vehicleCount,
            complaints,
            complaintCount,
            &stats
        );
    }

    printf("\n");
    printf("=====================================================\n");
    printf("              FINAL SIMULATION SUMMARY\n");
    printf("=====================================================\n");

    printf(
        "Cycles Completed       : %d\n",
        stats.cycleNumber
    );

    printf(
        "Bins Collected         : %d\n",
        stats.binsCollected
    );

    printf(
        "Complaints Handled     : %d\n",
        stats.complaintsHandled
    );

    printf(
        "Emergencies Handled    : %d\n",
        stats.emergenciesHandled
    );

    printf(
        "Total Distance         : %.1f units\n",
        stats.totalDistanceTravelled
    );

    printf(
        "Total Fuel Consumed    : %.2f L\n",
        stats.totalFuelConsumed
    );

    printf("=====================================================\n");

    printf("\nFINAL BIN STATE\n");

    displayBins(
        bins,
        binCount
    );

    printf("\nFINAL FLEET STATE\n");

    displayVehicles(
        vehicles,
        vehicleCount
    );

    printf("\nFINAL COMPLAINT LOG\n");

    displayComplaints(
        complaints,
        complaintCount
    );

    return 0;
}