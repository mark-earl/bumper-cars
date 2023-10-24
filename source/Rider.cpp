#include <Rider.hpp>
#include <semaphore>
#include <chrono>
#include <iostream>
#include <thread>

// Each wandering time is between 0 to TIME_WANDER
#define TIME_WANDER 20

Rider::Rider(int rid){
    this->rid = rid;
}

void Rider::enjoyPark() {
    while (true) {

        Wander();    // Wander around for a random amount of time
        GetInLine(); // Get in line for the ride
        TakeASeat(); // Take a set in a car
        TakeARide(); // Ride the ride

        // When its time to go, leave the park
        if(done) { break; }
    }
}

void Rider::leavePark() {
    done = true;
}

int Rider::getRID() {
    return rid;
}

void Rider::GetInLine() {
    P(WaitForRideBegin[rid]);
    std::cout << "Rider " << rid << " gets in the waiting line.\n";
}
void Rider::TakeASeat() {
    std::cout << "Rider " << rid << " takes a seat.\n";
}
void Rider::TakeARide() {
    P(WaitForRideOver[rid]);
    std::cout << "Rider " << rid << " is taking the ride.\n";
}
void Rider::Wander() {
    std::cout << "Rider " << rid << " is wandering around the park.\n";
    int wanderTime = rand() % TIME_WANDER + 1; // + 1 because rand() ranges [0, N-1]
    std::this_thread::sleep_for(std::chrono::seconds(wanderTime));
}
