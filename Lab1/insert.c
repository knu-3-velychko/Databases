#include "insert.h"

int IMAGE_NUMBER = -1;

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
            int lastImage = getLastImage(imageIndex, slaveFile);
            fseek(*slaveFile, 0, SEEK_SET);
            fseek(*slaveFile, lastImage * IMAGE_SIZE, SEEK_SET);

            if (IMAGE_NUMBER != -1){

            }
        }
        return true;
    }
}

int getContributorID(const unsigned long id, FILE **f) {
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

int getImageIndex(const int index, FILE **masterFile) {
    int imageIndex = -1;
    fseek(*masterFile, 0, SEEK_SET);
    fseek(*masterFile, CONTRIBUTOR_SIZE * (index + 1), SEEK_SET);
    fseek(*masterFile, -sizeof(int) * 2, SEEK_SET);
    fread(&imageIndex, sizeof(int), 1, *masterFile);
    return imageIndex;
}

int getLastImage(const int index, FILE **slaveFile) {
    int currentImage = index, nextImage = index;
    while (nextImage != -1) {
        currentImage = nextImage;
        fseek(*slaveFile, 0, SEEK_SET);
        fseek(*slaveFile, (index + 1) * IMAGE_SIZE, SEEK_SET);
        fseek(*slaveFile, -sizeof(int), SEEK_SET);
        fread(&nextImage, sizeof(int), 1, *slaveFile);
    }
    return currentImage;
}