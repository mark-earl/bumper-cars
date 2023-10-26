#ifndef RIDER_HPP
#define RIDER_HPP

#include <pthread.h>

class Rider {
public:
    Rider(int riderID);
    static void* enjoyPark(void* rider);
    void leavePark();

private:
    int getRID();
    void Wander();
    void GetInLine();
    void TakeASeat();
    void TakeARide();
    bool done = false;
    int rid;
    int assignedCar; // Add this attribute to track the assigned car

    // Allow Car access to private members of Rider
    friend class Car;
};


#endif // RIDER_HPP
