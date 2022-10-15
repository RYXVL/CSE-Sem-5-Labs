//Source code for OS Mini Project - Disk Scheduling Policies

#include<iostream>
#include<vector>

using namespace std;

int hardCodeRequestQueue[10] = { 90, 120, 30, 40, 115, 130, 110, 80, 190, 25 };

class DiskSchedulingPolicy{

    public:

    //hardcoded values should user choose not to manually enter them
    int *requestQueue;
    int globalCurrentHead;
    int queueLength;
    int *orderOfProcessing;
    int totalHeadMovement;

    //Method declarations
    void defInit();
    void manInit();
    void startDemo();
    void printAverageSeekTime(int totalHeadMovement, int totalLength);
    void FCFS();
    void SSTF();
    void SCAN();
    void CSCAN();
    void LOOK();
    void CLOOK();

};

void DiskSchedulingPolicy::defInit(){
    
    requestQueue = hardCodeRequestQueue;
    orderOfProcessing = (int*)malloc(10*sizeof(int));
    globalCurrentHead = 86;
    queueLength = 10;
    totalHeadMovement = 0;
    
}

void DiskSchedulingPolicy::manInit(){
    
    cout<<"\nEnter length of the request queue : ";
    cin>>queueLength;
    requestQueue = (int*)malloc(queueLength*sizeof(int));
    orderOfProcessing = (int*)malloc(queueLength*sizeof(int));
    cout<<"\nEnter the request queue : ";
    for(int i = 0; i < queueLength; i++){
        cout<<"\nEnter element "<<(i+1)<<": ";
        cin>>requestQueue[i];
    }
    cout<<"\nEnter the current head location : ";
    cin>>globalCurrentHead;
    totalHeadMovement = 0;
    
}

void DiskSchedulingPolicy::startDemo(){

    cout<<"\n\t\t Disk Scheduling Policies Demo \n\n";
    cout<<"Do you want to input values or should we do it for you ? [1/0] : ";
    int choice;
    cin>>choice;

    //defaulting or user input
    if(choice) manInit();
    else defInit();

    while(true){
        cout<<"\n\nPolicies you can try out :";
        cout<<"\n1. FCFS";
        cout<<"\n2. SSTF";
        cout<<"\n3. SCAN";
        cout<<"\n4. C-SCAN";
        cout<<"\n5. LOOK";
        cout<<"\n6. C-LOOK";
        cout<<"\n7. EXIT";
        cout<<"\n\nWhat would you like [1-7] : ";

        cin>>choice;
        switch(choice) {
            case 1:
                FCFS();
                break;
            case 2:
                SSTF();
                break;
            case 3:
                SCAN();
                break;
            case 4:
                CSCAN();
                break;
            case 5:
                LOOK();
                break;
            case 6:
                CLOOK();
                break;
            case 7:
                cout<<"\nThank you for using Disk Scheduling Policies Demo. Bye.\n\n";
                return;
                break;
            default:
                cout<<"Unsupported choice. Please try again.";
        }
    }
}

void DiskSchedulingPolicy::printAverageSeekTime(int totalHeadMovement, int totalLength){

    double avgSeekTime = (double)totalHeadMovement/totalLength;
    cout<<"\n\n\tAverage Seek Time : "<<totalHeadMovement<<"/"<<totalLength<<"="<<avgSeekTime;

}

void DiskSchedulingPolicy::FCFS(){}

void DiskSchedulingPolicy::SSTF(){}

void DiskSchedulingPolicy::SCAN(){}

void DiskSchedulingPolicy::CSCAN(){}

void DiskSchedulingPolicy::LOOK(){}

void DiskSchedulingPolicy::CLOOK(){}

int main(void){
     
    DiskSchedulingPolicy dsp;
    dsp.startDemo();
    return 0;

}