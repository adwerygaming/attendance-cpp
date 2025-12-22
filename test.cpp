#include <iostream>

using namespace std;

bool apakahGenap(int angka) {
    if (angka % 2 == 0) {
        return true;
    } else {
        return false;
    }
}

string Pesan() {
    return "Halo, selamat belajar C++";
}

int tambah(int a, int b) {
    return a + b;
}

int main() {
    int nomor_pertama = 6;
    int nomor_kedua = 7;
    int hasil = tambah(nomor_pertama, nomor_kedua);
    cout << "Hasil penjumlahan " << nomor_pertama << " + " << nomor_kedua << " = " << hasil << endl;
    return 0;
}
