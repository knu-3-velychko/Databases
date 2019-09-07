#include <stdio.h>
#include "run.h"

struct Date {
    int year;
    int month;
    int day;
    int hour;
    int minute;
};

struct Contributor {
    long userID;
    char eMail[25];
    char password[25];
    char name[25];
    char address[25];
};

struct Image {
    long imageID;
    char imageType[15];
    float width;
    float height;
    float earnings;
    char status[25];
    struct Date date;
    int nextIndex;
};

int main() {

    const char contributorFName[25] = "Contributor.fl";
    const char contributorIndexTable[25] = "Contributor.ind";
    const char imageFName[25] = "Image.fl";


    bool success = function(contributorFName, contributorIndexTable, imageFName);
    if (success) {
        printf("Success!\n");
    }
    else{
        printf("Error handled!\n");
    }
    return 0;
}