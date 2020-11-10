// Importing libraries
#include <unistd.h>

// Importing Classes
#include "classes/AllPlanes.h"
#include "classes/AllGates.h"
#include "classes/AllCheckinCounters.h"
#include "classes/AllBelts.h"

///////// Global variables /////////

    // Getting current time of the system
    time_t t = time(0);
    tm * currTime = localtime(&t);

    AllPlanes planes(*currTime);
    AllGates gates;
    AllCheckinCounter counters;
////////////////////////////////////

///////// Utility Functions /////////
    //   No utility functions yet
/////////////////////////////////////

//////////// Screens ////////////////
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
        break;
    case 3:
        // Create Data Screen
        x = crudShowScreen("create");
        switch (x)
        {
        case 1:
            // create flight schedule screen
            break;
        case 2:
            // create checkin counter screen
        case 3:
            // create flight gate screen
        case 9:
            crudScreen();
            break;
        default:
            break;
        }
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
    crudScreen();
}

int main() {
    initiateApp();
}
