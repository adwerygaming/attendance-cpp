#include <iostream>
#include <array>
#include "../types/AttendanceTypes.h"
using namespace std;

const int maxEntryLength = 32;
array<AttendanceEntry, maxEntryLength> attendanceList;
int attendanceEntryLength = 0;

bool AddEntry(AttendanceEntry entry) {
    if (attendanceEntryLength > attendanceList.size()) {
        return false;
    }

    attendanceList[attendanceEntryLength] = entry;
    attendanceEntryLength++;

    return true;
}

bool RemoveEntry(int index) {
    attendanceList[index] = {};

    return true;
}

array<AttendanceEntry, maxEntryLength> GetAllData() {
    if (attendanceEntryLength == 0) {
        return {};
    }

    return attendanceList;
}