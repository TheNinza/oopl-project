#include "Belt.h"
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
    for(int i = 0; i < 10; i++){
        belts.push_back(Belt(i+1));
    }
}

#endif