#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// Structure to hold person details
struct Person {
    string name;
    string address;
    int province;
    string bloodType;
    string mobileNumber;
};

// Function to parse a line and extract person details
Person parseLine(const string& line) {
    Person p;
    stringstream ss(line);
    ss >> p.name >> p.address >> p.province >> p.bloodType >> p.mobileNumber;
    return p;
}

int main() {
    int provinceName;
    cout << "Enter the name of the province: ";
    cin>> provinceName;

    ifstream file("sample.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    vector<Person> people;
    string line;
    // Read each line from the file and parse person details
    while (getline(file, line)) {
        Person p = parseLine(line);
        if (p.province == provinceName) {
            people.push_back(p);
        }
    }

    // Display people belonging to the entered province
    if (people.empty()) {
        cout << "No people found from " << provinceName << endl;
    } else {
        cout << "People from " << provinceName << ":" << endl;
        for (const auto& p : people) {
            cout << "Name: " << p.name << endl;
            cout << "Address: " << p.address << endl;
            cout << "Province: " << p.province << endl;
            cout << "Blood Type: " << p.bloodType << endl;
            cout << "Mobile Number: " << p.mobileNumber << endl;
            cout << endl;
        }
    }

    file.close();

    return 0;
}
