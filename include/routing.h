#ifndef ROUTING_H
#define ROUTING_H

#include "models.h"

int getPriorityBins(
    const Bin bins[],
    int binCount,
    int selectedIndices[]
);

void sortBinsByPriority(
    const Bin bins[],
    int indices[],
    int count
);

Route generateRoute(
    const Bin bins[],
    int binCount,
    Vehicle *vehicle
);

void displayRoute(
    const Route *route,
    const Bin bins[],
    int binCount
);

#endif