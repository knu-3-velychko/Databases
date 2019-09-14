#include "insert.h"

bool insert_m(char *ptr, FILE **masterFile, FILE **indexTable) {
    if (ptr != NULL) {
        setbuf(stdout, 0);
        printf("Wrong command.");
        return false;
    }

    struct Contributor contributor;
    unsigned long size = 0, id = 0;
    int cellsNumb = 0, status = 1;
    char userID[21];
    char *pEnd;

    setbuf(stdout, 0);
    printf("\nEnter Contributor User ID:");
    scanf("%s", userID);
    id = strtol(userID, NULL, 10);

    if (getContributorID(contributor.userID, indexTable) != -1) {
        setbuf(stdout, 0);
        printf("ID exists. Try to enter another one");
        return insert_m(ptr, masterFile, indexTable);
    } else {
        contributor = readContributor();
        contributor.userID = id;

        fseek(*indexTable, 0, SEEK_END);
        fseek(*masterFile, 0, SEEK_END);

        writeContributor(&contributor, masterFile);

        size = ftell(*indexTable);
        cellsNumb = size / (sizeof(unsigned int) + sizeof(unsigned long));

        fwrite(&contributor.userID, sizeof(unsigned long), 1, *indexTable);
        fwrite(&cellsNumb, sizeof(unsigned int), 1, *indexTable);
        fwrite(&status, sizeof(unsigned int), 1, *indexTable);

        return true;
    }
}

bool insert_s(char *ptr, FILE **masterFile, FILE **indexTable, FILE **slaveFile) {
    long id;
    char *tmp = ptr;

    if (ptr != NULL) {
        char *pEnd;
        id = strtol(ptr, &pEnd, 10);
        ptr = strtok(NULL, " ");
        setbuf(stdout, 0);
        printf("%ld", id);
        if (ptr != NULL)
            return false;
    } else {
        return false;
    }

    if (getContributorID(id, indexTable) != -1) {
        setbuf(stdout, 0);
        printf("ID exists. Try to enter another one");
        return insert_s(tmp, masterFile, indexTable, slaveFile);
    } else {

        return true;
    }
}

int getContributorID(unsigned long id, FILE **f) {
    unsigned long tmpID = 0;
    unsigned int index = 0, status = 0;
    fseek(*f, 0, SEEK_SET);
    while (fread(&tmpID, sizeof(unsigned long), 1, *f) == 1) {
        fread(&index, sizeof(unsigned int), 1, *f);
        fread(&status, sizeof(unsigned int), 1, *f);
        if (tmpID == id && status == 1)
            return index;
    }
    return -1;
}