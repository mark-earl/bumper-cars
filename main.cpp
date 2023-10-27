#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <semaphore.h>
#include "Car.hpp"
#include "Rider.hpp"

#define NUMBER_OF_CARS 8
#define NUMBER_OF_RIDERS 8
int NUMBER_OF_RIDES = 8;

// Waiting line to hold the riders
std::queue<Rider> waitingRiders;
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
sem_t waitingForRide;      // Prevent riders from loading when there is no car
sem_t riding;              // Prevent riders from wandering when the ride is not over

void* display(void *);

int main() {

    std::cout << "The park is now OPEN.\n\n";

    // Initialize semaphores and other necessary resources
    sem_init(&outputMutex, 0, 1);
    sem_init(&numberOfRidesMutex, 0, 1);
    sem_init(&riderIDMutex, 0, 1);
    sem_init(&waitingForRideMutex, 0, 1);

    sem_init(&waitingForRide, 0, 0);
    sem_init(&riding, 0, 0);

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

    // This does a ton of output
    // pthread_t mainThread;
    // pthread_create(&mainThread, NULL, display, NULL);

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
    sem_destroy(&waitingForRide);
    sem_destroy(&riding);

    std::cout << "\nThe park is now CLOSED.\n";

    return 0;
}

void* display(void *) {

    while (true) {
        std::cout << "The current situation in the park is:\n";

        for (int i = 0; i < NUMBER_OF_CARS; ++i) {
            if (cars[i].isRunning())
                std::cout << "Car i is running. The rider is ???\n";
            else
                std::cout << "Car i is not running.\n";
        }

        for (int i = 0; i < NUMBER_OF_RIDERS; ++i) {
            if (riders[i].isWandering())
                std::cout << "Rider i is wandering.\n";
            else if (riders[i].isWaiting())
                std::cout << "Rider i is waiting in line.\n";
            else
                std::cout << "Rider i is in a car.\n";
        }
    }

    return NULL;
};
