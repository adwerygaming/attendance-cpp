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

// TIPE DATA  NAMA FUNGSI    PARAMETER
//              TIPE DATA   NAMA VARIABEL
bool AddEntry(AttendanceCreate entry) {
    // Cek jika jumlah list absensi sudah penuh, jika iya maka tolak dengan true
    if (attendanceCount > attendanceMaxSize) {
        // tolak
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

/**
 * 
 * PRINT SATU PER SATU ENTRY DI DARI ARRAY attendanceList
 * 
 * ARRAY attendanceList SEPERTI INI
 * [
 *  0 { nim = "25.12.3654", name = "Devan Aditiya", timestamp = 1696543200 }, <---- ENTRY 1
 *  1 { nim = "25.12.3654", name = "Devan Aditiya", timestamp = 1696543200 }, <---- ENTRY 2
 *  2 { nim = "25.12.3654", name = "Devan Aditiya", timestamp = 1696543200 }, <---- ENTRY 3
 * ]
 * 
 * INDEKS SELALU MULAI DARI 0
 * BISA DIBILANG NOMOR URUT ARRAY
 */

// Meng-print hasil daftar kehadiran dari array attendanceList
void GetEntries() {
    // Print daftar kehadiran saat ini
    for (int i = 0; i < attendanceCount; i++) {
        AttendanceEntry entry = attendanceList[i]; // ambil entry ke-i, hanya 1 entry karena berdasarkan index
        /**
         * {
         *  nim = "25.12.3654",
         *  name = "Devan Aditiya",
         * }
         */
        tm* tm = localtime(&entry.timestamp); // konversi timestamp ke format waktu lokal

        Sleep(30); 
        cout << i + 1 << ")" << " | " << entry.name << " | " << entry.nim << " | " << put_time(tm, "%H:%M:%S") << endl;
    }
}

/**
 * user milih = 2
 * parameter index = 2 - 1
 * index yang dipakai = 1
 * 
 * ARRAY attendanceList SEPERTI INI
 * [
 *  0 { nim = "25.12.3654", name = "Devan Aditiya", timestamp = 1696543200 }, <---- ENTRY 1
 *  1 { nim = "25.12.3654", name = "Devan Aditiya", timestamp = 1696543200 }, <---- ENTRY 2
 *  2 { nim = "25.12.3654", name = "Devan Aditiya", timestamp = 1696543200 }, <---- ENTRY 3
 * ]
 * 
 * INDEKS SELALU MULAI DARI 0
 * BISA DIBILANG NOMOR URUT ARRAY
 */

// mengambil 1 data entry berdasarkan index
// TIPE DATA     NAMA FUNGSI    PARAMETER
AttendanceEntry GetEntryByIndex(int index) {
    return attendanceList[index - 1]; // mengurangi 1 untuk menyesuaikan indeks array
}

// Menghapus entry mahasiswa dari daftar kehadiran
// TIPE DATA     NAMA FUNGSI    PARAMETER
AttendanceEntry RemoveEntry(int index) {
    int idx = index - 1; // mengurangi 1 untuk menyesuaikan indeks array

    // cek jika index tidak valid atau index di luar attendanceMaxSize
    if (idx < 0 || idx >= attendanceCount) {
        return {};
    }

    // menyimpan item yang dihapus
    AttendanceEntry removed = attendanceList[idx];

    // menggeser semua item setelah index ke kiri satu slot
    for (int i = idx; i < attendanceCount - 1; i++) {
        attendanceList[i] = attendanceList[i + 1];
    }

    // mengosongkan slot terakhir
    attendanceList[attendanceCount - 1] = {};

    // mengurangi jumlah kehadiran, karena sudah dihapus satu entry
    attendanceCount--;

    return removed;
}

// Fungsi untuk mengambil input NIM dari user
// dipanggil di fungsi AddAttendance()
// mengambil promt lalu mengembalikan hasil dari inputan
string GetNIMInput() {
    string nim;
    cout << "Masukkan NIM: ";
    getline(cin, nim);

    return nim;
}

// Front-end //
// Untuk menghandle interaksi user di console

// Fungsi untuk menambahkan presensi ke dalam daftar kehadiran
//    NAMA FUNGSI
void AddAttendance() {
    // memanggil fungsi untuk membersihkan layar console
    clearConsole();

    // bool = true / false
    bool found = false;

    // minta nim dari user
    string nim = GetNIMInput();

    // tetap minta nim jika inputan kosong
    while (nim.empty()) {
        nim = GetNIMInput();
    }

    // nim ada value

    // kondisi untuk keluar dari fungsi jika user memasukkan "exit"
    if (nim == "exit") {
        return;
    }

    // melakukan perulangan pada daftar validMahasiswa untuk memastikan
    // apakah NIM yang dimasukkan valid atau tidak.
    for (int i = 0; i < validMahasiswa.size(); ++i) {
        AttendanceCreate item = validMahasiswa[i];

        // kondisi untuk mengecek apakah NIM yang dimasukkan
        // ada di dalam daftar NIM yang valid atau tidak.


        /*
            [
                25.12.1654 
                25.12.3648 
                25.12.3609 
            ]
        */

        if (nim == item.nim) {
            // mengecek apakah NIM yang dimasukkan sudah ada di dalam daftar kehadiran.
            // pengecekan dilakukan dari awal sampai akhir daftar.
            // jika NIM sudah ditemukan, maka variabel ini akan bernilai true.
            bool alreadyExists = any_of(attendanceList.begin(), attendanceList.end(),
                [&](const AttendanceEntry& e) {
                    return e.nim == nim;
                }
            );

            if (alreadyExists == true) {
                cout << "Mahasiswa sudah ada di dalam daftar presensi. Membatalkan menambahkan ke daftar kehadiran." << endl;
                Sleep(3000);
                return; // balik ke menu utama

            }

            /*
                item = { 
                   nim = "25.12.3654",
                   name = "Devan Aditiya",
                }
            */

            bool res = AddEntry(item);

            // res = response

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

// Function for removing attendance.
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
    // prefill attendance
    // for (int i = 0; attendanceCount < 3; i++) {
    //     AddEntry(validMahasiswa[i]);
    // }

    while (true) {
        clearConsole();

        int opt;
        string line;

        cout << "Sistem Presensi Simpel Berbasis CLI" << endl;
        cout << endl;

        // Print daftar kehadiran saat ini
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