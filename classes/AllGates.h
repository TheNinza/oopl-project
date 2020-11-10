#include "Gate.h"
#include "AllPlanes.h"
#include <vector>

using namespace std;

#ifndef ALLGATES_H
#define ALLGATES_H

class AllGates{
public:
    vector <Gate> gates;
    
    AllGates();
};

AllGates::AllGates(){
    for(int i = 0; i < 15; i++){
        gates.push_back(Gate(i+1));
    }
}

#endif