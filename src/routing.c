#include <stdio.h>
#include <float.h>

#include "routing.h"
#include "utils.h"


int getPriorityBins(
    const Bin bins[],
    int binCount,
    int selectedIndices[]
)
{
    int count = 0;

    for (int i = 0; i < binCount; i++)
    {
        if (bins[i].priority == PRIORITY_HIGH ||
            bins[i].priority == PRIORITY_CRITICAL)
        {
            selectedIndices[count] = i;
            count++;
        }
    }

    return count;
}


void sortBinsByPriority(
    const Bin bins[],
    int indices[],
    int count
)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (bins[indices[j]].priorityScore >
                bins[indices[i]].priorityScore)
            {
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }
}

Route generateRoute(
    const Bin bins[],
    int binCount,
    Vehicle *vehicle
)
{
    Route route = {0};

    route.vehicleId = vehicle->id;
    route.stopCount = 0;
    route.totalDistance = 0.0f;
    route.estimatedFuelConsumption = 0.0f;

    int priorityBins[MAX_BINS];

    int priorityCount = getPriorityBins(
        bins,
        binCount,
        priorityBins
    );

    if (priorityCount == 0)
    {
        return route;
    }

    sortBinsByPriority(
        bins,
        priorityBins,
        priorityCount
    );

    int visited[MAX_BINS] = {0};

    float currentX = vehicle->x;
    float currentY = vehicle->y;

    float remainingCapacity =
        vehicle->capacity - vehicle->currentLoad;

    while (route.stopCount < priorityCount)
    {
        int bestIndex = -1;
        float bestDistance = FLT_MAX;

        /*
         * First preference:
         * find the nearest CRITICAL bin.
         */
        for (int i = 0; i < priorityCount; i++)
        {
            int binIndex = priorityBins[i];

            if (visited[i])
                continue;

            if (bins[binIndex].priority != PRIORITY_CRITICAL)
                continue;

            float estimatedWaste =
                bins[binIndex].fillLevel * 5.0f;

            if (estimatedWaste > remainingCapacity)
                continue;

            float distance =
                calculateManhattanDistance(
                    currentX,
                    currentY,
                    bins[binIndex].x,
                    bins[binIndex].y
                );

            if (distance < bestDistance)
            {
                bestDistance = distance;
                bestIndex = i;
            }
        }

        /*
         * If no critical bin can be selected,
         * search HIGH priority bins.
         */
        if (bestIndex == -1)
        {
            for (int i = 0; i < priorityCount; i++)
            {
                int binIndex = priorityBins[i];

                if (visited[i])
                    continue;

                float estimatedWaste =
                    bins[binIndex].fillLevel * 5.0f;

                if (estimatedWaste > remainingCapacity)
                    continue;

                float distance =
                    calculateManhattanDistance(
                        currentX,
                        currentY,
                        bins[binIndex].x,
                        bins[binIndex].y
                    );

                if (distance < bestDistance)
                {
                    bestDistance = distance;
                    bestIndex = i;
                }
            }
        }

        if (bestIndex == -1)
        {
            break;
        }

        int selectedBinIndex =
            priorityBins[bestIndex];

        route.binIds[route.stopCount] =
            bins[selectedBinIndex].id;

        route.stopCount++;

        route.totalDistance += bestDistance;

        float estimatedWaste =
            bins[selectedBinIndex].fillLevel * 5.0f;

        remainingCapacity -= estimatedWaste;

        currentX = bins[selectedBinIndex].x;
        currentY = bins[selectedBinIndex].y;

        visited[bestIndex] = 1;
    }

    route.estimatedFuelConsumption =
        route.totalDistance / vehicle->fuelEfficiency;

    return route;
}

void displayRoute(
    const Route *route,
    const Bin bins[],
    int binCount
)
{
    printf("\n");
    printf("=============================================\n");
    printf("             COLLECTION ROUTE\n");
    printf("=============================================\n");

    printf("Vehicle : V%d\n", route->vehicleId);

    if (route->stopCount == 0)
    {
        printf("No collection route required.\n");
        printf("=============================================\n");
        return;
    }

    printf("\nRoute:\n");

    printf("START");

    for (int i = 0; i < route->stopCount; i++)
    {
        int binId = route->binIds[i];

        for (int j = 0; j < binCount; j++)
        {
            if (bins[j].id == binId)
            {
                printf(
                    " -> B%d(%s)",
                    bins[j].id,
                    bins[j].location
                );

                break;
            }
        }
    }

    printf("\n\n");

    printf(
        "Stops               : %d\n",
        route->stopCount
    );

    printf(
        "Total Distance      : %.1f units\n",
        route->totalDistance
    );

    printf(
        "Estimated Fuel Used : %.2f L\n",
        route->estimatedFuelConsumption
    );

    printf("=============================================\n");
}

