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

        printf("%ld %i %i\n",tmpID,index,status);
        if (tmpID == id && status == 1) {
            struct Contributor contributor;
//            unsigned long userID = 0;
//            char name[25], eMail[25], password[10], address[25];
            fseek(*masterFile, index * (sizeof(unsigned long) + sizeof(char) * (25 * 3 + 10) + sizeof(unsigned int)),
                  SEEK_SET);
            fread(&contributor.userID, sizeof(unsigned long), 1, *masterFile);
            fread(contributor.name, sizeof(char), 25, *masterFile);
            fread(contributor.eMail, sizeof(char), 25, *masterFile);
            fread(contributor.password, sizeof(char), 10, *masterFile);
            fread(contributor.address, sizeof(char), 25, *masterFile);

            printf("\nEnter Contributor name: %s", contributor.name);
            printf("\nEnter Contributor e-mail: %s", contributor.eMail);
            printf("\nEnter Contributor password: %s", contributor.password);
            printf("\nEnter Contributor address: %s", contributor.address);

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