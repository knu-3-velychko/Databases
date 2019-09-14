#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Contributor readContributor();

struct Date readDate();

unsigned int readTimeUnit(const char *text, const int left, const int right);

void writeContributor(const struct Contributor *contributor, FILE **masterFile);

void writeDate(const struct Date *date, FILE **slaveFile);
