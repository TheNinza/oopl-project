#include "Belt.h"
#include "AllPlanes.h"
#include <vector>

using namespace std;

#ifndef ALLBELTS_H
#define ALLBELTS_H

class AllBelts{
public:
    vector <Belt> belts;
    
    AllBelts();
};

AllBelts::AllBelts(){
    for(int i = 0; i < 15; i++){
        belts.push_back(Belt(i+1));
    }
}

#endif