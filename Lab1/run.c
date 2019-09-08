#include "run.h"

bool function(const char mainFName[25], const char indexTableFName[25], const char slaveFName[25]) {
    //open or create database files
    FILE *mainFile, *indexTable, *slaveFile;
    if (!openFile(mainFName, mainFile))
        return false;
    if (!openFile(indexTableFName, indexTable))
        return false;
    if (!openFile(slaveFName, slaveFile))
        return false;

    if (!listen())
        return false;

    return true;
}


bool openFile(const char fName[25], FILE *ptr) {
    ptr = fopen(fName, "r+");
    if (ptr == NULL) {
        printf("File %s does not exist!\n", fName);
        printf("Creating new %s file...\n", fName);
        ptr = fopen(fName, "w+");
        if (ptr == NULL) {
            printf("Creation failed.\n");
            return false;
        }
        printf("Creation successed.\n");
    }
    return true;
}

bool listen() {
    char buffer[100];
    int i = 0;
    while (gets(buffer)) {
        char*  ptr=strtok(buffer," ");
        i = 0;
    }
}

