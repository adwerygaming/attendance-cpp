#include <iostream>
#include <array> // LIBRARY ARRAY
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <thread>
#include <chrono>
#include <string>
#include <windows.h>

using namespace std;

// declarations
// Tipe data untuk menyimpan entry kehadiran
struct AttendanceEntry {
    string nim;
    string name;
    time_t timestamp;
};

// Tipe data untuk nenambahkan entry kehadiran
// Tidak perlu timestamp karena akan di-generate otomatis saat penambahan entry
struct AttendanceCreate {
    string nim;
    string name;
};

const int attendanceMaxSize = 64; // Maksimal ukuran attendanceList

//       TIPE DATA          MAX SIZE       NAMA VARIABEL
array<AttendanceEntry, attendanceMaxSize> attendanceList; // Array untuk menyimpan daftar kehadiran
int attendanceCount = 0; // Jumlah kehadiran array attendanceList

//       TIPE DATA          MAX SIZE        NAMA VARIABEL
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

// Back-end //

// Menambahkan entry ke dalam daftar kehadiran
bool AddEntry(AttendanceCreate entry) {
    // Cek jika jumlah list absensi sudah penuh, jika iya maka tolak dengan true
    if (attendanceCount > attendanceMaxSize) {
        return false;
    }

    // Jika entry object NIM itu ada, maka tambahkan ke list absensi.
    if (!entry.nim.empty()) {
        // Tambahkan entry ke dalam array attendanceList
        attendanceList[attendanceCount] = {
            entry.nim,
            entry.name,
            time(nullptr)
        };

        // Increment attendanceCount, total kehadiran ditambah 1
        attendanceCount++;

        // Berikan nilai balik (return value) true
        return true;
    } else {
        // Print error jika objek entry tidak mempunyai NIM
        cout << "ERROR: Entry tidak mempunyai NIM." << endl;
        return false;
    }
}

// Meng-print hasil daftar kehadiran dari array attendanceList
void GetEntries() {
    // Print daftar kehadiran saat ini
    for (int i = 0; i < attendanceCount; i++) {
        AttendanceEntry entry = attendanceList[i]; // ambil entry ke-i, hanya 1 entry karena berdasarkan index
        tm* tm = localtime(&entry.timestamp); // konversi timestamp ke format waktu lokal

        sleep(30);
        cout << i + 1 << ")" << " | " << entry.name << " | " << entry.nim << " | " << put_time(tm, "%H:%M:%S") << endl;
    }
}

// mengambil 1 data entry berdasarkan index
AttendanceEntry GetEntryByIndex(int index) {
    return attendanceList[index - 1]; // mengurangi 1 untuk menyesuaikan indeks array
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

    if (nim == "exit") {
        return;
    }

    // melakukan perulangan pada daftar validMahasiswa untuk memastikan
    // apakah NIM yang dimasukkan valid atau tidak.
    for (int i = 0; i < validMahasiswa.size(); ++i) {
        AttendanceCreate item = validMahasiswa[i];

        // kondisi untuk mengecek apakah NIM yang dimasukkan
        // ada di dalam daftar NIM yang valid atau tidak.
        if (nim == item.nim) {
            // mengecek apakah NIM yang dimasukkan sudah ada di dalam daftar kehadiran.
            // pengecekan dilakukan dari awal sampai akhir daftar.
            // jika NIM sudah ditemukan, maka variabel ini akan bernilai true.
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