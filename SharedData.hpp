// SharedData.hpp
#ifndef SHAREDDATA_HPP
#define SHAREDDATA_HPP

#include <semaphore.h>
#include "Rider.hpp"
#include <vector>

extern sem_t waitingForRide;
extern sem_t riding;
extern sem_t waitingLineMutex;
extern int NUMBER_OF_RIDES;
extern std::vector<Rider> waitingRiders;

#endif // SHAREDDATA_HPP
