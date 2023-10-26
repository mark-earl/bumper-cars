#ifndef RIDER_HPP
#define RIDER_HPP

#include <pthread.h>

class Rider {
public:
    Rider(int riderID);
    void leavePark();
    pthread_t getRiderThread() {
        return riderThread;
    }

private:
    int getRID();
    void Wander();
    void GetInLine();
    void TakeASeat();
    void TakeARide();
    bool done = false;
    int rid;
    int assignedCar; // Add this attribute to track the assigned car
    pthread_t riderThread;

    // Thread entry point
    static void* enjoyPark(void* rider);

    // Allow Car access to private members of Rider
    friend class Car;
};


#endif // RIDER_HPP
