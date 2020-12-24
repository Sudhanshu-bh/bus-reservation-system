/*
Bus Reservation System project.
This project makes the use of file handling.
Made by Sudhanshu Bhardwaj.
*/

#include<iostream>
#include<fstream>
#include<conio.h>

#define stars " ************** "
using namespace std;

void writeRecord();
void clearFile();
bool isempty();

class a
{
    string busn, driver, arrival, depart, from, to;
    string seat[8][4];

public:

    void install();
    void bookSeat();
    void showSeats();
    void showBuses();
    void removeBus();
}
myBus;

void a::install()
{
    system("CLS");
    cout<<"\n\n\n\n\n\t\t"<<stars<<"Install New Bus"<<stars;

    cout<<"\n\n\t\t\tEnter bus number: \t";
    cin>>busn;

    cout<<"\n\n\t\t\tEnter driver's name: \t";
    cin>>driver;

    cout<<"\n\n\t\t\tArrival Time: \t\t";
    cin>>arrival;

    cout<<"\n\n\t\t\tDepart time: \t\t";
    cin>>depart;

    cout<<"\n\n\t\t\tFrom: \t\t\t";
    cin>>from;

    cout<<"\n\n\t\t\tTo: \t\t\t";
    cin>>to;

    for(int i=0; i<8; i++)
    {
        for(int j=0; j<4; j++)
        {
            seat[i][j]="-";
        }
    }

    writeRecord();
}

void a::bookSeat()
{
    system("CLS");

    cout<<"\n\n\n\n\n\t\t"<<stars<<"Seat Reservation"<<stars;
    if( isempty() )
        return;

    string busNum;

    cout<<"\n\n\t\t\t Enter Bus No.: \t\t";
    cin>>busNum;

    fstream myFile;
    myFile.open("Buses_record.dat", ios::binary | ios::in | ios::out);

    while(myFile)
    {
        auto pos = myFile.tellg();
        myFile.read((char *)&myBus, sizeof(myBus));

        if(busn == busNum)
        {
            int rno, cno;

            cout<<"\n\t\t\t Enter row number (1-8): \t";
            cin>>rno;
            cout<<"\n\t\t\t Enter column number (1-4): \t";
            cin>>cno;

            if( rno>8 )
            {
                cout<<"\n\n\t\t\t Invalid row number!";
                return;
            }
            else if( cno>4 )
            {
                cout<<"\n\n\t\t\t Invalid column number!";
                return;
            }
            else if( seat[rno-1][cno-1] == "-" )
            {
                string name;
                cout<<"\n\t\t\t Enter your name: \t\t";
                cin>>name;
                seat[rno-1][cno-1]=name;

                myFile.seekg(pos);
                myFile.write((char *)&myBus, sizeof(myBus));

                cout<<"\n\n\t\t\t Seat reserved successfully!";

                getch();
                return;
            }
            else
            {
                cout<<"\n\n\t\t\tThis seat is already reserved!"
                    <<"\n\n\t\t\tPlease try another seat.";

                getch();
                return;
            }
        }
    }
    cout<<"\n\n\t\t\tInvalid Bus Number!";
    getch();
}

void a::showSeats()
{
    system("CLS");

    cout<<"\n\n\n\n\n\t\t"<<stars<<"Seat Enquiry"<<stars;
    if( isempty() )
        return;

    string busno;

    cout<<"\n\n\t\t\tEnter Bus Number: ";
    cin>>busno;

    ifstream rFile;
    rFile.open("Buses_record.dat", ios::binary);

    cout<<"\n\n\n";

    while(rFile)
    {
        rFile.read((char *)&myBus, sizeof(myBus));

        if(busn == busno)
        {
            for(int i=0; i<8; i++)
            {
                cout<<"\n\t\t\t"<<i+1<<".\t";
                for(int j=0; j<4; j++)
                {
                    if(j==2)
                        cout<<"\t";
                    cout<<seat[i][j]<<"\t";
                }
            }
            getch();
            return;
        }
    }

    rFile.close();
    cout<<"\t\t\tInvalid Bus number!";
    getch();
}

void a::showBuses()
{
    system("CLS");

    cout<<"\n\n\n\n\n\t\t"<<stars<<"Buses List"<<stars;
    if( isempty() )
        return;

    ifstream rFile("Buses_record.dat", ios::binary);

    while( rFile.read((char *)&myBus, sizeof(myBus)) )
    {
        cout<<"\n\n\n\t\t\tBus Number: \t"<<busn
            <<"\n\t\t\tDriver's Name: \t"<<driver
            <<"\n\t\t\tArrival Time: \t"<<arrival
            <<"\n\t\t\tDepart Time: \t"<<depart
            <<"\n\t\t\tFrom: \t\t"<<from
            <<"\n\t\t\tTo: \t\t"<<to;

    }
    cout<<"\n\n\n\t\t\tNo more buses!";
    getch();
}

void a::removeBus()
{
    system("CLS");

    cout<<"\n\n\n\n\n\t\t"<<stars<<"Bus Removal"<<stars;
    if( isempty() )
        return;

    string busNum;
    cout<<"\n\n\n\t\t\tEnter Bus Number to be removed: \t";
    cin>>busNum;

    ifstream rFile("Buses_record.dat", ios::binary );
    ofstream wFile("Buses_record_new.dat", ios::binary );

    while( rFile.read((char *)&myBus, sizeof(myBus)) )
    {
        if(busn == busNum)
        {
            cout<<"\n\n\n\t\t\tBus number "<<busNum<<" has been removed.";
            continue;
        }

        wFile.write((char *)&myBus, sizeof(myBus));
    }

    rFile.close();
    wFile.close();

    remove("Buses_record.dat");
    rename("Buses_record_new.dat", "Buses_record.dat");

    getch();
}

void writeRecord()
{
    ofstream myFile;
    myFile.open("Buses_record.dat", ios::binary | ios::app);

    myFile.write((char *)&myBus, sizeof(myBus));

    myFile.close();
    cout<<"\n\n\t\t\tBuss added successfully!";
    getch();
}

bool isempty()
{
    bool isemp=0;

    ifstream rFile("Buses_record.dat", ios::binary );

    if( !(rFile.read((char *)&myBus, sizeof(myBus))) )
    {
        cout<<"\n\n\t\t\tNo Buses Available!";
        isemp = 1;
        getch();
    }
    rFile.close();

    return isemp;
}

void clearFile()
{
    system("CLS");
    char cho;
    cout<<"\n\n\n\n\n\t\t"<<stars<<"WARNING!"<<stars
        <<"\n\n\t\t\tAll the bus records will be DELETED!"
        <<"\n\n\t\t\tDo you want to continue? (Y/N)\t\t";
    cin>>cho;

    if(cho=='Y' || cho=='y')
    {
        ofstream myFile;
        myFile.open("Buses_record.dat", ios::trunc);
        myFile.close();
        cout<<"\n\n\t\tAll buses' records have been deleted!";
        getch();
    }
    else{
        cout<<"\n\n\t\t\tNo bus record was deleted.";
        getch();
    }
}

int main()
{
    int choice;

    while(1)
    {
        system("CLS");
        cout<<"\n\n\n\n\n\t\t"<<stars<<"Bus Reservation System"<<stars
            <<"\n\t\t\t   (Project by Sudhanshu Bhardwaj)\n\n\n\t\t\t";

        cout<<"1. Install\n\t\t\t"
            <<"2. Reservation\n\t\t\t"
            <<"3. Show Seats\n\t\t\t"
            <<"4. Buses Available\n\t\t\t"
            <<"5. Remove a bus\n\t\t\t"
            <<"6. Clear all records\n\t\t\t"
            <<"7. Exit";

        cout<<"\n\n\t\t\t"
            <<"Enter your choice: \t";
        cin>>choice;

        switch(choice)
        {
        case 1:
            myBus.install();
            break;
        case 2:
            myBus.bookSeat();
            break;
        case 3:
            myBus.showSeats();
            break;
        case 4:
            myBus.showBuses();
            break;
        case 5:
            myBus.removeBus();
            break;
        case 6:
            clearFile();
            break;
        case 7:
            cout<<"\n\n\n";
            exit(0);
        default:
            cout<<"\n\n\t\t\tEnter a valid choice!";
            getch();
        }
    }
    //This project is made by Sudhanshu.
    return 0;
}
