#include "Airportfacilities.h"

#ifndef BELT_H
#define BELT_H

class Belt : public Airportfacilities{

public:
    Belt(int id){
        setId(id);
        setOccupied(false);
        setOccupiedByPlane(-1);
    }
};


#endif


