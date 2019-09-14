#include "io.h"

struct Contributor readContributor() {
    struct Contributor contributor = DefaultContributor();
    setbuf(stdout, 0);
    printf("\nEnter Contributor name:");
    scanf("%s", contributor.name);
    setbuf(stdout, 0);
    printf("\nEnter Contributor e-mail:");
    scanf("%s", contributor.eMail);
    setbuf(stdout, 0);
    printf("\nEnter Contributor password:");
    scanf("%s", contributor.password);
    setbuf(stdout, 0);
    printf("\nEnter Contributor address:");
    scanf("%s", contributor.address);
    return contributor;
}

void writeContributor(const struct Contributor *contributor, FILE **masterFile) {
    int status = 1;
    fwrite(&contributor->userID, sizeof(unsigned long), 1, *masterFile);
    fwrite(contributor->name, sizeof(char), 25, *masterFile);
    fwrite(contributor->eMail, sizeof(char), 25, *masterFile);
    fwrite(contributor->password, sizeof(char), 10, *masterFile);
    fwrite(contributor->address, sizeof(char), 25, *masterFile);
    fwrite(&contributor->firstImage, sizeof(unsigned int), 1, *masterFile);
    fwrite(&status, sizeof(unsigned int), 1, *masterFile);
}

struct Image readImage() {
    struct Image image;
    char width[25], height[25], earnings[25];
    setbuf(stdout, 0);
    printf("\nEnter Image type:");
    scanf("%s", image.imageType);
    setbuf(stdout, 0);
    printf("\nEnter Image width:");
    scanf("%s", width);
    image.width = strtof(width, NULL);
    setbuf(stdout, 0);
    printf("\nEnter Image height:");
    scanf("%s", height);
    image.height = strtof(height, NULL);
    setbuf(stdout, 0);
    printf("\nEnter earning for Image:");
    scanf("%s", earnings);
    image.earnings = strtof(earnings, NULL);
    setbuf(stdout, 0);
    printf("\nEnter Image status:");
    scanf("%s", image.status);


    return image;
}

struct Date readDate() {
    struct Date date;
    date.year = readTimeUnit("Enter Year: ", 1920, 2019);
    date.month = readTimeUnit("Enter Month: ", 1, 12);
    int days = 31;
    if (date.month == 2) {
        if (date.year % 4 == 0) {
            days = 29;
        } else {
            days = 28;
        }
    } else if (date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11) {
        days = 30;
    } else {
        days = 31;
    }
    date.day = readTimeUnit("Enter Day: ", 1, days);
    date.hour = readTimeUnit("Enter Hour: ", 0, 24);
    if (date.hour == 24) {
        date.minute = readTimeUnit("Enter Minute: ", 0, 0);
    } else {
        date.minute = readTimeUnit("Enter Minute: ", 0, 60);
    }
    return date;
}

int readTimeUnit(const char *text, const int left, const int right) {
    char unitStr[5];
    int unit = 0;
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