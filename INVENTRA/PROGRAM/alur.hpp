#pragma once
#include "inventaris.hpp"
   
// Membuat permintaan barang
void buatPermintaan() {
    Permintaan p;

    cout << "\n===== PERMINTAAN BARANG =====\n";

    p.namaBarang = inputTeks("Nama barang: ");

    p.jenis = pilihKategori();
    p.jumlah = inputAngka("Jumlah: ", 1, 100000);

    p.peminta = "Tata Usaha";
    p.status = 0;
    p.noSPB = "-";

    permintaan.push_back(p);

    SimpanSemua();

    cout << "Permintaan dikirim ke Fakultas.\n";
}

// Fakultas melihat permintaan
void lihatPermintaan() {
    cout << "\n===== DAFTAR PERMINTAAN =====\n";

    int nomor = 0;

    for (auto &p : permintaan) {
        if (p.status == 0) {
            nomor++;

            cout << nomor << ". "
                 << p.namaBarang
                 << " x" << p.jumlah
                 << " | Status: "
                 << statusMinta(p.status)
                 << endl;
        }
    }

    if (nomor == 0)
        cout << "-- TIDAK ADA PERMINTAAN --\n";
}

// Fakultas menyetujui atau menolak
void prosesPermintaan() {
    cout << "\n===== PROSES PERMINTAAN =====\n";

    bool ada = false;
    bool adaPerubahan = false;

    for (auto &p : permintaan) {
        if (p.status == 0) {
            ada = true;

            cout << "\nBarang  : " << p.namaBarang << endl;
            cout << "Jenis   : " << p.jenis << endl;
            cout << "Jumlah  : " << p.jumlah << endl;
            cout << "Peminta : " << p.peminta << endl;

            cout << "1. Setujui\n2. Tolak\n0. Lewati\n";

            int pilih = inputAngka("Pilihan: ", 0, 2);

            if (pilih == 0) {
                cout << "Dilewati. Permintaan tetap menunggu persetujuan.\n";
                continue;
            }

            if (pilih == 1) {
                p.status = 1;
                cout << "Permintaan disetujui.\n";
            }
            else {
                p.status = 2;
                cout << "Permintaan ditolak.\n";
            }

            adaPerubahan = true;
        }
    }

    if (!ada) {
        cout << "Tidak ada permintaan\n";
        return;
    }

    if (adaPerubahan)
        SimpanSemua();
}

// Fakultas mengirim barang
void kirimBarang() {
    cout << "\n===== KIRIM BARANG =====\n";

    bool ada = false;
    bool adaPerubahan = false;

    for (int i = 0; i < (int)permintaan.size(); i++) {
        auto &p = permintaan[i];

        // Hanya permintaan disetujui (1) atau retur (5) yang bisa dikirim
        if (p.status != 1 && p.status != 5) continue;

        ada = true;

        // Validasi data permintaan
        if (p.namaBarang.empty() || p.jumlah <= 0) {
            cout << "\nPermintaan dengan data tidak valid dilewati.\n";
            continue;
        }

        cout << "\nBarang  : " << p.namaBarang << endl;
        cout << "Jenis   : " << p.jenis << endl;
        cout << "Jumlah  : " << p.jumlah << endl;
        cout << "Tujuan  : " << p.peminta << endl;
        cout << "Status  : " << statusMinta(p.status)
             << (p.status == 5 ? " (kirim ulang)" : "") << endl;

        cout << "1. Kirim\n0. Lewati\n";

        int pilih = inputAngka("Pilihan: ", 0, 1);

        if (pilih == 0) {
            cout << "Dilewati. Barang belum dikirim.\n";
            continue;
        }

        // Konfirmasi sebelum pengiriman dicatat
        cout << "Yakin mengirim barang ini?\n1. Ya\n2. Tidak\n";

        if (inputAngka("Pilihan: ", 1, 2) == 2) {
            cout << "Dibatalkan. Barang belum dikirim.\n";
            continue;
        }

        p.noSPB = "SPB-" + to_string(i + 1);
        p.status = 3;
        adaPerubahan = true;

        cout << "Barang dikirim.\n";
        cout << "Nomor SPB: " << p.noSPB << endl;
    }

    if (!ada) {
        cout << "Tidak ada barang yang siap dikirim.\n";
        return;
    }

    if (adaPerubahan)
        SimpanSemua();
}

// TU menerima barang
void terimaBarang() {
    bool ada = false;

    for (auto &p : permintaan) {
        if (p.status == 3) {
            ada = true;

            cout << "\nBarang: " << p.namaBarang << endl;
            cout << "SPB: " << p.noSPB << endl;

            cout << "1. Sesuai dan layak\n2. Tidak sesuai\n";

            int pilih = inputAngka("Pilihan: ", 1, 2);

            if (pilih == 1) {
                string lokasi = inputTeks("Lokasi barang: ");

                tambahBarangData(
                    p.namaBarang,
                    p.jenis,
                    p.jumlah,
                    lokasi
                );

                p.status = 4;

                cout << "Barang berhasil diterima.\n";
            }
            else {
                p.status = 5;
                cout << "Barang ditolak. Retur dibuat.\n";
            }
        }
    }

    if (!ada) {
        cout << "\nTidak ada barang yang dikirim.\n";
        return;
    }

    SimpanSemua();
}

// Melihat daftar retur
void prosesRetur() {
    cout << "\n===== DAFTAR RETUR =====\n";

    bool ada = false;

    for (auto &p : permintaan) {
        if (p.status == 5) {
            cout << p.namaBarang << " x" << p.jumlah << endl;
            ada = true;
        }
    }

    if (!ada)
        cout << "Tidak ada barang retur.\n";
}

// Melihat pengajuan penghapusan
void lihatPengajuan() {
    cout << "\n===== PENGAJUAN PENGHAPUSAN =====\n";

    if (penghapusan.empty()) {
        cout << "--DAFTAR KOSONG--\n";
        return;
    }

    for (auto &h : penghapusan) {
        cout << h.kodeBarang << " - "
             << h.namaBarang << " x"
             << h.jumlah << " | "
             << h.alasan << endl;
    }
}

// Kaprodi memeriksa kondisi barang
void cekKelayakan() {
    cout << "\n===== CEK KELAYAKAN BARANG =====\n";

    bool ada = false;
    bool adaPerubahan = false;

    for (auto &h : penghapusan) {
        if (h.status != 0) continue;

        ada = true;

        // Validasi data pengajuan
        if (h.kodeBarang.empty() || h.jumlah <= 0) {
            cout << "\nPengajuan dengan data tidak valid dilewati.\n";
            continue;
        }

        // Cari barang di daftar inventaris
        int i = -1;

        for (int j = 0; j < (int)daftar.size(); j++) {
            if (daftar[j].kode == h.kodeBarang) {
                i = j;
                break;
            }
        }

        // Barang sudah tidak ada di inventaris -> pengajuan ditutup
        if (i == -1) {
            cout << "\nBarang " << h.kodeBarang << " - " << h.namaBarang
                 << " tidak ditemukan di inventaris.\n";
            cout << "Pengajuan ditutup (dibatalkan).\n";

            h.status = 2;
            adaPerubahan = true;
            continue;
        }

        // Jumlah yang diajukan tidak boleh melebihi stok saat ini
        if (h.jumlah > daftar[i].stok) {
            cout << "\nPengajuan " << h.kodeBarang << " dilewati: jumlah dihapus ("
                 << h.jumlah << ") melebihi stok saat ini ("
                 << daftar[i].stok << ").\n";
            continue;
        }

        cout << "\nKode     : " << h.kodeBarang << endl;
        cout << "Barang   : " << h.namaBarang << endl;
        cout << "Jumlah   : " << h.jumlah << " (stok saat ini: " << daftar[i].stok << ")" << endl;
        cout << "Kondisi  : " << daftar[i].kondisi << endl;
        cout << "Alasan   : " << h.alasan << endl;

        cout << "1. Masih layak\n2. Tidak layak\n0. Lewati\n";

        int pilih = inputAngka("Pilihan: ", 0, 2);

        if (pilih == 0) {
            cout << "Dilewati. Pengajuan tetap menunggu keputusan.\n";
            continue;
        }

        // Konfirmasi sebelum keputusan diterapkan
        if (pilih == 1)
            cout << "Yakin barang masih layak? (penghapusan dibatalkan)\n";
        else
            cout << "Yakin barang tidak layak? (stok akan dikurangi "
                 << h.jumlah << ")\n";

        cout << "1. Ya\n2. Tidak\n";

        if (inputAngka("Pilihan: ", 1, 2) == 2) {
            cout << "Dibatalkan. Pengajuan tetap menunggu keputusan.\n";
            continue;
        }

        if (pilih == 1) {
            h.status = 2;
            daftar[i].kondisi = "Baik";

            cout << "Penghapusan dibatalkan.\n";
        }
        else {
            h.status = 1;
            daftar[i].stok -= h.jumlah;

            if (daftar[i].stok <= 0)
                daftar.erase(daftar.begin() + i);
            else
                daftar[i].kondisi = "Baik";   // sisa barang masih bagus

            cout << "Penghapusan disetujui.\n";
        }

        adaPerubahan = true;
    }

    if (!ada) {
        cout << "Tidak ada pengajuan penghapusan yang menunggu.\n";
        return;
    }

    if (adaPerubahan)
        SimpanSemua();
}