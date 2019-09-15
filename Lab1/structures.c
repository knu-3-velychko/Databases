#include "structures.h"

const unsigned long CONTRIBUTOR_SIZE = sizeof(unsigned long) + sizeof(char) * (25 + 25 + 10 + 25) + sizeof(int);
const unsigned long DATE_SIZE = sizeof(unsigned int) * 5;
const unsigned long IMAGE_SIZE =
        sizeof(unsigned long) * 2 + sizeof(char) * (15 + 25) + sizeof(float) * 3 + DATE_SIZE + sizeof(int);

struct Contributor DefaultContributor() {
    struct Contributor contributor = {
            123456,
            "John",
            "john@gmail.com",
            "password",
            "address",
            -1};
    return contributor;
}

struct Date DefaultDate() {
    struct Date date = {
            2019,
            1,
            1,
            0,
            0
    };
    return date;
}

struct Image DefaultImage() {
    struct Image image = {
            123456,
            123456,
            "photo",
            2000.0,
            2000.0,
            0.0,
            "reviewed",
            DefaultDate(),
            -1
    };
    return image;
}