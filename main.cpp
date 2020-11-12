// Importing libraries
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <ctime>

// Importing Classes
#include "classes/AllPlanes.h"
#include "classes/AllGates.h"
#include "classes/AllCheckinCounters.h"
#include "classes/AllBelts.h"

///////// Global variables /////////

    // Getting current time of the system
    time_t t = time(0);
    tm * currTime = localtime(&t);

    AllPlanes allPlanes(*currTime);
    AllGates allGates;
    AllCheckinCounters allCheckinCounters;
    AllBelts allBelts;


////////////////////////////////////

///////// Utility Functions /////////

void reAssignResources(){
    allPlanes.resetPlanes();
    allGates.resetGates();
    allCheckinCounters.resetCheckinCounters();
    allBelts.resetBelts();
    allPlanes.assignGates(*currTime, allGates.gates);
    allPlanes.assignCounters(*currTime, allCheckinCounters.checkinCounters);
    allPlanes.assignBelts(*currTime, allBelts.belts);
}

/////////////////////////////////////

//////////// Screens ////////////////
void updateFlightScreen(){
link1:
    system("clear");
    cout << "\n\n" << endl;
    int id;
    cout << "\t\t\tEnter an id for the plane: ";
    cin >> id;
    for(int i = 0; i < allPlanes.planes.size(); i++){
        if(allPlanes.planes[i].getId() == id){
            cout << "\n\n\tFlight details for flight: " << allPlanes.planes[i].getId() << endl;
            cout << "Actual arrival: " << allPlanes.planes[i].getActualArrival() << endl;
            cout << "Scheduled arrival: " << allPlanes.planes[i].getScheduledArrival() << endl;
            cout << "Actual departure: " << allPlanes.planes[i].getActualDeparture() << endl;
            cout << "Scheduled departure: " << allPlanes.planes[i].getScheduledDeparture() << endl;
            cout << "Coming From: " << allPlanes.planes[i].getFrom() << endl;
            cout << "Going To" << allPlanes.planes[i].getTo() << endl;
            cout << "Gate: " << (allPlanes.planes[i].getGateId() == -1 ?  "Not Assigned" : to_string(allPlanes.planes[i].getGateId()))<< endl;
            cout << "Belt: " << (allPlanes.planes[i].getBeltId() == -1 ?  "Not Assigned" : to_string(allPlanes.planes[i].getBeltId()))<< endl;
            cout << "CheckinCounter: " << (allPlanes.planes[i].getCounterId() == -1 ?  "Not Assigned" : to_string(allPlanes.planes[i].getCounterId()))<< endl << endl;
            
            int option = -1;
            cout << "\n\t\tDo yo want to update actual arrival (1-yes/ 0-no): ";
            cin >> option;
            if(option == 1){
                int arr;
                cout << "\t\tEnter value: ";
                cin >> arr;
                allPlanes.planes[i].setActualArrival(arr);
                reAssignResources();
            }
            cout << "\n\t\tDo yo want to update scheduled arrival (1-yes/ 0-no): ";
            cin >> option;
            if(option == 1){
                int arr;
            linkA:
                cout << "\t\tEnter value: ";
                cin >> arr;
                // there must be atleast 5 hrs of gap between arrival and departure
                if(abs(arr - allPlanes.planes[i].getScheduledDeparture()) < 500){
                    cout << "There must be atleast 5 hours gap between schArr and schDep" << endl;
                    goto linkA;
                }
                allPlanes.planes[i].setScheduledArrival(arr);
                reAssignResources();
            }
            cout << "\n\t\tDo yo want to update actual departure (1-yes/ 0-no): ";
            cin >> option;
            if(option == 1){
                int dep;
                cout << "\t\tEnter value: ";
                cin >> dep;
                allPlanes.planes[i].setActualDeparture(dep);
                reAssignResources();
            }
            cout << "\n\t\tDo yo want to update scheduled departure (1-yes/ 0-no): ";
            cin >> option;
            if(option == 1){
                int dep;
            linkB:
                cout << "\t\tEnter value: ";
                cin >> dep;
                // there must be atleast 5 hrs of gap between arrival and departure
                if(abs(dep - allPlanes.planes[i].getScheduledArrival()) < 500){
                    cout << "There must be atleast 5 hours gap between schArr and schDep" << endl;
                    goto linkB;
                }
                allPlanes.planes[i].setScheduledDeparture(dep);
                reAssignResources();
            }
            cout << "\n\t\tDo yo want to update the TO location (1-yes/ 0-no): ";
            cin >> option;
            if(option == 1){
                string value;
                cout << "\t\tEnter value: ";
                cin >> value;
                allPlanes.planes[i].setTo(value);
            }
            cout << "\n\t\tDo yo want to update the FROM location (1-yes/ 0-no): ";
            cin >> option;
            if(option == 1){
                string value;
                cout << "\t\tEnter value: ";
                cin >> value;
                allPlanes.planes[i].setFrom(value);
            }
            if(allPlanes.planes[i].getGateId() != -1){
                cout << "\n\t\tDo you want to change gate (1-yes/ 0-no): ";
                cin >> option;
                if(option == 1){
                    for(int j = 0; j < allGates.gates.size(); j++){
                        if(allGates.gates[j].getOccupiedByPlane() == allPlanes.planes[i].getId()){
                            allGates.gates[j].setIsUnderMaintainance(false);
                            allGates.gates[j].setOccupied(false);
                            allGates.gates[j].setOccupiedByPlane(-1);
                            break;
                        }
                    }
                    int value;
                    linkC:
                    cout << "\t\tEnter value: ";
                    cin >> value;

                    for(int j = 0; j < allGates.gates.size(); j++){
                        if(allGates.gates[j].getId() == value){
                            if(allGates.gates[j].getOccupied() == true){
                                cout << "Gate is already occupied" << endl;
                                goto linkC;
                                break;
                            }
                            else{
                                allPlanes.planes[i].setGateId(allGates.gates[j].assignPlane(allPlanes.planes[i]));
                                break;
                            }
                        }
                        if(j == allGates.gates.size() - 1 && allGates.gates[j].getId() != value){
                            cout << "Gate doesn't exists" << endl;
                                goto linkC;
                        }
                        
                    }
                    
                }
            }
            if(allPlanes.planes[i].getCounterId() != -1){
                cout << "\n\t\tDo you want to change checkin counter (1-yes/ 0-no): ";
                cin >> option;
                if(option == 1){
                    for(int j = 0; j < allCheckinCounters.checkinCounters.size(); j++){
                        if(allCheckinCounters.checkinCounters[j].getOccupiedByPlane() == allPlanes.planes[i].getId()){
                            allCheckinCounters.checkinCounters[j].setOccupied(false);
                            allCheckinCounters.checkinCounters[j].setOccupiedByPlane(-1);
                            break;
                        }
                    }
                    int value;
                    linkD:
                    cout << "\t\tEnter value: ";
                    cin >> value;

                    for(int j = 0; j < allCheckinCounters.checkinCounters.size(); j++){
                        if(allCheckinCounters.checkinCounters[j].getId() == value){
                            if(allCheckinCounters.checkinCounters[j].getOccupied() == true){
                                cout << "CheckinCounter is already occupied" << endl;
                                goto linkD;
                                break;
                            }
                            else{
                                allPlanes.planes[i].setCounterId(allCheckinCounters.checkinCounters[j].assignPlane(allPlanes.planes[i]));
                                break;
                            }
                        }
                        if(j == allCheckinCounters.checkinCounters.size() - 1 && allCheckinCounters.checkinCounters[j].getId() != value){
                            cout << "CheckinCounter doesn't exists" << endl;
                                goto linkD;
                        }
                        
                    }
                    
                }
            }
            if(allPlanes.planes[i].getBeltId() != -1){
                cout << "\n\t\tDo you want to change luggage belt (1-yes/ 0-no): ";
                cin >> option;
                if(option == 1){
                    for(int j = 0; j < allBelts.belts.size(); j++){
                        if(allBelts.belts[j].getOccupiedByPlane() == allPlanes.planes[i].getId()){
                            allBelts.belts[j].setOccupied(false);
                            allBelts.belts[j].setOccupiedByPlane(-1);
                            break;
                        }
                    }
                    int value;
                    linkE:
                    cout << "\t\tEnter value: ";
                    cin >> value;

                    for(int j = 0; j < allBelts.belts.size(); j++){
                        if(allBelts.belts[j].getId() == value){
                            if(allBelts.belts[j].getOccupied() == true){
                                cout << "Belt is already occupied" << endl;
                                goto linkE;
                                break;
                            }
                            else{
                                allPlanes.planes[i].setCounterId(allBelts.belts[j].assignPlane(allPlanes.planes[i]));
                                break;
                            }
                        }
                        if(j == allBelts.belts.size() - 1 && allBelts.belts[j].getId() != value){
                            cout << "Belt doesn't exists" << endl;
                                goto linkE;
                        }
                        
                    }
                    
                }
            }
            cout << "updated" << endl;
             cout << "\n\n\tFlight details for flight: " << allPlanes.planes[i].getId() << endl;
            cout << "Actual arrival: " << allPlanes.planes[i].getActualArrival() << endl;
            cout << "Scheduled arrival: " << allPlanes.planes[i].getScheduledArrival() << endl;
            cout << "Actual departure: " << allPlanes.planes[i].getActualDeparture() << endl;
            cout << "Scheduled departure: " << allPlanes.planes[i].getScheduledDeparture() << endl;
            cout << "Coming From: " << allPlanes.planes[i].getFrom() << endl;
            cout << "Going To" << allPlanes.planes[i].getTo() << endl;
            cout << "Gate: " << (allPlanes.planes[i].getGateId() == -1 ?  "Not Assigned" : to_string(allPlanes.planes[i].getGateId()))<< endl;
            cout << "Belt: " << (allPlanes.planes[i].getBeltId() == -1 ?  "Not Assigned" : to_string(allPlanes.planes[i].getBeltId()))<< endl;
            cout << "Belt: " << (allPlanes.planes[i].getCounterId() == -1 ?  "Not Assigned" : to_string(allPlanes.planes[i].getCounterId()))<< endl << endl;
            cout << "Press Enter to continue ";
            getchar();
            getchar();
            return;
        }
    }
    cout << "\n\n\t\t\tNo plane with this id was found" << endl;
    sleep(1);
    goto link1;
}

void createFlightScreen(){
    system("clear");
    cout << "\n\n" << endl;
    int id, arrTime, depTime;
    string from, to;
    cout << "\t\t\tEnter an id for the plane: ";
    cin >> id;
    cout << "\n\t\t\tEnter arrival time: ";
    cin >> arrTime;
    cout << "\n\t\t\tEnter departure time: ";
    cin >> depTime;
    cout << "\n\t\t\tEnter Arriving from: ";
    cin >> from;
    cout << "\n\t\t\tEnter Departing to: ";
    cin >> to;
    allPlanes.createPlane(Plane(id, arrTime, depTime, arrTime, depTime, from, to));
    cout << "Plane Created" << endl;
    sleep(2);
    reAssignResources();
}

void createAirPortFacilities(string s){
    system("clear");
    cout << "\n\n" << endl;
    int id, arrTime, depTime;
    string from, to;
    cout << "\t\t\tEnter an id for the belt: ";
    cin >> id;
    if(s == "gate"){
        allGates.createGate(Gate(id));
    }
    if(s == "belt"){
        allBelts.createBelt(Belt(id));
    }
    if(s == "checkinCounter"){
        allCheckinCounters.createCheckinCounter(CheckinCounter(id));
    }
    cout << "Created" << endl;
    sleep(2);
    reAssignResources();
}

void loadingScreen(){
    system("clear");
    short int dot = 3;
    while(dot--){
        cout << "\n\n\n\t\t\t\tLoading" << string(3 - dot, '.') << endl;
        sleep(1);
        system("clear");
    }
    getchar();
}


int crudShowScreen(string s){
    system("clear");
    cout << "\n\n" << endl;
    cout << "\t\t\tWhich data you want to "<< s <<" ?" << endl;
    cout << "\n\n\t  1. Flight Data\t\t2.Checkin Counter Data" << endl;
    cout << "\n\n\t  3. Flight Gate Data    \t\t" << endl;
    cout << "\n\n\n\t  9. Back to CRUD menu \t\t 0. Exit program" << endl;
    link1:
    cout << "\n\n\tEnter your choice: ";
    int choice = -1;
    cin >> choice;
    if(choice == 0){
        exit(0);
    }
    if( choice == 1 || choice == 2 || choice == 3 || choice == 9){
        return choice;
    }
    goto link1;
    return choice;
}


void crudScreen(){
    system("clear");
    cout << "\n\n" << endl;
    cout << "\t\t\tChoose from following operations:" << endl;
    cout << "\n\n\t  1. Show Airport Data\t\t2.Update Airport Data" << endl;
    cout << "\n\n\t  3. Create New Data  \t\t4.Delete Airport Data" << endl;
    cout << "\n\n\n\t  0. Exit program" << endl;
    
    link1:
    cout << "\n\n\tEnter your choice: ";
    int choice, x = -1;
    cin >> choice;
    switch (choice)
    {
    case 1:
        // Airport Data Screen
        x = crudShowScreen("show");
        switch (x)
        {
        case 1:
            // show flight schedule screen
            break;
        case 2:
            // show checkin counter screen
        case 3:
            // show flight gate screen
        case 9:
            crudScreen();
            break;
        default:
            break;
        }
        break;
    case 2:
        // Update Data Screen
        x = crudShowScreen("update");
        switch (x)
        {
        case 1:
            // update flight schedule screen
            updateFlightScreen();
            break;
        case 2:
            // update checkin counter screen
        case 3:
            // update flight gate screen
        case 9:
            crudScreen();
            break;
        default:
            break;
        }
        crudScreen();
        break;
    case 3:
        // Create Data Screen
        x = crudShowScreen("create");
        switch (x)
        {
        case 1:
            // create flight schedule screen
            createFlightScreen();
            break;
        case 2:
            // create checkin counter screen
            createAirPortFacilities("checkinCounter");
            break;
        case 3:
            // create flight gate screen
            createAirPortFacilities("checkinCounter");
            break;
        case 9:
            crudScreen();
            break;
        default:
            break;
        }
        crudScreen();
        break;
    case 4:
        // Delete Airport Data
        x = crudShowScreen("delete");
        switch (x)
        {
        case 1:
            // delete flight schedule screen
            break;
        case 2:
            // delete checkin counter screen
        case 3:
            // delete flight gate screen
        case 9:
            crudScreen();
            break;
        default:
            break;
        }
        break;
    case 0:
        exit(0);
        break;
    default:
        cout << "\n\tWrong Option";
        goto link1;
    }
}

void modeSelectionScreen(){
    system("clear");
    cout << "\t\tChose your mode of operaion" << endl;
    cout << "\n\n\t1. Automatic\n\t(this will choose current time and as the time of operaion)" << endl;
    cout << "\n\t2. Manual\n\t(this will choose your desired time and as the time of operaion)" << endl;
     cout << "\n\n\tEnter your choice: ";
    int choice;
    cin >> choice;
    if(choice == 2){
        system("clear");
        cout << "Enter the time of the day to operate in 24 hr format (eg: 1454 for 14:54)" << endl;
        cout << "\tTime: ";
        int tempTime;
        cin >> tempTime;
        currTime->tm_hour = tempTime / 100;
        currTime->tm_min = tempTime % 100;
    }
    cout << "\nTime: " << currTime->tm_hour << ":" << currTime->tm_min << endl;
    sleep(2);
}

void initiateApp(){
    system("clear");
    cout << "\n\n\t\t\tWelcome to the\n\t\tAutomatic Airport Management System" << endl;
    cout<< "\n\n\nPress ENTER to continue" << endl;
    getchar();
    modeSelectionScreen();
    loadingScreen();
    

    allPlanes.assignGates(*currTime, allGates.gates);
    allPlanes.assignCounters(*currTime, allCheckinCounters.checkinCounters);
    allPlanes.assignBelts(*currTime, allBelts.belts);
    // for(int i = 0; i < allBelts.belts.size(); i++){
    //     cout << allBelts.belts[i].getOccupiedByPlane() << endl;
    // }

    crudScreen();
}

int main() {
    
    initiateApp();
}
