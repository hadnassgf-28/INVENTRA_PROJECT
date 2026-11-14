#pragma once
#include "alur.hpp"

// ================= MENU FAKULTAS =================
void menuFakultas() {
    int pilih;

    do {
        cout << "\n===== MENU FAKULTAS =====\n";
        cout << "1. Lihat permintaan\n";
        cout << "2. Proses permintaan\n";
        cout << "3. Kirim barang\n";
        cout << "4. Lihat retur\n";
        cout << "0. Keluar\n";

        pilih = inputAngka("Pilihan: ", 0, 4);

        switch (pilih) {
            case 1:
                lihatPermintaan();
                break;
            case 2:
                prosesPermintaan();
                break;
            case 3:
                kirimBarang();
                break;
            case 4:
                prosesRetur();
                break;
        }

    } while (pilih != 0);
}


// ================= MENU KAPRODI =================
void menuKaprodi() {
    int pilih;

    do {
        cout << "\n===== MENU KAPRODI =====\n";
        cout << "1. Lihat daftar barang\n";
        cout << "2. Lihat pengajuan penghapusan\n";
        cout << "3. Cek kelayakan barang\n";
        cout << "0. Keluar\n";

        pilih = inputAngka("Pilihan: ", 0, 3);

        switch (pilih) {
            case 1:
                tampilkanBarang();
                break;
            case 2:
                lihatPengajuan();
                break;
            case 3:
                cekKelayakan();
                break;
        }

    } while (pilih != 0);
}


// ================= MENU TATA USAHA =================
void menuTU() {
    int pilih;

    do {
        cout << "\n===== MENU TATA USAHA =====\n";
        cout << "1. Tambah barang\n";
        cout << "2. Tampilkan barang\n";
        cout << "3. Cari barang\n";
        cout << "4. Ubah lokasi\n";
        cout << "5. Ajukan penghapusan\n";
        cout << "6. Cek stok dan kondisi\n";
        cout << "7. Buat permintaan barang\n";
        cout << "8. Terima barang\n";
        cout << "0. Keluar\n";

        pilih = inputAngka("Pilihan: ", 0, 8);

        switch (pilih) {
            case 1:
                tambahBarang();
                break;
            case 2:
                tampilkanBarang();
                break;
            case 3:
                cariBarang();
                break;
            case 4:
                ubahLokasi();
                break;
            case 5:
                ajukanPenghapusan();
                break;
            case 6:
                cekStokKondisi();
                break;
            case 7:
                buatPermintaan();
                break;
            case 8:
                terimaBarang();
                break;
        }

    } while (pilih != 0);
}
