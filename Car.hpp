#ifndef CAR_HPP
#define CAR_HPP

#include <pthread.h>
#include "Rider.hpp"

class Car {
public:
    Car(int cid);
    pthread_t getCarThread() {
        return carThread;
    }

private:
    int cid;
    int currentRiderID = -1;
    pthread_t carThread;

    void Bump();
    void Load(Rider rider);
    void Unload();

    static void* ride(void* car);
};

#endif // CAR_HPP
