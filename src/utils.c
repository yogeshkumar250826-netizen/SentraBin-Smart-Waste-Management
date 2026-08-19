#include <stdlib.h>
#include <math.h>
#include "utils.h"

float calculateManhattanDistance(float x1, float y1, float x2, float y2)
{
    return fabsf(x1 - x2) + fabsf(y1 - y2);
}

int randomInt(int min, int max)
{
    return min + rand() % (max - min + 1);
}

float randomFloat(float min, float max)
{
    float value = (float)rand() / (float)RAND_MAX;

    return min + value * (max - min);
}

const char *getWasteTypeString(WasteType type)
{
    switch (type)
    {
        case WASTE_GENERAL:
            return "General";

        case WASTE_RECYCLABLE:
            return "Recyclable";

        case WASTE_ORGANIC:
            return "Organic";

        case WASTE_HAZARDOUS:
            return "Hazardous";

        default:
            return "Unknown";
    }
}

const char *getPriorityString(PriorityLevel priority)
{
    switch (priority)
    {
        case PRIORITY_NORMAL:
            return "Normal";

        case PRIORITY_MEDIUM:
            return "Medium";

        case PRIORITY_HIGH:
            return "High";

        case PRIORITY_CRITICAL:
            return "Critical";

        default:
            return "Unknown";
    }
}

const char *getBinStatusString(BinStatus status)
{
    switch (status)
    {
        case BIN_AVAILABLE:
            return "Available";

        case BIN_COLLECTION_REQUIRED:
            return "Collection Required";

        case BIN_UNDER_COLLECTION:
            return "Under Collection";

        default:
            return "Unknown";
    }
}

const char *getVehicleStatusString(VehicleStatus status)
{
    switch (status)
    {
        case VEHICLE_AVAILABLE:
            return "Available";

        case VEHICLE_ASSIGNED:
            return "Assigned";

        case VEHICLE_REFUELING:
            return "Refueling";

        case VEHICLE_MAINTENANCE:
            return "Maintenance";

        default:
            return "Unknown";
    }
}

const char *getDriverStatusString(DriverStatus status)
{
    switch (status)
    {
        case DRIVER_AVAILABLE:
            return "Available";

        case DRIVER_ASSIGNED:
            return "Assigned";

        case DRIVER_OFF_DUTY:
            return "Off Duty";

        default:
            return "Unknown";
    }
}

const char *getVehicleTypeString(VehicleType type)
{
    switch (type)
    {
        case VEHICLE_STANDARD:
            return "Standard";

        case VEHICLE_RECYCLING:
            return "Recycling";

        case VEHICLE_HAZMAT:
            return "Hazmat";

        default:
            return "Unknown";
    }
}