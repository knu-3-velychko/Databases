#include "io.h"

struct Contributor *readContributor() {
    struct Contributor *contributor = malloc(sizeof(struct Contributor));
    char name[25];
    setbuf(stdout, 0);
    printf("\nEnter Contributor name:");
    scanf("%s", name);
    strcpy(contributor->name, name);
    setbuf(stdout, 0);
    printf("\nEnter Contributor e-mail:");
    scanf("%s", contributor->eMail);
    setbuf(stdout, 0);
    printf("\nEnter Contributor password:");
    scanf("%s", contributor->password);
    setbuf(stdout, 0);
    printf("\nEnter Contributor address:");
    scanf("%s", contributor->address);
    return contributor;
}

struct Image *readImage() {
    struct Image *image = malloc(sizeof(struct Image));
    char width[25], height[25], earnings[25];
    setbuf(stdout, 0);
    printf("\nEnter Image type:");
    scanf("%s", image->imageType);
    setbuf(stdout, 0);
    printf("\nEnter Image width:");
    scanf("%s", width);
    image->width = strtof(width, NULL);
    setbuf(stdout, 0);
    printf("\nEnter Image height:");
    scanf("%s", height);
    image->height = strtof(height, NULL);
    setbuf(stdout, 0);
    printf("\nEnter earning for Image:");
    scanf("%s", earnings);
    image->earnings = strtof(earnings, NULL);
    setbuf(stdout, 0);
    printf("\nEnter Image status:");
    scanf("%s", image->status);
    image->date = readDate();
    return image;
}

struct Date *readDate() {
    struct Date *date = malloc(sizeof(struct Date));
    date->year = readTimeUnit("Enter Year: ", 1920, 2019);
    date->month = readTimeUnit("Enter Month: ", 1, 12);
    unsigned int days = 31;
    if (date->month == 2) {
        if (date->year % 4 == 0) {
            days = 29;
        } else {
            days = 28;
        }
    } else if (date->month == 4 || date->month == 6 || date->month == 9 || date->month == 11) {
        days = 30;
    } else {
        days = 31;
    }
    date->day = readTimeUnit("Enter Day: ", 1, days);
    date->hour = readTimeUnit("Enter Hour: ", 0, 24);
    if (date->hour == 24) {
        date->minute = readTimeUnit("Enter Minute: ", 0, 0);
    } else {
        date->minute = readTimeUnit("Enter Minute: ", 0, 60);
    }
    return date;
}

unsigned int readTimeUnit(const char *text, const int left, const int right) {
    char unitStr[5];
    unsigned int unit = 0;
    bool valid = false;
    while (!valid) {
        setbuf(stdout, 0);
        printf("\n%s", text);
        scanf("%s", unitStr);
        unit = strtol(unitStr, NULL, 10);
        if (unit >= left && unit <= right)
            valid = true;
    }
    return unit;
}

void writeContributor(const struct Contributor *contributor, FILE **masterFile) {
    int status = 1;
    fwrite(contributor, sizeof(struct Contributor), 1, *masterFile);
    fwrite(&status, sizeof(unsigned int), 1, *masterFile);
    printf("%ld", ftell(*masterFile));
}

void writeImage(const struct Image *image, FILE **slaveFile) {
    int status = 1;
    fwrite(image, sizeof(struct Image), 1, *slaveFile);
    fwrite(&status, sizeof(unsigned int), 1, *slaveFile);
}

void writeDate(const struct Date *date, FILE **slaveFile) {
    fwrite(&date->year, sizeof(unsigned int), 1, *slaveFile);
    fwrite(&date->month, sizeof(unsigned int), 1, *slaveFile);
    fwrite(&date->day, sizeof(unsigned int), 1, *slaveFile);
    fwrite(&date->hour, sizeof(unsigned int), 1, *slaveFile);
    fwrite(&date->minute, sizeof(unsigned int), 1, *slaveFile);
}