#include <thread>

class Rider {

public:
    Rider(int rid);
    void enjoyPark();
    void leavePark();

    int getRID();

private:

    void GetInLine();
    void TakeASeat();
    void TakeARide();
    void Wander();

    bool done = false;
    int rid;
    std::thread riderThread;
};
