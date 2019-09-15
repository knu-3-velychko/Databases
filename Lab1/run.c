#include "run.h"

bool function(const char masterFName[25], const char indexTableFName[25], const char slaveFName[25]) {
    //open or create database files
    FILE *masterFile = NULL, *indexTable = NULL, *slaveFile = NULL;
    if (!openFile(masterFName, &masterFile))
        return false;
    if (!openFile(indexTableFName, &indexTable))
        return false;
    if (!openFile(slaveFName, &slaveFile))
        return false;

    if (!listen(&masterFile, &indexTable, &slaveFile))
        return false;

    rewrite(masterFName, indexTableFName, slaveFName,
            &masterFile, &indexTable, &slaveFile);

    return true;
}


bool openFile(const char fName[25], FILE **ptr) {
    *ptr = fopen(fName, "r+");
    if (*ptr == NULL) {
        setbuf(stdout, 0);
        printf("File %s does not exist!\n", fName);
        setbuf(stdout, 0);
        printf("Creating new %s file...\n", fName);
        *ptr = fopen(fName, "w+");
        if (*ptr == NULL) {
            setbuf(stdout, 0);
            printf("Creation failed.\n");
            return false;
        }
        setbuf(stdout, 0);
        printf("Creation successed.\n");
    }
    return true;
}

bool listen(FILE **masterFile, FILE **indexFile, FILE **slaveFile) {
    char buffer[100];
    while (gets(buffer)) {
        char *ptr = strtok(buffer, " ");
        if (ptr == NULL)
            continue;
        else if (strcmp(ptr, "end") == 0)
            break;
        else if (strcmp(ptr, "insert-m") == 0) {
            ptr = strtok(NULL, " ");
            if (insert_m(ptr, masterFile, indexFile))
                continue;
            else
                return false;
        } else if (strcmp(ptr, "insert-s") == 0) {
            ptr = strtok(NULL, " ");
            if (insert_s(ptr, masterFile, indexFile, slaveFile))
                continue;
            else
                return false;
        } else if (strcmp(ptr, "get-m") == 0) {
            ptr = strtok(NULL, " ");
            if (get_m(ptr, masterFile, indexFile))
                continue;
            else
                return false;
        }
//        else if (strcmp(ptr, "get-s") == 0) {
//            ptr = strtok(NULL, " ");
//            if (get_s(ptr))
//                continue;
//            else
//                return false;
//        }
//        else if (strcmp(ptr, "get-i") == 0) {
//            ptr = strtok(NULL, " ");
//            if (get_i(ptr))
//                continue;
//            else
//                return false;
//        }
        else if (strcmp(ptr, "del-m") == 0) {
            ptr = strtok(NULL, " ");
            if (del_m(ptr, masterFile, indexFile))
                continue;
            else
                return false;
        }
//        else if (strcmp(ptr, "del-s") == 0) {
//            ptr = strtok(NULL, " ");
//            if (del_s(ptr))
//                continue;
//            else
//                return false;
//        }
        else if (strcmp(ptr, "update-m") == 0) {
            ptr = strtok(NULL, " ");
            if (update_m(ptr, indexFile, masterFile))
                continue;
            else
                return false;
        }
//        else if (strcmp(ptr, "update-s") == 0) {
//            ptr = strtok(NULL, " ");
//            if (update_s(ptr))
//                continue;
//            else
//                return false;
//        }
        else if (strcmp(ptr, "count-m") == 0) {
            ptr = strtok(NULL, " ");
            setbuf(stdout, 0);
            printf("Number of cells in master file: %i", count_m(ptr, indexFile));
            continue;

        }
//        else if (strcmp(ptr, "count-s") == 0) {
//            ptr = strtok(NULL, " ");
//            if (count_s(ptr))
//                continue;
//            else
//                return false;
//        }
        else if (strcmp(ptr, "count-all") == 0) {
            ptr = strtok(NULL, " ");
            printf("Number of cells in slave file: %i", count_all(ptr, slaveFile));
            continue;
        } else {
            setbuf(stdout, 0);
            printf("Wrong command!");
            continue;
        }
    }
    return true;
}

void rewrite(const char masterFName[25], const char indexTableFName[25], const char slaveFName[25],
             FILE **masterFile, FILE **indexFile, FILE **slaveFile) {

    FILE *newMaster = fopen("master.fl", "w+");
    FILE *newIndex = fopen("master.ind", "w+");
    struct Contributor contributor;
    struct Cell array[100];
    unsigned int status = 0, s = 1, i = 0;
    fseek(*masterFile, 0, SEEK_SET);
    while (fread(&contributor.userID, sizeof(unsigned long), 1, *masterFile) == 1) {
        fread(contributor.name, sizeof(char), 25, *masterFile);
        fread(contributor.eMail, sizeof(char), 25, *masterFile);
        fread(contributor.password, sizeof(char), 10, *masterFile);
        fread(contributor.address, sizeof(char), 25, *masterFile);
        fread(&status, sizeof(unsigned int), 1, *masterFile);
        if (status == 1) {
            struct Cell tmp = {contributor.userID, i};
            array[i] = tmp;
            i++;
            writeContributor(&contributor, &newMaster);
        }
    }

    qsort(array, i, sizeof(*array), comp);

    for (unsigned int j = 0; j < i; j++) {
        fwrite(&array[j].id, sizeof(unsigned long), 1, newIndex);
        fwrite(&array[j].index, sizeof(unsigned int), 1, newIndex);
        fwrite(&s, sizeof(unsigned int), 1, newIndex);
        setbuf(stdout, 0);
        printf("%ld %i %i\n", array[j].id, array[j].index, s);
    }
    fclose(*masterFile);
    fclose(*indexFile);
    fclose(*slaveFile);

    remove(masterFName);
    remove(indexTableFName);

    fclose(newMaster);
    fclose(newIndex);
    rename("master.fl", masterFName);
    rename("master.ind", indexTableFName);
}

int comp(const void *elem1, const void *elem2) {
    struct Cell f = *((struct Cell *) elem1);
    if (elem2 == NULL)
        return 1;
    struct Cell s = *((struct Cell *) elem2);
    if (f.id > s.id) return 1;
    if (f.id < s.id) return -1;
    return 0;
}