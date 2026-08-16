#ifndef COMPLAINT_H
#define COMPLAINT_H

#include "models.h"

int findBinByAddress(
    const char address[],
    const Bin bins[],
    int binCount
);

int detectComplaintSeverity(
    const char description[]
);

int submitComplaint(
    Complaint complaints[],
    int *complaintCount,
    Bin bins[],
    int binCount,
    const char address[],
    const char description[]
);

void displayComplaints(
    const Complaint complaints[],
    int complaintCount
);

void resolveComplaintsForBin(
    Complaint complaints[],
    int complaintCount,
    int binId,
    SimulationStats *stats
);

#endif