#ifndef SIMULATION_H
#define SIMULATION_H

#include "models.h"

void runSimulationCycle(
    Bin bins[],
    int binCount,
    Vehicle vehicles[],
    int vehicleCount,
    Complaint complaints[],
    int complaintCount,
    SimulationStats *stats
);

#endif