#include "Gate.h"
#include <vector>

using namespace std;

#ifndef ALLGATES_H
#define ALLGATES_H

class AllGates{
public:
    vector <Gate> gates;
    
    AllGates();
    void resetGates();
    void createGate(Gate g);
};

AllGates::AllGates(){
    for(int i = 0; i < 50; i++){
        gates.push_back(Gate(i+1));
    }
}

void AllGates::resetGates(){
    for(int i = 0; i < gates.size(); i++){
        gates[i].setIsUnderMaintainance(false);
        gates[i].setOccupied(false);
        gates[i].setOccupiedByPlane(-1);
    }
}

void AllGates::createGate(Gate g){
    gates.push_back(g);
}

#endif