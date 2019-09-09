#include "insert.h"

bool insert_m(char *ptr, FILE **masterFile, FILE **indexTable) {
    if (ptr != NULL) {
        printf("Wrong command.");
        return false;
    }
    struct Contributor contributor;
    unsigned long
//            userID = 0,
            size = 0;
    int cellsNumb = 0, status = 1;
//    char name[25], eMail[25], password[25], address[25];
    printf("\nEnter Contributor User ID:");
    scanf("%ld", &contributor.userID);
    if (!checkContributorID(contributor.userID, indexTable)) {
        printf("ID exists. Try to enter another one");
        return insert_m(ptr, masterFile, indexTable);
    } else {

        printf("\nEnter Contributor name:");
        scanf("%s", contributor.name);
        printf("\nEnter Contributor e-mail:");
        scanf("%s", contributor.eMail);
        printf("\nEnter Contributor password:");
        scanf("%s", contributor.password);
        printf("\nEnter Contributor address:");
        scanf("%s", contributor.address);

        fseek(*indexTable, 0, SEEK_END);
        fseek(*masterFile, 0, SEEK_END);

        size = ftell(*indexTable);
        cellsNumb = size / (sizeof(unsigned int) + sizeof(unsigned long));

        fwrite(&contributor.userID, sizeof(unsigned long), 1, *indexTable);
        fwrite(&cellsNumb, sizeof(unsigned int), 1, *indexTable);
        fwrite(&status, sizeof(unsigned int), 1, *indexTable);

        fwrite(&contributor.userID, sizeof(unsigned long), 1, *masterFile);
        fwrite(contributor.name, sizeof(char), 25, *masterFile);
        fwrite(contributor.eMail, sizeof(char), 25, *masterFile);
        fwrite(contributor.password, sizeof(char), 10, *masterFile);
        fwrite(contributor.address, sizeof(char), 25, *masterFile);
        fwrite(&status, sizeof(unsigned int), 1, *masterFile);
        return true;
    }
    return true;
}

bool insert_s(char *ptr, FILE **f) {
    return true;
}

bool checkContributorID(unsigned long id, FILE **f) {
    unsigned long tmpID = 0;
    unsigned int index = 0, status = 0;
    fseek(*f, 0, SEEK_SET);
    while (fread(&tmpID, sizeof(unsigned long), 1, *f) == 1) {
        fread(&index, sizeof(unsigned int), 1, *f);
        fread(&status, sizeof(unsigned int), 1, *f);
        if (tmpID == id && status == 1)
            return false;
    }
    return true;
}