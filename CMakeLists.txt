cmake_minimum_required(VERSION 4.0)
project(attendance_cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(types)

add_executable(attendance_cpp
        types/AttendanceTypes.h
        main.cpp
        services/AttendanceService.h
        services/AttendanceService.cpp
        services/AttendanceService.h)
