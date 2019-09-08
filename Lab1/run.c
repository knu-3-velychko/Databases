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

    fclose(masterFile);
    fclose(indexTable);
    fclose(slaveFile);

    return true;
}


bool openFile(const char fName[25], FILE **ptr) {
    *ptr = fopen(fName, "r+");
    if (*ptr == NULL) {
        printf("File %s does not exist!\n", fName);
        printf("Creating new %s file...\n", fName);
        *ptr = fopen(fName, "w+");
        if (*ptr == NULL) {
            printf("Creation failed.\n");
            return false;
        }
        printf("Creation successed.\n");
    }
    return true;
}

bool listen(FILE **masterFile, FILE **indexFile, FILE **slaveFile) {
    char buffer[100];
    while (gets(buffer)) {
        char *ptr = strtok(buffer, " ");
        if (ptr == NULL || strcmp(ptr, "end") == 0)
            break;
        else if (strcmp(ptr, "insert-m") == 0) {
            ptr = strtok(NULL, " ");
            if (insert_m(ptr, masterFile, indexFile))
                continue;
            else
                return false;
        } else if (strcmp(ptr, "insert-s") == 0) {
            ptr = strtok(NULL, " ");
            if (insert_s(ptr, slaveFile))
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
//        else if (strcmp(ptr, "del-m") == 0) {
//            ptr = strtok(NULL, " ");
//            if (del_m(ptr))
//                continue;
//            else
//                return false;
//        }
//        else if (strcmp(ptr, "del-s") == 0) {
//            ptr = strtok(NULL, " ");
//            if (del_s(ptr))
//                continue;
//            else
//                return false;
//        }
//        else if (strcmp(ptr, "update-m") == 0) {
//            ptr = strtok(NULL, " ");
//            if (update_m(ptr))
//                continue;
//            else
//                return false;
//        }
//        else if (strcmp(ptr, "update-s") == 0) {
//            ptr = strtok(NULL, " ");
//            if (update_s(ptr))
//                continue;
//            else
//                return false;
//        }
        else if (strcmp(ptr, "count-m") == 0) {
            ptr = strtok(NULL, " ");
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
//        else if (strcmp(ptr, "count-all") == 0) {
//            ptr = strtok(NULL, " ");
//            if (count_all(ptr))
//                continue;
//            else
//                return false;
//        }
        else {
            printf("Wrong command!");
            continue;
        }
    }
    return true;
}
