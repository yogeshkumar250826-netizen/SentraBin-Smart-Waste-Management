#include <stdio.h>
#include <string.h>

#include "storage.h"

#define BINS_FILE "data/bins.csv"
#define VEHICLES_FILE "data/vehicles.csv"
#define DRIVERS_FILE "data/drivers.csv"
#define COMPLAINTS_FILE "data/complaints.csv"


int saveBins(
    const Bin bins[],
    int binCount
)
{
    FILE *file = fopen(BINS_FILE, "w");

    if (file == NULL)
    {
        printf("Error: unable to save bin data.\n");
        return 0;
    }

    fprintf(
        file,
        "id,location,zone,fillLevel,wasteType,"
        "priorityScore,priority,emergencyFlag,"
        "complaintCount,status,x,y\n"
    );

    for (int i = 0; i < binCount; i++)
    {
        fprintf(
            file,
            "%d,%s,%s,%.2f,%d,%.2f,%d,%d,%d,%d,%.2f,%.2f\n",
            bins[i].id,
            bins[i].location,
            bins[i].zone,
            bins[i].fillLevel,
            bins[i].wasteType,
            bins[i].priorityScore,
            bins[i].priority,
            bins[i].emergencyFlag,
            bins[i].complaintCount,
            bins[i].status,
            bins[i].x,
            bins[i].y
        );
    }

    fclose(file);

    return 1;
}

int loadBins(
    Bin bins[],
    int *binCount
)
{
    FILE *file = fopen(BINS_FILE, "r");

    if (file == NULL)
        return 0;

    char line[512];

    /* Skip CSV header */
    fgets(line, sizeof(line), file);

    *binCount = 0;

    while (*binCount < MAX_BINS &&
           fgets(line, sizeof(line), file) != NULL)
    {
        Bin *bin = &bins[*binCount];

        int wasteType;
        int priority;
        int status;

        int fields = sscanf(
            line,
            "%d,%49[^,],%29[^,],%f,%d,%f,%d,%d,%d,%d,%f,%f",
            &bin->id,
            bin->location,
            bin->zone,
            &bin->fillLevel,
            &wasteType,
            &bin->priorityScore,
            &priority,
            &bin->emergencyFlag,
            &bin->complaintCount,
            &status,
            &bin->x,
            &bin->y
        );

        if (fields == 12)
        {
            bin->wasteType = (WasteType)wasteType;
            bin->priority = (PriorityLevel)priority;
            bin->status = (BinStatus)status;

            (*binCount)++;
        }
    }

    fclose(file);

    return *binCount > 0;
}

int saveVehicles(
    const Vehicle vehicles[],
    int vehicleCount
)
{
    FILE *file = fopen(VEHICLES_FILE, "w");

    if (file == NULL)
    {
        printf("Error: unable to save vehicle data.\n");
        return 0;
    }

    fprintf(
        file,
        "id,registrationNumber,capacity,currentLoad,"
        "fuelLevel,fuelEfficiency,x,y,status,"
        "assignedDriverId,totalDistance,totalFuel\n"
    );

    for (int i = 0; i < vehicleCount; i++)
    {
        fprintf(
            file,
            "%d,%s,%.2f,%.2f,%.2f,%.2f,"
            "%.2f,%.2f,%d,%d,%.2f,%.2f\n",
            vehicles[i].id,
            vehicles[i].registrationNumber,
            vehicles[i].capacity,
            vehicles[i].currentLoad,
            vehicles[i].fuelLevel,
            vehicles[i].fuelEfficiency,
            vehicles[i].x,
            vehicles[i].y,
            vehicles[i].status,
            vehicles[i].assignedDriverId,
            vehicles[i].totalDistanceTravelled,
            vehicles[i].totalFuelConsumed
        );
    }

    fclose(file);

    return 1;
}

int loadVehicles(
    Vehicle vehicles[],
    int *vehicleCount
)
{
    FILE *file = fopen(VEHICLES_FILE, "r");

    if (file == NULL)
        return 0;

    char line[512];

    fgets(line, sizeof(line), file);

    *vehicleCount = 0;

    while (*vehicleCount < MAX_VEHICLES &&
           fgets(line, sizeof(line), file) != NULL)
    {
        Vehicle *vehicle =
            &vehicles[*vehicleCount];

        int status;

        int fields = sscanf(
            line,
            "%d,%19[^,],%f,%f,%f,%f,%f,%f,%d,%d,%f,%f",
            &vehicle->id,
            vehicle->registrationNumber,
            &vehicle->capacity,
            &vehicle->currentLoad,
            &vehicle->fuelLevel,
            &vehicle->fuelEfficiency,
            &vehicle->x,
            &vehicle->y,
            &status,
            &vehicle->assignedDriverId,
            &vehicle->totalDistanceTravelled,
            &vehicle->totalFuelConsumed
        );

        if (fields == 12)
        {
            vehicle->status =
                (VehicleStatus)status;

            (*vehicleCount)++;
        }
    }

    fclose(file);

    return *vehicleCount > 0;
}

int saveDrivers(
    const Driver drivers[],
    int driverCount
)
{
    FILE *file = fopen(DRIVERS_FILE, "w");

    if (file == NULL)
    {
        printf("Error: unable to save driver data.\n");
        return 0;
    }

    fprintf(
        file,
        "id,name,status,assignedVehicleId\n"
    );

    for (int i = 0; i < driverCount; i++)
    {
        fprintf(
            file,
            "%d,%s,%d,%d\n",
            drivers[i].id,
            drivers[i].name,
            drivers[i].status,
            drivers[i].assignedVehicleId
        );
    }

    fclose(file);

    return 1;
}

int loadDrivers(
    Driver drivers[],
    int *driverCount
)
{
    FILE *file = fopen(DRIVERS_FILE, "r");

    if (file == NULL)
        return 0;

    char line[256];

    fgets(line, sizeof(line), file);

    *driverCount = 0;

    while (*driverCount < MAX_DRIVERS &&
           fgets(line, sizeof(line), file) != NULL)
    {
        Driver *driver =
            &drivers[*driverCount];

        int status;

        int fields = sscanf(
            line,
            "%d,%49[^,],%d,%d",
            &driver->id,
            driver->name,
            &status,
            &driver->assignedVehicleId
        );

        if (fields == 4)
        {
            driver->status =
                (DriverStatus)status;

            (*driverCount)++;
        }
    }

    fclose(file);

    return *driverCount > 0;
}

int saveComplaints(
    const Complaint complaints[],
    int complaintCount
)
{
    FILE *file = fopen(COMPLAINTS_FILE, "w");

    if (file == NULL)
    {
        printf("Error: unable to save complaint data.\n");
        return 0;
    }

    fprintf(
        file,
        "id,address,description,binId,severity,status\n"
    );

    for (int i = 0; i < complaintCount; i++)
    {
        fprintf(
            file,
            "%d,%s,%s,%d,%d,%d\n",
            complaints[i].id,
            complaints[i].address,
            complaints[i].description,
            complaints[i].binId,
            complaints[i].severity,
            complaints[i].status
        );
    }

    fclose(file);

    return 1;
}

int loadComplaints(
    Complaint complaints[],
    int *complaintCount
)
{
    FILE *file = fopen(COMPLAINTS_FILE, "r");

    if (file == NULL)
        return 0;

    char line[1024];

    fgets(line, sizeof(line), file);

    *complaintCount = 0;

    while (*complaintCount < MAX_COMPLAINTS &&
           fgets(line, sizeof(line), file) != NULL)
    {
        Complaint *complaint =
            &complaints[*complaintCount];

        int status;

        int fields = sscanf(
            line,
            "%d,%99[^,],%199[^,],%d,%d,%d",
            &complaint->id,
            complaint->address,
            complaint->description,
            &complaint->binId,
            &complaint->severity,
            &status
        );

        if (fields == 6)
        {
            complaint->status =
                (ComplaintStatus)status;

            (*complaintCount)++;
        }
    }

    fclose(file);

    return 1;
}