#include <thread>
#include <Rider.hpp>

class Car {

public:
    Car(int cid);

    void Bump(int randomBumpTime);
    void Load();
    void Unload();

private:
    int cid;
    Rider rider = NULL;
    std::thread carThread;
};
