#include <iostream>
#include <string.h>
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

// make a list
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
        }
    }
}

void traversal(listMhs first) {
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

int main(int argc, char** argv) {
    pMhs pBaruMhs, pHapusMhs;
    pMatkul pBaruMatkul, pHapusMatkul;
    listMhs firstMhs = NULL;

    insertFirstMhs(firstMhs, pBaruMhs);
    insertFirstMhs(firstMhs, pBaruMhs);
    insertFirstMhs(firstMhs, pBaruMhs);
    insertFirstMhs(firstMhs, pBaruMhs);

    insertFirstMatkul(firstMhs, pBaruMatkul);
    insertFirstMatkul(firstMhs, pBaruMatkul);
    insertFirstMatkul(firstMhs, pBaruMatkul);
    insertFirstMatkul(firstMhs, pBaruMatkul);

    cout << "\nTraversal\n";
    traversal(firstMhs);

    deleteFirstMahasiswa(firstMhs, pHapusMhs);
    traversal(firstMhs);
    printf("deleted mahasiswa: npm.%s\n", pHapusMhs->npm);

    deleteFirstMatkul(firstMhs, pHapusMatkul);
    traversal(firstMhs);
    printf("deleted matkul: %s\n", pHapusMatkul->nama);
}

/* DUMMY DATA
fahmi
28
irfan
90
junior
33
nabgar
22

28
fisika
33
fisika
28
oop
90
etprof

*/