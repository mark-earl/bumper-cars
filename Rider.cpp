#include "Rider.hpp"
#include "SharedData.hpp"
#include <iostream>
#include <semaphore.h>
#include <unistd.h>

// Each wandering time is between 0 to TIME_WANDER
#define TIME_WANDER 20

Rider::Rider(int riderID){
    rid = riderID;
}

void* Rider::enjoyPark(void* rider) {
    Rider* riderInstance = static_cast<Rider*>(rider);

    while (true) {

        riderInstance->wandering = true;
        riderInstance->Wander();    // Wander around for a random amount of time
        riderInstance->wandering = false;

        riderInstance->waiting = true;
        riderInstance->GetInLine(); // Get in line for the ride
        riderInstance->waiting = false;

        sem_wait(&waitingForRide);
        riderInstance->TakeASeat(); // Take a seat in a car
        riderInstance->TakeARide(); // Ride the ride
        sem_wait(&riding);
    }

    return NULL;
}

void Rider::leavePark() {
    done = true;
}

void Rider::GetInLine() {

    sem_wait(&outputMutex);
    std::cout << "Rider " << rid << " gets in the waiting line.\n";
    sem_post(&outputMutex);

    // Add the rider's ID to the waiting queue
    sem_wait(&waitingForRideMutex);
    waitingRiderIDs.push(rid);
    sem_post(&waitingForRideMutex);
}
void Rider::TakeASeat() {
    sem_wait(&outputMutex);
    std::cout << "Rider " << rid << " takes a seat.\n";
    sem_post(&outputMutex);
}
void Rider::TakeARide() {
    sem_wait(&outputMutex);
    std::cout << "Rider " << rid << " is taking the ride.\n";
    sem_post(&outputMutex);
}
void Rider::Wander() {
    sem_wait(&outputMutex);
    std::cout << "Rider " << rid << " is wandering around the park.\n";
    sem_post(&outputMutex);

    sleep(rand() % TIME_WANDER + 1); // + 1 because rand() ranges [0, N-1]
}
