#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "models.h"
#include "utils.h"

int main(void)
{
    srand((unsigned int)time(NULL));

    Bin bin = {
        .id = 1,
        .fillLevel = 82.5f,
        .wasteType = WASTE_HAZARDOUS,
        .priority = PRIORITY_HIGH,
        .status = BIN_COLLECTION_REQUIRED
    };

    printf("Bin ID      : %d\n", bin.id);
    printf("Fill Level  : %.1f%%\n", bin.fillLevel);
    printf("Waste Type  : %s\n", getWasteTypeString(bin.wasteType));
    printf("Priority    : %s\n", getPriorityString(bin.priority));
    printf("Status      : %s\n", getBinStatusString(bin.status));

    float distance = calculateManhattanDistance(
        10.0f,
        20.0f,
        25.0f,
        35.0f
    );

    printf("Distance    : %.1f units\n", distance);

    return 0;
}