#include "update.h"

bool update_m(char *ptr, FILE **masterFile) {
    int index = get_m(ptr, masterFile);
    if (index == -1)
        return false;
    unsigned long id = 0;
    fseek(*masterFile, sizeof(struct Contributor) * index, SEEK_SET);
    fread(&id, sizeof(unsigned long), 1, *masterFile);
    struct Contributor *contributor = readContributor();
    contributor->userID = id;
    fseek(*masterFile, sizeof(struct Contributor) * index, SEEK_SET);
    fwrite(contributor, sizeof(struct Contributor), 1, *masterFile);
    return true;
}