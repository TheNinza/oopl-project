#include "Airportfacilities.h"

#ifndef GATE_H
#define GATE_H

class Gate : protected Airportfacilities{
private:
    bool isUnderMaintainance;
public:
    Gate(int id){
        setId(id);
    }
};


#endif