#include "insert.h"

int IMAGE_NUMBER = -1;

bool insert_m(char *ptr, FILE **masterFile) {
    if (ptr != NULL) {
        setbuf(stdout, 0);
        printf("Wrong command.");
        return false;
    }

    char userID[21];
    unsigned long id = 0;
    setbuf(stdout, 0);
    printf("\nEnter Contributor User ID:");
    scanf("%s", userID);
    id = strtol(userID, NULL, 10);

    if (getContributorID(id, masterFile) != -1) {
        setbuf(stdout, 0);
        printf("ID exists. Try to enter another one");
        return insert_m(ptr, masterFile);
    } else {
        struct Contributor *contributor = readContributor();
        contributor->userID = id;

        fseek(*masterFile, 0, SEEK_END);
        long index = ftell(*masterFile) / (sizeof(struct Contributor) + sizeof(int));
        writeContributor(contributor, masterFile);
        add(id, index);
        return true;
    }

}

int getContributorID(const unsigned long id, FILE **masterFile) {
    unsigned int status = 0;
    int index = searchTable(id);
    printf("%i",index);
    if (index != -1) {
        fseek(*masterFile, (index + 1) * sizeof(struct Contributor), SEEK_SET);
        fread(&status, sizeof(unsigned int), 1, *masterFile);
        if (status == 1)
            return index;
    }
    return -1;
}

/*

bool insert_s(char *ptr, FILE **masterFile, FILE **indexTable, FILE **slaveFile) {
    unsigned long contributorID = 0;
    char *tmp = ptr;

    if (ptr != NULL) {
        char *pEnd;
        contributorID = strtol(ptr, &pEnd, 10);
        ptr = strtok(NULL, " ");
        setbuf(stdout, 0);
        printf("%ld", contributorID);
        if (ptr != NULL)
            return false;
    } else {
        return false;
    }

    int index = 0, imageIndex = -1;
    if ((index = getContributorID(contributorID, indexTable)) == -1) {
        setbuf(stdout, 0);
        printf("ID not exists. Try to enter another one");
        return insert_s(tmp, masterFile, indexTable, slaveFile);
    } else {
        imageIndex = getImageIndex(index, masterFile);
        if (imageIndex != -1) {
            fseek(*slaveFile, 0, SEEK_SET);
            if (IMAGE_NUMBER != -1) {
                IMAGE_NUMBER = count_all(NULL, slaveFile);
            }

        }
        return true;
    }
}

int getImageID(const unsigned long id, FILE **slaveFile) {
    unsigned long tmpID = 0;
    unsigned int index = 0;
}

int getImageIndex(const int index, FILE **masterFile) {
    int imageIndex = -1;
    fseek(*masterFile, 0, SEEK_SET);
    fseek(*masterFile, CONTRIBUTOR_SIZE * (index + 1), SEEK_SET);
    fseek(*masterFile, -sizeof(int) * 2, SEEK_SET);
    fread(&imageIndex, sizeof(int), 1, *masterFile);
    return imageIndex;
}

void setImageIndex(const int contributorIndex, const int imageIndex, FILE **masterFile) {
    fseek(*masterFile, 0, SEEK_SET);
    fseek(*masterFile, CONTRIBUTOR_SIZE * (contributorIndex + 1), SEEK_SET);
    fseek(*masterFile, -sizeof(int) * 2, SEEK_SET);
    fwrite(&imageIndex, sizeof(int), 1, SEEK_SET);
}
 */

