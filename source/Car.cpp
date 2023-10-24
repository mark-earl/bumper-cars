#include <Car.hpp>
#include <iostream>

Car::Car(int cid) {
    this->cid = cid;
}

void Car::Bump(int rand) {
    // TODO
}

void Car::Load() {
    rider = WaitArea[LineHead];
    // TODO SHARED VARIABLE LineHead++;
    V(WaitForRideBegin[rider.getRID()]);
    std::cout << "Car " << cid << " takes rider: " << rider.getRID() << ".\n";
}

void Car::Unload() {
    V(WaitForRideOver[rider.getRID()]);
    std::cout << "This ride of Car " << cid << " is over.\n";
}
