#include "Car.hpp"
#include "SharedData.hpp"
#include <iostream>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>

// Each bumping time is between 0 to TIME_BUMP
#define TIME_BUMP 10

Car::Car(int cid) {

    this->cid = cid;
    pthread_create(&carThread, NULL, ride, this);
}

void* Car::ride(void* car) {

    Car* carInstance = static_cast<Car*>(car);

    while (true) {
        carInstance->Load();
        carInstance->Bump();
        carInstance->Unload();
        --NUMBER_OF_RIDES;

        // Check for the condition to exit the while loop
        if (NUMBER_OF_RIDES == 0)
            break;
    }

    return NULL;
}

void Car::Bump() {
    sleep(rand() % TIME_BUMP + 1); // +1 because rand() ranges [0, N-1]
    std::cout << "Rider: " << rider.getRID() << " just bumped\n";
}

void Car::Load() {
    sem_wait(&waitingForRide);  // Wait for a rider to get in line
    sem_wait(&waitingLineMutex); // Protect access to the waiting line

    // Logic to select and assign a rider to the car
    for (int i = 0; i < waitingRiders.size(); ++i) {
        if (waitingRiders[i].assignedCar == -1) {
            waitingRiders[i].assignedCar = cid;
            rider = waitingRiders[i];
            waitingRiders.erase(waitingRiders.begin() + i);
            break;
        }
    }

    sem_post(&waitingLineMutex); // Release the waiting line mutex

    std::cout << "Car " << cid << " takes rider: " << rider.getRID() << ".\n";
}

void Car::Unload() {
    sem_post(&riding);
    std::cout << "This ride of Car " << cid << " is over.\n";
}
