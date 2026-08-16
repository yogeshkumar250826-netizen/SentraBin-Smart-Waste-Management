#include "priority.h"

float calculatePriorityScore(const Bin *bin)
{
    float score = 0.0f;

    /*
     * Fill level contributes up to 60 points.
     * 100% full bin -> 60 points.
     */
    score += bin->fillLevel * 0.60f;

    /*
     * Waste type contribution.
     */
    switch (bin->wasteType)
    {
        case WASTE_HAZARDOUS:
            score += 20.0f;
            break;

        case WASTE_ORGANIC:
            score += 10.0f;
            break;

        case WASTE_RECYCLABLE:
            score += 5.0f;
            break;

        case WASTE_GENERAL:
        default:
            break;
    }

    /*
     * Complaints contribute up to 10 points.
     * Each complaint adds 2 points.
     */
    score += bin->complaintCount * 2.0f;

    if (score > 90.0f)
        score = 90.0f;

    /*
     * Emergency adds the final urgency boost.
     */
    if (bin->emergencyFlag)
        score += 10.0f;

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
    bin->priorityScore = calculatePriorityScore(bin);
    bin->priority = determinePriorityLevel(bin->priorityScore);

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