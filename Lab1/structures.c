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
};