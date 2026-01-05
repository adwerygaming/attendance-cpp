#include <iostream>

using namespace std;

double nUTS, nUAS, nTugas, nAkhir;
char nilaiHuruf;
string grade;

float pTugas = 0.20;
float pUTS = 0.30;
float pUAS = 0.50;

int main() {
    cout << "25.12.3654 - Dhevan Adhitya Prasetyo\n" << endl;
    cout << "Masukkan Nilai UTS: ";
    cin >> nUTS;
    cout << "Masukkan Nilai UAS: ";
    cin >> nUAS;
    cout << "Masukkan Nilai Tugas: ";
    cin >> nTugas;

    cout << endl;
    nAkhir = (nTugas * pTugas) + (nUTS * pUTS) + (nUAS * pUAS);
    cout << "Nilai Akhir: " << nAkhir << endl;

    if (nAkhir >= 81) {
        nilaiHuruf = 'A';
        grade = "Sangat Memuaskan";
    } else if (nAkhir >= 61) {
        nilaiHuruf = 'B';
        grade = "Memuaskan";
    } else if (nAkhir >= 41) {
        nilaiHuruf = 'C';
        grade = "Cukup Memuaskan";
    } else if (nAkhir >= 21) {
        nilaiHuruf = 'D';
        grade = "Kurang Memuaskan";
    } else {
        nilaiHuruf = 'E';
        grade = "Sangat Kurang Memuaskan";
    }

    cout << "Nilai Huruf: " << nilaiHuruf << endl;
    cout << "Predikat: " << grade << endl;
    return 0;
}