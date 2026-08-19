#ifndef MODELS_H
#define MODELS_H

#include "constants.h"

/* =========================================================
   USER / ROLE TYPES
   ========================================================= */

typedef enum
{
    ROLE_USER,
    ROLE_ADMIN
} UserRole;


/* =========================================================
   WASTE TYPES
   ========================================================= */

typedef enum
{
    WASTE_GENERAL,
    WASTE_RECYCLABLE,
    WASTE_ORGANIC,
    WASTE_HAZARDOUS
} WasteType;


/* =========================================================
   PRIORITY TYPES
   ========================================================= */

typedef enum
{
    PRIORITY_NORMAL,
    PRIORITY_MEDIUM,
    PRIORITY_HIGH,
    PRIORITY_CRITICAL
} PriorityLevel;


/* =========================================================
   BIN STATUS
   ========================================================= */

typedef enum
{
    BIN_AVAILABLE,
    BIN_COLLECTION_REQUIRED,
    BIN_UNDER_COLLECTION,
    BIN_OUT_OF_SERVICE
} BinStatus;


/* =========================================================
   VEHICLE TYPES
   ========================================================= */

typedef enum
{
    VEHICLE_STANDARD,
    VEHICLE_RECYCLING,
    VEHICLE_HAZMAT
} VehicleType;


/* =========================================================
   VEHICLE STATUS
   ========================================================= */

typedef enum
{
    VEHICLE_AVAILABLE,
    VEHICLE_ASSIGNED,
    VEHICLE_REFUELING,
    VEHICLE_MAINTENANCE,
    VEHICLE_OUT_OF_SERVICE
} VehicleStatus;


/* =========================================================
   DRIVER STATUS
   ========================================================= */

typedef enum
{
    DRIVER_AVAILABLE,
    DRIVER_ASSIGNED,
    DRIVER_OFF_DUTY
} DriverStatus;


/* =========================================================
   COMPLAINT STATUS
   ========================================================= */

typedef enum
{
    COMPLAINT_OPEN,

    /*
     * Waste collection related to the complaint has
     * been completed, but the admin has not closed it yet.
     */
    COMPLAINT_SERVICED,

    COMPLAINT_RESOLVED
} ComplaintStatus;


/* =========================================================
   USER ACCOUNT
   Demo role-based authentication.
   ========================================================= */

typedef struct
{
    int id;

    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    UserRole role;

    int active;

} UserAccount;


/* =========================================================
   ZONE

   Every zone will eventually be created by the admin.
   Each zone has its own depot coordinates.
   ========================================================= */

typedef struct
{
    int id;

    char name[MAX_NAME_LENGTH];

    float depotX;
    float depotY;

    int active;

} Zone;


/* =========================================================
   BIN

   currentWasteKg is the actual stored waste.

   fillLevel is maintained as a derived percentage:

       currentWasteKg
   ----------------------- x 100
       capacityKg
   ========================================================= */

typedef struct
{
    int id;

    char location[MAX_ADDRESS_LENGTH];

    int zoneId;

    /*
     * Kept temporarily because old display/setup code
     * still uses the zone name directly.
     */
    char zone[MAX_NAME_LENGTH];

    float x;
    float y;

    WasteType wasteType;

    float capacityKg;
    float currentWasteKg;

    float fillLevel;

    PriorityLevel priority;
    BinStatus status;

    int complaintCount;
    int emergencyFlag;

    float priorityScore;

} Bin;


/* =========================================================
   VEHICLE
   ========================================================= */

typedef struct
{
    int id;

    char registrationNumber[MAX_NAME_LENGTH];

    VehicleType type;

    /*
     * Zone to which this vehicle normally belongs.
     * 0 means not yet configured.
     */
    int homeZoneId;

    float capacity;
    float currentLoad;

    /*
     * These percentage-based fields are preserved only so
     * existing code continues working during this patch.

     * Next patch will replace this with actual:
       tankCapacityLitres
       currentFuelLitres
       mileageKmPerLitre
     */
    float fuelLevel;
    float fuelEfficiency;

    float x;
    float y;

    VehicleStatus status;

    int assignedDriverId;

    float totalDistanceTravelled;
    float totalFuelConsumed;

} Vehicle;


/* =========================================================
   DRIVER
   ========================================================= */

typedef struct
{
    int id;

    char name[MAX_NAME_LENGTH];

    DriverStatus status;

    int assignedVehicleId;

    int hazmatCertified;

} Driver;


/* =========================================================
   COMPLAINT
   ========================================================= */

typedef struct
{
    int id;

    char description[MAX_DESCRIPTION_LENGTH];
    char address[MAX_ADDRESS_LENGTH];

    int binId;
    int zoneId;

    int severity;

    ComplaintStatus status;

} Complaint;


/* =========================================================
   ROUTE
   ========================================================= */

typedef struct
{
    int vehicleId;

    int binIds[MAX_ROUTE_STOPS];
    int stopCount;

    float totalDistance;
    float estimatedFuelConsumption;

} Route;


/* =========================================================
   SIMULATION / OPERATION STATISTICS
   ========================================================= */

typedef struct
{
    int cycleNumber;

    int binsCollected;
    int complaintsHandled;
    int emergenciesHandled;

    int routesCompleted;
    int failedCollections;

    float totalWasteCollectedKg;

    float totalDistanceTravelled;
    float totalFuelConsumed;

} SimulationStats;

#endif