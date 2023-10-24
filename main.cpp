// Libraries
#include <iostream>
#include <time.h>

// Constants
#define NUMBER_OF_CARS 2   // Number of bumper cars
#define NUMBER_OF_RIDERS 5 // Number of riders
#define TIME_WANDER 100    // Each wandering time is between 0 to TIME_WANDER
#define TIME_BUMP 40       // Each bumping time is between 0 to TIME_BUMP */
int NUMBER_OF_RIDES = 10;  // Total number of bumper car rides (control length of execution)

int main()
{
    // Use current time as seed for random generator
    srand(time(0));
    return 0;
}

// Rider thread. rid is a number between 1 to NUMBER_OF_RIDERS.
void Rider(int rid)
{
    while (true)
    {
        // wander around for a random amount of time
        Wander(rid, rand() % TIME_WANDER + 1); // + 1 because rand() ranges [0, N-1]
        GetInLine(rid);
        TakeASeat(rid);
        TakeARide(rid);
        // TODO: check for the condition to exit the while loop here
    }
}
void GetInLine(int rid)
{
    // TODO
    std::cout << "Rider " << rid << " gets in the waiting line.\n";
}
void TakeASeat(int rid)
{
    // TODO
    std::cout << "Rider " << rid << " takes a seat.\n";
}
void TakeARide(int rid)
{
    std::cout << "Rider " << rid << " is taking the ride.\n";
    // TODO
}
void Wander(int rid, int interval)
{
    std::cout << "Rider " << rid << " is wandering around the park.\n";
    // TODO
}

void Bump(int cid, int rand)
{
    // TODO
}

// Bumper car thread. cid is a number between 1 to NUMBER_OF_CARS.
void Car(int cid)
{
    while (true)
    {
        Load(cid);
        Bump(cid, rand() % TIME_BUMP + 1); // + 1 because rand() ranges [0, N-1]
        Unload(cid);
        // TODO decrease the NUMBER_OF_RIDES
        // TODO: check for the condition to exit the while loop
    }
}
void Load(int cid)
{
    // TODO this_guy = WaitArea[LineHead];
    // TODO SHARED VARIABLE LineHead++;
    std::cout << "Car " << cid << " takes the rider "; // TODO define: << this_guy << ".\n";
    // TODO
}

void Unload(int cid)
{
    // TODO
    std::cout << "This ride of Car " << cid << " is over.\n";
    // TODO
}

// Displaying thread
void Display(int dummy)
{
    while (NUMBER_OF_RIDES > 0)
    {
        std::cout << "The current situation in the park is:\n";
        for (int i = 0; i < NUMBER_OF_CARS; ++i)
            if (dummy) // TODO (Car[i] is running)
                std::cout << "Car i is running. The rider is ???";
            else
                std::cout << "Car i is not running.";

        for (int i = 0; i < NUMBER_OF_RIDERS; ++i)
            if (dummy) // TODO (Rider[i] is wandering)
                std::cout << "Rider i is wandering";
            else if (dummy) // TODO (Rider[i] is waiting in line)
                std::cout << "Rider i is waiting in line";
            else
                std::cout << "Rider i is in a car.";
    }
}
