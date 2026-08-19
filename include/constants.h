#ifndef CONSTANTS_H
#define CONSTANTS_H

#define MAX_ZONES 20
#define MAX_BINS 200
#define MAX_VEHICLES 100
#define MAX_DRIVERS 100
#define MAX_COMPLAINTS 500
#define MAX_USERS 100
#define MAX_ROUTE_STOPS 200

#define MAX_NAME_LENGTH 50
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_ADDRESS_LENGTH 120
#define MAX_DESCRIPTION_LENGTH 200

/* Coordinate-grid simulation limits */
#define MIN_COORDINATE 0.0f
#define MAX_COORDINATE 1000.0f

/* Bin limits */
#define MIN_BIN_CAPACITY_KG 20.0f
#define MAX_BIN_CAPACITY_KG 5000.0f
#define DEFAULT_BIN_CAPACITY_KG 500.0f
#define MAX_FILL_LEVEL 100.0f

/* Priority thresholds */
#define CRITICAL_PRIORITY_THRESHOLD 85.0f
#define HIGH_PRIORITY_THRESHOLD 70.0f
#define MEDIUM_PRIORITY_THRESHOLD 50.0f

/* Legacy fuel threshold.
   We will replace percentage-based fuel with litres
   in the next dedicated fuel patch. */
#define LOW_FUEL_THRESHOLD 20.0f
#define FULL_FUEL_LEVEL 100.0f

/* Routing */
#define MAX_ROUTE_DETOUR 15.0f

/* Default depot used only until admin-defined zones are active */
#define DEPOT_X 5.0f
#define DEPOT_Y 5.0f

#endif