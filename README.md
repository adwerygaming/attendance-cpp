<div align="center">
    <h1>Simple Attendance System</h1>
    <p>A simple Command Line Interface (CLI) attendance system written in C++</p>
</div>

---

## Overview

This project is a simple attendance management system built using C++.  
It runs in a terminal (CLI) environment and allows users to:

- Record student attendance using a student ID (NIM)
- Prevent duplicate attendance entries
- Cancel or remove attendance records
- Display attendance data along with timestamps

The system is designed for learning purposes and demonstrates the use of arrays, structures, functions, and basic input validation in C++.

## Platform Compatibility

This repository contains **two source files** with the same system logic but different implementations for the delay function (`Sleep`), depending on the operating system.

### Files

- `main-windows.cpp`  
  Uses `Sleep()` from the `<windows.h>` library.

- `main-linux.cpp`  
  Uses `std::this_thread::sleep_for(std::chrono::milliseconds(ms))` from the C++ standard library.

Aside from the delay implementation, **both files are functionally identical**.

## Features

- CLI-based interactive menu
- Attendance recording based on valid student data
- Duplicate attendance prevention
- Attendance cancellation with confirmation
- Automatic timestamp generation
- Simple and structured program flow

## Program Structure

The system is divided into several logical parts:

- **Data Structures**
  - `AttendanceCreate` for valid student data
  - `AttendanceEntry` for attendance rec

## How to Compile and Run

> [!NOTE]
> Make sure you are using a compiler that supports C++11 or newer.

### Windows

```bash
g++ main-windows.cpp -o attendance.exe && ./attendance.exe
```

### Linux
```bash
g++ main-linux.cpp -o attendance && ./attendance
```
