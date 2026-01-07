#include <iostream>
#include <array>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <string>
#include <windows.h>

using namespace std;

// deklarasi
struct AttendanceEntry {
    string nim;
    string name;
    time_t timestamp;
};

struct AttendanceCreate {
    string nim;
    string name;
};

const int attendanceMaxSize = 64; 

array<AttendanceEntry, attendanceMaxSize> attendanceList;
int attendanceCount = 0;

array<AttendanceCreate, attendanceMaxSize> validMahasiswa = {
    AttendanceCreate{"25.12.3654", "Devan Aditiya"},
    AttendanceCreate{"25.12.3648", "Kenny Sopiyanti"},
    AttendanceCreate{"25.12.3609", "Nur Dwi Cahyo"},
};

// Fungsi bantuan //

// fungsi untuk membersihkan console
void clearConsole() {
    system("clear");
}

// Backend //

// Menambahkan entry ke dalam daftar kehadiran
bool AddEntry(AttendanceCreate entry) {
    if (attendanceCount > attendanceMaxSize) {
        return false;
    }

    if (!entry.nim.empty()) {
        attendanceList[attendanceCount] = {
            entry.nim,
            entry.name,
            time(nullptr)
        };

        attendanceCount++;

        return true;
    } else {
        cout << "ERROR: Entry tidak mempunyai NIM." << endl;
        return false;
    }
}

// Meng-print hasil daftar kehadiran dari array attendanceList
void GetEntries() {
    for (int i = 0; i < attendanceCount; i++) {
        AttendanceEntry entry = attendanceList[i];
        tm* tm = localtime(&entry.timestamp);

        Sleep(30); 
        cout << i + 1 << ")" << " | " << entry.name << " | " << entry.nim << " | " << put_time(tm, "%H:%M:%S") << endl;
    }
}

// mengambil 1 data entry berdasarkan index
AttendanceEntry GetEntryByIndex(int index) {
    return attendanceList[index - 1];
}

// Menghapus entry mahasiswa dari daftar kehadiran
AttendanceEntry RemoveEntry(int index) {
    int idx = index - 1;

    if (idx < 0 || idx >= attendanceCount) {
        return {};
    }

    AttendanceEntry removed = attendanceList[idx];

    for (int i = idx; i < attendanceCount - 1; i++) {
        attendanceList[i] = attendanceList[i + 1];
    }

    attendanceList[attendanceCount - 1] = {};

    attendanceCount--;

    return removed;
}

// Fungsi untuk mengambil input NIM dari user
string GetNIMInput() {
    string nim;
    cout << "Masukkan NIM: ";
    getline(cin, nim);

    return nim;
}

// Frontend //
// Untuk menghandle interaksi user di console

// Fungsi untuk menambahkan presensi ke dalam daftar kehadiran
void AddAttendance() {
    clearConsole();

    bool found = false;

    string nim = GetNIMInput();

    while (nim.empty()) {
        nim = GetNIMInput();
    }

    if (nim == "exit") {
        return;
    }

    for (int i = 0; i < validMahasiswa.size(); ++i) {
        AttendanceCreate item = validMahasiswa[i];

        if (nim == item.nim) {
            bool alreadyExists = any_of(attendanceList.begin(), attendanceList.end(),
                [&](const AttendanceEntry& e) {
                    return e.nim == nim;
                }
            );

            if (alreadyExists == true) {
                cout << "Mahasiswa sudah ada di dalam daftar presensi. Membatalkan menambahkan ke daftar kehadiran." << endl;
                Sleep(3000);
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

    Sleep(3000);
}

// Fungsi untuk menggagalkan presensi
void RemoveAttendance() {
    clearConsole();
    if (attendanceCount == 0) {
        cout << "Daftar kehadiran masih kosong, apa yang mau di hapus?" << endl;
        return;
    }

    cout << "Kehadiran: " << endl;
    GetEntries();
    Sleep(100);
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

    Sleep(3000);
}

// Fungsi inti C++
int main() {
    // for (int i = 0; attendanceCount < 3; i++) {
    //     AddEntry(validMahasiswa[i]);
    // }

    while (true) {
        clearConsole();

        int opt;
        string line;

        cout << "Sistem Presensi Simpel Berbasis CLI" << endl;
        cout << endl;

        // Tampilkan daftar kehadiran saat ini
        cout << "Daftar Kehadiran: " << endl;
        GetEntries();
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