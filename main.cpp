#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <semaphore.h>
#include "Car.hpp"
#include "Rider.hpp"

#define NUMBER_OF_CARS 2
#define NUMBER_OF_RIDERS 5

// Waiting line to hold the riders
std::queue<Rider> waitingRiders;

sem_t waitingForRide;   // Semaphore to track empty slots in the waiting line
sem_t riding;           // Semaphore to track occupied cars
sem_t mutex;

int main() {
    // Initialize semaphores and other necessary resources
    sem_init(&waitingForRide, 0, NUMBER_OF_RIDERS);
    sem_init(&riding, 0, NUMBER_OF_CARS);
    sem_init(&mutex, 0, 1);

    // Containers to hold riders and cars
    std::vector<Rider> riders;
    std::vector<Car> cars;

    // Containers to hold rider and car threads
    std::vector<pthread_t> riderThreads;
    std::vector<pthread_t> carThreads;

    // Load riderThreads
    for (int i = 0; i < NUMBER_OF_RIDERS; ++i) {
        pthread_t riderThread;
        riderThreads.push_back(riderThread);
    }

    // Load carThreads
    for (int i = 0; i < NUMBER_OF_CARS; ++i) {
        pthread_t carThread;
        carThreads.push_back(carThread);
    }

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
        pthread_create(&riderThreads[i], NULL, riders[i].enjoyPark, NULL);
    }

    // Create threads for all cars
    for (int i = 0; i < NUMBER_OF_CARS; ++i) {
        pthread_create(&carThreads[i], NULL, cars[i].ride, NULL);
    }

    // Join all rider threads to ensure they finish before exiting.
    for (auto& riderThread : riderThreads) {
        pthread_join(riderThread, NULL);
    }

    // Create threads for all cars
    for (auto& carThread : carThreads) {
        pthread_join(carThread, NULL);
    }

    // Destroy semaphores and release resources.
    sem_destroy(&waitingForRide);
    sem_destroy(&riding);
    sem_destroy(&mutex);

    return 0;
}
