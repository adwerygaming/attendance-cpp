#include <iostream>
#include <array>
#include <ctime>
#include <algorithm>
#include <iomanip>

#include "./types/AttendanceTypes.h"
using namespace std;

// functions
const int attendanceMaxSize = 64;
array<AttendanceEntry, attendanceMaxSize> attendanceList;
int attendanceCount = 0;

array<AttendanceCreate, attendanceMaxSize> validMahasiswa = {
    AttendanceCreate{"25.12.1234", "Alice"},
    AttendanceCreate{"25.12.2345", "Alice 2"},
    AttendanceCreate{"25.12.3213", "Alice 3"},
    AttendanceCreate{"25.12.6654", "Alice 4"},
};

void clearConsole() {
    // system("clear");
    cout << "\033[2J\033[1;1H";
}

// Create
// marking new attendance
bool AddEntry(AttendanceCreate entry) {
    if (attendanceCount > attendanceMaxSize) {
        return false;
    }

    attendanceList[attendanceCount] = {
        entry.nim,
        entry.name,
        time(nullptr) // returns the current Unix time in seconds since 1970.
    };
    attendanceCount++;

    return true;
}

// Read
// get all attendance on the list
void GetAttendance() {
    for (int i = 0; i < attendanceCount; i++) {
        AttendanceEntry entry = attendanceList[i];
        tm* tm = std::localtime(&entry.timestamp);

        cout << "[" << i + 1 << "] " << entry.name << " | " << entry.nim
             << " | " << put_time(tm, "%a %b %e %H:%M:%S %Y") << endl;
    }
}

// Update
// update existing attendance or sum like that idk
bool UpdateAttendance(AttendanceEntry entry, int index) {
    attendanceList[index] = entry;
    return true;
}

// Delete
// delete existing attendance or sum like that idk
bool DeleteAttendance(int index) {
    attendanceList[index] = {};
    attendanceCount--;
    return true;
}

// splitted bcs to multiple triggers in 1 same function
string GetNIMInput() {
    string nim;
    cout << "Enter NIM: ";
    getline(cin, nim);

    return nim;
}

void AddAttendance() {
    clearConsole();
    cout << "DEBUG: Adding attendance" << endl;
    bool found = false;

    string nim = GetNIMInput();

    // keep asking for NIM if empty
    while (nim.empty()) {
        nim = GetNIMInput();
    }

    cout << "DEBUG: NIM entered: " << nim << endl;

    for (int i = 0; i < validMahasiswa.size(); ++i) {
        AttendanceCreate item = validMahasiswa[i];
        if (nim == item.nim) {
            // avoid duplicate entry
            bool alreadyExists = any_of(attendanceList.begin(), attendanceList.end(),
                [&](const AttendanceEntry& e) {
                    return e.nim == nim;
                }
            );

            if (alreadyExists) {
                cout << "Mahasiswa already marked attendance." << endl;
                return;
            }

            cout << "Added " << item.name << " to attendance list." << endl;
            bool res = AddEntry(item);

            if (res) {
                cout << "add ok" << endl;
            }

            found = true;
            break;
        }
    }

    if (found == false) {
        cout << "Could find mahasiswa on database." << endl;
        nim = GetNIMInput();
    }
}

void RemoveAttendance() {
    cout << "Current attendance: " << "(" << attendanceCount << " student has attended" << ")" << endl;
    GetAttendance();
}

int main() {
    while (true) {
        clearConsole();
        // why there is 2 datatypes for menu opt?
        // bcs cin sets a "\n" buffer for next getLine on add attendance functions
        // so we use string first then convert to int and remove the \n buffer

        int opt;
        string line;
        cout << "Attendance Management System" << endl;
        cout << "Current attendance: " << "(" << attendanceCount << " student has attended" << ")" << endl;

        GetAttendance();

        // menu
        cout << endl;
        cout << "Menu:" << endl;
        cout << "[1] Add Attendance" << endl;
        cout << "[2] Remove Attendance" << endl;
        cout << "[3] Refresh" << endl;
        cout << "[0] Exit" << endl;
        cout << "Choose an option >> ";
        getline(cin, line);

        opt = stoi(line);

        if (opt == 1) {
            AddAttendance();
        } else if (opt == 2) {
            RemoveAttendance();
        } else if (opt == 3) {
            // just refresh
            // loops back this progieaming
        } else if (opt == 0) {
            cout << "Have a nice day!" << endl;
            break;
        }

        cout << endl;
    }

    return 0;
}
