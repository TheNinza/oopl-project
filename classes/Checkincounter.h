#include "Airportfacilities.h"

#ifndef CHECKINCOUNTER_H
#define CHECKINCOUNTER_H

class CheckinCounter : public Airportfacilities{

public:
    CheckinCounter(int id){
        setId(id);
        setOccupied(false);
        setOccupiedByPlane(-1);
    }

};


#endif


