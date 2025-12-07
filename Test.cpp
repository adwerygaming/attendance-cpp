#include <iostream>
#include "./services/AttendanceService.h"
using namespace std;

int main() {
    // get entry
    AddEntry({"25.12.0000", "MasDepan"});
    auto list = GetAllEntry();

    for (int i = 0; i < list.size(); i++) {
        cout << "NIM: " << list[i].nim << ", Name: " << list[i].name << ", Timestamp: " << ctime(&list[i].timestamp);
    }

    return 0;
}
