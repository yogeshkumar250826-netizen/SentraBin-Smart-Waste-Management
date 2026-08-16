#include "priority.h"

float calculatePriorityScore(const Bin *bin)
{
    float score;

    if (bin->fillLevel <= 0.0f)
        return 0.0f;

    /* Fill level is the primary factor */
    score = bin->fillLevel * 0.80f;

    switch (bin->wasteType)
    {
        case WASTE_HAZARDOUS:
            score += 10.0f;
            break;

        case WASTE_ORGANIC:
            score += 6.0f;
            break;

        case WASTE_RECYCLABLE:
            score += 3.0f;
            break;

        case WASTE_GENERAL:
        default:
            break;
    }

    /* Complaints contribute a maximum of 5 points */
    float complaintScore =
        bin->complaintCount * 2.0f;

    if (complaintScore > 5.0f)
        complaintScore = 5.0f;

    score += complaintScore;

    if (bin->emergencyFlag)
        score += 5.0f;

    if (score > 100.0f)
        score = 100.0f;

    return score;
}

PriorityLevel determinePriorityLevel(float score)
{
    if (score >= CRITICAL_PRIORITY_THRESHOLD)
        return PRIORITY_CRITICAL;

    if (score >= HIGH_PRIORITY_THRESHOLD)
        return PRIORITY_HIGH;

    if (score >= MEDIUM_PRIORITY_THRESHOLD)
        return PRIORITY_MEDIUM;

    return PRIORITY_NORMAL;
}

void updateBinPriority(Bin *bin)
{
    bin->priorityScore =
        calculatePriorityScore(bin);

    bin->priority =
        determinePriorityLevel(bin->priorityScore);

    /*
     * Operational overrides:
     * fill level must trigger collection before overflow.
     */
    if (bin->emergencyFlag ||
        bin->fillLevel >= 95.0f)
    {
        bin->priority = PRIORITY_CRITICAL;
    }
    else if (bin->fillLevel >= 80.0f &&
             bin->priority < PRIORITY_HIGH)
    {
        bin->priority = PRIORITY_HIGH;
    }

    if (bin->priority == PRIORITY_HIGH ||
        bin->priority == PRIORITY_CRITICAL)
    {
        bin->status = BIN_COLLECTION_REQUIRED;
    }
    else
    {
        bin->status = BIN_AVAILABLE;
    }
}