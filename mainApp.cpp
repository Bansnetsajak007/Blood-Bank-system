/*
    This is the main project file
    lessss goooo hell yeahhhh
*/

#include<iostream>
#include<fstream>
#include<string>

using namespace std;

#define SIZE 1000

class Donor {
    public:
        long int number;
        string name,address, bloodType , district;

    public:
        void donorDetails() const {
            //will implement this function
        }
};

class BloodDatabase {
    private:
        const string fileName = "data.txt";
        Donor donors[SIZE];

    public:
        void getDonorDetails() {
            cout<<"Enter your Details\n";

            for(int i = 0 ; i < 2; ++i) {
                cout<<"Name: ";
                cin >>donors[i].name;
                cout<<"\n";
                cout<<"Address: ";
                cin >>donors[i].address;
                cout<<"\n";

                cout<<"Disctrict: ";
                cin >>donors[i].district;
                cout<<"\n";

                cout<<"Blood Type: ";
                cin >>donors[i].bloodType;
                cout<<"\n";

                cout<<"Number: ";
                cin >>donors[i].number;
        }
    }

    void writeDataToFile() const {
        ofstream outfile(fileName, ios::binary);

        if(!outfile) {
            cout << "Error opening file for writing." << endl;
            return;
        }

        Donor donor[SIZE];
        bool flag = false;

    }
};

