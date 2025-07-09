#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

const int MAX = 100;
string data[MAX][5];
int totalBarang = 0;

// Konversi string ke int
int StringToInt(string s) {
    stringstream ss(s);
    int result;
    ss >> result;
    return result;
}

// Konversi int ke string
string IntToString(int n) {
    stringstream ss;
    ss << n;
    return ss.str();
}

// Buat file jika belum ada
void buatFileAwal(string filename) {
    ifstream cek(filename.c_str());
    if (!cek) {
        ofstream buat(filename.c_str());
        if (buat) {
            buat << "K001 Minyak 2 15000\n";
            buat << "K002 Gula 3 12000\n";
            buat << "K003 Tepung 1 10000\n";
            buat << "K004 Kopi 5 7000\n";
            buat << "K005 Garam 4 4000\n";
            buat.close();
            cout << "?? File '" << filename << "' berhasil dibuat otomatis.\n";
        } else {
            cout << "? Gagal membuat file '" << filename << "'.\n";
            exit(1);
        }
    }
    cek.close();
}

// Hitung total harga per barang
void hitungTotal() {
    for (int i = 0; i < totalBarang; i++) {
        int jumlah = StringToInt(data[i][2]);
        int harga = StringToInt(data[i][3]);
        data[i][4] = IntToString(jumlah * harga);
    }
}

// Tampilkan data
void tampilData() {
    cout << left << setw(10) << "Kode" << setw(15) << "Nama"
         << setw(10) << "Jumlah" << setw(15) << "Harga" << setw(10) << "Total\n";
    cout << "---------------------------------------------------------------\n";
    for (int i = 0; i < totalBarang; i++) {
        for (int j = 0; j < 5; j++)
            cout << setw(15) << data[i][j];
        cout << endl;
    }
}

// Sorting berdasarkan harga
void sortHarga(bool ascending) {
    for (int i = 0; i < totalBarang - 1; i++) {
        for (int j = 0; j < totalBarang - i - 1; j++) {
            int harga1 = StringToInt(data[j][3]);
            int harga2 = StringToInt(data[j + 1][3]);
            if ((ascending && harga1 > harga2) || (!ascending && harga1 < harga2)) {
                for (int k = 0; k < 5; k++)
                    swap(data[j][k], data[j + 1][k]);
            }
        }
    }
}

// Cari berdasarkan kode
void cariKode(string kode) {
    bool ketemu = false;
    for (int i = 0; i < totalBarang; i++) {
        if (data[i][0] == kode) {
            cout << "\n? Barang ditemukan:\n";
            for (int j = 0; j < 5; j++) cout << data[i][j] << " ";
            cout << endl;
            ketemu = true;
            break;
        }
    }
    if (!ketemu)
        cout << "? Barang tidak ditemukan.\n";
}

// Cari barang termurah
void cariTermurah() {
    int idxMin = 0;
    int hargaMin = StringToInt(data[0][3]);
    for (int i = 1; i < totalBarang; i++) {
        int harga = StringToInt(data[i][3]);
        if (harga < hargaMin) {
            hargaMin = harga;
            idxMin = i;
        }
    }
    cout << "\n?? Barang termurah:\n";
    for (int j = 0; j < 5; j++)
        cout << data[idxMin][j] << " ";
    cout << endl;
}

// Hitung total belanja
void totalKeseluruhan() {
    int total = 0;
    for (int i = 0; i < totalBarang; i++)
        total += StringToInt(data[i][4]);
    cout << "\n?? Total Belanja: Rp. " << total << endl;
}

// Simpan ke file hasil sort
void simpanKeFile(string namaFile) {
    ofstream out(namaFile.c_str());
    for (int i = 0; i < totalBarang; i++) {
        for (int j = 0; j < 5; j++)
            out << data[i][j] << (j < 4 ? " " : "\n");
    }
    out.close();
    cout << "?? Data disimpan ke file: " << namaFile << endl;
}

// Load data dari file
void loadData(string filename) {
    ifstream file(filename.c_str());
    while (file >> data[totalBarang][0] >> data[totalBarang][1] >> data[totalBarang][2] >> data[totalBarang][3]) {
        totalBarang++;
    }
    file.close();
    hitungTotal();
}

// MAIN
int main() {
    string namaFile = "NotaBelanja.txt";
    buatFileAwal(namaFile);     // otomatis buat jika belum ada
    loadData(namaFile);         // load isi file

    int pilihan;
    string kode;

    do {
        cout << "\n=== Menu Nota Belanja ===\n";
        cout << "1. Tampilkan Data\n2. Sorting Harga (Ascending)\n3. Sorting Harga (Descending)\n";
        cout << "4. Cari Kode Barang\n5. Cari Barang Termurah\n6. Total Belanja\n7. Simpan ke File\n0. Keluar\n";
        cout << "Pilih: "; cin >> pilihan;

        switch (pilihan) {
            case 1: tampilData(); break;
            case 2: sortHarga(true); cout << "? Diurutkan dari Murah ke Mahal.\n"; break;
            case 3: sortHarga(false); cout << "? Diurutkan dari Mahal ke Murah.\n"; break;
            case 4: cout << "Masukkan kode barang: "; cin >> kode; cariKode(kode); break;
            case 5: cariTermurah(); break;
            case 6: totalKeseluruhan(); break;
            case 7: simpanKeFile("Nota-Belanjaan-HasilSort.txt"); break;
            case 0: cout << "?? Keluar dari program...\n"; break;
            default: cout << "? Pilihan tidak valid!\n";
        }

    } while (pilihan != 0);

    return 0;
}

