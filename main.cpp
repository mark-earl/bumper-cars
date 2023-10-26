#include <iostream>
#include <thread>
#include <vector>
#include <semaphore.h>
#include "Car.hpp"
#include "Rider.hpp"

#define NUMBER_OF_CARS 2
#define NUMBER_OF_RIDERS 5
int NUMBER_OF_RIDES = 10;

// Waiting line to hold the riders
std::vector<Rider> waitingRiders;

sem_t waitingForRide;     // Semaphore to track empty slots in the buffer
sem_t riding;  // Semaphore to track occupied slots in the buffer
sem_t waitingLineMutex;    // Mutex to protect buffer access

int main() {
    // Initialize semaphores and other necessary resources
    sem_init(&waitingForRide, 0, NUMBER_OF_RIDERS);
    sem_init(&riding, 0, NUMBER_OF_CARS);
    sem_init(&waitingLineMutex, 0, 1);

    // Create car instances and rider instances
    std::vector<Car> cars;
    std::vector<Rider> riders;

    // Set cid from [1, NUMBER_OF_CARS]
    for (int i = 1; i <= NUMBER_OF_CARS; ++i) {
        cars.push_back(Car(i));
    }

    // Set rid from [1, NUMBER_OF_RIDERS]
    for (int i = 1; i <= NUMBER_OF_RIDERS; ++i) {
        riders.push_back(Rider(i));
    }

    // Run the simulation for a specified number of rides
    while (NUMBER_OF_RIDES > 0) {
        // Logic for the simulation:
        // 1. Allow cars to pick up riders when they're available.
        // 2. Riders get in line, take a seat, and enjoy the ride.
        // 3. Update ride counts and exit conditions.

        // Reduce NUMBER_OF_RIDES when a ride is completed
        // Check for your exit condition here

        // For example, you might implement a simple exit condition as follows:
        if (NUMBER_OF_RIDES == 0) {
            break; // All rides are completed
        }
    }

    // At this point, all rides are completed. Perform cleanup and join threads.

    // Set done flags for all riders to signal them to leave the park.
    for (Rider& rider : riders) {
        rider.leavePark();
    }

    // Join all rider threads to ensure they finish before exiting.
    for (Rider& rider : riders) {
        pthread_join(rider.getRiderThread(), NULL);
    }

    // Join car threads (optional if your Car class uses pthreads).
    for (Car& car : cars) {
        pthread_join(car.getCarThread(), NULL);
    }

    // Destroy semaphores and release resources.
    sem_destroy(&waitingForRide);
    sem_destroy(&riding);
    sem_destroy(&waitingLineMutex);

    return 0;
}
