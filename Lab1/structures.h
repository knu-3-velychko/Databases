//
// Created by Taya on 9/8/2019.
//

#ifndef UNTITLED_STRUCTURES_H
#define UNTITLED_STRUCTURES_H

struct Date {
    int year;
    int month;
    int day;
    int hour;
    int minute;
};

struct Contributor {
    unsigned long userID;
    char name[25];
    char eMail[25];
    char password[10];
    char address[25];
    int firstImage;
};

struct Contributor DefaultContributor();

struct Image {
    unsigned long imageID;
    char imageType[15];
    float width;
    float height;
    float earnings;
    char status[25];
    struct Date date;
    unsigned int nextIndex;
};

struct Cell {
    unsigned long id;
    unsigned int index;
};

#endif //UNTITLED_STRUCTURES_H
