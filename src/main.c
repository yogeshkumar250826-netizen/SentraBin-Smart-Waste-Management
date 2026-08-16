#include <stdio.h>

#include "models.h"
#include "utils.h"
#include "priority.h"

int main(void)
{
    Bin bin = {
        .id = 7,
        .fillLevel = 90.0f,
        .wasteType = WASTE_HAZARDOUS,
        .complaintCount = 3,
        .emergencyFlag = 1,
        .status = BIN_AVAILABLE
    };

    updateBinPriority(&bin);

    printf("Bin ID         : %d\n", bin.id);
    printf("Fill Level     : %.1f%%\n", bin.fillLevel);
    printf("Waste Type     : %s\n",
           getWasteTypeString(bin.wasteType));

    printf("Complaints     : %d\n",
           bin.complaintCount);

    printf("Emergency      : %s\n",
           bin.emergencyFlag ? "Yes" : "No");

    printf("Priority Score : %.1f\n",
           bin.priorityScore);

    printf("Priority       : %s\n",
           getPriorityString(bin.priority));

    printf("Status         : %s\n",
           getBinStatusString(bin.status));

    return 0;
}