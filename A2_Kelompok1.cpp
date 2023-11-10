#include <iostream>
#include <limits>
using namespace std;

struct kegiatan
{
    int id_kegiatan;
    string nama_kegiatan;
    string lokasi;
    string waktu;
    kegiatan *next;
};

struct volunteer
{
    string nama;
    int umur;
    string jenis_kelamin;
    string status_pekerjaan;
    string alamat;
    int id_kegiatan;
    string status;
    bool admin_approval;
    volunteer *next;
};

struct VolunteerNew
{
    string nama;
    int umur;
    string jenis_kelamin;
    string status_pekerjaan;
    string alamat;
    int id_kegiatan;
    string status;
    VolunteerNew *next;
};

kegiatan *newKegiatan()
{
    // Membuat objek kegiatan baru
    kegiatan *kegiatanBaru = new kegiatan;

    // Meminta input id kegiatan dengan penanganan kesalahan
    cout << "Masukkan id kegiatan : ";
    while (!(cin >> kegiatanBaru->id_kegiatan) || kegiatanBaru->id_kegiatan < 0)
    {
        cout << "Inputan Tidak Sesuai Ketentuan" << endl;
        cin.clear();  // Menghapus flag kesalahan
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Mengabaikan input yang tidak valid
        cout << "Masukkan id kegiatan : ";
    }
    cin.ignore();  // Mengabaikan karakter newline yang tersisa di buffer

    // Meminta input nama kegiatan dengan validasi
    cout << "Masukkan nama kegiatan : ";
    getline(cin, kegiatanBaru->nama_kegiatan);

    // Meminta input lokasi kegiatan
    cout << "Masukkan lokasi kegiatan : ";
    getline(cin, kegiatanBaru->lokasi);

    // Meminta input waktu kegiatan
    cout << "Masukkan waktu kegiatan : ";
    getline(cin, kegiatanBaru->waktu);

    return kegiatanBaru;  // Mengembalikan objek kegiatan yang telah dibuat
}

volunteer *newVolunteer(kegiatan *listKegiatan)
{
    // membuat object volunteer baru
    volunteer *volunteerBaru = new volunteer;

    // Input nama
    cout << "Masukkan nama : ";
    getline(cin, volunteerBaru->nama);

    // Input umur
    cout << "Masukkan umur : ";
    while (!(cin >> volunteerBaru->umur))
    {
        cout << "Masukkan umur yang valid." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    // Input jenis kelamin
    cout << "Masukkan jenis kelamin : ";
    getline(cin, volunteerBaru->jenis_kelamin);

    // Input status pekerjaan
    cout << "Masukkan status pekerjaan : ";
    getline(cin, volunteerBaru->status_pekerjaan);

    // Input alamat
    cout << "Masukkan alamat : ";
    getline(cin, volunteerBaru->alamat);

    volunteerBaru->status = "Belum Disetujui";

    // Pilih id kegiatan
    cout << "Pilih id kegiatan untuk volunteer ini: ";
    while (!(cin >> volunteerBaru->id_kegiatan))
    {
        cout << "Masukkan id kegiatan yang valid." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    // Validasi id kegiatan
    kegiatan *currentKegiatan = listKegiatan;
    while (currentKegiatan != NULL)
    {
        if (currentKegiatan->id_kegiatan == volunteerBaru->id_kegiatan)
        {
            break;
        }
        currentKegiatan = currentKegiatan->next;
    }

    if (currentKegiatan == NULL)
    {
        cout << "ID Kegiatan tidak valid." << endl;
        delete volunteerBaru;
        return NULL;
    }

    volunteerBaru->status = "Belum Disetujui";
    volunteerBaru->admin_approval = false;

    return volunteerBaru;
}

// fungsi menambahkan kegiatan menggunakan first add
void KegiatanAddFirst(kegiatan **head)
{
    kegiatan *kegiatanBaru = newKegiatan();
    kegiatanBaru->next = *head;
    *head = kegiatanBaru;
}

// fungsi menambahkan data volunteer menggunakan first add
void volunteerAddFirst(volunteer **volhead, kegiatan *listKegiatan)
{
    volunteer *volunteerBaru = newVolunteer(listKegiatan);
    if (volunteerBaru != NULL)
    {
        volunteerBaru->next = *volhead;
        *volhead = volunteerBaru;
        cout << "Volunteer berhasil ditambahkan!" << endl;
    }
    else
    {
        cout << "Gagal menambahkan volunteer." << endl;
    }
}

// fungsi untuk mengedit kegiatan
void editKegiatan(kegiatan **head, int index)
{
    int pilih;
    kegiatan *temp = *head;
    for (int i = 1; i < index; i++)
    {
        temp = temp->next;
    }
    cout << "==============================" << endl;
    cout << "|            Ubah            |" << endl;
    cout << "==============================" << endl;
    cout << "|1. Ubah Nama Kegiatan       |" << endl;
    cout << "|2. Ubah Lokasi Kegiatan     |" << endl;
    cout << "|3. Ubah Waktu Kegiatan      |" << endl;
    cout << "|4. Keluar                   |" << endl;
    cout << "==============================" << endl;
    cout << "Silahkan pilih menu yang ingin di ubah : ";
    cin >> pilih;
    cin.ignore();
    if (pilih == 1)
    {
        cout << "Masukkan nama kegiatan : ";
        getline(cin, temp->nama_kegiatan);
    }
    if (pilih == 2)
    {
        cout << "Masukkan lokasi kegiatan : ";
        getline(cin, temp->lokasi);
    }
    if (pilih == 3)
    {
        cout << "Masukkan waktu kegiatan : ";
        getline(cin, temp->waktu);
    }
}

// fungsi untuk menampilkan kegiatan
void displayKegiatan(kegiatan *head)
{
    kegiatan *temp = head;
    cout << "======================================" << endl;
    cout << "|           Daftar Kegiatan          |" << endl;
    cout << "======================================" << endl;
    while (temp != NULL)
    {
        cout << "Id Kegiatan : " << temp->id_kegiatan << endl;
        cout << "Nama Kegiatan : " << temp->nama_kegiatan << endl;
        cout << "Lokasi Kegiatan : " << temp->lokasi << endl;
        cout << "Waktu Kegiatan : " << temp->waktu << endl;
        temp = temp->next;
    }
}

// fungsi untuk menampilkan data volunteer dengan kegiatannya
void displayVolunteerWithKegiatan(volunteer *volhead, kegiatan *keghead)
{
    volunteer *tempVol = volhead;
    while (tempVol != NULL)
    {
        // Menemukan kegiatan yang sesuai dengan id_kegiatan di volunteer
        kegiatan *tempKeg = keghead;
        cout << "id Kegiatan : " << tempVol->id_kegiatan << endl;
        while (tempKeg != NULL)
        {
            if (tempKeg->id_kegiatan == tempVol->id_kegiatan)
            {
                cout << "Nama Kegiatan : " << tempKeg->nama_kegiatan << endl;
                cout << "Lokasi : " << tempKeg->lokasi << endl;
                cout << "Waktu : " << tempKeg->waktu << endl;
                break;
            }
            tempKeg = tempKeg->next;
        }
        cout << "Nama : " << tempVol->nama << endl;
        cout << "Umur : " << tempVol->umur << endl;
        cout << "Jenis Kelamin : " << tempVol->jenis_kelamin << endl;
        cout << "Status Pekerjaan : " << tempVol->status_pekerjaan << endl;
        cout << "Alamat : " << tempVol->alamat << endl;
        cout << "Status : " << tempVol->status << endl;

        tempVol = tempVol->next;
    }
}

// fungsi untuk menghapus kegiatan dengan memilih kegiatan mana yang ingin kita hapus
void DeleteMiddleKegiatan(kegiatan **head)
{
    int index;
    cout << "Ingin Hapus Kegiatan Nomor Berapa : ";
    cin >> index;
    cin.ignore();
    if (index == 1)
    {
        kegiatan *Delete = *head;
        *head = (*head)->next;
        delete Delete;
    }
    if (index > 1)
    {
        kegiatan *temp = *head;
        for (int i = 1; i < index - 1; i++)
        {
            temp = temp->next;
        }
        kegiatan *toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
    }
    cout << "Data Nomor " << index << " Telah Terhapus" << endl;
}

void displayDeletedData(const VolunteerNew &deletedData)
{
    cout << "Data Volunteer yang akan dihapus:" << endl;
    cout << "Nama : " << deletedData.nama << endl;
    cout << "Umur : " << deletedData.umur << endl;
    cout << "Jenis Kelamin : " << deletedData.jenis_kelamin << endl;
    cout << "Status Pekerjaan : " << deletedData.status_pekerjaan << endl;
    cout << "Alamat : " << deletedData.alamat << endl;
    cout << "id Kegiatan : " << deletedData.id_kegiatan << endl;
    cout << "Status : " << deletedData.status << endl;
}

// Fungsi untuk menghapus elemen pertama dari daftar volunteer
void deleteFirstVolunteer(volunteer **volhead, VolunteerNew &deletedData)
{
    if (*volhead == NULL)
    {
        cout << "Daftar volunteer kosong." << endl;
        // Inisialisasi data yang dihapus dengan nilai default
        deletedData.nama = "";
        deletedData.umur = 0;
        deletedData.jenis_kelamin = "";
        deletedData.status_pekerjaan = "";
        deletedData.alamat = "";
        deletedData.id_kegiatan = 0;
        deletedData.status = "";
    }
    else
    {
        volunteer *temp = *volhead;
        // Salin data yang akan dihapus ke dalam struct DeletedVolunteer
        deletedData.nama = temp->nama;
        deletedData.umur = temp->umur;
        deletedData.jenis_kelamin = temp->jenis_kelamin;
        deletedData.status_pekerjaan = temp->status_pekerjaan;
        deletedData.alamat = temp->alamat;
        deletedData.id_kegiatan = temp->id_kegiatan;
        deletedData.status = temp->status;

        // Tampilkan data yang akan dihapus
        displayDeletedData(deletedData);

        // Ubah status menjadi "Disetujui"
        temp->status = "Disetujui";

        // Pindahkan pointer ke elemen selanjutnya
        *volhead = temp->next;

        // Hapus elemen pertama
        delete temp;
        cout << "Volunteer berhasil dihapus dan status diubah menjadi 'Disetujui'." << endl;
    }
}

// fungsi untuk sorting
int length(kegiatan *head)
{
    int panjang = 0;
    kegiatan *temp = head;
    while (temp != NULL)
    {
        temp = temp->next;
        panjang++;
    }
    return panjang;
}

kegiatan *findNode(kegiatan *head, int idx)
{
    for (int a = 0; a < idx; a++)
    {
        head = head->next;
    }
    return head;
}

void shellSortNamaASC(kegiatan *head, int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp_id_kegiatan = findNode(head, i)->id_kegiatan;
            string temp_nama_kegiatan = findNode(head, i)->nama_kegiatan;
            string temp_lokasi = findNode(head, i)->lokasi;
            string temp_waktu = findNode(head, i)->waktu;
            int j;
            for (j = i; j >= gap && findNode(head, j - gap)->nama_kegiatan > temp_nama_kegiatan; j -= gap)
            {
                findNode(head, j)->id_kegiatan = findNode(head, j - gap)->id_kegiatan;
                findNode(head, j)->nama_kegiatan = findNode(head, j - gap)->nama_kegiatan;
                findNode(head, j)->lokasi = findNode(head, j - gap)->lokasi;
                findNode(head, j)->waktu = findNode(head, j - gap)->waktu;
            }
            findNode(head, j)->id_kegiatan = temp_id_kegiatan;
            findNode(head, j)->nama_kegiatan = temp_nama_kegiatan;
            findNode(head, j)->lokasi = temp_lokasi;
            findNode(head, j)->waktu = temp_waktu;
        }
    }
}

// SEARCHING MENU
const int NO_OF_CHARS = 256;
void badCharHeuristic(string str, int size, int badChar[NO_OF_CHARS])
{
    for (int i = 0; i < NO_OF_CHARS; i++)
    {
        badChar[i] = -1;
    }

    for (int i = 0; i < size; i++)
    {
        badChar[(int)str[i]] = i;
    }
}

void searchVolunteerByName(volunteer *volhead, string pattern)
{
    volunteer *temp = volhead;
    while (temp != NULL)
    {
        int n = temp->nama.size();
        int m = pattern.size();

        int badChar[NO_OF_CHARS];
        badCharHeuristic(pattern, m, badChar);

        int s = 0;
        while (s <= (n - m))
        {
            int j = m - 1;

            while (j >= 0 && pattern[j] == temp->nama[s + j])
            {
                j--;
            }

            if (j < 0)
            {
                // Pattern found, display the volunteer's information
                cout << "Nama Volunteer: " << temp->nama << endl;
                cout << "Umur: " << temp->umur << endl;
                cout << "Jenis Kelamin: " << temp->jenis_kelamin << endl;
                cout << "Status Pekerjaan: " << temp->status_pekerjaan << endl;
                cout << "Alamat: " << temp->alamat << endl;
                cout << "ID Kegiatan: " << temp->id_kegiatan << endl;
                cout << "Status: " << temp->status << endl;
                cout << "==============================" << endl;
                break;
            }
            else
            {
                s += max(1, j - badChar[temp->nama[s + j]]);
            }
        }
        temp = temp->next;
    }
}

// fungsi menu
void menu()
{
    cout << "===============================" << endl;
    cout << "|            MENU             |" << endl;
    cout << "===============================" << endl;
    cout << "|1. Pengguna                  |" << endl;
    cout << "|2. Admin                     |" << endl;
    cout << "|3. Keluar                    |" << endl;
    cout << "===============================" << endl;
}

// fungsi menu admin
void menuAdmin(kegiatan **head, volunteer **volhead)
{
    while (true)
    {
        int pilih, index;
        // kegiatan *head =  NULL;
        cout << "===============================" << endl;
        cout << "|            ADMIN            |" << endl;
        cout << "===============================" << endl;
        cout << "|1. Menambahkan Kegiatan      |" << endl;
        cout << "|2. Mengubah Kegiatan         |" << endl;
        cout << "|3. Menghapus Kegiatan        |" << endl;
        cout << "|4. Melihat Kegiatan          |" << endl;
        cout << "|5. Melihat Data Volunteer    |" << endl;
        cout << "|6. Mencari Nama Volunteer    |" << endl;
        cout << "|7. Menerima Volunteer        |" << endl;
        cout << "|0. Keluar                    |" << endl;
        cout << "===============================" << endl;
        cout << "Pilih menu apa : ";
        cin >> pilih;
        cin.ignore();
        if (pilih == 1)
        {
            KegiatanAddFirst(head);
        }
        if (pilih == 2)
        {
            displayKegiatan(*head);
            cout << "Ingin Merubah Nomor Berapa : ";
            cin >> pilih;
            cin.ignore();
            editKegiatan(head, pilih);
        }
        if (pilih == 3)
        {
            displayKegiatan(*head);
            DeleteMiddleKegiatan(head);
        }
        if (pilih == 4)
        {
            displayKegiatan(*head);
        }
        if (pilih == 5)
        {
            displayVolunteerWithKegiatan(*volhead, *head);
        }
        if (pilih == 6)
        {
            string searchPattern;
            cout << "Masukkan nama volunteer yang ingin dicari: ";
            getline(cin, searchPattern);
            searchVolunteerByName(*volhead, searchPattern);
        }
        if (pilih == 7)
        {
            displayVolunteerWithKegiatan(*volhead, *head);

            // Admin approval process
            cout << "Masukkan nomor volunteer yang ingin disetujui: ";
            cin >> index;
            volunteer *temp = *volhead;
            for (int i = 1; i < index; i++)
            {
                temp = temp->next;
            }
            temp->status = "Disetujui";
            temp->admin_approval = true;
            cout << "Status volunteer berhasil disetujui." << endl;
        }
        if (pilih == 0)
        {
            break;
        }
    }
}

// fungsi login admin
void loginAdmin(kegiatan **head, volunteer **volhead)
{
    int i;
    string admin_input, admin_pass;
    cout << "========================================================================" << endl;
    cout << "|                    JIKA ANDA ADMIN SILAHKAN LOGIN                    |" << endl;
    cout << "========================================================================" << endl;
    string username = "admin";
    string password = "admin";
    string login = "block";
    i = 1;
    //        cin.ignore();
    do
    {
        cout << "Masukkan Username : ";
        getline(cin, admin_input);
        cout << "Masukkan Password : ";
        getline(cin, admin_pass);

        if (admin_input == username && admin_pass == password)
        {
            // system("cls");
            cout << "===========================================" << endl;
            cout << "|              Login Berhasil             |" << endl;
            cout << "===========================================" << endl;
            i = 4;
            login = "berhasil";
            menuAdmin(head, volhead);
        }
        else if (admin_input != username && admin_pass == password)
        {
            cout << "\n==========================================" << endl;
            cout << "|    Username Yang Anda Masukkan Salah!    |" << endl;
            cout << "============================================\n"
                 << endl;
            i = i + 1;
        }
        else if (admin_input == username && admin_pass != password)
        {
            cout << "\n==========================================" << endl;
            cout << "|    Password Yang Anda Masukkan Salah!    |" << endl;
            cout << "============================================\n"
                 << endl;
            i = i + 1;
        }
        else
        {
            cout << "\n==========================================" << endl;
            cout << "|      Username / Password Anda Salah!     |" << endl;
            cout << "============================================\n"
                 << endl;
            i = i + 1;
        }
    } while (i <= 3);
    if (login != "berhasil")
    {
        // system("cls");
        cout << "\n===========================================" << endl;
        cout << "| Kamu sudah terblokir karena salah terus |" << endl;
        cout << "|           YAHAHAHAHAHHAYYYYYUK          |" << endl;
        cout << "===========================================\n"
             << endl;
        exit(0);
    }
};

// fungsi menu user
void menuUser(kegiatan **head, volunteer **volhead)
{
    while (true)
    {
        kegiatan *temp = *head;
        int pilih, id_kegiatan;
        cout << "===============================" << endl;
        cout << "|           Menu User         |" << endl;
        cout << "===============================" << endl;
        cout << "|1. Daftar Volunteer          |" << endl;
        cout << "|2. Lihat Status              |" << endl;
        cout << "|3. Keluar                    |" << endl;
        cout << "===============================" << endl;
        cout << "Pilih Menu : ";
        cin >> pilih;
        cin.ignore();
        if (pilih == 1)
        {
            shellSortNamaASC(*head, length(*head));
            displayKegiatan(*head);
            cout << "Silahkan Pilih Kegiatan : ";
            cin >> id_kegiatan;
            cin.ignore();
            while (temp != NULL)
            {
                if (id_kegiatan == temp->id_kegiatan)
                {
                    volunteerAddFirst(volhead, *head);
                    break;
                }
                temp = temp->next;
            }
        }
        if (pilih == 2)
        {
            VolunteerNew deletedData;
            // Memanggil fungsi displayDeletedData
            displayVolunteerWithKegiatan(*volhead, *head);
        }
        if (pilih == 3)
        {
            break;
        }
        // Tambahkan opsi menu lain dan fungsionalitas yang sesuai di sini
    }
}

int main()
{
    int pilih, index;
    volunteer *volhead = NULL;
    kegiatan *head = NULL;
    kegiatan *listKegiatan = NULL;   // Inisialisasi daftar kegiatan
    volunteer *listVolunteer = NULL; // Inisialisasi daftar volunteer
    while (true)
    {
        menu();
        cout << "Silahkan Pilih Menu : ";
        cin >> pilih;
        cin.ignore();
        if (pilih == 1)
        {
            menuUser(&head, &volhead);
        }
        if (pilih == 2)
        {
            // menuAdmin(&head);
            loginAdmin(&head, &volhead);
        }
    }
}
