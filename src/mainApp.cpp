#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <stdexcept>
#include <cctype>
#include <algorithm>

using namespace std;

class Donor {
public:
    int donorId, district, number;
    string name, address, bloodType;

    void donorDetails() const {
        cout << "Donor Name: " << name << endl;
        cout << "Donor District: " << district << endl;
        cout << "Donor Blood Type: " << bloodType << endl;
    }

    static Donor parseLine(const string& line) {
        Donor d;
        stringstream ss(line);
        string token;

        getline(ss, token, ','); d.donorId = stoi(token);
        getline(ss, token, ','); d.name = token;
        getline(ss, token, ','); d.address = token;
        getline(ss, token, ','); d.district = stoi(token);
        getline(ss, token, ','); d.bloodType = token;
        getline(ss, token, ','); d.number = stoi(token);

        return d;
    }
};

class BloodDatabase {
private:
    const string fileName = "data.txt";
    vector<Donor> donors;

    static void displayProvinces() {
        cout << "Choose the province:\n";
        cout << "1. Koshi\n";
        cout << "2. Madhesh\n";
        cout << "3. Bagmati\n";
        cout << "4. Gandaki\n";
        cout << "5. Lumbini\n";
        cout << "6. Karnali\n";
        cout << "7. Sudurpashchim\n";
    }

public:
    static void clearConsole() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    static void waitForKeyPress() {
        cout << "Press any key to continue...";
        cin.ignore();
        cin.get();
    }

    static int getValidatedInput(const string& prompt) {
        int value;
        string input;
        while (true) {
            cout << prompt;
            getline(cin, input);
            try {
                if (!all_of(input.begin(), input.end(), ::isdigit)) {
                    throw invalid_argument("Input contains non-numeric characters");
                }
                value = stoi(input);
                break; // if conversion is successful, exit loop
            } catch (const invalid_argument& e) {
                cout << "Invalid input: " << e.what() << ". Please enter a valid number." << endl;
            } catch (const out_of_range&) {
                cout << "Input out of range. Please enter a valid number." << endl;
            }
        }
        return value;
    }

    void getDonorDetails() {
        clearConsole();
        cout << "Enter donor details\n";

        Donor newDonor;
        newDonor.donorId = getValidatedInput("Id: ");
        cout << "Name: ";
        getline(cin, newDonor.name);
        cout << "Address: ";
        getline(cin, newDonor.address);
        
        displayProvinces();
        newDonor.district = getValidatedInput("Province (enter the corresponding number): ");
        cout << "Blood Type: ";
        getline(cin, newDonor.bloodType);
        newDonor.number = getValidatedInput("Number: ");

        donors.push_back(newDonor);
    }

    void writeDataToFile() {
        ofstream outfile(fileName, ios::app);

        if (!outfile) {
            cout << "Error opening file for writing." << endl;
            return;
        }

        Donor newDonor = donors.back();
        outfile << newDonor.donorId << "," << newDonor.name << "," << newDonor.address << "," << newDonor.district << "," << newDonor.bloodType << "," << newDonor.number << endl;

        outfile.close();
    }

    void searchAndDisplay() const {
        clearConsole();
        displayProvinces();
        int provinceName = getValidatedInput("Enter the province number: ");

        ifstream inFile(fileName);

        if (!inFile) {
            cout << "Error opening file for reading." << endl;
            return;
        }

        vector<Donor> donors;
        string line;
        bool found = false;

        while (getline(inFile, line)) {
            Donor d = Donor::parseLine(line);
            if (d.district == provinceName) {
                donors.push_back(d);
                found = true;
            }
        }

        if (!found) {
            cout << "No people found from province " << provinceName << endl;
        } else {
            cout << "People from province " << provinceName << ":" << endl;
            for (const auto& d : donors) {
                cout << "Name: " << d.name << endl;
                cout << "Address: " << d.address << endl;
                cout << "Province: " << d.district << endl;
                cout << "Blood Type: " << d.bloodType << endl;
                cout << "Mobile Number: " << d.number << endl;
                cout << endl;
            }
        }

        inFile.close();
        waitForKeyPress();
    }

    void deleteDonor(const string& donorName) {
        ifstream inFile(fileName);
        ofstream tempFile("temp.txt");

        if (!inFile) {
            cerr << "Error opening file " << fileName << endl;
            return;
        }

        if (!tempFile) {
            cerr << "Error creating temporary file" << endl;
            return;
        }

        string line;
        bool found = false;

        while (getline(inFile, line)) {
            Donor d = Donor::parseLine(line);
            if (d.name == donorName) {
                found = true;
                cout << "Name: " << d.name << endl;
                cout << "Address: " << d.address << endl;
                cout << "Blood Type: " << d.bloodType << endl;
                cout << "Mobile Number: " << d.number << endl;
                cout << endl;
                cout << "Are you sure you want to delete donor? [y/n]: ";
                char sureChoice;
                cin >> sureChoice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard any extra input

                if (sureChoice == 'y' || sureChoice == 'Y') {
                    continue;
                }
            }

            tempFile << d.donorId << "," << d.name << "," << d.address << "," << d.district << "," << d.bloodType << "," << d.number << endl;
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

    while (true) {
        BloodDatabase::clearConsole();
        cout <<
            "  ____  _                 _   ____               _      \n"
            " | __ )| | ___   ___   __| | | __ )  __ _ _ __ | | __  \n"
            " |  _ \\| |/ _ \\ / _ \\ / _` | |  _ \\ / _` | '_ \\| |/ /  \n"
            " | |_) | | (_) | (_) | (_| | | |_) | (_| | | | |   <   \n"
            " |____/|_|\\___/ \\___/ \\__,_| |____/ \\__,_|_| |_|_|\\_\\  \n"
            "                                                      \n\n";
        cout << "1. Register Donor\n2. Find Donor\n3. Delete Donor\n4. Exit\nEnter your choice: ";
        choice = BloodDatabase::getValidatedInput("");

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
            exit(0);
        default:
            cout << "Invalid choice\n";
        }
    }
    return 0;
}
