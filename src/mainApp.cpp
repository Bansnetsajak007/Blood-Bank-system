//completed register donor
// search donor (done) (still more filter function to implement)
//delete door (will implement)
// implement effective error handiling

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Donor {
public:
    long int number;
    int donorId, district;
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

        cout << "Province: ";
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
        ofstream outfile(fileName, ios::app); 

        if (!outfile) {
            cout << "Error opening file for writing." << endl;
            return;
        }

        Donor newDonor = donors.back(); 
        outfile << newDonor.name << "    " << newDonor.address << "    " << newDonor.district << "    " << newDonor.bloodType << "    " << newDonor.number << "," << endl;

        outfile.close();
    }

    void searchAndDisplay() const {
        int provinceName;
        cout << "Enter the name of the province: ";
        cin >> provinceName;

        ifstream inFile(fileName);

        if (!inFile) {
            cout << "Error opening file for reading." << endl;
            return;
        }

        vector<Donor> donor;
        Donor temp;  //temporary object
        string line;
        bool found = false;

        while (getline(inFile, line)) {
            Donor d = temp.parseLine(line);
            if (d.district == provinceName) {
                donor.push_back(d);
            }
        }

        if (donor.empty()) {
            cout << "No people found from " << provinceName << endl;
        } else {
            cout << "People from " << provinceName << ":" << endl;
            for (const auto& d : donor) {
                cout << "Name: " << d.name << endl;
                cout << "Address: " << d.address << endl;
                cout << "Province: " << d.district << endl;
                cout << "Blood Type: " << d.bloodType << endl;
                cout << "Mobile Number: " << d.number << endl;
                cout << endl;
            }
        }

        inFile.close();
    }

    void deleteDonor(const string& donorName) {
        ifstream inFile(fileName);
        ofstream tempFile("temp.txt"); // Temporary file to store non-deleted donors

        if (!inFile) {
            cerr << "Error opening file " << fileName << endl;
            return;
        }

        if (!tempFile) {
            cerr << "Error creating temporary file" << endl;
            return;
        }

        Donor temp;  //temporary object
        string line;
        bool found = false; // Flag to check if the donor is found

        while (getline(inFile, line)) {
            Donor d = temp.parseLine(line);
            if (d.name == donorName) {
                found = true; // Set found flag to true
                cout << "Name: " << d.name << endl;
                cout << "Address: " << d.address << endl;
                cout << "Blood Type: " << d.bloodType << endl;
                cout << "Mobile Number: " << d.number << endl;
                cout << endl;
                cout << "Are you sure you want to delete donor? [y/n]: ";
                char sureChoice;
                cin >> sureChoice;

                if (sureChoice == 'y' || sureChoice == 'Y') {
                    continue;
                }
            }

            tempFile << line << endl;
        }

        inFile.close();
        tempFile.close();

        if (remove(fileName.c_str()) != 0) {
            cerr << "Error removing original file" << endl;
            return;
        }

        if (rename("temp.txt", fileName.c_str()) != 0) {
            cerr << "Error renaming temporary file" << endl;
            return;
        }

        if (!found) {
            cout << "No donor found with the name " << donorName << endl;
        }
    }
};

int main() {
    string donorName;
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
        cin.ignore(); // This will clear the newline character left in the buffer

        switch (choice) {
        case 1:
            database.getDonorDetails();
            database.writeDataToFile();
            break;
        case 2:
            database.searchAndDisplay();
            break;
        case 3:
            cout << "Enter the Name of Donor: ";
            getline(cin, donorName);
            database.deleteDonor(donorName);
            break;
        case 4:
            exit(1);
        default:
            cout << "Invalid choice\n";
        }
    }
    return 0;
}
