/*
    @file Rider.cpp

    Implementation file for Rider class
*/

#include "Rider.hpp"
#include "SharedData.hpp"
#include "output.hpp"
#include <iostream>
#include <semaphore.h>
#include <unistd.h>

// Each wandering time is between 0 to TIME_WANDER
#define TIME_WANDER 3

Rider::Rider(int riderID){
    rid = riderID;
}

void* Rider::enjoyPark(void* rider) {
    Rider* riderInstance = static_cast<Rider*>(rider);

    while (true) {

        sem_wait(&numberOfRidesMutex);

        if (NUMBER_OF_RIDES > 0) {

            --NUMBER_OF_RIDES;
            sem_post(&numberOfRidesMutex);

            riderInstance->Wander();
            riderInstance->GetInLine();

            sem_wait(&waitingForRide[riderInstance->rid-1]);

            riderInstance->TakeASeat();
            riderInstance->TakeARide();

            sem_wait(&riding[riderInstance->rid-1]);
        }

        else {
            sem_post(&numberOfRidesMutex);
            riderInstance->leavePark();
            break;
        }
    }

    return NULL;
}

void Rider::leavePark() {
    sem_wait(&outputMutex);
    std::string msg = "Rider " + std::to_string(rid) + " is leaving the park.\n";
    display(msg, rid);
    sem_post(&outputMutex);
}

void Rider::Wander() {
    sem_wait(&outputMutex);
    std::string msg = "Rider " + std::to_string(rid) + " is wandering around the park.\n";
    display(msg, rid);
    sem_post(&outputMutex);

    sleep(rand() % TIME_WANDER + 1); // + 1 because rand() ranges [0, N-1]
}

void Rider::GetInLine() {

    sem_wait(&outputMutex);
    std::string msg = "Rider " + std::to_string(rid) + " gets in the waiting line.\n";
    display(msg, rid);
    sem_post(&outputMutex);

    // Add the rider's ID to the waiting queue
    sem_wait(&waitingForRideMutex);
    waitingRiderIDs.push(rid);
    sem_post(&waitingForRideMutex);
}

void Rider::TakeASeat() {
    sem_wait(&outputMutex);
    std::string msg = "Rider " + std::to_string(rid) + " takes a seat.\n";
    display(msg, rid);
    sem_post(&outputMutex);
}

void Rider::TakeARide() {
    sem_wait(&outputMutex);
    std::string msg = "Rider " + std::to_string(rid) + " is taking the ride.\n";
    display(msg, rid);
    sem_post(&outputMutex);
}
