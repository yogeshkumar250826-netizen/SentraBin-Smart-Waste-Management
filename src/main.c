#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "models.h"
#include "bin.h"

int main(void)
{
    Bin bins[MAX_BINS];
    int binCount = 0;

    srand((unsigned int)time(NULL));

    initializeBins(bins, &binCount);

    printf("\nINITIAL STATE\n");
    displayBins(bins, binCount);

    printf("\nRunning one simulation cycle...\n");

    updateBinFillLevels(bins, binCount);
    updateAllBinPriorities(bins, binCount);

    printf("\nAFTER ONE CYCLE\n");
    displayBins(bins, binCount);

    printf("\nCritical Bins: %d\n",
           countCriticalBins(bins, binCount));

    return 0;
}