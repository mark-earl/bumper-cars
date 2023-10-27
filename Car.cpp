#include "Car.hpp"
#include "SharedData.hpp"
#include <iostream>
#include <semaphore.h>
#include <unistd.h>
#include <cstdlib>

// Each bump time is between 0 to TIME_BUMP
#define TIME_BUMP 10

Car::Car(int carID) {
    cid = carID;
}

void* Car::ride(void* car) {

    Car* carInstance = static_cast<Car*>(car);

    while (true) {

        // Bumper Car Ride
        sem_wait(&waitingForRideMutex);
        if (!waitingRiderIDs.empty()) {
            carInstance->running = true;
            carInstance->Load(waitingRiderIDs.front());
            waitingRiderIDs.pop();
            sem_post(&waitingForRideMutex);
            sem_post(&waitingForRide);
        }

        else {
            sem_post(&waitingForRideMutex);
            continue; // No riders in line, continue to next iteration
        }

        carInstance->Bump();
        carInstance->running = false;
        carInstance->Unload();
        sem_post(&riding);
    }

    return NULL;
}

bool Car::isRunning() {
    return running;
}

void Car::Load(int riderID) {

    sem_wait(&riderIDMutex);
    currentRiderID = riderID;
    sem_post(&riderIDMutex);

    sem_wait(&outputMutex);
    std::cout << "Car " << cid << " takes Rider " << currentRiderID << ".\n";
    sem_post(&outputMutex);
}


void Car::Bump() {

    sleep(rand() % TIME_BUMP + 1); // +1 because rand() ranges [0, N-1]

    sem_wait(&outputMutex);
    std::cout << "Car " << cid << " with Rider " << currentRiderID << " just bumped.\n";
    sem_post(&outputMutex);
}

void Car::Unload() {

    sem_wait(&outputMutex);
    std::cout << "Car " << cid << " ride with Rider " << currentRiderID << " is over.\n";
    sem_post(&outputMutex);
    currentRiderID = -1;
}
