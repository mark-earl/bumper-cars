#include "Car.hpp"
#include "SharedData.hpp"
#include <iostream>
#include <semaphore.h>
#include <unistd.h>
#include <cstdlib>

int NUMBER_OF_RIDES = 10;

// Each bumping time is between 0 to TIME_BUMP
#define TIME_BUMP 10

Car::Car(int carID) {
    cid = carID;
}

void* Car::ride(void* car) {

    Car* carInstance = static_cast<Car*>(car);

    while (true) {

        // Bumper Car Ride
        carInstance->Load(carInstance->currentRiderID);
        carInstance->Bump();
        carInstance->Unload();

        // Decrement number of rides (protected)
        sem_wait(&mutex);
        --NUMBER_OF_RIDES;
        sem_post(&mutex);

        // Check for the condition to exit the while loop
        if (NUMBER_OF_RIDES > 0)
            continue;
        else if (NUMBER_OF_RIDES == 0)
            break;
        else if (NUMBER_OF_RIDES < 0)
            std::cerr << "ERROR: More riders let ride than allowed!\n";
    }

    return NULL;
}

void Car::Load(int riderID) {
    // Wait for an available slot in the car (using the 'riding' semaphore)
    sem_wait(&riding);

    // Lock the 'mutex' to ensure safe access to the 'currentRiderID' variable
    sem_wait(&mutex);

    // Assign the rider to the car
    currentRiderID = riderID;

    // Release the 'mutex'
    sem_post(&mutex);

    std::cout << "Car " << cid << " takes rider: " << currentRiderID << ".\n";
}


void Car::Bump() {
    sleep(rand() % TIME_BUMP + 1); // +1 because rand() ranges [0, N-1]
    std::cout << "Rider: " << currentRiderID << " just bumped.\n";
}

void Car::Unload() {
    sem_post(&riding);
    std::cout << "This ride of Car " << cid << " with Rider " << currentRiderID << " is over.\n";
    currentRiderID = -1;
}
