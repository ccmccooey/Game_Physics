#ifndef _PLANET_SCALE_FACTOR_H
#define _PLANET_SCALE_FACTOR_H

//1 / earth scale or 1 / sun scale? IDK
#define PLANET_SIZE_SCALE 1 / 695800 //6371 
#define PLANET_DISTANCE_SCALE 1.9e-7//1 / 149500000 * 100 //100 puts the cubes outside each other
#define PLANET_MASS_SCALE 1 / 5.97219e24 
#define PLANET_VELOCITY_CONVERT 60 * 60 * 24 //convert km/second to km/d
#define PLANET_GRAVITY_FACTOR 60 * 60 * 24 / 1000 //convert m/s^2 to km/d^2

#endif