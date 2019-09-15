#include "get.h"

bool get_m(char *ptr, FILE **masterFile) {
    long id;

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

    int index = 0;
    if ((index = getContributorIndex(id, masterFile)) == -1) {
        setbuf(stdout, 0);
        printf("ID does not exist. Try to enter another one");
        return true;
    } else {
        struct Contributor *contributor = malloc(sizeof(struct Contributor));
        fseek(*masterFile, sizeof(struct Contributor) * index, SEEK_SET);
        fread(contributor, sizeof(struct Contributor), 1, *masterFile);
        printContributor(contributor);
        return true;
    }
}

/*

}

bool get_s(char *ptr) {
    return true;
}

bool get_i(char *ptr) {
    return true;
}*/