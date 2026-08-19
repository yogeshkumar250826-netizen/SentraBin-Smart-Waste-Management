#ifndef STORAGE_H
#define STORAGE_H

#include "models.h"

int loadBins(
    Bin bins[],
    int *binCount
);

int saveBins(
    const Bin bins[],
    int binCount
);

int loadVehicles(
    Vehicle vehicles[],
    int *vehicleCount
);

int saveVehicles(
    const Vehicle vehicles[],
    int vehicleCount
);

int loadDrivers(
    Driver drivers[],
    int *driverCount
);

int saveDrivers(
    const Driver drivers[],
    int driverCount
);

int loadComplaints(
    Complaint complaints[],
    int *complaintCount
);

int saveComplaints(
    const Complaint complaints[],
    int complaintCount
);

#endif