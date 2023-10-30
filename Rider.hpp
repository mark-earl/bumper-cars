/*
    @file Rider.hpp

    Interface file for Rider class
*/

#ifndef RIDER_HPP
#define RIDER_HPP

class Rider {
public:
    Rider(int riderID);
    static void* enjoyPark(void* rider);

private:
    int rid = -1;
    int assignedCarID = -1;

    void leavePark();
    void Wander();
    void GetInLine();
    void TakeASeat();
    void TakeARide();
};

#endif // RIDER_HPP
