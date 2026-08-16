#include <stdio.h>

#include "fleet.h"
#include "utils.h"

void initializeVehicles(Vehicle vehicles[], int *vehicleCount)
{
    *vehicleCount = 3;

    vehicles[0] = (Vehicle){
        .id = 1,
        .registrationNumber = "TN01AB1001",
        .capacity = 500.0f,
        .currentLoad = 0.0f,
        .fuelLevel = 80.0f,
        .fuelEfficiency = 8.0f,
        .x = 5.0f,
        .y = 5.0f,
        .status = VEHICLE_AVAILABLE,
        .assignedDriverId = -1,
        .totalDistanceTravelled = 0.0f,
        .totalFuelConsumed = 0.0f
    };

    vehicles[1] = (Vehicle){
        .id = 2,
        .registrationNumber = "TN02CD2002",
        .capacity = 700.0f,
        .currentLoad = 0.0f,
        .fuelLevel = 65.0f,
        .fuelEfficiency = 9.0f,
        .x = 20.0f,
        .y = 10.0f,
        .status = VEHICLE_AVAILABLE,
        .assignedDriverId = -1,
        .totalDistanceTravelled = 0.0f,
        .totalFuelConsumed = 0.0f
    };

    vehicles[2] = (Vehicle){
        .id = 3,
        .registrationNumber = "TN03EF3003",
        .capacity = 900.0f,
        .currentLoad = 0.0f,
        .fuelLevel = 90.0f,
        .fuelEfficiency = 10.0f,
        .x = 10.0f,
        .y = 15.0f,
        .status = VEHICLE_AVAILABLE,
        .assignedDriverId = -1,
        .totalDistanceTravelled = 0.0f,
        .totalFuelConsumed = 0.0f
    };
}

void initializeDrivers(Driver drivers[], int *driverCount)
{
    *driverCount = 3;

    drivers[0] = (Driver){
        .id = 1,
        .name = "Arun",
        .status = DRIVER_AVAILABLE,
        .assignedVehicleId = -1
    };

    drivers[1] = (Driver){
        .id = 2,
        .name = "Karthik",
        .status = DRIVER_AVAILABLE,
        .assignedVehicleId = -1
    };

    drivers[2] = (Driver){
        .id = 3,
        .name = "Ravi",
        .status = DRIVER_AVAILABLE,
        .assignedVehicleId = -1
    };
}

void assignDriversToVehicles(
    Vehicle vehicles[],
    int vehicleCount,
    Driver drivers[],
    int driverCount
)
{
    int driverIndex = 0;

    for (int i = 0; i < vehicleCount && driverIndex < driverCount; i++)
    {
        if (vehicles[i].assignedDriverId == -1 &&
            drivers[driverIndex].status == DRIVER_AVAILABLE)
        {
            vehicles[i].assignedDriverId = drivers[driverIndex].id;

            drivers[driverIndex].assignedVehicleId = vehicles[i].id;
            drivers[driverIndex].status = DRIVER_ASSIGNED;

            driverIndex++;
        }
    }
}

void displayVehicles(const Vehicle vehicles[], int vehicleCount)
{
    printf("\n");
    printf("==============================================================================================\n");
    printf("                                      VEHICLE STATUS\n");
    printf("==============================================================================================\n");

    printf("%-5s %-12s %-10s %-10s %-10s %-10s %-12s %-10s\n",
           "ID",
           "Reg No",
           "Capacity",
           "Load",
           "Fuel",
           "Driver",
           "Status",
           "Distance");

    printf("----------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < vehicleCount; i++)
    {
        printf("%-5d %-12s %-10.1f %-10.1f %-9.1f%% %-10d %-12s %-10.1f\n",
               vehicles[i].id,
               vehicles[i].registrationNumber,
               vehicles[i].capacity,
               vehicles[i].currentLoad,
               vehicles[i].fuelLevel,
               vehicles[i].assignedDriverId,
               getVehicleStatusString(vehicles[i].status),
               vehicles[i].totalDistanceTravelled);
    }

    printf("==============================================================================================\n");
}

void displayDrivers(const Driver drivers[], int driverCount)
{
    printf("\n");
    printf("==============================================================\n");
    printf("                         DRIVER STATUS\n");
    printf("==============================================================\n");

    printf("%-5s %-15s %-15s %-10s\n",
           "ID",
           "Name",
           "Status",
           "Vehicle");

    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < driverCount; i++)
    {
        printf("%-5d %-15s %-15s %-10d\n",
               drivers[i].id,
               drivers[i].name,
               getDriverStatusString(drivers[i].status),
               drivers[i].assignedVehicleId);
    }

    printf("==============================================================\n");
}

void updateVehicleFuelState(Vehicle vehicles[], int vehicleCount)
{
    for (int i = 0; i < vehicleCount; i++)
    {
        if (vehicles[i].fuelLevel <= LOW_FUEL_THRESHOLD)
        {
            vehicles[i].status = VEHICLE_REFUELING;

            printf(
                "\nVehicle %d fuel low (%.1f%%). Automatic refuelling triggered.\n",
                vehicles[i].id,
                vehicles[i].fuelLevel
            );

            vehicles[i].fuelLevel = FULL_FUEL_LEVEL;
            vehicles[i].status = VEHICLE_AVAILABLE;

            printf(
                "Vehicle %d refuelled to %.1f%%.\n",
                vehicles[i].id,
                vehicles[i].fuelLevel
            );
        }
    }
}