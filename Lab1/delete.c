#include "delete.h"

bool del_m(char *ptr, FILE **indexFile, FILE **masterFile) {
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
    unsigned int index = 0, status = 0, i = 0;
    fseek(*indexFile, 0, SEEK_SET);
    while (fread(&tmpID, sizeof(unsigned long), 1, *indexFile) == 1) {
        fread(&index, sizeof(unsigned int), 1, *indexFile);
        fread(&status, sizeof(unsigned int), 1, *indexFile);
        if (tmpID == id && status == 1) {
            struct Contributor contributor;
            unsigned int status = 0;
//            unsigned long userID = 0, size = 0;
//            char name[25], eMail[25], password[10], address[25];
            fseek(*masterFile, index * (sizeof(unsigned long) + sizeof(char) * (25 * 3 + 10) + sizeof(unsigned int)),
                  SEEK_SET);
            fseek(*masterFile, sizeof(unsigned long) + sizeof(char) * (25 * 3 + 10), SEEK_CUR);

            fseek(*indexFile, (i * (sizeof(unsigned long) + 2 * sizeof(unsigned int)) + sizeof(unsigned long) +
                                   sizeof(unsigned int)), SEEK_SET);
            fwrite(&status, sizeof(unsigned int), 1, *masterFile);
            fwrite(&status, sizeof(unsigned int), 1, *indexFile);

            return true;
        }
        i++;
    }
    printf("ID %ld does not exist.", id);
    return true;
}

bool del_s(char *ptr) {
    return true;
}