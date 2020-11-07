#include <iostream>
using namespace std;

#ifndef PLANE_H
#define PLANE_H


class Plane {
private:
    // Data
    int id;
    int actualArrival;
    int actualDeparture;
    int scheduledArrival;
    int scheduledDeparture;
    bool isLanded;
    string status;
    
public:

    // Constructor
    Plane(int id, int arr, int dep, int sArr, int sDep);

    // Getter Functions
    int getId();
    int getActualArrival();
    int getActualDeparture();
    int getScheduledArrival();
    int getScheduledDeparture();
    bool getIsLanded();
    string getStatus();

    // Setter Functions
    void setId(int val);
    void setActualArrival(int val);
    void setActualDeparture(int val);
    void setScheduledArrival(int val);
    void setScheduledDeparture(int val);
    void setIsLanded(bool val);
    void setStatus(string s);

    // Friend Functions
    friend void showPlane(Plane &p);
};

// Definitions of member functions and constructors, in order

Plane::Plane(int id, int arr, int dep, int sArr, int sDep)
    : id(id), actualArrival(arr), actualDeparture(dep), scheduledArrival(sArr), scheduledDeparture(sDep), isLanded(false){}

int Plane::getId(){
    return id;
}

int Plane::getActualArrival(){
    return actualArrival;
}

int Plane::getActualDeparture(){
    return actualDeparture;
}

int Plane::getScheduledArrival(){
    return scheduledArrival;
}

int Plane::getScheduledDeparture(){
    return scheduledDeparture;
}

bool Plane::getIsLanded(){
    return isLanded;
}

string Plane::getStatus(){
    return status;
}

void Plane::setId(int val){
    id = val;
}

void Plane::setActualArrival(int val){
    actualArrival = val;
}

void Plane::setActualDeparture(int val){
    actualDeparture = val;
}

void Plane::setScheduledArrival(int val){
    scheduledArrival = val;
}

void Plane::setScheduledDeparture(int val){
    scheduledDeparture = val;
}

void Plane::setIsLanded(bool val){
    isLanded = val;
}

void Plane::setStatus(string s){
    status = s;
}

//setStatus definition

void showPlane(Plane &p){
    cout << "id: " << p.id << '\n'
        << "actualArrival: " <<  p.actualArrival << '\n'
        << "actualDeparture: " <<  p.actualDeparture << '\n'
        << "scheduledArrival: " <<  p.scheduledArrival << '\n'
        << "scheduledDeparture: " <<  p.scheduledDeparture << '\n'
        << "isLanded: " <<  p.isLanded << '\n';
}

#endif
