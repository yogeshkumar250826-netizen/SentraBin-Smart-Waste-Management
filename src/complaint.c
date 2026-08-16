#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "complaint.h"
#include "priority.h"

static void toLowerString(
    const char source[],
    char destination[],
    int size
)
{
    int i;

    for (i = 0; source[i] != '\0' && i < size - 1; i++)
    {
        destination[i] =
            (char)tolower((unsigned char)source[i]);
    }

    destination[i] = '\0';
}


int findBinByAddress(
    const char address[],
    const Bin bins[],
    int binCount
)
{
    char input[MAX_ADDRESS_LENGTH];
    char location[MAX_ADDRESS_LENGTH];
    char zone[MAX_NAME_LENGTH];

    toLowerString(
        address,
        input,
        MAX_ADDRESS_LENGTH
    );

    for (int i = 0; i < binCount; i++)
    {
        toLowerString(
            bins[i].location,
            location,
            MAX_ADDRESS_LENGTH
        );

        toLowerString(
            bins[i].zone,
            zone,
            MAX_NAME_LENGTH
        );

        if (strstr(input, location) != NULL)
        {
            return i;
        }

        if (strstr(input, zone) != NULL)
        {
            return i;
        }
    }

    return -1;
}


int detectComplaintSeverity(
    const char description[]
)
{
    char text[MAX_DESCRIPTION_LENGTH];

    toLowerString(
        description,
        text,
        MAX_DESCRIPTION_LENGTH
    );

    int severity = 1;

    if (strstr(text, "smell") != NULL ||
        strstr(text, "dirty") != NULL ||
        strstr(text, "garbage") != NULL)
    {
        severity = 2;
    }

    if (strstr(text, "overflow") != NULL ||
        strstr(text, "hazardous") != NULL ||
        strstr(text, "toxic") != NULL ||
        strstr(text, "fire") != NULL)
    {
        severity = 3;
    }

    return severity;
}

int submitComplaint(
    Complaint complaints[],
    int *complaintCount,
    Bin bins[],
    int binCount,
    const char address[],
    const char description[]
)
{
    if (*complaintCount >= MAX_COMPLAINTS)
    {
        printf("Complaint storage is full.\n");
        return 0;
    }

    int binIndex =
        findBinByAddress(
            address,
            bins,
            binCount
        );

    if (binIndex == -1)
    {
        printf(
            "\nComplaint rejected: location could not be matched to a bin.\n"
        );

        return 0;
    }

    int severity =
        detectComplaintSeverity(description);

    Complaint *complaint =
        &complaints[*complaintCount];

    complaint->id =
        *complaintCount + 1;

    strncpy(
        complaint->address,
        address,
        MAX_ADDRESS_LENGTH - 1
    );

    complaint->address[MAX_ADDRESS_LENGTH - 1] =
        '\0';

    strncpy(
        complaint->description,
        description,
        MAX_DESCRIPTION_LENGTH - 1
    );

    complaint->description[MAX_DESCRIPTION_LENGTH - 1] =
        '\0';

    complaint->binId =
        bins[binIndex].id;

    complaint->severity =
        severity;

    complaint->status =
        COMPLAINT_OPEN;

    bins[binIndex].complaintCount++;

    /*
     * Severe complaints trigger emergency handling.
     */
    if (severity == 3)
    {
        bins[binIndex].emergencyFlag = 1;
    }

    updateBinPriority(
        &bins[binIndex]
    );

    (*complaintCount)++;

    printf("\nComplaint registered successfully.\n");

    printf(
        "Matched Bin : B%d - %s\n",
        bins[binIndex].id,
        bins[binIndex].location
    );

    printf(
        "Severity    : %s\n",
        severity == 3 ? "HIGH" :
        severity == 2 ? "MEDIUM" :
                        "LOW"
    );

    if (severity == 3)
    {
        printf(
            "Emergency handling activated.\n"
        );
    }

    return 1;
}

void displayComplaints(
    const Complaint complaints[],
    int complaintCount
)
{
    printf("\n");
    printf("====================================================================\n");
    printf("                         COMPLAINT LOG\n");
    printf("====================================================================\n");

    if (complaintCount == 0)
    {
        printf("No complaints registered.\n");
        return;
    }

    for (int i = 0; i < complaintCount; i++)
    {
        printf(
            "\nComplaint #%d\n",
            complaints[i].id
        );

        printf(
            "Address     : %s\n",
            complaints[i].address
        );

        printf(
            "Matched Bin : B%d\n",
            complaints[i].binId
        );

        printf(
            "Description : %s\n",
            complaints[i].description
        );

        printf(
            "Severity    : %d\n",
            complaints[i].severity
        );

        printf(
            "Status      : %s\n",
            complaints[i].status == COMPLAINT_OPEN
                ? "OPEN"
                : "RESOLVED"
        );
    }

    printf("====================================================================\n");
}

void resolveComplaintsForBin(
    Complaint complaints[],
    int complaintCount,
    int binId,
    SimulationStats *stats
)
{
    for (int i = 0; i < complaintCount; i++)
    {
        if (complaints[i].binId == binId &&
            complaints[i].status == COMPLAINT_OPEN)
        {
            complaints[i].status = COMPLAINT_RESOLVED;

            stats->complaintsHandled++;

            printf(
                "Complaint #%d automatically resolved.\n",
                complaints[i].id
            );
        }
    }
}