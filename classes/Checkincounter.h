#include "Airportfacilities.h"

#ifndef CHECKINCOUNTER_H
#define CHECKINCOUNTER_H

class CheckinCounter : protected Airportfacilities{

public:
    CheckinCounter(int id){
        setId(id);
    }

};


#endif


