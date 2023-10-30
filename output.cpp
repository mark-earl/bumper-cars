/*
    Implementation file for display function
*/

#include "output.hpp"
#include <iostream>

void display(std::string message, int rid) {

    // Set output color (for a max of 5 riders, just use default coloring beyond that)
    if (rid == 1) message = "\033[31m" + message + "\033[0m";
    else if (rid == 2) message = "\033[32m" + message + "\033[0m";
    else if (rid == 3) message = "\033[33m" + message + "\033[0m";
    else if (rid == 4) message = "\033[34m" + message + "\033[0m";
    else if (rid == 5) message = "\033[37m" + message + "\033[0m";

    std::cout << message;
}
