#ifndef PRIORITY_H
#define PRIORITY_H

#include "models.h"

float calculatePriorityScore(const Bin *bin);
PriorityLevel determinePriorityLevel(float score);
void updateBinPriority(Bin *bin);

#endif