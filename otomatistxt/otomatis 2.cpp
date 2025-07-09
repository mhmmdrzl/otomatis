#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX = 100;

struct Barang {
    string kode;
    string nama;
    int jumlah;
    int harga;
    int total;
};

Barang data[MAX];
int totalBarang = 0;

// Buat data awal otomatis (jika file belum ada)
void buatDataOtomatis(string namaFile) {
    ofstream file(namaFile.c_str());
    file << "B001 Sabun 3 10000\n";
    file << "B002 Sikat 2 11000\n";
    file << "B003 Pasta 4 3000\n";
    file << "B004 Shampoo 1 12000\n";
    file.close();
    cout << "?? File " << namaFile << " berhasil dibuat otomatis.\n";
}

// Baca dari file txt
void loadData(string namaFile) {
    ifstream file(namaFile.c_str());

    if (!file) {
        cout << "?? File tidak ditemukan. Membuat file baru...\n";
        buatDataOtomatis(namaFile);
        file.open(namaFile.c_str());
    }

    while (file >> data[totalBarang].kode >> data[totalBarang].nama
                >> data[totalBarang].jumlah >> data[totalBarang].harga) {
        data[totalBarang].total = data[totalBarang].jumlah * data[totalBarang].harga;
        totalBarang++;
    }

    file.close();
}

// Tampilkan data
void tampilkanData() {
    cout << left << setw(8) << "Kode" << setw(12) << "Nama"
         << setw(8) << "Jumlah" << setw(10) << "Harga" << setw(10) << "Total\n";
    for (int i = 0; i < totalBarang; i++) {
        cout << left << setw(8) << data[i].kode
             << setw(12) << data[i].nama
             << setw(8) << data[i].jumlah
             << setw(10) << data[i].harga
             << setw(10) << data[i].total << endl;
    }
}

// Sorting harga
void sortHarga(bool ascending) {
    for (int i = 0; i < totalBarang - 1; i++) {
        for (int j = 0; j < totalBarang - i - 1; j++) {
            if ((ascending && data[j].harga > data[j + 1].harga) ||
                (!ascending && data[j].harga < data[j + 1].harga)) {
                swap(data[j], data[j + 1]);
            }
        }
    }
}

// Searching kode
void cariBarang(string kodeCari) {
    bool ketemu = false;
    for (int i = 0; i < totalBarang; i++) {
        if (data[i].kode == kodeCari) {
            cout << "\n? Barang ditemukan:\n";
            cout << "Kode   : " << data[i].kode << endl;
            cout << "Nama   : " << data[i].nama << endl;
            cout << "Jumlah : " << data[i].jumlah << endl;
            cout << "Harga  : " << data[i].harga << endl;
            cout << "Total  : " << data[i].total << endl;
            ketemu = true;
            break;
        }
    }

    if (!ketemu) {
        cout << "? Barang dengan kode " << kodeCari << " tidak ditemukan.\n";
    }
}

// Simpan data hasil sort
void simpanKeFile(string namaFile) {
    ofstream file(namaFile.c_str());
    for (int i = 0; i < totalBarang; i++) {
        file << data[i].kode << " "
             << data[i].nama << " "
             << data[i].jumlah << " "
             << data[i].harga << "\n";
    }
    file.close();
    cout << "?? Data berhasil disimpan ke file " << namaFile << "\n";
}

// Menu utama
int main() {
    string fileAwal = "TransaksiHarian.txt";
    loadData(fileAwal);

    int pilihan;
    string kode;

    do {
        cout << "\n=== MENU TRANSAKSI TOKO ===\n";
        cout << "1. Tampilkan Data\n";
        cout << "2. Sorting Harga (Ascending)\n";
        cout << "3. Sorting Harga (Descending)\n";
        cout << "4. Cari Barang (Kode)\n";
        cout << "5. Simpan ke File Hasil Sort\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: tampilkanData(); break;
            case 2: sortHarga(true); cout << "? Diurutkan dari murah ke mahal.\n"; break;
            case 3: sortHarga(false); cout << "? Diurutkan dari mahal ke murah.\n"; break;
            case 4: cout << "Masukkan kode barang: "; cin >> kode; cariBarang(kode); break;
            case 5: simpanKeFile("TransaksiHarian-HasilSort.txt"); break;
            case 0: cout << "?? Keluar dari program...\n"; break;
            default: cout << "? Pilihan tidak valid!\n";
        }

    } while (pilihan != 0);

    return 0;
}

