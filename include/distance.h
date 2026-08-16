#ifndef DISTANCE_H
#define DISTANCE_H

#include "models.h"

void generateBinDistanceMatrix(
    const Bin bins[],
    int binCount,
    float matrix[MAX_BINS][MAX_BINS]
);

void displayDistanceMatrix(
    const Bin bins[],
    int binCount,
    float matrix[MAX_BINS][MAX_BINS]
);

int findNearestAvailableVehicle(
    const Vehicle vehicles[],
    int vehicleCount,
    const Bin *bin
);

#endif