#ifndef RIDER_HPP
#define RIDER_HPP

class Rider {
public:
    Rider(int riderID);
    static void* enjoyPark(void* rider);
    void leavePark();

private:
    int rid = -1;
    int assignedCarID = -1;
    bool done = false;

    void Wander();
    void GetInLine();
    void TakeASeat();
    void TakeARide();
};

#endif // RIDER_HPP
