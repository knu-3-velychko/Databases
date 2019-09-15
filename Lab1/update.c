#include "update.h"
/*
bool update_m(char *ptr, FILE **indexFile, FILE **masterFile) {
    long id;

    if (ptr != NULL) {
        char *pEnd;
        id = strtol(ptr, NULL, 10);
        ptr = strtok(NULL, " ");
        setbuf(stdout, 0);
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
            struct Contributor contributor;
            fseek(*masterFile, index * (sizeof(unsigned long) + sizeof(char) * (25 * 3 + 10) + sizeof(unsigned int)),
                  SEEK_SET);

            contributor = readContributor();
            contributor.userID = id;
            writeContributor(&contributor, masterFile);
            return true;
        }
    }
    setbuf(stdout, 0);
    printf("ID %ld does not exist.", id);
    return true;
}

bool update_s(char *ptr) {
    return true;
}
 */