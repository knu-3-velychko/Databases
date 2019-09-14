#include "structures.h"
#include <stdio.h>

struct Contributor readContributor();

void writeContributor(const struct Contributor *contributor, FILE **masterFile);