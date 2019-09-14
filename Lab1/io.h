#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Contributor readContributor();

void writeContributor(const struct Contributor *contributor, FILE **masterFile);

struct Date readDate();

int readTimeUnit(const char *text, const int left, const int right);

