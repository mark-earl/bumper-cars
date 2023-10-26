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
    Rider rider = NULL;
    pthread_t carThread;

    void Bump();
    void Load();
    void Unload();

    static void* ride(void* car);
};

#endif // CAR_HPP
