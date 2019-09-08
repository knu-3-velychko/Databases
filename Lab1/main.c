#include <stdio.h>
#include "run.h"

int main() {

    const char contributorFName[25] = "Contributor.fl";
    const char contributorIndexTable[25] = "Contributor.ind";
    const char imageFName[25] = "Image.fl";


    bool success = function(contributorFName, contributorIndexTable, imageFName);
    if (success) {
        printf("Success!\n");
    }
    else{
        printf("Error handled!\n");
    }
    return 0;
}