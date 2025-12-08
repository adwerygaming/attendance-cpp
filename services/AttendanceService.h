// services/AttendanceService.h
#pragma once

#include <array>
#include "AttendanceTypes.h"

constexpr int attendanceMaxSize = 64;

extern std::array<AttendanceEntry, attendanceMaxSize> attendanceList;
extern int attendanceCount;

// Create
bool AddEntry(AttendanceEntry entry);

// Read
std::array<AttendanceEntry, attendanceMaxSize> GetAttendance();

// Update
bool UpdateAttendance(AttendanceEntry entry, int index);

// Delete
bool DeleteAttendance(int index);
