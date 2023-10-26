#include "Car.hpp"
#include "SharedData.hpp"
#include <iostream>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>

// Each bumping time is between 0 to TIME_BUMP
#define TIME_BUMP 10

Car::Car(int carID) {
    cid = carID;
}

void* Car::ride(void* car) {

    Car* carInstance = static_cast<Car*>(car);

    while (true) {
        carInstance->Load(carInstance->currentRiderID);
        carInstance->Bump();
        carInstance->Unload();
        --NUMBER_OF_RIDES;

        // Check for the condition to exit the while loop
        if (NUMBER_OF_RIDES == 0)
            break;
    }

    return NULL;
}

void Car::Load(int riderID) {
    // TODO Logic to select and assign a rider to the car using semaphores
    std::cout << "Car " << cid << " takes rider: " << currentRiderID << ".\n";
}

void Car::Bump() {
    sleep(rand() % TIME_BUMP + 1); // +1 because rand() ranges [0, N-1]
    std::cout << "Rider: " << currentRiderID << " just bumped.\n";
}

void Car::Unload() {
    sem_post(&riding);
    std::cout << "This ride of Car " << cid << " is over.\n";
}
