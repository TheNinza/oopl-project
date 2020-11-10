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

    // /*
    // * let total num of gates be 14
    // * and 6 to 10 flights
    // * for the sake of assignment user will first create all the planes
    // * and after chosing update airport option (to be provided), program will
    // * assign all the airport resources to that data of planes
    // */
    
    // // There must be atleast 5 to 8 planes for past 30 min which has already been arrived;
    // int numAlreadyLanded = 5 + rand() % 6;
    // for(int i = 0; i < numAlreadyLanded; i++){
    //     int landingTimeOfset = rand() % 30;
    //     int tempArrivalMin = t.tm_min - landingTimeOfset;
    //     int tempArrivalHr = t.tm_hour;

    //     if(tempArrivalMin < 0){
    //         tempArrivalMin = 60 - tempArrivalMin;
    //         tempArrivalHr -= 1;
    //     }
    //     tempArrivalHr = tempArrivalHr < 0 ? (24 - tempArrivalHr) : tempArrivalHr;
    //     int arrival = (tempArrivalHr * 100) + tempArrivalMin;

    //     int departure = arrival + ((5 + rand() % 8) * 100);
    //     departure = departure > 2400 ? (departure - 2400) : departure;

    //     int delay = rand() % 2;
    // }
    for(int i = 0; i < 10; i++){
        int numPlanes = 5 + rand() % 8;
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
    for(int i = 0; i < planes.size(); i++){
        if(t.tm_hour * 100>= planes[i].getScheduledArrival() - 300 && t.tm_hour < planes[i].getScheduledDeparture() && !planes[i].getIsLanded()){
            int gap = gates.size() / 2;
            for(int j = 0; j < gates.size(); j += gap){
                if(!gates[j].getOccupied())
                    planes[i].setGateId(gates[j].assignPlane(planes[i]));
                if(t.tm_hour * 100 >= planes[i].getScheduledArrival())
                    planes[i].setIsLanded(true);
            }
            gap /= 2;
            if(gap == 0) break;
        }
    }
}

#endif