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
    // for(auto pl: planes){
    //     showPlane(pl);
    //     cout << endl; 
    // }
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
        if(planes[i].getScheduledArrival() <= currentTime && planes[i].getScheduledArrival() > tempCurrentTime){
            // find a gate;
            int gap = gates.size() / 2;
            while(planes[i].getGateId() == -1 && gap > 0){

                for(int j = 0; j < gates.size(); j += gap){
                    if(!gates[j].getOccupied()){
                        planes[i].setGateId(gates[j].assignPlane(planes[i]));
                        planes[i].setIsLanded(true);
                        planes[i].setStatus("landed");
                        break;
                    }
                }

                gap /= 2;
            }
        }

        // planes to be landed

        tempCurrentTime = currentTime + 300;

        if(tempCurrentTime > 2400){
            tempCurrentTime -= 2400;
        }

        if(planes[i].getScheduledArrival() > currentTime && planes[i].getScheduledArrival() <= tempCurrentTime){
            int gap = gates.size() / 2;
            while(planes[i].getGateId() == -1 && gap > 0){

                for(int j = 0; j < gates.size(); j += gap){
                    if(!gates[j].getOccupied()){
                        planes[i].setGateId(gates[j].assignPlane(planes[i]));
                        planes[i].setIsLanded(false);
                        planes[i].setStatus("gate assigned");
                        break;
                    }
                }

                gap /= 2;
            }
        }

        // planes to be departed


        if(planes[i].getScheduledDeparture() >= currentTime && planes[i].getScheduledDeparture() < tempCurrentTime){
            int gap = gates.size() / 2;
            while(planes[i].getGateId() == -1 && gap > 0){

                for(int j = 0; j < gates.size(); j += gap){
                    if(!gates[j].getOccupied()){
                        planes[i].setGateId(gates[j].assignPlane(planes[i]));
                        planes[i].setIsLanded(true);
                        planes[i].setStatus("counter open");
                        break;
                    }
                }

                gap /= 2;
            }
        }

        // for planes already departed
        // remove there gateId and set gate to maintainance if it's been less than 30 min since departure

        // tempCurrentTime = currentTime - 30;
        // if(tempCurrentTime % 100 > 59){
        //     int timeDeductionOffset = 100 - (tempCurrentTime % 100);
        //     tempCurrentTime = (tempCurrentTime / 100) * 100 + (60 - timeDeductionOffset);
        // }

        // if(tempCurrentTime < 0){
        //     tempCurrentTime += 2400;
        // }

        // if(planes[i].getScheduledDeparture() < currentTime){
        //     if(planes[i].getGateId() != -1){
        //         for(int j = 0; j < gates.size(); j++){
        //             if(gates[j].getId() == planes[i].getGateId()){
        //                 gates[j].setId(-1);
        //                 planes[i].setGateId(-1);

        //                 if(planes[i].getScheduledDeparture() >= tempCurrentTime){
        //                     gates[j].setIsUnderMaintainance(true);
        //                 }
        //                 else{
        //                     gates[j].setIsUnderMaintainance(false);
        //                 }
        //             }
        //         }
        //     }
            
        // }
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
        // removing counters for already departed flights
        // else {
        //     if(planes[i].getCounterId() != 1){
        //         for(int j = 0; j < counters.size(); j++){
        //             if(counters[j].getOccupiedByPlane() == planes[i].getId()){
        //                 counters[j].setOccupiedByPlane(-1);
        //                 counters[j].setOccupied(false);
        //                 break;
        //             }
        //         }
        //         planes[i].setCounterId(-1);
        //     }
        // }
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
        // Removing belts for all other planes who didn't fall in the above time intervals
        // else {
        //     if(planes[i].getBeltId() != 1){
        //         for(int j = 0; j < belts.size(); j++){
        //             if(belts[j].getOccupiedByPlane() == planes[i].getId()){
        //                 belts[j].setOccupiedByPlane(-1);
        //                 belts[j].setOccupied(false);
        //                 break;
        //             }
        //         }
        //         planes[i].setBeltId(-1);
        //     }
        // }

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

#endif