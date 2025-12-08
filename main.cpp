#include <iostream>
#include "services//AttendanceService.h"
using namespace std;

int main() {
    cout << "Attendance test" << endl;

    AddEntry({ "25.12.1111", "john doe", time() });
    return 0;
}