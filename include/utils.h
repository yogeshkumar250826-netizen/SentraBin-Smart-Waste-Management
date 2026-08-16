#ifndef UTILS_H
#define UTILS_H

#include "models.h"

float calculateManhattanDistance(float x1, float y1, float x2, float y2);

int randomInt(int min, int max);
float randomFloat(float min, float max);

const char *getWasteTypeString(WasteType type);
const char *getPriorityString(PriorityLevel priority);
const char *getBinStatusString(BinStatus status);
const char *getVehicleStatusString(VehicleStatus status);
const char *getDriverStatusString(DriverStatus status);

#endif