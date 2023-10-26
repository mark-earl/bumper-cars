// SharedData.hpp
#ifndef SHAREDDATA_HPP
#define SHAREDDATA_HPP

#include <semaphore.h>
#include <queue>
#include "Rider.hpp"

extern sem_t waitingForRide;
extern sem_t riding;
extern sem_t mutex;
extern std::queue<Rider> waitingRiders;

#endif // SHAREDDATA_HPP
