#include "Plane.h"
#include <vector>
#include <algorithm>

using namespace std;

#ifndef ALLPLANES_H
#define ALLPLANES_H

class AllPlanes{
public:

    vector <Plane> planes;

    // providing a constructor for 
    // creating flights and their default schedule
    AllPlanes(tm &t);
};

AllPlanes::AllPlanes(tm &t){
    vector <Plane> p;
    /*
    * let total num of gates be 14
    * and 6 to 10 flights
    * for the sake of assignment user will first create all the planes
    * and after chosing update airport option (to be provided), program will
    * assign all the airport resources to that data of planes
    */

    planes = p;
}

#endif