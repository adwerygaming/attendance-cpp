#include <iostream>

using namespace std;

string input; 
string nama;

int main() {
    cout << "Masukkan Mas / Mba / Dek: ";
    getline(cin, input);
    cout << "Masukkan Nama: ";
    getline(cin, nama);
1
    if (input == "Mas" || input == "mas") {
        cout << "Hai Mas " << nama << " ganteng." << endl;
    } else if (input == "Mba" || input == "mba") {
        cout << "Hai Mba " << nama << " cantik." << endl;
    } else if (input == "Dek" || input == "dek") {
        cout << "Hai Dek " << nama << " sayang" << endl;
    } 
}