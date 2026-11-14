#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <iomanip>
#include <sstream>

using namespace std;

const int BATAS_MINIMUM = 5;

struct Barang {
    string kode, nama, jenis;
    int stok = 0;
    string kondisi, lokasi;
};

struct Permintaan {
    string namaBarang, jenis;
    int jumlah = 0;
    string peminta;
    int status = 0;
    string noSPB;
};

struct Penghapusan {
    string kodeBarang, namaBarang, alasan;
    int jumlah = 0, status = 0;
};

vector<Barang> daftar;
vector<Permintaan> permintaan;
vector<Penghapusan> penghapusan;

const string FILE_DATA = "inventaris_data.txt";

string statusMinta(int status) {
    const string statusNama[] = {
        "Menunggu persetujuan", "Disetujui", "Ditolak",
        "Barang dikirim", "Barang diterima", "Retur"
    };
    return (status >= 0 && status <= 5) ? statusNama[status] : "Status tidak dikenal";
}

void BacaSemua() {
    ifstream file(FILE_DATA);
    if (!file) return;

    daftar.clear();
    permintaan.clear();
    penghapusan.clear();

    string bagian;
    size_t jumlah;

    while (file >> bagian >> jumlah) {
        if (bagian == "BARANG") {
            for (size_t i = 0; i < jumlah; ++i) {
                Barang b;
                if (!(file >> quoted(b.kode) >> quoted(b.nama) >> quoted(b.jenis)
                          >> b.stok >> quoted(b.kondisi) >> quoted(b.lokasi))) return;
                daftar.push_back(b);
            }
        } else if (bagian == "PERMINTAAN") {

            for (size_t i = 0; i < jumlah; ++i) {
                Permintaan p;
                if (!(file >> quoted(p.namaBarang) >> quoted(p.jenis) >> p.jumlah
                          >> quoted(p.peminta) >> p.status >> quoted(p.noSPB))) return;
                permintaan.push_back(p);
            }
        } else if (bagian == "PENGHAPUSAN") {
            for (size_t i = 0; i < jumlah; ++i) {
                Penghapusan h;
                if (!(file >> quoted(h.kodeBarang) >> quoted(h.namaBarang)
                          >> quoted(h.alasan) >> h.jumlah >> h.status)) return;
                penghapusan.push_back(h);
            }
        } else {
            cerr << "Bagian data tidak dikenal: " << bagian << '\n';
            return;
        }
    }
}

void SimpanSemua() {
    ofstream file(FILE_DATA);
    if (!file) {
        cerr << "Gagal menyimpan data ke " << FILE_DATA << '\n';
        return;
    }

    file << "BARANG " << daftar.size() << '\n';
    for (const auto &b : daftar)
        file << quoted(b.kode) << ' ' << quoted(b.nama) << ' '
             << quoted(b.jenis) << ' ' << b.stok << ' '
             << quoted(b.kondisi) << ' ' << quoted(b.lokasi) << '\n';

    file << "PERMINTAAN " << permintaan.size() << '\n';
    for (const auto &p : permintaan)
        file << quoted(p.namaBarang) << ' ' << quoted(p.jenis) << ' '
             << p.jumlah << ' ' << quoted(p.peminta) << ' '
             << p.status << ' ' << quoted(p.noSPB) << '\n';

    file << "PENGHAPUSAN " << penghapusan.size() << '\n';
    for (const auto &h : penghapusan)
        file << quoted(h.kodeBarang) << ' ' << quoted(h.namaBarang) << ' '
             << quoted(h.alasan) << ' ' << h.jumlah << ' ' << h.status << '\n';
}