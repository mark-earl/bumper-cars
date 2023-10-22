#include <iostream>
#include <time.h>

#define NUMBER_OF_CARS 2
#define NUMBER_OF_RIDERS 5
#define TIME_WANDER 100 /* each wandering time is between 0 to TIME_WANDER */
#define TIME_BUMP 40    /* each bumping time is between 0 to TIME_BUMP */
int COUNT_DOWN = 10;    /* Sim time: Total number of bumper car rides */

int main()
{
    // Use current time as seed for random generator
    srand(time(0));
    return 0;
}

int done()
{
    if (COUNT_DOWN == 0)
        return true;
    else
        return false;
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
        // TODO decrease the COUNT_DOWN
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
    while (!done())
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
