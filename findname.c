#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>

int rsearch(char *path, char *target) {
    DIR *dir;
    struct dirent *dstruct;
    if ((dir = opendir(path)) != NULL) {
        while ((dstruct = readdir (dir)) != NULL) {
            if (dstruct->d_type == DT_DIR) {
                if (strcmp(dstruct->d_name, ".")) {
                    if (strcmp(dstruct->d_name, "..")) {
                        char *new_path;
                        if ((new_path = malloc(strlen(path)+strlen(dstruct->d_name)+2)) != NULL) {
                            strcpy(new_path, path);
                            strcat(new_path, "/");
                            strcat(new_path, dstruct->d_name);
                            rsearch(new_path, target);
                        } else {
                            fprintf(stderr, "malloc failed");
                            return(EXIT_FAILURE);
                        }
                    }
                }
            }
            if(!strcmp(dstruct->d_name, target)) {
                printf("%s//%s\n", path, target);
            }
        }
    } else {
        fprintf(stderr, "Cannot open %s\n", path);
        return(EXIT_FAILURE);
    }
    return 0;
}

int main(int argc, char *argv[]) {
    char *filename;
    static char *progname;
    int status = 0;

    progname = argv[0];

    if (argc < 3) {
        fprintf(stderr, "usage: %s filename\n", progname);
    }

    filename = argv[1];

    int i;
    for (i = 2; i < argc; i++) {
        status = rsearch(argv[i], filename);
    }

    return(status);
}
