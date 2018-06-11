/*
Desctiption: This is the implementation of the multilist question in the final exam of
Data Structure lab activity.
The question: 
    Buat lah multilist mata kuliah (mahasiswa dan matkul)
    Sertakan fungsi-fungsi berikut:
    - createElementMhs
    - createElementMatkul
    - insertFirstMahasiswa
    - deleteFirstMahasiswa
    - insertFirstMatkul
    - deleteFirstMatkul
    - traversalMhsMatkul
    
Author: Muhammad Fahmi Irfananda
@2018
*/

#include <iostream>
#include <string.h>
#include <unistd.h>

using namespace std;

struct Matkul {
    char nama[10];
    Matkul* next;
};
typedef Matkul* pMatkul;

struct Mahasiswa {
    char npm[10];
    char nama[10];
    Mahasiswa* next;
    pMatkul firstMatkul;
};
typedef Mahasiswa* pMhs;

typedef pMhs listMhs;

void createElementMhs(pMhs& mhs) {
    mhs = new Mahasiswa;
    cout << "nama : "; cin >> mhs->nama;
    cout << "npm : "; cin >> mhs->npm;
    mhs->firstMatkul = NULL;
    mhs->next = NULL;
}

void createElementMatkul(pMatkul &matkul) {
    matkul = new Matkul;
    cout << "nama matkul: "; cin >> matkul->nama;
    matkul->next == NULL;
}

pMhs findMhsByNpm(listMhs first, char npm[10]) {
    listMhs trav = first;
    bool found = false;
    while(trav != NULL && found == false) {
        if(strcmp(trav->npm, npm) == 0) {
            found = true;
        } else trav = trav->next;
    }
    return trav;
}

void insertFirstMatkul(listMhs &first, pMatkul &matkul) {
    // find mahasiswa
    char npm[10];
    pMhs mhs;
    cout << "cari npm mahasiswa: "; cin >> npm;
    mhs = findMhsByNpm(first, npm);
    
    // if mahasiswa not found show message to user, else do insert 
    if(mhs == NULL) {
        cout << "Mahasiswa not found" << endl;
    } else {
        cout << "ketemu: " << mhs->nama << endl;
        createElementMatkul(matkul);

        if(mhs->firstMatkul == NULL) mhs->firstMatkul = matkul;
        else {
            matkul->next = mhs->firstMatkul;
            mhs->firstMatkul = matkul;
        }
    }
}

void insertFirstMhs(listMhs &first, pMhs &mhs) {
    createElementMhs(mhs);

    if(first == NULL) first = mhs;
    else {
        mhs->next = first;
        first = mhs;
    }
}

void deleteFirstMahasiswa(listMhs &first, pMhs &pHapus) {
    if(first == NULL){
        pHapus = NULL;
        cout << "List kosong!" << endl;
    } else {
        pHapus = first;
        first = first->next;
        pHapus->next = NULL;
    }
}

void deleteFirstMatkul(listMhs &first, pMatkul &pHapus) {
    // serach for mahasiswa
    char npm[10];
    pMhs mhs;

    cout << "cari npm mahasiswa: "; cin >> npm;
    cout << endl;
    
    mhs = findMhsByNpm(first, npm);    
    // if mahasiswa not found show message to user, else do delete 
    if(mhs == NULL) {
        pHapus = NULL;
        cout << "Mahasiswa not found!" << endl;
    } else{
        pMatkul &first = mhs->firstMatkul;
        if(first == NULL) {
            pHapus = NULL;
            cout << "List Matkul kosong!" << endl;
        } else {
            pHapus = first;
            first = first->next;
            pHapus->next = NULL;
        }
    }
}

void traversalMhsMatkul(listMhs first) {
    listMhs trav = first;
    pMatkul travMatkul = NULL;
    int count = 1;

    cout << "no\tnama\tnpm\tmatkul\t" << endl;
    cout << "--\t----\t----\t-----\t" << endl;

    // looping the list & print the node
    while(trav != NULL) {
        printf("%d\t%s\t%s\t", count, trav->nama, trav->npm);

        // for every node print the matkul if exists        
        travMatkul = trav->firstMatkul;
        while(travMatkul != NULL) {
            printf("%s,", travMatkul->nama);
            travMatkul = travMatkul->next;
        }
        cout << endl;

        trav = trav->next;
        count++;
    }
    cout << endl;
}

// validate user menu choice
bool checkPilihan(int pil, int max) {
    return pil >= 1 && pil <=max;
}

void menu() {
    cout << "Menu:\n";
    cout << "1. Insert First Mahasiswa\n";
    cout << "2. Insert First Matkul\n";
    cout << "3. Delete First Mahasiswa\n";
    cout << "4. Delete First Matkul\n";
    cout << "5. Traversal Mahasiswa Matkul\n";
    cout << "6. Exit\n";
}

int main(int argc, char** argv) {
    pMhs pBaruMhs, pHapusMhs = NULL;
    pMatkul pBaruMatkul, pHapusMatkul = NULL;
    listMhs firstMhs = NULL;
    char dummy;
    int pilihan = 1, maxAns = 6;

    bool isAnsValide = true;
    
    do {
        system("clear");
        traversalMhsMatkul(firstMhs);
        if(!isAnsValide) {
            cout << "Pilihan is not valid\n";
            cout << "It should (1-6)\n";
        }
        menu();
        cout << "Input pilihan (1-6): "; cin >> pilihan;
        isAnsValide = checkPilihan(pilihan, maxAns);
        if(!isAnsValide) {
            pilihan = 0;
            system("clear");
        }
        switch(pilihan) {
            case 0: break;
            case 1:
                insertFirstMhs(firstMhs, pBaruMhs);
                traversalMhsMatkul(firstMhs);
                break;
            
            case 2:
                insertFirstMatkul(firstMhs, pBaruMatkul);
                traversalMhsMatkul(firstMhs);
                break;
            
            case 3:
                deleteFirstMahasiswa(firstMhs, pHapusMhs);
                traversalMhsMatkul(firstMhs);
                break;
            
            case 4: 
                deleteFirstMatkul(firstMhs, pHapusMatkul);
                traversalMhsMatkul(firstMhs);
                break;
            
            case 5:
                traversalMhsMatkul(firstMhs);
                break;

            case 6:
                pilihan = 6;
                break; 
        }
    } while(pilihan != 6);
}