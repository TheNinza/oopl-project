#include "Airportfacilities.h"

#ifndef BELT_H
#define BELT_H

class Belt : protected Airportfacilities{

public:
    Belt(int id){
        setId(id);
    }
};


#endif


