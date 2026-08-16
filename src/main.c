#include <stdio.h>
#include "../include/models.h"

int main(void)
{
    Bin bin = {
        .id = 1,
        .fillLevel = 75.0f,
        .wasteType = WASTE_GENERAL,
        .priority = PRIORITY_HIGH
    };

    printf("Bin ID: %d\n", bin.id);
    printf("Fill Level: %.1f%%\n", bin.fillLevel);

    return 0;
}