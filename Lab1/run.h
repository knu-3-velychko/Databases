//
// Created by Taya on 9/7/2019.
//

#ifndef UNTITLED_RUN_H
#define UNTITLED_RUN_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool function(const char mainFName[25], const char indexTableFName[25], const char slaveFName[25]);

bool openFile(const char fName[25],  FILE *ptr);

bool listen();


#endif //UNTITLED_RUN_H
