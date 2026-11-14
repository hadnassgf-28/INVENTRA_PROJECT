#pragma once
#include "data.hpp"

// Menghapus spasi di awal dan akhir teks
string trim(const string &s) {
    size_t awal = s.find_first_not_of(" \t\r\n");
    if (awal == string::npos) return "";
    size_t akhir = s.find_last_not_of(" \t\r\n");
    return s.substr(awal, akhir - awal + 1);
}

// VALIDASI TEKS (tidak boleh kosong)
string inputTeks(string pesan) {
    string teks;

    while (true) {
        cout << pesan;
        getline(cin, teks);
        teks = trim(teks);

        if (!teks.empty())
            return teks;

        cout << "Input tidak valid! Tidak boleh kosong.\n";
    }
}

// VALIDASI ANGKA (tidak boleh kosong, harus angka, harus dalam rentang)
int inputAngka(string pesan, int min, int maks) {
    string baris;

    while (true) {
        cout << pesan;
        getline(cin, baris);
        baris = trim(baris);

        if (!baris.empty()) {
            stringstream ss(baris);
            int angka;
            char sisa;

            // harus angka penuh (tidak ada huruf di belakang) dan dalam rentang
            if ((ss >> angka) && !(ss >> sisa) && angka >= min && angka <= maks)
                return angka;
        }

        cout << "Input tidak valid! Coba lagi.\n";
    }
}

// Memilih jenis barang
string pilihKategori() {
    cout << "\n1. Aset Tetap\n";
    cout << "2. BHP\n";

    int pilih = inputAngka("Pilih jenis: ", 1, 2);

    if (pilih == 1)
        return "Aset Tetap";   // sebelumnya "AsetTetap"
    else
        return "BHP";
}

// Membuat kode barang otomatis
string buatKode(string jenis) {
    int nomor = 1;
    string kode;

    do {
        stringstream ss;

        if (jenis == "Aset Tetap")
            ss << "AST-";
        else
            ss << "BHP-";

        if (nomor < 10) ss << "00";
        else if (nomor < 100) ss << "0";

        ss << nomor;
        kode = ss.str();

        bool ada = false;

        for (auto &b : daftar) {
            if (b.kode == kode) {
                ada = true;
                break;
            }
        }

        if (!ada)
            return kode;

        nomor++;

    } while (true);
}

// Fungsi nomorKode()
int nomorKode(const string &kode) {
    return stoi(kode.substr(4));
}

// Fungsi hurufKecil() dan samaTeks()
string hurufKecil(string s) {
    for (auto &c : s)
        c = tolower((unsigned char)c);
    return s;
}

// Bandingkan teks tanpa peduli huruf besar/kecil
bool samaTeks(const string &a, const string &b) {
    return hurufKecil(a) == hurufKecil(b);
}

// Menampilkan seluruh barang (Aset Tetap yang berurutan digabung jadi rentang)
//fungsi tampilkanBarang()
void tampilkanBarang(string judul = "DAFTAR BARANG") {
    cout << "\n===== " << judul << " =====\n";

    if (daftar.empty()) {
        cout << "Belum ada barang.\n";
        return;
    }

    size_t i = 0;

    while (i < daftar.size()) {
        size_t j = i;

        // Gabungkan hanya Aset Tetap dengan data sama dan kode berurutan
        if (daftar[i].jenis == "Aset Tetap") {
            while (j + 1 < daftar.size() &&
                   daftar[j + 1].jenis == "Aset Tetap" &&
                   samaTeks(daftar[j + 1].nama, daftar[i].nama) &&
                   samaTeks(daftar[j + 1].lokasi, daftar[i].lokasi) &&
                   daftar[j + 1].kondisi == daftar[i].kondisi &&
                   nomorKode(daftar[j + 1].kode) == nomorKode(daftar[j].kode) + 1) {
                j++;
            }
        }

        const Barang &b = daftar[i];

        // Aset Tetap: stok = banyak unit dalam blok, BHP: stok barang
        int stok = (b.jenis == "Aset Tetap") ? (int)(j - i + 1) : b.stok;

        cout << "\nKode     : " << b.kode;
        if (j > i)
            cout << " - " << daftar[j].kode;

        cout << "\nNama     : " << b.nama;
        cout << "\nJenis    : " << b.jenis;
        cout << "\nStok     : " << stok;
        cout << "\nLokasi   : " << b.lokasi;
        cout << "\nKondisi  : " << b.kondisi << endl;

        if (b.kondisi == "Rusak")
            cout << "ALERT: Barang rusak!\n";

        i = j + 1;
    }
}


//fungsi tambahBarangData()
void tambahBarangData(string nama, string jenis, int jumlah, string lokasi) {

    // BHP dengan nama sama digabung
    if (jenis == "BHP") {
        for (auto &b : daftar) {
            if (b.nama == nama && b.jenis == "BHP") {
                b.stok += jumlah;
                SimpanSemua();
                return;
            }
        }
    }

    // Aset tetap dibuat satu kode untuk setiap unit
    if (jenis == "Aset Tetap") {
        for (int i = 0; i < jumlah; i++) {
            Barang b;

            b.kode = buatKode(jenis);
            b.nama = nama;
            b.jenis = jenis;
            b.stok = 1;
            b.kondisi = "Baik";
            b.lokasi = lokasi;

            daftar.push_back(b);
        }
    }
    else {
        Barang b;

        b.kode = buatKode(jenis);
        b.nama = nama;
        b.jenis = jenis;
        b.stok = jumlah;
        b.kondisi = "Baik";
        b.lokasi = lokasi;

        daftar.push_back(b);
    }
    SimpanSemua();
}

// Input teks yang tidak boleh mengandung angkak
string inputTanpaAngka(string pesan, string namaField) {
    while (true) {
        string teks = inputTeks(pesan);

        bool adaAngka = false;
        for (char c : teks) {
            if (isdigit((unsigned char)c)) {
                adaAngka = true;
                break;
            }
        }

        if (!adaAngka)
            return teks;

        cout << "Input tidak valid! " << namaField << " tidak boleh mengandung angka.\n";
    }
}

// Input lokasi: boleh ada angka, tapi harus mengandung minimal satu huruf
string inputLokasi(string pesan) {
    while (true) {
        string teks = inputTeks(pesan);

        bool adaHuruf = false;
        for (char c : teks) {
            if (isalpha((unsigned char)c)) {
                adaHuruf = true;
                break;
            }
        }

        if (adaHuruf)
            return teks;

        cout << "Input tidak valid! Lokasi harus mengandung huruf (contoh: Lab 1, JT01).\n";
    }
}

void tambahBarang() {
    cout << "\n===== TAMBAH BARANG =====\n";

    string nama = inputTanpaAngka("Nama barang: ", "Nama barang");
    string jenis = pilihKategori();
    int jumlah = inputAngka("Jumlah: ", 1, 100000);
    string lokasi = inputLokasi("Lokasi: ");

    tambahBarangData(nama, jenis, jumlah, lokasi);

    cout << "\n" << nama << " berhasil ditambahkan.\n";
}

void cariBarang() {
    bool ditemukan = false;

    string kode = inputTeks("\nMasukkan kode barang: ");

    for (auto &b : daftar) {
        if (b.kode == kode) {
            cout << "\nNama    : " << b.nama;
            cout << "\nStok    : " << b.stok;
            cout << "\nLokasi  : " << b.lokasi;
            cout << "\nKondisi : " << b.kondisi << endl;

            ditemukan = true;
        }
    }

    if (!ditemukan)
        cout << "Barang tidak ditemukan.\n";
}

// Mengubah lokasi barang
void ubahLokasi() {
    string kode = inputTeks("\nMasukkan kode barang: ");

    for (auto &b : daftar) {
        if (b.kode == kode) {
            cout << "Lokasi saat ini: " << b.lokasi << endl;

            b.lokasi = inputLokasi("Lokasi baru: ");

            SimpanSemua();

            cout << "Lokasi berhasil diubah.\n";
            return;
        }
    }

    cout << "Barang tidak ditemukan.\n";
}

void cekStokKondisi() {
    cout << "\n===== CEK STOK DAN KONDISI =====\n";

    if (daftar.empty()) {
        cout << "Belum ada barang.\n";
        return;
    }

    bool adaAlert = false;
    size_t i = 0;

    while (i < daftar.size()) {
        size_t j = i;

        // Gabungkan Aset Tetap yang datanya sama dan kodenya berurutan
        if (daftar[i].jenis == "Aset Tetap") {
            while (j + 1 < daftar.size() &&
                   daftar[j + 1].jenis == "Aset Tetap" &&
                   samaTeks(daftar[j + 1].nama, daftar[i].nama) &&
                   samaTeks(daftar[j + 1].lokasi, daftar[i].lokasi) &&
                   daftar[j + 1].kondisi == daftar[i].kondisi &&
                   nomorKode(daftar[j + 1].kode) == nomorKode(daftar[j].kode) + 1) {
                j++;
            }
        }

        const Barang &b = daftar[i];

        bool stokMenipis = (b.jenis == "BHP" && b.stok <= BATAS_MINIMUM);
        bool rusak = (b.kondisi == "Rusak");

        // Lewati barang yang aman
        if (!stokMenipis && !rusak) {
            i = j + 1;
            continue;
        }

        adaAlert = true;

        cout << "\nKode     : " << b.kode;
        if (j > i)
            cout << " - " << daftar[j].kode;

        cout << "\nNama     : " << b.nama;
        cout << "\nJenis    : " << b.jenis;

        if (b.jenis == "Aset Tetap")
            cout << "\nJumlah   : " << (j - i + 1) << " unit";
        else
            cout << "\nStok     : " << b.stok;

        cout << "\nLokasi   : " << b.lokasi;
        cout << "\nKondisi  : " << b.kondisi << endl;

        if (stokMenipis)
            cout << "ALERT STOK: Stok menipis (batas minimum " << BATAS_MINIMUM << ")!\n";

        if (rusak)
            cout << "ALERT RUSAK: Barang rusak!\n";

        i = j + 1;
    }

    if (!adaAlert)
        cout << "Semua stok dan kondisi barang aman.\n";
}

// Mengajukan penghapusan barang
// Mengajukan penghapusan barang
void ajukanPenghapusan() {
    string kode = inputTeks("\nKode barang: ");

    for (auto &b : daftar) {
        if (b.kode == kode) {

            // Hitung jumlah yang sudah diajukan dan masih menunggu keputusan Kaprodi
            int menunggu = 0;
            for (auto &h : penghapusan) {
                if (h.kodeBarang == b.kode && h.status == 0)
                    menunggu += h.jumlah;
            }

            int tersedia = b.stok - menunggu;

            if (tersedia <= 0) {
                if (menunggu > 0)
                    cout << "Barang ini sudah diajukan dan menunggu keputusan Kaprodi.\n";
                else
                    cout << "Stok barang ini 0, tidak ada yang bisa dihapus.\n";
                return;
            }

            cout << "\nBarang: " << b.nama << " (" << b.kode << ")\n";

            int jumlah;

            if (b.jenis == "Aset Tetap") {
                // Satu kode = satu unit, tidak perlu input jumlah
                jumlah = 1;
            }
            else {
                cout << "Stok tersedia: " << tersedia << endl;
                jumlah = inputAngka("Jumlah dihapus: ", 1, tersedia);
            }

            string alasan = inputTanpaAngka("Alasan: ", "Alasan");

            penghapusan.push_back(
                {b.kode, b.nama, alasan, jumlah, 0}
            );

            // Tandai rusak hanya jika semua stok diajukan
            if (jumlah == b.stok)
                b.kondisi = "Rusak";

            SimpanSemua();

            cout << "Pengajuan dikirim ke Kaprodi.\n";
            return;
        }
    }

    cout << "Barang tidak ditemukan.\n";
}