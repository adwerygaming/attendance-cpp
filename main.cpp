#include <iostream>
#include <array>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <thread>

#include "./types/AttendanceTypes.h"
using namespace std;

// declarations
const int attendanceMaxSize = 64;
array<AttendanceEntry, attendanceMaxSize> attendanceList;
int attendanceCount = 0;

array<AttendanceCreate, attendanceMaxSize> validMahasiswa = {
    AttendanceCreate{"25.12.3654", "Devan Aditiya"},
    AttendanceCreate{"25.12.3648", "Kenny Sopiyanti"},
    AttendanceCreate{"25.12.3609", "Nur Dwi Cahyo"},
};

void clearConsole() {
    // system("clear");
    cout << "\033[2J\033[1;1H";
    // cout << endl;
}

void sleep(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}

// Create
// marking new attendance
bool AddEntry(AttendanceCreate entry) {
    if (attendanceCount > attendanceMaxSize) {
        return false;
    }

    if (!entry.nim.empty()) {
        attendanceList[attendanceCount] = {
            entry.nim,
            entry.name,
            time(nullptr) // returns the current Unix time in seconds since 1970.
        };
        attendanceCount++;
    } else {
        cout << "ERROR: Entry tidak mempunyai NIM." << endl;
        return false;
    }

    return true;
}

// Read
// get all attendance on the list
void GetEntries() {
    for (int i = 0; i < attendanceCount; i++) {
        AttendanceEntry entry = attendanceList[i];
        tm* tm = localtime(&entry.timestamp);

        sleep(30);
        cout << "[" << i + 1 << "]" << " | " << entry.name << " | " << entry.nim
             << " | " << put_time(tm, "%H:%M:%S") << endl;
    }
}

AttendanceEntry GetEntryByIndex(int index) {
    return attendanceList[index - 1];
}

// Update
// update existing attendance or sum like that idk
bool UpdateEntry(AttendanceEntry entry, int index) {
    attendanceList[index] = entry;
    return true;
}

// Delete
// delete existing attendance or sum like that idk
AttendanceEntry RemoveEntry(int index1based) {
    int idx = index1based - 1;

    // safety check
    if (idx < 0 || idx >= attendanceCount) {
        return {}; // just return nothing idk lol
    }

    // store removed item
    AttendanceEntry removed = attendanceList[idx];

    // shift everything down one slot
    for (int i = idx; i < attendanceCount - 1; i++) {
        attendanceList[i] = attendanceList[i + 1];
    }

    // clear last slot (important!)
    attendanceList[attendanceCount - 1] = {};

    attendanceCount--;

    return removed;
}

// splitted bcs due to multiple triggers in 1 same function
string GetNIMInput() {
    string nim;
    cout << "Masukkan NIM: ";
    getline(cin, nim);

    return nim;
}

void AddAttendance() {
    clearConsole();
    // cout << "DEBUG: Adding attendance" << endl;
    bool found = false;

    string nim = GetNIMInput();

    // keep asking for NIM if empty
    while (nim.empty()) {
        nim = GetNIMInput();
    }

    // cout << "DEBUG: NIM entered: " << nim << endl;

    if (nim == "exit") {
        return;
    }

    for (int i = 0; i < validMahasiswa.size(); ++i) {
        AttendanceCreate item = validMahasiswa[i];

        // if (item.name == "Pink Fish") {
        //     cout << item.name << " telah di banned di kelas ini." << endl;
        //     return;
        // }

        // check valid mahasigma
        if (nim == item.nim) {

            // avoid duplicate entry
            bool alreadyExists = any_of(attendanceList.begin(), attendanceList.end(),
                [&](const AttendanceEntry& e) {
                    return e.nim == nim;
                }
            );

            if (alreadyExists) {
                cout << "Mahasiswa ini sudah ada di dalam daftar presensi." << endl;
                sleep(3000);
                return;
            }

            bool res = AddEntry(item);

            if (res) {
                cout << "Berhasil menambahkan " << item.name << " ke daftar kehadiran." << endl;
            }

            found = true;
            break;
        }
    }

    if (found == false) {
        cout << "Tidak ditemukan mahasiswa dengan NIM tersebut di database.." << endl;
        nim = GetNIMInput();
    }

    sleep(3000);
}

void RemoveAttendance() {
    clearConsole();
    if (attendanceCount == 0) {
        cout << "Daftar kehadiran masih kosong, apa yang mau di hapus?" << endl;
        return;
    }

    cout << "Kehadiran: " << endl;
    GetEntries();
    sleep(100);
    cout << endl;
    cout << "(" << attendanceCount << " mahasiswa hadir" << ")" << endl;

    cout << endl;
    cout << "Untuk menggagalkan presensi, masukkan nomor index [int] dari list di atas ini." << endl;
    cout << "Nomor Index yang ingin digagalkan >> ";

    int opt;
    string line;

    getline(cin, line);

    if (line == "exit") {
        return;
    }

    opt = stoi(line);
    // cin >> opt;

    AttendanceEntry check = GetEntryByIndex(opt);

    if (!check.nim.empty()) {
        clearConsole();
        cout << "Apakah anda yakin ingin menggagalkan presensi " << check.name << " (" << check.nim << ")? (y/n): ";
        string answer;
        getline(cin, answer);

        while (answer.empty()) {
            // handle empty input if newline is leftover
            getline(cin, answer);
        }

        char confirm = answer[0];

        if (confirm == 'y' || confirm == 'Y') {
            AttendanceEntry res = RemoveEntry(opt);

            if (!res.name.empty()) {
                cout << "Absensi " << res.name << " (" << res.nim << ") " << "berhasil digagalkan." << endl;
            } else {
                cout << "Gagal menggagalkan presensi." << endl;
            }
        } else {
            cout << "Gagalkan presensi dibatalkan." << endl;
        }
    } else {
        cout << "Index tidak valid." << endl;
    }

    sleep(3000);
}

int main() {
    // dummy pre-load data
    // for (int i = 0; i < validMahasiswa.size(); ++i) {
    //     AttendanceCreate item = validMahasiswa[i];
    //     AddEntry(item);
    // }

    while (true) {
        clearConsole();
        // why there is 2 datatypes for menu opt?
        // bcs cin sets a "\n" buffer for next getLine on add attendance functions
        // so we use string first then convert to int and remove the \n buffer

        int opt;
        string line;
        cout << "Sistem Presensi Simpel Berbasis CLI" << endl;

        cout << endl;
        cout << "Daftar Kehadiran: " << endl;
        GetEntries();
        cout << endl;
        cout << "(" << attendanceCount << " mahasiswa hadir" << ")" << endl;

        // menu
        cout << endl;
        cout << "===== Menu =====" << endl;
        cout << "[1] Lakukan Presensi" << endl;
        cout << "[2] Gagalkan Presensi" << endl;
        cout << "[3] Refresh Data" << endl;
        cout << "[0] Akhiri Sesi" << endl;
        cout << endl;
        cout << "Pilih Opsi >> ";

        getline(cin, line);
        opt = stoi(line);

        if (opt == 1) {
            AddAttendance();
        } else if (opt == 2) {
            RemoveAttendance();
        } else if (opt == 3) {
            // just refresh
            // loops back this progieaming
        } else if (opt == 0) {
            cout << "Dari sesi ini, ada " << attendanceCount << " mahasiswa yang hadir." << endl;
            break;
        }

        cout << endl;
    }

    return 0;
}