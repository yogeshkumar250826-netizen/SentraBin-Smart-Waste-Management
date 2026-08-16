#include <stdio.h>

#include "simulation.h"
#include "bin.h"
#include "fleet.h"
#include "routing.h"
#include "collection.h"
#include "distance.h"


void runSimulationCycle(
    Bin bins[],
    int binCount,
    Vehicle vehicles[],
    int vehicleCount,
    Complaint complaints[],
    int complaintCount,
    SimulationStats *stats
)
{
    stats->cycleNumber++;

    printf("\n");
    printf("=====================================================\n");
    printf("              SIMULATION CYCLE %d\n",
           stats->cycleNumber);
    printf("=====================================================\n");

    /* Bins fill only once per cycle */
    updateBinFillLevels(bins, binCount);
    updateAllBinPriorities(bins, binCount);

    printf("\nUpdated bin state:\n");
    displayBins(bins, binCount);

    updateVehicleFuelState(
        vehicles,
        vehicleCount
    );

    int dispatchCount = 0;

    while (1)
    {
        int targetBinIndex = -1;
        float highestScore = -1.0f;

        /*
         * Emergency bins always get first preference.
         */
        for (int i = 0; i < binCount; i++)
        {
            if (!bins[i].emergencyFlag)
                continue;

            if (bins[i].priorityScore > highestScore)
            {
                highestScore = bins[i].priorityScore;
                targetBinIndex = i;
            }
        }

        /*
         * If there is no emergency,
         * select highest priority collection bin.
         */
        if (targetBinIndex == -1)
        {
            highestScore = -1.0f;

            for (int i = 0; i < binCount; i++)
            {
                if ((bins[i].priority == PRIORITY_HIGH ||
                     bins[i].priority == PRIORITY_CRITICAL) &&
                    bins[i].priorityScore > highestScore)
                {
                    highestScore =
                        bins[i].priorityScore;

                    targetBinIndex = i;
                }
            }
        }

        /*
         * Nothing else requires collection.
         */
        if (targetBinIndex == -1)
            break;

        printf(
            "\nDispatch target: B%d - %s [%s]\n",
            bins[targetBinIndex].id,
            bins[targetBinIndex].location,
            bins[targetBinIndex].emergencyFlag
                ? "EMERGENCY"
                : "PRIORITY"
        );

        int vehicleIndex =
            findNearestAvailableVehicle(
                vehicles,
                vehicleCount,
                &bins[targetBinIndex]
            );

        if (vehicleIndex == -1)
        {
            printf(
                "No suitable vehicle available for B%d.\n",
                bins[targetBinIndex].id
            );

            break;
        }

        Vehicle *vehicle =
            &vehicles[vehicleIndex];

        printf(
            "Selected vehicle: V%d\n",
            vehicle->id
        );

        Route route = generateRoute(
            bins,
            binCount,
            vehicle
        );

        if (route.stopCount == 0)
        {
            printf(
                "Unable to generate collection route.\n"
            );

            break;
        }

        displayRoute(
            &route,
            bins,
            binCount
        );

        executeCollectionRoute(
            &route,
            bins,
            binCount,
            vehicle,
            complaints,
            complaintCount,
            stats
        );

        returnVehicleToDepot(
            vehicle,
            stats
        );

        updateVehicleFuelState(
            vehicles,
            vehicleCount
        );

        dispatchCount++;
    }

    if (dispatchCount == 0)
    {
        printf(
            "\nNo bins currently require collection.\n"
        );
    }
    else
    {
        printf(
            "\nCycle %d completed with %d dispatch(es).\n",
            stats->cycleNumber,
            dispatchCount
        );
    }

    printf("=====================================================\n");
}