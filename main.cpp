/*
    @file main.cpp

    Simulate an amusment park that has a bumper cars ride.
*/

#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <semaphore.h>
#include "Car.hpp"
#include "Rider.hpp"

// Define behavior of the park here
#define NUMBER_OF_CARS 2
#define NUMBER_OF_RIDERS 5
int NUMBER_OF_RIDES = 10;

// Waiting line to hold the riders
std::queue<int> waitingRiderIDs;

// Containers to hold riders and cars
std::vector<Rider> riders;
std::vector<Car> cars;

// Mutex
sem_t outputMutex;         // Only one thread is allowed to output at a time
sem_t numberOfRidesMutex;  // Only one thread can alter the number of rides left at a time
sem_t riderIDMutex;        // Only one thread can assign a rider ID at a time
sem_t waitingForRideMutex; // Only one thread can push rids to the queue at a time

// Counting Semaphores
std::vector<sem_t> waitingForRide(NUMBER_OF_RIDERS);      // Prevent riders from loading when there is no car
std::vector<sem_t> riding(NUMBER_OF_RIDERS);              // Prevent riders from wandering when the ride is not over

int main() {

    std::cout << "The park is now OPEN.\n\n";

    // Initialize semaphores and other necessary resources
    sem_init(&outputMutex, 0, 1);
    sem_init(&numberOfRidesMutex, 0, 1);
    sem_init(&riderIDMutex, 0, 1);
    sem_init(&waitingForRideMutex, 0, 1);

    for (int i = 0; i < NUMBER_OF_RIDERS; ++i) {
        sem_init(&waitingForRide[i], 0, 0);
        sem_init(&riding[i], 0, 0);
    }

    // Containers to hold rider and car threads
    std::vector<pthread_t> riderThreads(NUMBER_OF_RIDERS);
    std::vector<pthread_t> carThreads(NUMBER_OF_CARS);

    // Set rid from [1, NUMBER_OF_RIDERS]
    for (int i = 1; i <= NUMBER_OF_RIDERS; ++i) {
        riders.push_back(Rider(i));
    }

    // Set cid from [1, NUMBER_OF_CARS]
    for (int i = 1; i <= NUMBER_OF_CARS; ++i) {
        cars.push_back(Car(i));
    }

    // Create threads for all riders
    for (int i = 0; i < NUMBER_OF_RIDERS; ++i) {
        pthread_create(&riderThreads[i], NULL, riders[i].enjoyPark, &riders[i]);
    }

    // Create threads for all cars
    for (int i = 0; i < NUMBER_OF_CARS; ++i) {
        pthread_create(&carThreads[i], NULL, cars[i].ride, &cars[i]);
    }

    // Join all rider threads to ensure they finish before exiting.
    for (auto& riderThread : riderThreads) {
        pthread_join(riderThread, NULL);
    }

    // Manually stop the car threads once the riders leave the park
    for (auto& carThread : carThreads) {
        pthread_cancel(carThread);
    }

    // Destroy semaphores and release resources.
    sem_destroy(&outputMutex);
    sem_destroy(&numberOfRidesMutex);
    sem_destroy(&riderIDMutex);
    sem_destroy(&waitingForRideMutex);

    for (int i = 0; i < NUMBER_OF_RIDERS; ++i) {
        sem_destroy(&waitingForRide[i]);
        sem_destroy(&riding[i]);
    }

    std::cout << "\nThe park is now CLOSED.\n";

    return 0;
}
