#include "insert.h"

bool insert_m(char *ptr, FILE **masterFile, FILE **indexTable) {
    if (ptr != NULL) {
        printf("Wrong command.");
        return false;
    }
    unsigned long userID = 0, size = 0;
    int cellsNumb = 0, status = 1;
    char name[25], eMail[25], password[25], address[25];
    printf("\nEnter Contributor User ID:");
    scanf("%ld", &userID);
    if (!checkContributorID(userID, indexTable)) {
        printf("ID exists. Try to enter another one");
        return insert_m(ptr, masterFile, indexTable);
    } else {
        printf("\nEnter Contributor name:");
        scanf("%s", name);
        printf("\nEnter Contributor e-mail:");
        scanf("%s", eMail);
        printf("\nEnter Contributor password:");
        scanf("%s", password);
        printf("\nEnter Contributor address:");
        scanf("%s", address);

        struct Contributor contributor = {
                .userID=userID,
                .name=name,
                .eMail=eMail,
                .password=password,
                .address=address};

        fseek(*indexTable, 0, SEEK_END);
        fseek(*masterFile, 0, SEEK_END);

        size = ftell(*indexTable);
        cellsNumb = size / (sizeof(unsigned int) + sizeof(unsigned long));

        fwrite(&userID, sizeof(unsigned long), 1, *indexTable);
        fwrite(&cellsNumb, sizeof(unsigned int), 1, *indexTable);
        fwrite(&status, sizeof(unsigned int), 1, *indexTable);

        fwrite(&userID, sizeof(unsigned long), 1, *masterFile);
        fwrite(name, sizeof(char), 25, *masterFile);
        fwrite(eMail, sizeof(char), 25, *masterFile);
        fwrite(password, sizeof(char), 10, *masterFile);
        fwrite(address, sizeof(char), 25, *masterFile);
        fwrite(&status, sizeof(unsigned int), 1, *masterFile);

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