//refactoring search code

#include<iostream>
#include<string>
#include <fstream>
#include <vector>

using namespace std;


void donerRegistration() {
    long int number;
    string name, address, bloodType;

    ofstream outfile("data.txt",ios::app);

    cout<<"Enter your Details\n";
    cout<<"Mobile Number: ";
    cin >> number;
    cin.ignore();
    cout<<"Address: ";
    getline(cin, address);
    cout<<"BloodType: ";
    getline(cin, bloodType);

    //store the details in file

    if (!outfile.is_open()) {
        cerr << "Error opening file!" << std::endl;
        return;
    }

    outfile << number << "\t" << address << "\t" << bloodType << std::endl;

    outfile.close();

}

void findDonor(const string& address, const string& bloodType) {
    // Open the file for reading
    ifstream infile("data.txt");
    
    // Check if the file opened successfully
    if (!infile.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    // Variables to store data read from the file
    string line;
    string donorAddress;
    string donorBloodType;
    bool found = false;

    // Read each line from the file
    while (getline(infile, line)) {
        // Extract address and blood type from the line
        size_t pos1 = line.find('\t');
        size_t pos2 = line.find('\t', pos1 + 1);

        donorAddress = line.substr(pos1 + 1, pos2 - pos1 - 1);
        donorBloodType = line.substr(pos2 + 1);

        // Check if the address and blood type match the criteria
        if (donorAddress == address && donorBloodType == bloodType) {
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
    string searchAddress, searchBloodType;
    cout<<"Blood Bank Management System"<<endl;
    cout<<"1) Be a Blood Donor"<<endl;
    cout<<"1) Find a Blood Donor"<<endl;
    cout<<"1) Delete a Blood Donor"<<endl;
    cout<<"Enter your Choice: ";
    cin>>choice;

    switch (choice) {
    {
    case 1:
        donerRegistration();
        break;

    case 2:
        cin.ignore();
        cout<<"Search Address: ";
        getline(cin, searchAddress);
        cout<<"Search BloodType: ";
        getline(cin, searchAddress);
        findDonor(searchAddress, searchBloodType);
        break;

    case 3:
        deleteDoner();
        break;
    default:
        break;
    }
    return 0;
}
}