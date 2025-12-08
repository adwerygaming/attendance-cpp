#include <iostream>
#include <ctime>
using namespace std;

struct AttendanceEntry {
    string nim;
    string name;
    time_t timestamp;
};

struct AttendanceCreate {
    string nim;
    string name;
};