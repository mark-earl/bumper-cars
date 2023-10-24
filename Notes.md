
Simulated bumper car ride using semaphores and threads in C++

Things to note:
* Each car holds one person
* People who want to ride a bumper car line up and wait for a free car.

* When a car is returned:
1) Previous rider gets out
2) New rider gets in the car from the head of the waiting line
3) That rider then rides around on the bumper ride floor, bumping into the other cars
4) After riding for a while, the rider returns the car to the area where new riders line up.
5) A new rider gets in and takes a ride in the bumper car.
6) The rider who just got out of a bumper car wanders around the amusement park.
7) After wandering for a while, the rider returns to the rider waiting area, and gets in line.
8) If there are more free cars that people wishing to ride, any free car can take the rider in the head of the waiting line.

## Threads:
* There are NUMBER_OF_RIDERS rider threads
* There are NUMBER_OF_CARS bumper car threads

## Identifying riders and cars:
* Riders are identified by rider IDs (rid) from 1 to NUMBER_OF_RIDERS
* Bumper cars are identified by car IDs (cid) from 1 to NUMBER_OF_CARS

## Simulating the ride:
* Each car takes a (different) random amount of time between 0 to TIME_BUMP seconds to bump around the floor
* Simulated with Bump()
* Runs each time a rider gets into a car (regenerated each time a car goes onto the bumper floor)

## Simulating wandering:
* After a ride, each rider wanders around the amusement park
* Random amount of time between 0 to TIME_WANDER seconds
* Then, they return to the waiting area to get in line for another ride.
* The wander time is a random number regenerated each time a rider leaves a car and goes into the amusement park.

## Criteria:
* Develop code for a multi-thread program simulating the rider and the car threads.
* Use semaphores for synchronization.
* Run the simulation for NUMBER_OF_RIDES number of total bumper car rides.
* Each of the NUMBER_OF_RIDERS is simulated with a rider thread, identified by the input parameter rid.
* Each bumper car is simulated with a car thread, identified by the input cid.
* Finally, there is another displaying thread which is active all the time printing out the current situation in the amusement park:
    * "Who is taking which car?"
    * "Who is wandering around the park?"
    * "Who is in the waiting line?"
    * etc.

## Implementation Guidelines:
* Implemented with a bounded buffer with the size at least NUMBER_OF_RIDERS

* Each rider who finishes wandering around the amusement park gets in line by depositing their rid into the buffer
    * They then wait on their slot in an array of semaphores: P(WaitForRideBegin[rid])

* When a bumper car is ready to pick up a rider, it fetches an rid from the head of the bounded buffer
    *  Executes V(WaitForRideBegin[rid]) (releases the rider from the waiting line so that they can take a seat)

*  After taking the seat
    * The rider executes P(WaitForRideOver[rid]) (blocking itself until the ride is over)
* When the bumper car's bumping time is over
    * The car thread executes V(WaitForRideOver[rid]) (so the rider can wander around the park again)

! Make sure you have eliminated all the race conditions by protecting the critical sections in other semaphores.
In order to solve this part, you need to develop the codes to simulate the behavior of the cars and the riders.
* Each rider thread contains an instance of the rider function Rider(int rid), each with an unique rid.
* Each car thread contains an instance of the car function Car(int cid), each with an unique cid.
* Each time a rider wants to get in line, it calls the GetInLine(rid) function.
    * When it returns, the rider's rid has been placed into the bounded buffer.
    * The rider then calls the TakeASeat(rid) to block itself in the corresponding slot of WaitForRideBegin[] semaphore to wait for a car to pick it up.
    * After the rider gets in the car, it calls TakeARide(rid) to wait for the ride over.
    * When the car is ready to load a rider, it calls the function Load(cid) to load the rider in the head of the waiting line.
    * When the ride is over, the car calls the function Unload(cid) to free the rider.

Note that the pseudo code given is not completely correct. It seems that occasionally a rider in the
head of the waiting line is taken at the same time by two or more cars, which is impossible in the real
world. Nonetheless, use this as a starting point for writing your simulation of the problem.
