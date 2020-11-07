// Importing libraries
#include <iostream>


// Importing Classes
#include "classes/Plane.h"
#include "classes/Airportfacilities.h"
#include "classes/Belt.h"

// Functions


int main() {
    // Getting current time of the system
    time_t t = time(0);
    tm * currTime = localtime(&t);
    cout << "CurrentTime is: " << currTime->tm_hour << ":" << currTime->tm_min << endl;

}
