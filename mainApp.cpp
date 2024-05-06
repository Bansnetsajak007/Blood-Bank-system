#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

class Donor {
public:
    long int number;
    int donorId;
    string name, address, bloodType, district;

public:
    void donorDetails() const {
        cout << "Donor Name: " << name << endl;
        cout << "Donor District: " << district << endl;
        cout << "Donor Blood Type: " << bloodType << endl;
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

        cout << "District: ";
        getline(cin, newDonor.district);
        cout << "\n";

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
        outfile << "Id: " << newDonor.donorId << endl;
        outfile << "Name: " << newDonor.name << endl;
        outfile << "Address: " << newDonor.address << endl;
        outfile << "District: " << newDonor.district << endl;
        outfile << "Blood Type: " << newDonor.bloodType << endl;
        outfile << "Number: " << newDonor.number << endl;
        outfile << endl; // Add a blank line between donors for readability

        outfile.close();
    }

    void searchAndDisplay(int idToSearch) const {
        ifstream inFile(fileName);

        if (!inFile) {
            cout << "Error opening file for reading." << endl;
            return;
        }

        Donor donor;
        bool found = false;

        while (inFile >> donor.donorId >> donor.name >> donor.address >> donor.district >> donor.bloodType >> donor.number) {
            if (donor.donorId == idToSearch) {
                found = true;
                donor.donorDetails();
                break;
            }
        }

        if (!found) {
            cout << "Donor with ID " << idToSearch << " not found." << endl;
        }

        inFile.close();
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


int main() {
    BloodDatabase database;

    int choice;
    cout << "1. Register Donor\n2. Find Donor\n3. Delete Donor\nEnter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        database.getDonorDetails();
        database.writeDataToFile();
        break;
    case 2:
        int idToSearch;
        cout << "Enter ID to search: ";
        cin >> idToSearch;
        database.searchAndDisplay(idToSearch);
        break;
    case 3:
        int idToDelete;
        cout << "Enter ID to delete: ";
        cin >> idToDelete;
        database.deleteDonor(idToDelete);
        break;
    default:
        cout << "Invalid choice." << endl;
        break;
    }

    return 0;
}
