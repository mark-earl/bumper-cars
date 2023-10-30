/*
    @file SharedData.hpp

    Variables that are accessed by Car and/or Rider threads
*/

#ifndef SHAREDDATA_HPP
#define SHAREDDATA_HPP

#include <semaphore.h>
#include <queue>
#include "Rider.hpp"

extern int NUMBER_OF_RIDES;
extern sem_t outputMutex;
extern sem_t numberOfRidesMutex;
extern sem_t riderIDMutex;
extern sem_t waitingForRideMutex;
extern std::vector<sem_t> waitingForRide;
extern std::vector<sem_t> riding;
extern std::queue<int> waitingRiderIDs;

#endif // SHAREDDATA_HPP
