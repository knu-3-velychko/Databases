#include "count.h"

unsigned int count_m(char *ptr, FILE **masterFile) {
    if (ptr != NULL) {
        setbuf(stdout, 0);
        printf("Wrong command.");
        return false;
    }
    unsigned int status = 0, i = 0;
    fseek(*masterFile, 0, SEEK_SET);
    while (!feof(*masterFile)) {
        fseek(*masterFile, CONTRIBUTOR_SIZE, SEEK_CUR);
        fread(&status, sizeof(int), 1, *masterFile);
        if (status == 1)
            i++;
    }
    return i;
}

unsigned int count_s(char *ptr, FILE **slaveFile) {
    if (ptr != NULL) {
        setbuf(stdout, 0);
        printf("Wrong command.");
        return false;
    }
    unsigned long id = 0;
    unsigned int status = 0, i = 0;
    fseek(*slaveFile, 0, SEEK_SET);
    while ((fread(&id, sizeof(long int), 1, *slaveFile)) == 1) {
        fseek(*slaveFile, IMAGE_SIZE - sizeof(long int), SEEK_CUR);
        fread(&status, sizeof(int), 1, *slaveFile);
        if (status == 1)
            i++;
    }
    return i;
}

unsigned int count_all(char *ptr, FILE **slaveFile) {
    if (ptr != NULL) {
        setbuf(stdout, 0);
        printf("Wrong command.");
        return false;
    }
    unsigned int status = 0, i = 0;
    fseek(*slaveFile, 0, SEEK_SET);
    while (!feof(*slaveFile)) {
        fseek(*slaveFile, IMAGE_SIZE, SEEK_CUR);
        fread(&status, sizeof(int), 1, *slaveFile);
        if (status == 1)
            i++;
    }
    return i;
}