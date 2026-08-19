#include <stdio.h>
#include <string.h>

#include "menu.h"
#include "bin.h"
#include "fleet.h"
#include "simulation.h"
#include "complaint.h"
#include "distance.h"
#include "storage.h"

static void saveSystemState(
    const Bin bins[],
    int binCount,
    const Vehicle vehicles[],
    int vehicleCount,
    const Driver drivers[],
    int driverCount,
    const Complaint complaints[],
    int complaintCount
)
{
    int success = 1;

    if (!saveBins(bins, binCount))
        success = 0;

    if (!saveVehicles(vehicles, vehicleCount))
        success = 0;

    if (!saveDrivers(drivers, driverCount))
        success = 0;

    if (!saveComplaints(complaints, complaintCount))
        success = 0;

    if (success)
        printf("\nSystem state saved successfully.\n");
    else
        printf("\nWarning: some data could not be saved.\n");
}


static void displaySimulationSummary(
    const SimulationStats *stats
)
{
    printf("\n");
    printf("=====================================================\n");
    printf("              SIMULATION SUMMARY\n");
    printf("=====================================================\n");

    printf(
        "Cycles Completed       : %d\n",
        stats->cycleNumber
    );

    printf(
        "Bins Collected         : %d\n",
        stats->binsCollected
    );

    printf(
        "Complaints Handled     : %d\n",
        stats->complaintsHandled
    );

    printf(
        "Emergencies Handled    : %d\n",
        stats->emergenciesHandled
    );

    printf(
        "Total Distance         : %.1f units\n",
        stats->totalDistanceTravelled
    );

    printf(
        "Total Fuel Consumed    : %.2f L\n",
        stats->totalFuelConsumed
    );

    printf("=====================================================\n");
}


static void submitComplaintInteractive(
    Complaint complaints[],
    int *complaintCount,
    Bin bins[],
    int binCount
)
{
    char address[MAX_ADDRESS_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];

    printf("\n");
    printf("=====================================================\n");
    printf("                 SUBMIT COMPLAINT\n");
    printf("=====================================================\n");

    printf("Enter location/address: ");

    fgets(
        address,
        sizeof(address),
        stdin
    );

    address[strcspn(address, "\n")] = '\0';

    printf("Enter complaint description: ");

    fgets(
        description,
        sizeof(description),
        stdin
    );

    description[strcspn(description, "\n")] = '\0';

    /*
     * Basic CSV-safe sanitization.
     */
    for (int i = 0; address[i] != '\0'; i++)
    {
        if (address[i] == ',')
            address[i] = ' ';
    }

    for (int i = 0; description[i] != '\0'; i++)
    {
        if (description[i] == ',')
            description[i] = ' ';
    }

    submitComplaint(
        complaints,
        complaintCount,
        bins,
        binCount,
        address,
        description
    );
}


void runMainMenu(
    Bin bins[],
    int *binCount,
    Vehicle vehicles[],
    int *vehicleCount,
    Driver drivers[],
    int *driverCount,
    Complaint complaints[],
    int *complaintCount,
    SimulationStats *stats
)
{
    int choice;

    while (1)
    {
        printf("\n");
        printf("=====================================================\n");
        printf("      SENTRABIN - SMART WASTE COLLECTION SYSTEM\n");
        printf("=====================================================\n");
        printf("1. Run One Simulation Cycle\n");
        printf("2. Run Multiple Simulation Cycles\n");
        printf("3. View Bin Status\n");
        printf("4. View Fleet Status\n");
        printf("5. Submit Complaint\n");
        printf("6. View Complaint Log\n");
        printf("7. View Distance Matrix\n");
        printf("8. View Simulation Summary\n");
        printf("9. Save System State\n");
        printf("0. Save and Exit\n");
        printf("=====================================================\n");

        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid input.\n");

            while (getchar() != '\n')
                ;

            continue;
        }

        while (getchar() != '\n')
            ;

        switch (choice)
        {
            case 1:
            {
                runSimulationCycle(
                    bins,
                    *binCount,
                    vehicles,
                    *vehicleCount,
                    complaints,
                    *complaintCount,
                    stats
                );

                break;
            }

            case 2:
            {
                int cycles;

                printf("Enter number of cycles: ");

                if (scanf("%d", &cycles) != 1)
                {
                    printf("Invalid input.\n");

                    while (getchar() != '\n')
                        ;

                    break;
                }

                while (getchar() != '\n')
                    ;

                if (cycles <= 0)
                {
                    printf(
                        "Number of cycles must be greater than 0.\n"
                    );

                    break;
                }

                for (int i = 0; i < cycles; i++)
                {
                    runSimulationCycle(
                        bins,
                        *binCount,
                        vehicles,
                        *vehicleCount,
                        complaints,
                        *complaintCount,
                        stats
                    );
                }

                break;
            }

            case 3:
            {
                displayBins(
                    bins,
                    *binCount
                );

                break;
            }

            case 4:
            {
                displayVehicles(
                    vehicles,
                    *vehicleCount
                );

                displayDrivers(
                    drivers,
                    *driverCount
                );

                break;
            }

            case 5:
            {
                submitComplaintInteractive(
                    complaints,
                    complaintCount,
                    bins,
                    *binCount
                );

                break;
            }

            case 6:
            {
                displayComplaints(
                    complaints,
                    *complaintCount
                );

                break;
            }

            case 7:
            {
                float matrix[MAX_BINS][MAX_BINS];

                generateBinDistanceMatrix(
                    bins,
                    *binCount,
                    matrix
                );

                displayDistanceMatrix(
                    bins,
                    *binCount,
                    matrix
                );

                break;
            }

            case 8:
            {
                displaySimulationSummary(
                    stats
                );

                break;
            }

            case 9:
            {
                saveSystemState(
                    bins,
                    *binCount,
                    vehicles,
                    *vehicleCount,
                    drivers,
                    *driverCount,
                    complaints,
                    *complaintCount
                );

                break;
            }

            case 0:
            {
                saveSystemState(
                    bins,
                    *binCount,
                    vehicles,
                    *vehicleCount,
                    drivers,
                    *driverCount,
                    complaints,
                    *complaintCount
                );

                printf("\nExiting SentraBin.\n");

                return;
            }

            default:
            {
                printf("\nInvalid menu option.\n");
            }
        }
    }
}