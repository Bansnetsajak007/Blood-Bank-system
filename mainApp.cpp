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
        int donorId;
        string name,address, bloodType , district;

    public:
        void donorDetails() const {
            //will implement this function
            cout << "donorDetails" << endl;
            cout << "Donor Name: " << name << endl;
            cout << "Donor District: " << district << endl;
            cout << "Donor Blood Type: " << bloodType << endl;
        }
};

class BloodDatabase {
    private:
        const string fileName = "data.txt";
        Donor donors[SIZE];

    public:
        void getDonorDetails() {
            cout<<"Enter your Details\n";

            for(int i = 0 ; i < 3; ++i) {
                cout<<"Id: ";
                cin >>donors[i].donorId;
                cout<<"\n";
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

        outfile.write(reinterpret_cast<const char*>(donors), sizeof(donors));
        outfile.close();

    }

    void searchAndDisplay(int idToSearch) const {
        ifstream inFile(fileName, ios::binary);

        if (!inFile) {
            cout << "Error opening file for reading." << endl;
            return;
        }

        Donor donor;
        bool found = false;

        while (inFile.read(reinterpret_cast<char*>(&donor), sizeof(Donor))){
            if (donor.donorId == idToSearch) {
                found = true;
                donor.donorDetails();
                break;
            }
        }

        if (!found) {
            cout << "Donor with ID" << idToSearch << " not found." <<endl;
        }
        inFile.close();
    }
};


int main() {
    BloodDatabase database;

    database.getDonorDetails();
    database.writeDataToFile();

    int idToSearch;

    cout<< "Enter ID to search: "<<endl;
    cin >> idToSearch;

    database.searchAndDisplay(idToSearch);

    return 0;
}

