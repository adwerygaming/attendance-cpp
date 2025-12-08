#include <iostream>
#include <array>
#include <ctime>

#include "AttendanceTypes.h"
using namespace std;

// functions
const int attendanceMaxSize = 64;
array<AttendanceEntry, attendanceMaxSize> attendanceList;
int attendanceCount = 0;

// Create
// marking new attendance
bool AddEntry(AttendanceCreate entry) {
    if (attendanceCount > attendanceMaxSize) {
        return false;
    }

    attendanceList[attendanceCount++] = {
        entry.name,
        entry.nim,
        time(nullptr) // returns the current Unix time in seconds since 1970.
    };

    return true;
}

// Read
// get all attendance on the list
void GetAttendance() {
    for (int i = 0; i < attendanceCount; i++) {
        cout << "[" << i << "] " << "Name: " << attendanceList[i].name << ", NIM: " << attendanceList[i].nim
             << ", Timestamp: " << ctime(&attendanceList[i].timestamp);
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

int main() {
    cout << "Attendance Management System" << endl;
    cout << "Current attendance: " << "(" << attendanceCount << "student has attended" << ")" << endl;

    GetAttendance();
}