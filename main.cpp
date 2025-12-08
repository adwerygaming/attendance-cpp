#include <iostream>
#include <array>
#include <ctime>
#include <algorithm>
#include <iomanip>

#include "AttendanceTypes.h"
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


void AddAttendance() {
    int opt;
    bool found = false;
    string nim;

    cout << "Enter NIM: ";
    cin >> nim;

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
    }
}

int opt;
int main() {
    while (true) {
        cout << "Attendance Management System" << endl;
        cout << "Current attendance: " << "(" << attendanceCount << " student has attended" << ")" << endl;

        GetAttendance();

        // menu
        cout << "Menu:" << endl;
        cout << "1. Add Attendance" << endl;
        cout << "2. Exit" << endl;
        cout << "Choose an option >> ";
        cin >> opt;

        if (opt == 1) {
            AddAttendance();
        } else if (opt == 2) {
            break;
        }

        cout << endl;
    }

    return 0;
}
