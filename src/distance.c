#include <stdio.h>
#include <float.h>

#include "distance.h"
#include "utils.h"

void generateBinDistanceMatrix(
    const Bin bins[],
    int binCount,
    float matrix[MAX_BINS][MAX_BINS]
)
{
    for (int i = 0; i < binCount; i++)
    {
        for (int j = 0; j < binCount; j++)
        {
            if (i == j)
            {
                matrix[i][j] = 0.0f;
            }
            else
            {
                matrix[i][j] = calculateManhattanDistance(
                    bins[i].x,
                    bins[i].y,
                    bins[j].x,
                    bins[j].y
                );
            }
        }
    }
}

void displayDistanceMatrix(
    const Bin bins[],
    int binCount,
    float matrix[MAX_BINS][MAX_BINS]
)
{
    printf("\nBIN DISTANCE MATRIX\n\n");

    printf("%8s", "");

    for (int i = 0; i < binCount; i++)
    {
        printf("B%-7d", bins[i].id);
    }

    printf("\n");

    for (int i = 0; i < binCount; i++)
    {
        printf("B%-7d", bins[i].id);

        for (int j = 0; j < binCount; j++)
        {
            printf("%-8.1f", matrix[i][j]);
        }

        printf("\n");
    }
}

int findNearestAvailableVehicle(
    const Vehicle vehicles[],
    int vehicleCount,
    const Bin *bin
)
{
    int selectedIndex = -1;
    float minimumDistance = FLT_MAX;

    for (int i = 0; i < vehicleCount; i++)
    {
        if (vehicles[i].status != VEHICLE_AVAILABLE)
        {
            continue;
        }

        if (vehicles[i].assignedDriverId == -1)
        {
            continue;
        }

        if (vehicles[i].fuelLevel <= LOW_FUEL_THRESHOLD)
        {
            continue;
        }

        float estimatedWaste =
            (bin->fillLevel / 100.0f) * BIN_CAPACITY_KG;

        float remainingCapacity =
        vehicles[i].capacity -
        vehicles[i].currentLoad;

        if (estimatedWaste > remainingCapacity)
        {
            continue;
        }

        float distance = calculateManhattanDistance(
            vehicles[i].x,
            vehicles[i].y,
            bin->x,
            bin->y
        );

        if (distance < minimumDistance)
        {
            minimumDistance = distance;
            selectedIndex = i;
        }
    }

    return selectedIndex;
}