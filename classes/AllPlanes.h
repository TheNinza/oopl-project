#include "Plane.h"
#include "AllGates.h"
#include "AllCheckinCounters.h"
#include "AllBelts.h"
#include <vector>
#include <algorithm>

using namespace std;

#ifndef ALLPLANES_H
#define ALLPLANES_H

// custom funciton for sorting
bool sortByArrival(Plane & a, Plane &b) {
    return a.getScheduledArrival() < b.getScheduledArrival();
}

bool sortByDeparture(Plane & a, Plane &b) {
    return a.getScheduledDeparture() < b.getScheduledDeparture();
}

class AllPlanes{
public:

    vector <Plane> planes;

    // providing a constructor for 
    // creating flights and their default schedule
    AllPlanes(tm &t);

    void assignGates(tm &t, vector <Gate> &gates);
    void assignCounters(tm &t, vector <CheckinCounter> & counters);
    void assignBelts(tm &t, vector <Belt> & belts);
    
    // resetting planes
    void resetPlanes();

    // creating new plane
    void createPlane(Plane p);
};

AllPlanes::AllPlanes(tm &t){
    // vector <Plane> p;

    int planeIdCount = 1001;
    for(int i = 0; i < 24; i++){
        int numPlanes = 1 + rand() % 4;
        for(int j = 0; j < numPlanes; j++){
            int min = rand() % 60;
            int arrivalTime = (i * 100) + min;
            int delay = rand() % 5;
            int schArr = arrivalTime;
            if(delay == 0 || delay == 1){
                schArr += 5 + rand() % 84;
                if(schArr > 2400){
                    schArr -= 2400;
                }
                if(schArr % 100 > 60){
                    schArr -= 60;
                    schArr += 100;
                }
            }

            int depTime = arrivalTime + 500 + rand() % 1300;
            if(depTime > 2400){
                depTime -= 2400;
            }
            delay = rand() % 5;
            int schDep = depTime;
            if(delay == 0 || delay == 1){
                schDep += 5 + rand() % 84;
                if(schDep % 100 > 59){
                    schDep -= 60;
                    schDep += 100;
                }
                if(schDep > 2400){
                    schDep -= 2400;
                }
            }
            planes.push_back(Plane(planeIdCount++, arrivalTime, depTime, schArr, schDep, "location " + to_string(i*10 + j), "location " + to_string(i*10 + j)));
        }
    }
}

void AllPlanes::assignGates(tm & t, vector <Gate> & gates){
    sort(planes.begin(), planes.end(), sortByArrival);

    int currentTime = (t.tm_hour * 100) + t.tm_min;

    for(int i = 0; i < planes.size(); i++){

        
        // assign gates for arrivals
        int tempCurrentTime = currentTime - 300;
        if(tempCurrentTime < 0)
            tempCurrentTime += 2400;

        // already landed planes
        if(planes[i].getScheduledArrival() <= currentTime && planes[i].getScheduledArrival() > tempCurrentTime && planes[i].getGateId() == -1){
            
            int currPos = 0;
            int maxDist = 0;
            int x = 0, y = 0;
            while(x < gates.size() && y < gates.size()){
                if(gates[y].getOccupied() || y == gates.size() - 1){
                    if(maxDist < y-x){
                        currPos = x;
                        
                        maxDist =  y - x;
                    }
                    x = y;
                }
                y++;
            }
            planes[i].setGateId(gates[currPos + (maxDist / 2)].assignPlane(planes[i]));
            planes[i].setIsLanded(true);
            planes[i].setStatus("landed");
        }

        // planes to be landed

        tempCurrentTime = currentTime + 300;

        if(tempCurrentTime > 2400){
            tempCurrentTime -= 2400;
        }

        if(planes[i].getScheduledArrival() > currentTime && planes[i].getScheduledArrival() <= tempCurrentTime && planes[i].getGateId() == -1){
            
            int currPos = 0;
            int maxDist = 0;
            int x = 0, y = 0;
            while(x < gates.size() && y < gates.size()){
                if(gates[y].getOccupied() || y == gates.size() - 1){
                    if(maxDist < y-x ){
                        currPos = x;
                        
                        maxDist =  y - x;
                    }
                    x = y;
                }
                y++;
            }
            planes[i].setGateId(gates[currPos + (maxDist / 2)].assignPlane(planes[i]));
            planes[i].setIsLanded(false);
            planes[i].setStatus("gate assigned");
        }

        // planes to be departed


        if(planes[i].getScheduledDeparture() >= currentTime && planes[i].getScheduledDeparture() < tempCurrentTime && planes[i].getGateId() == -1){
            
            int currPos = 0;
            int maxDist = 0;
            int x = 0, y = 0;
            while(x < gates.size() && y < gates.size()){
                if(gates[y].getOccupied() || y == gates.size() - 1){
                    if(maxDist < y-x){
                        currPos = x;
                        
                        maxDist =  y - x;
                    }
                    x = y;
                }
                y++;
            }
            planes[i].setGateId(gates[currPos + (maxDist / 2)].assignPlane(planes[i]));
            planes[i].setIsLanded(true);
            planes[i].setStatus("counter open");
        }

    }
}

void AllPlanes::assignCounters(tm &t, vector <CheckinCounter> & counters){
    sort(planes.begin(), planes.end(), sortByDeparture);

    int currentTime = (t.tm_hour * 100) + t.tm_min;

    for(int i = 0; i < planes.size(); i++){
        int tempCurrentTime = currentTime + 300;

        if(tempCurrentTime > 2400){
            tempCurrentTime -= 2400;
        }
        if(planes[i].getScheduledDeparture() >= currentTime && planes[i].getScheduledDeparture() < tempCurrentTime && planes[i].getCounterId() == -1){
            for(int j = 0; j < counters.size(); j++){
                if(!counters[j].getOccupied()){
                    planes[i].setCounterId(counters[j].assignPlane(planes[i]));
                    break;
                }
            }
        }
    }

}

void AllPlanes::assignBelts(tm &t, vector <Belt> & belts){
    sort(planes.begin(), planes.end(), sortByArrival);

    int currentTime = (t.tm_hour * 100) + t.tm_min;

    for(int i = 0; i < planes.size(); i++){
        
        // for already arrived flights
        int tempCurrentTime = currentTime - 30;
        if(tempCurrentTime % 100 > 59){
            int timeOffset = 100 - (tempCurrentTime % 100);
            tempCurrentTime = (tempCurrentTime/100) * 100 + 60 - timeOffset;
        }

        if(planes[i].getScheduledArrival() <= currentTime && planes[i].getScheduledArrival() > tempCurrentTime && planes[i].getBeltId() == -1){
            for(int j = 0; j < belts.size(); j++){
                if(!belts[j].getOccupied()){
                    planes[i].setBeltId(belts[j].assignPlane(planes[i]));
                    break;
                }
            }
        }

        // for arriving flights belts can be assigned 15 min earlier
        tempCurrentTime = currentTime + 15;
        if(tempCurrentTime % 100 > 59){
            tempCurrentTime += 100;
            tempCurrentTime -= 60;
        }

        if(planes[i].getScheduledArrival() > currentTime && planes[i].getScheduledArrival() <= tempCurrentTime && planes[i].getBeltId() == -1){
            for(int j = 0; j < belts.size(); j++){
                if(!belts[j].getOccupied()){
                    planes[i].setBeltId(belts[j].assignPlane(planes[i]));
                    break;
                }
            }
        }

    }

}

void AllPlanes::resetPlanes(){
    for(int i = 0; i < planes.size(); i++){
        planes[i].setIsLanded(false);
        planes[i].setGateId(-1);
        planes[i].setCounterId(-1);
        planes[i].setBeltId(-1);
    }
}

void AllPlanes::createPlane(Plane p){
    planes.push_back(p);
}

#endif