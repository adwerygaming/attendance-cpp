#include <iostream>
#include <array>
#include <chrono>

#include "../types/AttendanceTypes.h"
using namespace std;

const int maxEntryLength = 32;
array<AttendanceEntry, maxEntryLength> attendanceList;
int attendanceEntryLength = 0;

bool AddEntry(AttendanceEntry entry) {
    if (attendanceEntryLength > attendanceList.size()) {
        return false;
    }

    // auto assign timestamp for each entry
    auto now = chrono::system_clock::now();
    entry.timestamp = now::to_time_t(now);
    attendanceList[attendanceEntryLength] = entry;
    attendanceEntryLength++;

    return true;
}

bool RemoveEntry(int index) {
    attendanceList[index] = {};

    return true;
}

array<AttendanceEntry, maxEntryLength> GetAllEntry() {
    if (attendanceEntryLength == 0) {
        return {};
    }

    return attendanceList;
}