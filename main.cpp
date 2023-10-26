#include <iostream>
#include <thread>
#include <vector>
#include <map>
#include <semaphore.h>
#include "Car.hpp"
#include "Rider.hpp"

#define NUMBER_OF_CARS 2
#define NUMBER_OF_RIDERS 5
int NUMBER_OF_RIDES = 10;

// Waiting line to hold the riders
std::vector<Rider> waitingRiders(NUMBER_OF_RIDERS);

sem_t waitingForRide;   // Semaphore to track empty slots in the waiting line
sem_t riding;           // Semaphore to track occupied cars
sem_t waitingLineMutex; // Mutex to protect buffer access to the waiting line

int main() {
    // Initialize semaphores and other necessary resources
    sem_init(&waitingForRide, 0, NUMBER_OF_RIDERS);
    sem_init(&riding, 0, NUMBER_OF_CARS);
    sem_init(&waitingLineMutex, 0, 1);

    // Containers to hold riders and cars
    std::vector<std::map<Rider, pthread_t>> riders;
    std::vector<std::map<Car, pthread_t>> cars;

    // Set rid from [1, NUMBER_OF_RIDERS]
    for (int i = 1; i <= NUMBER_OF_RIDERS; ++i) {
        riders.push_back(Rider(i));
    }

    // Set cid from [1, NUMBER_OF_CARS]
    for (int i = 1; i <= NUMBER_OF_CARS; ++i) {
        cars.push_back(Car(i));
    }

    // Create rider threads
    for (Car& car: cars) {
        pthread_create(car.getCarThread(), )
    }

    // Create car threads
    for (Car& car: cars) {
        // TODO
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
