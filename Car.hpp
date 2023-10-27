#ifndef CAR_HPP
#define CAR_HPP

class Car {
public:
    Car(int carID);
    static void* ride(void* car);
    bool isRunning();

private:
    int cid = -1;
    int currentRiderID = -1;

    void Load(int riderID);
    void Bump();
    void Unload();

    bool running = false;
};

#endif // CAR_HPP
