#include "Checkincounter.h"
#include <vector>

using namespace std;

#ifndef ALLCHECKIN_COUNTERS
#define ALLCHECKIN_COUNTERS

class AllCheckinCounters{
public:
    vector <CheckinCounter> checkinCounters;
    
    AllCheckinCounters();
    void resetCheckinCounters();
};

AllCheckinCounters::AllCheckinCounters(){
    for(int i = 0; i < 15; i++){
        checkinCounters.push_back(CheckinCounter(i+1));
    }
}

void AllCheckinCounters::resetCheckinCounters(){
    for(int i = 0; i < checkinCounters.size(); i++){
        checkinCounters[i].setOccupied(false);
        checkinCounters[i].setOccupiedByPlane(-1);
    }
}

#endif