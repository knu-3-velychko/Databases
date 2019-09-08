#include "get.h"

bool get_m(char *ptr, FILE **masterFile, FILE **indexFile) {
    long id;

    if (ptr != NULL) {
        char *pEnd;
        id = strtol(ptr, pEnd, 10);
        ptr = strtok(NULL, " ");
        printf("%ld", id);
        if (ptr != NULL)
            return false;
    } else {
        return false;
    }

    unsigned long tmpID = 0;
    unsigned int index = 0, status = 0;
    fseek(*indexFile, 0, SEEK_SET);
    while (fread(&tmpID, sizeof(unsigned long), 1, *indexFile) == 1) {
        fread(&index, sizeof(unsigned int), 1, *indexFile);
        fread(&status, sizeof(unsigned int), 1, *indexFile);
        if (tmpID == id && status == 1) {
            unsigned long userID = 0, size = 0;
            int cellsNumb = 0, status = 1;
            char name[25], eMail[25], password[10], address[25];
            fseek(*masterFile, index * (sizeof(unsigned long) + sizeof(char) * (25 * 3 + 10) + sizeof(unsigned int)),
                  SEEK_SET);
            fread(&userID, sizeof(unsigned long), 1, *masterFile);
            fread(name, sizeof(char), 25, *masterFile);
            fread(eMail, sizeof(char), 25, *masterFile);
            fread(password, sizeof(char), 10, *masterFile);
            fread(address, sizeof(char), 25, *masterFile);

            printf("\nEnter Contributor name: %s", name);
            printf("\nEnter Contributor e-mail: %s", eMail);
            printf("\nEnter Contributor password: %s", password);
            printf("\nEnter Contributor address: %s", address);

            return true;
        }
    }
    return false;
}

bool get_s(char *ptr) {
    return true;
}

bool get_i(char *ptr) {
    return true;
}