/*
    @file Car.hpp

    Interface file for Car class
*/

#ifndef CAR_HPP
#define CAR_HPP

class Car {
public:
    Car(int carID);
    static void* ride(void* car);

private:
    int cid = -1;
    int currentRiderID = -1;

    void Load(int riderID);
    void Bump();
    void Unload();
};

#endif // CAR_HPP
