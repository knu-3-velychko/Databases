#include "update.h"

bool update_m(char *ptr, FILE **indexFile, FILE **masterFile) {
    long id;

    if (ptr != NULL) {
        char *pEnd;
        id = strtol(ptr, pEnd, 10);
        ptr = strtok(NULL, " ");
        setbuf(stdout, 0);printf("%ld", id);
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
            int status = 1;
//            unsigned long userID = 0, size = 0;
//            char name[25], eMail[25], password[10], address[25];
            fseek(*masterFile, index * (sizeof(unsigned long) + sizeof(char) * (25 * 3 + 10) + sizeof(unsigned int)),
                  SEEK_SET);

            setbuf(stdout, 0);printf("\nEnter new Contributor name:");
            scanf("%s", contributor.name);
            setbuf(stdout, 0);printf("\nEnter new Contributor e-mail:");
            scanf("%s", contributor.eMail);
            setbuf(stdout, 0);printf("\nEnter new Contributor password:");
            scanf("%s", contributor.password);
            setbuf(stdout, 0);printf("\nEnter new Contributor address:");
            scanf("%s", contributor.address);
            fwrite(&contributor.userID, sizeof(unsigned long), 1, *masterFile);
            fwrite(contributor.name, sizeof(char), 25, *masterFile);
            fwrite(contributor.eMail, sizeof(char), 25, *masterFile);
            fwrite(contributor.password, sizeof(char), 10, *masterFile);
            fwrite(contributor.address, sizeof(char), 25, *masterFile);
            fwrite(&status, sizeof(unsigned int), 1, *masterFile);
            return true;
        }
    }
    setbuf(stdout, 0);printf("ID %ld does not exist.", id);
    return true;
}

bool update_s(char *ptr) {
    return true;
}