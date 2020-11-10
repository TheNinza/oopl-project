#include "Checkincounter.h"
#include "AllPlanes.h"
#include <vector>

using namespace std;

#ifndef ALLCHECKIN_COUNTERS
#define ALLCHECKIN_COUNTERS

class AllCheckinCounter{
public:
    vector <CheckinCounter> checkinCounters;
    
    AllCheckinCounter();
};

AllCheckinCounter::AllCheckinCounter(){
    for(int i = 0; i < 15; i++){
        checkinCounters.push_back(CheckinCounter(i+1));
    }
}

#endif