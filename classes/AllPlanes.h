#include "Plane.h"
#include "AllGates.h"
#include "AllGates.h"
#include <vector>
#include <algorithm>

using namespace std;

#ifndef ALLPLANES_H
#define ALLPLANES_H

// custom funciton for sorting
bool sortByArrival(Plane & a, Plane &b) {
    return a.getScheduledArrival() < b.getScheduledArrival();
}

class AllPlanes{
public:

    vector <Plane> planes;

    // providing a constructor for 
    // creating flights and their default schedule
    AllPlanes(tm &t);

    void assignGates(tm &t, vector <Gate> &gates);
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


        // int leftBoundry = planes[i].getScheduledArrival() - 300;
        // if(leftBoundry < 0){
        //     leftBoundry += 2400;
        // }

        // int rightBoundry = leftBoundry + 300;
        // if(rightBoundry > 2400)

        // if(currentTime >= leftBoundry && currentTime < rightBoundry && !planes[i].getIsLanded()){
        //     int gap = gates.size() / 2;
        //     for(int j = 0; j < gates.size(); j += gap){
        //         if(!gates[j].getOccupied()){
        //             planes[i].setGateId(gates[j].assignPlane(planes[i]));
        //             gates[j].setOccupied(true);
        //         }
        //     }
        //     gap /= 2;
        //     if(gap == 0) break;
        // }
    }
}

#endif