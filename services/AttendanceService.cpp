#include <iostream>
#include <array>
#include "AttendanceService.h"
#include "../types/AttendanceTypes.h"
using namespace std;

const int maxEntryLength = 32;
array<AttendanceEntry, maxEntryLength> attendanceList;

bool AddEntry(AttendanceEntry entry) {
    if (attendanceList.size() > maxEntryLength) {
        return false;
    }

    attendanceList.fill(entry);

    return true;
}

bool RemoveEntry(int index) {
    attendanceList.
}