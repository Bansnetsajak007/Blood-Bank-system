#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Member class to encapsulate member details and operations
class Member {
private:
    std::string name;
    int age;
    std::string gender;
    double feePaid;
    int totalDays;

public:
    Member(const std::string& name, int age, const std::string& gender, double feePaid, int totalDays)
        : name(name), age(age), gender(gender), feePaid(feePaid), totalDays(totalDays) {}

    void displayInfo() const {
        std::cout << "Name: " << name << "\n"
                  << "Age: " << age << "\n"
                  << "Gender: " << gender << "\n"
                  << "Fee Paid: Rs" << feePaid << "\n"
                  << "Total Days: " << totalDays << "\n";
    }

    void addFee(double amount) {
        feePaid += amount;
    }

    void addDays(int days) {
        totalDays += days;
    }

    void updateInfo(int newAge, const std::string& newGender) {
        age = newAge;
        gender = newGender;
    }

    const std::string& getName() const {
        return name;
    }
};

// GymManagement class to handle member management
class GymManagement {
private:
    std::vector<Member> members;

    std::vector<Member>::iterator findMember(const std::string& name) {
        return std::find_if(members.begin(), members.end(), [&](const Member& m) { return m.getName() == name; });
    }

public:
    void registerMember(const std::string& name, int age, const std::string& gender, double feePaid, int totalDays) {
        members.emplace_back(name, age, gender, feePaid, totalDays);
        std::cout << "Member registered successfully.\n";
    }

    void displayAllMembers() const {
        if (members.empty()) {
            std::cout << "No members to display.\n";
            return;
        }
        for (const auto& member : members) {
            member.displayInfo();
            std::cout << "-----------------------\n";
        }
    }

    void addFeeToMember(const std::string& name, double amount) {
        auto it = findMember(name);
        if (it != members.end()) {
            it->addFee(amount);
            std::cout << "Fee added successfully.\n";
        } else {
            std::cout << "Member not found.\n";
        }
    }

    void addDaysToMember(const std::string& name, int days) {
        auto it = findMember(name);
        if (it != members.end()) {
            it->addDays(days);
            std::cout << "Days added successfully.\n";
        } else {
            std::cout << "Member not found.\n";
        }
    }

    void deleteMember(const std::string& name) {
        auto it = findMember(name);
        if (it != members.end()) {
            members.erase(it);
            std::cout << "Member deleted successfully.\n";
        } else {
            std::cout << "Member not found.\n";
        }
    }

    void searchMember(const std::string& name) const {
        auto it = std::find_if(members.begin(), members.end(), [&](const Member& m) { return m.getName() == name; });
        if (it != members.end()) {
            it->displayInfo();
        } else {
            std::cout << "Member not found.\n";
        }
    }

    void updateMemberInfo(const std::string& name, int newAge, const std::string& newGender) {
        auto it = findMember(name);
        if (it != members.end()) {
            it->updateInfo(newAge, newGender);
            std::cout << "Member information updated successfully.\n";
        } else {
            std::cout << "Member not found.\n";
        }
    }
};

// Function to validate positive integer input
int getValidPositiveInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || value < 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a positive integer.\n";
        } else {
            return value;
        }
    }
}

// Function to validate positive double input
double getValidPositiveDouble(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || value < 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a positive number.\n";
        } else {
            return value;
        }
    }
}

// Function to validate non-empty string input
std::string getValidString(const std::string& prompt) {
    std::string value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (value.empty()) {
            std::cout << "Invalid input. Please enter a non-empty string.\n";
        } else {
            return value;
        }
    }
}

int main() {
    GymManagement gym;
    int choice;

    do {
        std::cout << "1. Register Member\n"
                  << "2. Display All Members\n"
                  << "3. Add Fee to Member\n"
                  << "4. Add Days to Member\n"
                  << "5. Delete Member\n"
                  << "6. Search Member\n"
                  << "7. Update Member Information\n"
                  << "8. Exit\n"
                  << "Enter your choice: ";
        choice = getValidPositiveInt("");

        std::string name, gender;
        int age, days;
        double amount;

        switch (choice) {
        case 1:
            name = getValidString("Enter name: ");
            age = getValidPositiveInt("Enter age: ");
            gender = getValidString("Enter gender: ");
            amount = getValidPositiveDouble("Enter fee paid: ");
            days = getValidPositiveInt("Enter total days: ");
            gym.registerMember(name, age, gender, amount, days);
            break;
        case 2:
            gym.displayAllMembers();
            break;
        case 3:
            name = getValidString("Enter name: ");
            amount = getValidPositiveDouble("Enter amount to add: ");
            gym.addFeeToMember(name, amount);
            break;
        case 4:
            name = getValidString("Enter name: ");
            days = getValidPositiveInt("Enter days to add: ");
            gym.addDaysToMember(name, days);
            break;
        case 5:
            name = getValidString("Enter name: ");
            gym.deleteMember(name);
            break;
        case 6:
            name = getValidString("Enter name: ");
            gym.searchMember(name);
            break;
        case 7:
            name = getValidString("Enter name: ");
            age = getValidPositiveInt("Enter new age: ");
            gender = getValidString("Enter new gender: ");
            gym.updateMemberInfo(name, age, gender);
            break;
        case 8:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 8);

    return 0;
}
