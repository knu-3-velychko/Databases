#include "structures.h"

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