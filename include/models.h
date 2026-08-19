#ifndef MODELS_H
#define MODELS_H

#include "constants.h"

/* ---------- ENUMS ---------- */

typedef enum
{
    WASTE_GENERAL,
    WASTE_RECYCLABLE,
    WASTE_ORGANIC,
    WASTE_HAZARDOUS
} WasteType;

typedef enum
{
    PRIORITY_NORMAL,
    PRIORITY_MEDIUM,
    PRIORITY_HIGH,
    PRIORITY_CRITICAL
} PriorityLevel;

typedef enum
{
    BIN_AVAILABLE,
    BIN_COLLECTION_REQUIRED,
    BIN_UNDER_COLLECTION
} BinStatus;

typedef enum
{
    VEHICLE_AVAILABLE,
    VEHICLE_ASSIGNED,
    VEHICLE_REFUELING,
    VEHICLE_MAINTENANCE
} VehicleStatus;

typedef enum
{
    DRIVER_AVAILABLE,
    DRIVER_ASSIGNED,
    DRIVER_OFF_DUTY
} DriverStatus;

typedef enum
{
    COMPLAINT_OPEN,
    COMPLAINT_RESOLVED
} ComplaintStatus;

typedef enum
{
    VEHICLE_STANDARD,
    VEHICLE_RECYCLING,
    VEHICLE_HAZMAT
} VehicleType;


/* ---------- BIN ---------- */

typedef struct
{
    int id;

    char location[MAX_ADDRESS_LENGTH];
    char zone[MAX_NAME_LENGTH];

    float x;
    float y;

    float fillLevel;

    WasteType wasteType;
    PriorityLevel priority;
    BinStatus status;

    int complaintCount;
    int emergencyFlag;

    float priorityScore;

} Bin;


/* ---------- VEHICLE ---------- */

typedef struct
{
    int id;

    char registrationNumber[MAX_NAME_LENGTH];

    VehicleType type;

    float capacity;
    float currentLoad;

    float fuelLevel;
    float fuelEfficiency;

    float x;
    float y;

    VehicleStatus status;

    int assignedDriverId;

    float totalDistanceTravelled;
    float totalFuelConsumed;

} Vehicle;


/* ---------- DRIVER ---------- */

typedef struct
{
    int id;

    char name[MAX_NAME_LENGTH];

    DriverStatus status;

    int assignedVehicleId;

    int hazmatCertified;

} Driver;


/* ---------- COMPLAINT ---------- */

typedef struct
{
    int id;

    char description[MAX_DESCRIPTION_LENGTH];
    char address[MAX_ADDRESS_LENGTH];

    int binId;

    int severity;

    ComplaintStatus status;

} Complaint;


/* ---------- ROUTE ---------- */

typedef struct
{
    int vehicleId;

    int binIds[MAX_ROUTE_STOPS];
    int stopCount;

    float totalDistance;
    float estimatedFuelConsumption;

} Route;


/* ---------- SIMULATION STATISTICS ---------- */

typedef struct
{
    int cycleNumber;

    int binsCollected;
    int complaintsHandled;
    int emergenciesHandled;

    float totalDistanceTravelled;
    float totalFuelConsumed;

} SimulationStats;

#endif