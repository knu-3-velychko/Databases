#include "io.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool insert_m(char *ptr, FILE **masterFile, FILE **indexFile);

bool insert_s(char *ptr, FILE **masterFile, FILE **indexTable, FILE** slaveFile);

int getContributorID(unsigned long id, FILE **indexTable);