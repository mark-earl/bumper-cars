// SharedData.hpp
#ifndef SHAREDDATA_HPP
#define SHAREDDATA_HPP

#include <semaphore.h>
#include "Rider.hpp"
#include <queue>

extern int NUMBER_OF_RIDES;
extern sem_t waitingForRide;
extern sem_t riding;
extern sem_t waitingLineMutex;
extern std::queue<Rider> waitingRiders;

#endif // SHAREDDATA_HPP
