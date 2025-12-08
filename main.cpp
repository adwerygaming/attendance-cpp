#include <iostream>
#include <array>

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
        entry.nim
        time_t
    };
    return true;
}

// Read
// get all attendance on the list
array<AttendanceEntry, attendanceMaxSize> GetAttendance() {
    return attendanceList;
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

}