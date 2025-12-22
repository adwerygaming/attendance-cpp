#include <iostream>
#include <array>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <thread>
#include <string>

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

// Helper functions //

void clearConsole() {
    // system("clear");
    cout << "\033[2J\033[1;1H";
    // cout << endl;
}

void sleep(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}

// Back-end //

// Adding Attendance Entry to the Attendance List
bool AddEntry(AttendanceCreate entry) {
    // Cek jika jumlah list absensi sudah penuh, jika iya maka tolak dengan true
    if (attendanceCount > attendanceMaxSize) {
        return false;
    }

    // Jika entry object NIM itu ada, maka tambahkan ke list absensi.
    if (!entry.nim.empty()) {
        attendanceList[attendanceCount] = {
            entry.nim,
            entry.name,
            time(nullptr)
        };

        attendanceCount++;

        // Berikan nilai balik (return value) true
        return true;
    } else {
        // Print error jika objek entry tidak mempunyai NIM
        cout << "ERROR: Entry tidak mempunyai NIM." << endl;
        return false;
    }
}

// Print all attended students from the lists.
void GetEntries() {
    for (int i = 0; i < attendanceCount; i++) {
        AttendanceEntry entry = attendanceList[i];
        tm* tm = localtime(&entry.timestamp);

        sleep(30);
        cout << i + 1 << ")" << " | " << entry.name << " | " << entry.nim
             << " | " << put_time(tm, "%H:%M:%S") << endl;
    }
}

// Get attended student entry by index
AttendanceEntry GetEntryByIndex(int index) {
    return attendanceList[index - 1];
}

// Remove attended student entry from the list
AttendanceEntry RemoveEntry(int index1based) {
    int idx = index1based - 1;

    // safety check
    if (idx < 0 || idx >= attendanceCount) {
        return {};
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

// Function for taking input for inputing NIM.
string GetNIMInput() {
    string nim;
    cout << "Masukkan NIM: ";
    getline(cin, nim);

    return nim;
}

// Front-end //

// Function for adding student entry to the attendance list.
void AddAttendance() {
    clearConsole();
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

    // looping through validMahasiswa list, to verify if the entered NIM is valid or not.
    for (int i = 0; i < validMahasiswa.size(); ++i) {
        AttendanceCreate item = validMahasiswa[i];

        // condition to check if entered NIM is on the valid list or not.
        if (nim == item.nim) {
            // check if entered NIM is already on the list.
            // checking from index 0 to end of the list, if any entered NIM is already on the list or not.
            // if yes, this variable will became true.
            bool alreadyExists = any_of(attendanceList.begin(), attendanceList.end(),
                [&](const AttendanceEntry& e) {
                    return e.nim == nim;
                }
            );

            if (alreadyExists) {
                cout << "Mahasiswa sudah ada di dalam daftar presensi. Membatalkan menambahkan ke daftar kehadiran." << endl;
                sleep(3000);
                return;
            }

            bool res = AddEntry(item);

            if (res == true) {
                cout << "Berhasil menambahkan " << item.name << " ke daftar kehadiran." << endl;
            } else {
                cout << "Gagal menambahkan ke daftar absensi." << endl;
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

// Function for removing attendance.
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

    AttendanceEntry check = GetEntryByIndex(opt);

    if (!check.nim.empty()) {
        clearConsole();
        cout << "Apakah anda yakin ingin menggagalkan presensi " << check.name << " (" << check.nim << ")? (y/n): ";
        string answer;
        getline(cin, answer);

        while (answer.empty()) {
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

// Fungsi inti C++
int main() {
    // debug prefill attendance
    for (int i = 0; attendanceCount < 3; i++) {
        AddEntry(validMahasiswa[i]);
    }
    
    // Menggunakan while loop, karena ...

    while (true) {
        clearConsole();
        // why there is 2 datatypes for menu opt?
        // bcs cin sets a "\n" buffer for next getLine on add attendance functions
        // so we use string first then convert to int and remove the \n buffer

        int opt;
        string line;

        cout << "Sistem Presensi Simpel Berbasis CLI" << endl;
        cout << endl;

        // Print daftar kehadiran saat ini
        cout << "Daftar Kehadiran: " << endl;
        
        for (int i = 0; i < attendanceCount; i++) {
            AttendanceEntry entry = attendanceList[i];
            tm* tm = localtime(&entry.timestamp);

            sleep(30);2
            cout << i + 1 << ")" << " | " << entry.nim << " | " << entry.name
                << " | " << put_time(tm, "%H:%M:%S") << endl;
        }

        cout << endl;
        cout << "(" << attendanceCount << " mahasiswa hadir" << ")" << endl;

        // Tampilkan menu
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
            // Opsi untuk menambahkan presensi
            AddAttendance();
        } else if (opt == 2) {
            // Opsi untuk mengagalkan presensi
            RemoveAttendance();
        } else if (opt == 0) {
            // Opsi untuk keluar dari loop (program)
            cout << "Dari sesi ini, ada " << attendanceCount << " mahasiswa yang hadir." << endl;
            break;
        }

        cout << endl;
    }

    return 0;
}