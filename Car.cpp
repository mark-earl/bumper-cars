/*
    @file Car.cpp

    Implementation file for Car class
*/

#include "Car.hpp"
#include "SharedData.hpp"
#include "output.hpp"
#include <iostream>
#include <semaphore.h>
#include <unistd.h>

// Each bump time is between 0 to TIME_BUMP
#define TIME_BUMP 3

Car::Car(int carID) {
    cid = carID;
}

void* Car::ride(void* car) {

    Car* carInstance = static_cast<Car*>(car);

    while (true) {

        // Bumper Car Ride
        sem_wait(&waitingForRideMutex);
        if (!waitingRiderIDs.empty()) {
            carInstance->Load(waitingRiderIDs.front());
            waitingRiderIDs.pop();
            sem_post(&waitingForRideMutex);
            sem_post(&waitingForRide[carInstance->currentRiderID-1]);
        }

        else {
            sem_post(&waitingForRideMutex);
            continue; // No riders in line, continue to next iteration
        }

        carInstance->Bump();
        carInstance->Unload();
        sem_post(&riding[carInstance->currentRiderID-1]);
        carInstance->currentRiderID = -1;
    }

    return NULL;
}

void Car::Load(int riderID) {

    sem_wait(&riderIDMutex);
    currentRiderID = riderID;
    sem_post(&riderIDMutex);

    sem_wait(&outputMutex);

    std::string msg = "Car " + std::to_string(cid) + " takes Rider " + std::to_string(currentRiderID) + ".\n";
    display(msg, currentRiderID);
    sem_post(&outputMutex);
}


void Car::Bump() {

    sleep(rand() % TIME_BUMP + 1); // +1 because rand() ranges [0, N-1]

    sem_wait(&outputMutex);
    std::string msg = "Car " + std::to_string(cid) + " with Rider " + std::to_string(currentRiderID) + " just bumped.\n";
    display(msg, currentRiderID);
    sem_post(&outputMutex);
}

void Car::Unload() {

    sem_wait(&outputMutex);
    std::string msg = "Car " + std::to_string(cid) + " ride with Rider " + std::to_string(currentRiderID) + " is over.\n";
    display(msg, currentRiderID);
    sem_post(&outputMutex);
}
