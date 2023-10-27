#ifndef RIDER_HPP
#define RIDER_HPP

class Rider {
public:
    Rider(int riderID);
    static void* enjoyPark(void* rider);
    void leavePark();

    bool isWandering() { return wandering; }
    bool isWaiting() { return waiting; }

private:
    int rid = -1;
    int assignedCarID = -1;

    void Wander();
    void GetInLine();
    void TakeASeat();
    void TakeARide();

    bool wandering = false;
    bool waiting = false;
};

#endif // RIDER_HPP
