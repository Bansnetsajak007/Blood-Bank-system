//completed register donor
// search donor (done) (still more filter function to implement)
//delete door (will implement)

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>

using namespace std;

class Donor {
public:
    long int number;
    int donorId,district;
    string name, address, bloodType;

public:
    void donorDetails() const {
        cout << "Donor Name: " << name << endl;
        cout << "Donor District: " << district << endl;
        cout << "Donor Blood Type: " << bloodType << endl;
    }

        Donor parseLine(const string& line) {
    Donor d;
    stringstream ss(line);
    ss >> d.name >> d.address >> d.district >> d.bloodType >> d.number;
    return d;
}
};

class BloodDatabase {
private:
    const string fileName = "data.txt";
    vector<Donor> donors;

//     Donor parseLine(const string& line) {
//     Donor d;
//     stringstream ss(line);
//     ss >> d.name >> d.address >> d.district >> d.bloodType >> d.number;
//     return d;
// }

public:
    

    void getDonorDetails() {
        cout << "Enter donor details\n";

        Donor newDonor;
        cout << "Id: ";
        cin >> newDonor.donorId;
        cout << "\n";
        cout << "Name: ";
        cin.ignore();
        getline(cin, newDonor.name);
        cout << "\n";
        cout << "Address: ";
        getline(cin, newDonor.address);
        cout << "\n";

        cout << "Provience: ";
        cin >> newDonor.district;
        cout << "\n";
        cin.ignore();
        cout << "Blood Type: ";
        getline(cin, newDonor.bloodType);
        cout << "\n";

        cout << "Number: ";
        cin >> newDonor.number;

        donors.push_back(newDonor);
    }

    void writeDataToFile() {
        ofstream outfile(fileName, ios::app); // Open in append mode to add new donors to the end of the file

        if (!outfile) {
            cout << "Error opening file for writing." << endl;
            return;
        }

        Donor newDonor = donors.back(); // Get the last donor added
        outfile << endl;
        outfile << newDonor.name <<"    " << newDonor.address <<"    " << newDonor.district <<"    " << newDonor.bloodType <<"    " << newDonor.number << "," <<endl;

        outfile.close();
    }



    void searchAndDisplay() const {

        int provienceName;
        cout<< "Enter the name of the province: ";
        cin >> provienceName;

        ifstream inFile(fileName);

        if (!inFile) {
            cout << "Error opening file for reading." << endl;
            return;
        }

        vector<Donor> donor;
        Donor temp;
        string line;
        bool found = false;

        while (getline(inFile, line)) {
            Donor d = temp.parseLine(line); 
            // cout << d.district << endl; 
            if(d.district == provienceName) {
                donor.push_back(d);
            }
        }

        if(donor.empty()) {
        cout << "No people found from " << provienceName << endl;
        } else {
        cout << "People from " << provienceName << ":" << endl;
        for (const auto& d : donor) {
            cout << "Name: " << d.name << endl;
            cout << "Address: " << d.address << endl;
            cout << "Province: " << d.district << endl;
            cout << "Blood Type: " << d.bloodType << endl;
            cout << "Mobile Number: " << d.number << endl;
            cout << endl;
        }

        inFile.close();
    }
}

    void deleteDonor(int idToDelete) {
        ifstream inFile(fileName);
        ofstream tempFile("temp.txt");

        if (!inFile || !tempFile) {
            cout << "Error opening files for reading/writing." << endl;
            return;
        }

        Donor donor;
        bool found = false;

        while (inFile >> donor.donorId >> donor.name >> donor.address >> donor.district >> donor.bloodType >> donor.number) {
            if (donor.donorId == idToDelete) {
                found = true;
                continue; // Don't write this donor to the temp file, effectively deleting it
            }
            tempFile << "Id: " << donor.donorId << endl;
            tempFile << "Name: " << donor.name << endl;
            tempFile << "Address: " << donor.address << endl;
            tempFile << "District: " << donor.district << endl;
            tempFile << "Blood Type: " << donor.bloodType << endl;
            tempFile << "Number: " << donor.number << endl;
            tempFile << endl;
        }

        inFile.close();
        tempFile.close();

        remove(fileName.c_str());         // Delete the original file
        rename("temp.txt", fileName.c_str()); // Rename temp file to original name
        if (found)
            cout << "Donor with ID " << idToDelete << " deleted successfully." << endl;
        else
            cout << "Donor with ID " << idToDelete << " not found." << endl;
    }
};

//function to parse a line and extract donor details
// Donor parseLine(const string& line) {
//     Donor d;
//     stringstream ss(line);
//     ss >> d.name >> d.address >> d.district >> d.bloodType >> d.number;
//     return d;
// }

int main() {
    BloodDatabase database;
    int choice;

while (1) {
        cout << 
    "  ____  _                 _   ____              _      \n"
    " | __ )| | ___   ___   __| | | __ )  __ _ _ __ | | __  \n"
    " |  _ \\| |/ _ \\ / _ \\ / _` | |  _ \\ / _` | '_ \\| |/ /  \n"
    " | |_) | | (_) | (_) | (_| | | |_) | (_| | | | |   <   \n"
    " |____/|_|\\___/ \\___/ \\__,_| |____/ \\__,_|_| |_|_|\\_\\  \n" 
    "                                                      \n\n";
    cout << "1. Register Donor\n2. Find Donor\n3. Delete Donor\n4. Exit\nEnter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        database.getDonorDetails();
        database.writeDataToFile();
        break;
    case 2:
        database.searchAndDisplay();
        break;
    case 3:
        int idToDelete;
        cout << "Enter ID to delete: ";
        cin >> idToDelete;
        database.deleteDonor(idToDelete);
        break;
    case 4:
        exit(1);
    default:
        cout << "Invalid choice\n";
    }
}
    return 0;
}
