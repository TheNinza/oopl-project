#ifndef AIRPORTFACILITIES_H
#define AIRPORTFACILITIES_H

class Airportfacilities {
protected:
    // Data
    int id;
    bool occupied;
    int occupiedByPlane;
public:

    // Constructors
    Airportfacilities(int id);
    
    // SetterFunctions
    void setId(int fId);
    void setOccupied(bool a);
    void setOccupiedByPlane(int planeId);

    // GetterFunctions
    int getId();
    bool getOccupied();
    int getOccupiedByPlane();

    // Custom Functions
    void reAssign(Airportfacilities & b);

};

// Definitions of member functions and constructors in order

Airportfacilities::Airportfacilities(int id): id(id), occupied(false), occupiedByPlane(-1){}

void Airportfacilities::setId(int fId){
    id = fId;
}

void Airportfacilities::setOccupied(bool a){
    occupied = a;
}

void Airportfacilities::setOccupiedByPlane(int planeId){
    occupiedByPlane = planeId;
}

int Airportfacilities::getId(){
    return id;
}

bool Airportfacilities::getOccupied(){
    return occupied;
}

int Airportfacilities::getOccupiedByPlane(){
    return occupiedByPlane;
}

void Airportfacilities::reAssign(Airportfacilities & a){
    a.setOccupied(occupied);
    a.setOccupiedByPlane(occupiedByPlane);

    // resetting the datas
    this->setOccupied(false);
    this->setOccupiedByPlane(-1);
}

#endif