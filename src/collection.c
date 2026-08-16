#include <stdio.h>

#include "collection.h"
#include "priority.h"
#include "complaint.h"

float estimateBinWasteKg(const Bin *bin)
{
    return (bin->fillLevel / 100.0f) * BIN_CAPACITY_KG;
}

void executeCollectionRoute(
    Route *route,
    Bin bins[],
    int binCount,
    Vehicle *vehicle,
    Complaint complaints[],
    int complaintCount,
    SimulationStats *stats
)
{
    if (route->stopCount == 0)
    {
        printf("\nNo bins require collection.\n");
        return;
    }

    printf("\n");
    printf("=====================================================\n");
    printf("              COLLECTION EXECUTION\n");
    printf("=====================================================\n");

    vehicle->status = VEHICLE_ASSIGNED;

    for (int i = 0; i < route->stopCount; i++)
    {
        int binIndex = -1;

        for (int j = 0; j < binCount; j++)
        {
            if (bins[j].id == route->binIds[i])
            {
                binIndex = j;
                break;
            }
        }

        if (binIndex == -1)
            continue;

        Bin *bin = &bins[binIndex];

        float wasteKg = estimateBinWasteKg(bin);

        if (vehicle->currentLoad + wasteKg > vehicle->capacity)
        {
            printf(
                "B%d skipped: insufficient vehicle capacity.\n",
                bin->id
            );

            continue;
        }

        printf(
            "\nCollecting B%d - %s\n",
            bin->id,
            bin->location
        );

        printf(
            "Fill Level : %.1f%%\n",
            bin->fillLevel
        );

        printf(
            "Waste      : %.1f kg\n",
            wasteKg
        );

        vehicle->currentLoad += wasteKg;

        bin->fillLevel = 0.0f;
        bin->complaintCount = 0;

        if (bin->emergencyFlag)
        {
            bin->emergencyFlag = 0;
            stats->emergenciesHandled++;
        }

        updateBinPriority(bin);

        vehicle->x = bin->x;
        vehicle->y = bin->y;

        stats->binsCollected++;

        resolveComplaintsForBin(
            complaints,
            complaintCount,
            bin->id,
            stats
        );

        printf("Collection completed.\n");
    }

    vehicle->totalDistanceTravelled +=
        route->totalDistance;

    vehicle->totalFuelConsumed +=
        route->estimatedFuelConsumption;

    vehicle->fuelLevel -=
        route->estimatedFuelConsumption;

    if (vehicle->fuelLevel < 0.0f)
    {
        vehicle->fuelLevel = 0.0f;
    }

    stats->totalDistanceTravelled +=
        route->totalDistance;

    stats->totalFuelConsumed +=
        route->estimatedFuelConsumption;

    vehicle->status = VEHICLE_AVAILABLE;

    printf("\nRoute completed.\n");

    printf(
        "Vehicle Load : %.1f / %.1f kg\n",
        vehicle->currentLoad,
        vehicle->capacity
    );

    printf(
        "Fuel Left    : %.1f%%\n",
        vehicle->fuelLevel
    );

    printf("=====================================================\n");
}