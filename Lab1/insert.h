#include "structures.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool insert_m(char *ptr, FILE **masterFile, FILE **indexFile);

bool insert_s(char *ptr, FILE **f);

bool checkContributorID(unsigned long id,FILE **indexTable);