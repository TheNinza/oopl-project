#include "Airportfacilities.h"

#ifndef GATE_H
#define GATE_H

class Gate : public Airportfacilities{
private:
    bool isUnderMaintainance;
public:
    Gate(int id){
        setId(id);
        setOccupied(false);
        setOccupiedByPlane(-1);
        isUnderMaintainance = false;
    }

    bool getIsUnderMaintainance(){
        return isUnderMaintainance;
    }

    void setIsUnderMaintainance(bool value){
        isUnderMaintainance = value;
    }

};


#endif