#include <iostream>
using namespace std;

const int maxAkun = 100;
const int maxBuku = 100;

string *userName = new string[maxAkun];
string *password = new string[maxAkun];
int *total = new int[maxAkun]();
int pos = 0;
int currentUserIndex = -1;
int jmlh = 0;

struct book {
    string judul;
    string terbit;
    string penulis;
};

book *buku = new book[maxBuku];

void banner(int b);
void signIn();
void logIn();
void menuUtama();
void inputBuku();
void daftarBuku();
void hapusBuku();
void menuAdmin();
void cariBuku();
void menuUser();

void banner(int b) {
    switch (b) {
        case 1:
            cout << R"(
===========================================================================
 __ __    _     _ ___    _  _ ___ _     __    _ ___    _     _____ _     _ 
(_ |_ |  |_||V||_| |    | \|_| | |_||\|/__   | \ |    |_)| |(_  | |_||/ |_|
__)|__|__| || || | |    |_/| | | | || |\_|   |_/_|_   |  |_|__) | | ||\ | |

===========================================================================    
        )" << endl;
            break;

        case 2:
            cout << R"(
==========================
|        RAK BUKU        |
==========================    
        )" << endl;
            break;

        case 3:
            cout << R"(
==========================
|          MENU          |
==========================    
        )" << endl;
            break;

        case 4:
            cout << R"(
==========================
|        SIGN-IN         |
==========================  
        )" << endl;
            break;

        case 5:
            cout << R"(
==========================
|        LOG-IN          |
==========================  
        )" << endl;
    }
}

void signIn() {
    if (pos < maxAkun) {
        cin.ignore();
        banner(4);
        cout << "Masukkan Username: ";
        getline(cin, *(userName + pos));
        cout << "Masukkan Password: ";
        getline(cin, *(password + pos));
        bool usernameAda = false;
        for (int i = 0; i < pos; ++i) {
            if (*(userName + i) == *(userName + pos)) {
                usernameAda = true;
                break;
            }
        }
        if (usernameAda || (*(userName + pos) == "admin" && *(password + pos) == "admin")) {
            cout << "Username sudah ada\n";
        } else {
            cout << "Sign-In Berhasil\n";
            *(total + pos) = 0;
            pos++;
        }
    } else {
        cout << "Sign-In Gagal, Jumlah pengguna maksimal telah tercapai\n";
    }
    system("pause");
}

void logIn() {
    cin.ignore();
    banner(5);
    cout << "Masukkan Username: ";
    string username;
    getline(cin, username);
    cout << "Masukkan Password: ";
    string passwordInput;
    getline(cin, passwordInput);
    bool found = false;
    for (int i = 0; i < pos; i++) {
        if (username == *(userName + i) && passwordInput == *(password + i)) {
            found = true;
            currentUserIndex = i;
            break;
        }
    }
    if (username == "admin" && passwordInput == "admin") {
        cout << "Log-In Berhasil\n";
        system("pause");
        menuAdmin();
    } else if (found) {
        cout << "Log-In Berhasil\n";
        system("pause");
        menuUser();
    } else {
        cout << "Log-In Gagal\n";
    }
    system("pause");
}

void menuUtama() {
    while (true) {
        system("cls");
        banner(1);
        cout << "1. Log-In" << endl;
        cout << "2. Sign-In" << endl;
        cout << "3. Exit" << endl;
        cout << ">> ";
        int input;
        cin >> input;
        system("cls");
        switch (input) {
            case 1:
                logIn();
                break;
            case 2:
                signIn();
                break;
            case 3:
                delete[] userName;
                delete[] password;
                delete[] total;
                delete[] buku;
                return;
            default:
                cout << "Invalid Input\n";
                system("pause");
        }
    }
}

void inputBuku() {
    int n;
    system("cls");
    banner(2);
    cout << "Masukkan jumlah buku: ";
    cin >> n;
    cout << endl;
    for (int i = jmlh; i < jmlh + n; i++) {
        cout << "Masukkan judul buku: ";
        getline(cin >> ws, (*(buku + i)).judul);
        cout << "Masukkan tahun terbit buku: ";
        getline(cin >> ws, (*(buku + i)).terbit);
        cout << "Masukkan nama penulis buku: ";
        getline(cin >> ws, (*(buku + i)).penulis);
        cout << endl;
    }
    jmlh += n;
}

void daftarBuku() {
    system("cls");
    banner(2);
    for (int i = 0; i < jmlh; i++) {
        cout << "Judul Buku: " << (*(buku + i)).judul << "\n";
        cout << "Tahun Terbit: " << (*(buku + i)).terbit << "\n";
        cout << "Penulis Buku: " << (*(buku + i)).penulis << "\n";
        cout << "==========================================" << endl;
    }
}

void hapusBuku() {
    system("cls");
    banner(2);
    if (jmlh == 0) {
        cout << "Tidak ada buku yang tersedia untuk dihapus.\n";
        system("pause");
        return;
    }

    cout << "Daftar Buku yang Tersedia:\n";
    for (int i = 0; i < jmlh; i++) {
        cout << i + 1 << ". " << (*(buku + i)).judul << endl;
    }

    int nomorBuku;
    cout << "Masukkan nomor buku yang ingin dihapus: ";
    cin >> nomorBuku;

    if (nomorBuku < 1 || nomorBuku > jmlh) {
        cout << "Nomor buku tidak valid.\n";
        system("pause");
        return;
    }

    for (int i = nomorBuku - 1; i < jmlh - 1; i++) {
        *(buku + i) = *(buku + i + 1);
    }
    jmlh--;

    cout << "Buku berhasil dihapus.\n";
}

void menuAdmin() {
    while (true) {
        system("cls");
        banner(3);
        cout << "1. Tambah Buku" << endl;
        cout << "2. Daftar Buku" << endl;
        cout << "3. Hapus Buku" << endl;
        cout << "4. Log-out" << endl;
        cout << ">> ";
        int input;
        cin >> input;
        switch (input) {
            case 1:
                inputBuku();
                break;
            case 2:
                daftarBuku();
                break;
            case 3:
                hapusBuku();
                break;
            case 4:
                return;
        }
        system("pause");
    }
}

void cariBuku() {
    system("cls");
    cin.ignore();
    banner(2);
    cout << "Pilihan pencarian:\n";
    cout << "1. Berdasarkan Judul\n";
    cout << "2. Berdasarkan Penulis\n";
    cout << "3. Berdasarkan Tahun Terbit\n";
    cout << ">> ";
    int pilihan;
    cin >> pilihan;
    bool ditemukan = false;
    string kataKunci;
    switch (pilihan) {
        case 1:
            cout << "Masukkan judul buku yang ingin dicari: ";
            getline(cin >> ws, kataKunci);
            for (int i = 0; i < jmlh; i++) {
                if ((*(buku + i)).judul == kataKunci) {
                    ditemukan = true;
                    cout << "Judul Buku: " << (*(buku + i)).judul << "\n";
                    cout << "Tahun Terbit: " << (*(buku + i)).terbit << "\n";
                    cout << "Penulis Buku: " << (*(buku + i)).penulis << "\n";
                    cout << "==========================================" << endl;
                }
            }
            break;
        case 2:
            cout << "Masukkan nama penulis buku yang ingin dicari: ";
            getline(cin >> ws, kataKunci);
            for (int i = 0; i < jmlh; i++) {
                if ((*(buku + i)).penulis == kataKunci) {
                    ditemukan = true;
                    cout << "Judul Buku: " << (*(buku + i)).judul << "\n";
                    cout << "Tahun Terbit: " << (*(buku + i)).terbit << "\n";
                    cout << "Penulis Buku: " << (*(buku + i)).penulis << "\n";
                    cout << "==========================================" << endl;
                }
            }
            break;
        case 3:
            cout << "Masukkan tahun terbit buku yang ingin dicari: ";
            getline(cin >> ws, kataKunci);
            for (int i = 0; i < jmlh; i++) {
                if ((*(buku + i)).terbit == kataKunci) {
                    ditemukan = true;
                    cout << "Judul Buku: " << (*(buku + i)).judul << "\n";
                    cout << "Tahun Terbit: " << (*(buku + i)).terbit << "\n";
                    cout << "Penulis Buku: " << (*(buku + i)).penulis << "\n";
                    cout << "==========================================" << endl;
                }
            }
            break;
        default:
            cout << "Pilihan tidak valid.";
            system("pause");
            cariBuku();
    }
    if (!ditemukan) {
        cout << "Buku yang dicari tidak ditemukan.";
        system("pause");
        cariBuku();
    }
}

void menuUser() {
    while (true) {
        system("cls");
        banner(3);
        cout << "1. Daftar Buku" << endl;
        cout << "2. Cari Buku" << endl;
        cout << "3. Log-out" << endl;
        cout << ">> ";
        int input;
        cin >> input;
        switch (input) {
            case 1:
                daftarBuku();
                break;
            case 2:
                cariBuku();
                break;
            case 3:
                return;
        }
        system("pause");
    }
}

int main() {
    menuUtama();
    return 0;
}