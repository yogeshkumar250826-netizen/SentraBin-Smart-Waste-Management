#ifndef COLLECTION_H
#define COLLECTION_H

#include "models.h"

float estimateBinWasteKg(const Bin *bin);

void executeCollectionRoute(
    Route *route,
    Bin bins[],
    int binCount,
    Vehicle *vehicle,
    Complaint complaints[],
    int complaintCount,
    SimulationStats *stats
);

#endif