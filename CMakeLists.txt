cmake_minimum_required(VERSION 4.0)
project(attendance_cpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(types)

add_executable(attendance_cpp
        services/AttendanceService.cpp
        types/AttendanceTypes.h
        Test.cpp
        services/AttendanceService.h)
