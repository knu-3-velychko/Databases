#include "io.h"

struct Contributor readContributor() {
    struct Contributor contributor = DefaultContributor();
    setbuf(stdout, 0);
    printf("\nEnter Contributor name:");
    scanf("%s", contributor.name);
    setbuf(stdout, 0);
    printf("\nEnter Contributor e-mail:");
    scanf("%s", contributor.eMail);
    setbuf(stdout, 0);
    printf("\nEnter Contributor password:");
    scanf("%s", contributor.password);
    setbuf(stdout, 0);
    printf("\nEnter Contributor address:");
    scanf("%s", contributor.address);
    return contributor;
}

void writeContributor(const struct Contributor *contributor, FILE **masterFile) {
    int status = 1;
    fwrite(&contributor->userID, sizeof(unsigned long), 1, *masterFile);
    fwrite(contributor->name, sizeof(char), 25, *masterFile);
    fwrite(contributor->eMail, sizeof(char), 25, *masterFile);
    fwrite(contributor->password, sizeof(char), 10, *masterFile);
    fwrite(contributor->address, sizeof(char), 25, *masterFile);
    fwrite(&contributor->firstImage, sizeof(unsigned int), 1, *masterFile);
    fwrite(&status, sizeof(unsigned int), 1, *masterFile);
}