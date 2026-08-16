#ifndef BIN_H
#define BIN_H

#include "models.h"

void initializeBins(Bin bins[], int *binCount);

void updateBinFillLevels(Bin bins[], int binCount);

void updateAllBinPriorities(Bin bins[], int binCount);

void displayBins(const Bin bins[], int binCount);

int countCriticalBins(const Bin bins[], int binCount);

#endif