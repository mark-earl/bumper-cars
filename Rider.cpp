#include "Rider.hpp"
#include "SharedData.hpp"
#include <iostream>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>


// Each wandering time is between 0 to TIME_WANDER
#define TIME_WANDER 20

Rider::Rider(int rid){
    this->rid = rid;
    pthread_create(&riderThread, NULL, enjoyPark, this);
}

void* Rider::enjoyPark(void* rider) {
    Rider* riderInstance = static_cast<Rider*>(rider);

    while (true) {
        riderInstance->Wander();    // Wander around for a random amount of time
        riderInstance->GetInLine(); // Get in line for the ride
        riderInstance->TakeASeat(); // Take a seat in a car
        riderInstance->TakeARide(); // Ride the ride

        // When it's time to go, leave the park
        if (riderInstance->done) {
            break;
        }
    }

    return NULL;
}

void Rider::leavePark() {
    done = true;
}

int Rider::getRID() {
    return rid;
}

void Rider::GetInLine() {
    sem_wait(&waitingForRide);
    std::cout << "Rider " << rid << " gets in the waiting line.\n";
}
void Rider::TakeASeat() {
    std::cout << "Rider " << rid << " takes a seat.\n";
}
void Rider::TakeARide() {
    std::cout << "Rider " << rid << " is taking the ride.\n";
    sem_wait(&riding);
}
void Rider::Wander() {
    std::cout << "Rider " << rid << " is wandering around the park.\n";
    sleep(rand() % TIME_WANDER + 1); // + 1 because rand() ranges [0, N-1]
}