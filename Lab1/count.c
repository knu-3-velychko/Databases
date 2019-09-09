#include "count.h"

unsigned int count_m(char *ptr, FILE **indexFile) {
    if (ptr != NULL) {
        setbuf(stdout, 0);printf("Wrong command.");
        return false;
    }
    unsigned long tmpID = 0;
    unsigned int index = 0, status = 0, i = 0;
    fseek(*indexFile, 0, SEEK_SET);
    while (fread(&tmpID, sizeof(unsigned long), 1, *indexFile) == 1) {
        fread(&index, sizeof(unsigned int), 1, *indexFile);
        fread(&status, sizeof(unsigned int), 1, *indexFile);
        if (status == 1)
            i++;
    }
    return i;
}

unsigned int count_s(char *ptr) {
    return true;
}

unsigned int count_all(char *ptr) {
    return true;
}