#include "role.hpp"

int main() {

    BacaSemua();

    int role;

    do {
        cout << "\n===== INVENTARIS BARANG KAMPUS =====\n";
        cout << "1. Fakultas\n";
        cout << "2. Kaprodi\n";
        cout << "3. Tata Usaha\n";
        cout << "4. Keluar\n";

        role = inputAngka("Pilih role: ", 1, 4);

        switch (role) {
            case 1:
                menuFakultas();
                break;

            case 2:
                menuKaprodi();
                break;

            case 3:
                menuTU();
                break;

            case 4:
                SimpanSemua();
                cout << "Data berhasil disimpan.\n";
                break;
        }

    } while (role != 4);

    return 0;
}