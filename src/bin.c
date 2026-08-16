#include <stdio.h>

#include "bin.h"
#include "priority.h"
#include "utils.h"

void initializeBins(Bin bins[], int *binCount)
{
    *binCount = 6;

    bins[0] = (Bin){
        .id = 1,
        .location = "Anna Nagar",
        .zone = "North",
        .x = 10.0f,
        .y = 20.0f,
        .fillLevel = 55.0f,
        .wasteType = WASTE_GENERAL,
        .complaintCount = 0,
        .emergencyFlag = 0
    };

    bins[1] = (Bin){
        .id = 2,
        .location = "T Nagar",
        .zone = "Central",
        .x = 30.0f,
        .y = 25.0f,
        .fillLevel = 72.0f,
        .wasteType = WASTE_ORGANIC,
        .complaintCount = 1,
        .emergencyFlag = 0
    };

    bins[2] = (Bin){
        .id = 3,
        .location = "Adyar",
        .zone = "South",
        .x = 45.0f,
        .y = 40.0f,
        .fillLevel = 80.0f,
        .wasteType = WASTE_RECYCLABLE,
        .complaintCount = 0,
        .emergencyFlag = 0
    };

    bins[3] = (Bin){
        .id = 4,
        .location = "Perambur",
        .zone = "North",
        .x = 18.0f,
        .y = 60.0f,
        .fillLevel = 91.0f,
        .wasteType = WASTE_HAZARDOUS,
        .complaintCount = 2,
        .emergencyFlag = 0
    };

    bins[4] = (Bin){
        .id = 5,
        .location = "Velachery",
        .zone = "South",
        .x = 60.0f,
        .y = 50.0f,
        .fillLevel = 48.0f,
        .wasteType = WASTE_GENERAL,
        .complaintCount = 0,
        .emergencyFlag = 0
    };

    bins[5] = (Bin){
        .id = 6,
        .location = "Guindy",
        .zone = "Central",
        .x = 50.0f,
        .y = 30.0f,
        .fillLevel = 65.0f,
        .wasteType = WASTE_ORGANIC,
        .complaintCount = 1,
        .emergencyFlag = 0
    };

    updateAllBinPriorities(bins, *binCount);
}

void updateBinFillLevels(Bin bins[], int binCount)
{
    for (int i = 0; i < binCount; i++)
    {
        float increase;

        switch (bins[i].wasteType)
        {
            case WASTE_ORGANIC:
                increase = randomFloat(5.0f, 10.0f);
                break;

            case WASTE_HAZARDOUS:
                increase = randomFloat(2.0f, 6.0f);
                break;

            case WASTE_RECYCLABLE:
                increase = randomFloat(3.0f, 7.0f);
                break;

            case WASTE_GENERAL:
            default:
                increase = randomFloat(4.0f, 8.0f);
                break;
        }

        bins[i].fillLevel += increase;

        if (bins[i].fillLevel >= MAX_FILL_LEVEL)
        {
            bins[i].fillLevel = MAX_FILL_LEVEL;
            bins[i].emergencyFlag = 1;
        }
    }
}

void updateAllBinPriorities(Bin bins[], int binCount)
{
    for (int i = 0; i < binCount; i++)
    {
        updateBinPriority(&bins[i]);
    }
}

void displayBins(const Bin bins[], int binCount)
{
    printf("\n");
    printf("=============================================================================================\n");
    printf("                                  BIN STATUS\n");
    printf("=============================================================================================\n");

    printf("%-5s %-15s %-10s %-8s %-12s %-10s %-10s %-10s\n",
           "ID",
           "Location",
           "Zone",
           "Fill",
           "Waste",
           "Score",
           "Priority",
           "Emergency");

    printf("---------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < binCount; i++)
    {
        printf("%-5d %-15s %-10s %-7.1f%% %-12s %-10.1f %-10s %-10s\n",
               bins[i].id,
               bins[i].location,
               bins[i].zone,
               bins[i].fillLevel,
               getWasteTypeString(bins[i].wasteType),
               bins[i].priorityScore,
               getPriorityString(bins[i].priority),
               bins[i].emergencyFlag ? "YES" : "NO");
    }

    printf("=============================================================================================\n");
}

int countCriticalBins(const Bin bins[], int binCount)
{
    int count = 0;

    for (int i = 0; i < binCount; i++)
    {
        if (bins[i].priority == PRIORITY_CRITICAL)
        {
            count++;
        }
    }

    return count;
}