//refactoring search code

#include<iostream>
#include<string>
#include <fstream>
#include <vector>

using namespace std;


void donerRegistration() {
    long int number;
    string name, address, bloodType, district;

    ofstream outfile("data.txt",ios::app);

    cout<<"Enter your Details\n";
    cout<<"Mobile Number: ";
    cin >> number;
    cin.ignore();
    cout<<"Address: ";
    getline(cin, address);
    cout<<"District: ";
    getline(cin, district);
    cout<<"BloodType: ";
    getline(cin, bloodType);

    //store the details in file

    if (!outfile.is_open()) {
        cerr << "Error opening file!" << std::endl;
        return;
    }

    outfile << number << "\t" << address << "\t" << district << "\t" << bloodType << endl;

    outfile.close();

}

void findDonor(const string& district, const string& bloodType) {
    ifstream infile("data.txt");
    
    if (!infile.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    string line;
    string donorDisctict;
    string donorBloodType;
    bool found = false;

    while (getline(infile, line)) {
        // Extract address and blood type from the line
        size_t pos1 = line.find('\t');
        size_t pos2 = line.find('\t', pos1 + 1);

        donorDisctict = line.substr(pos1 + 1, pos2 - pos1 - 1);
        donorBloodType = line.substr(pos2 + 1);

        if (donorDisctict == district && donorBloodType == bloodType) {
            // Print the donor details
            cout << "Donor found:" << endl;
            cout << line << endl;
            found = true;
        }
    }

    // Close the file
    infile.close();

    // If donor not found
    if (!found) {
        cout << "No donor found with the specified criteria." << endl;
    }
}
void deleteDoner() {

}


int main() {
    int choice;
    string searchDistrict, searchBloodType;

    while(1) {

    cout<<"Blood Bank Management System"<<endl;
    cout<<"1) Be a Blood Donor"<<endl;
    cout<<"2) Find a Blood Donor"<<endl;
    cout<<"3) Delete a Blood Donor"<<endl;
    cout<<"Enter your Choice: ";
    cin>>choice;


    switch (choice) {
    {
    case 1:
        donerRegistration();
        break;

    case 2:
        cin.ignore();
        cout<<"Search District: ";
        getline(cin, searchDistrict);
        cout<<"Search BloodType: ";
        getline(cin, searchBloodType);
        findDonor(searchDistrict, searchBloodType);
        break;

    case 3:
        deleteDoner();
        break;
    default:
        cout<<"Invalid Choice Please Enter Again\n";
    }
    }
    return 0;
    }
}