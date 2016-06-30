#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> //getopt
#include<string.h> //strstr

static char *progname;
static int hflag = 0, lflag = 0, stdflag = 0, mflag = 0, count;

int main(int argc, char **argv) {
    int c, status = 0;
    FILE *fp;
    char *pattern;
    char *pattern_prefix;
    char *line;
    size_t len = 0;


    progname = argv[0];

    while ((c = getopt(argc, argv, "lhm:")) != EOF) {
        switch (c) {
            case 'l':
                lflag = 1;
                break;
            case 'h':
                hflag = 1;
                break;
            case 'm':
                mflag = 1;
                count = atoi(optarg);
                break;
            default:
                status = 1;
                break;
        }
    }

    pattern = argv[optind];

    if (argc < 2) {
        printf("%d", argc);
        fprintf(stderr, "usage: %s [-h] [-l] [-m ...] pattern filename\n", progname);
        return(status);
    } else if (optind == argc-1 || !strcmp(argv[argc-1], "-")){
        stdflag = 1;
    }

    if (stdflag) {
        int matchFound = 0;
        while ((getline(&line, &len, stdin)) != EOF) {
            if ((strstr(line, pattern)) != NULL) {
                if (mflag) {
                    if (!count) {
                        break;
                    }
                    count--;
                }
                if (lflag == 1) {
                    if (!matchFound) {
                        printf("stdin\n");
                        matchFound = 1;
                    }
                } else {
                    printf("%s", line);
                }
            }
        }
        return(status);
    }

    int i;
    for (i = optind + 1; i < argc; i++) {
        int matchFound = 0;
        if ((fp = fopen(argv[i], "r")) == NULL) {
            perror(argv[i]);
            exit(1);
        }

        while ((getline(&line, &len, fp)) != EOF) {
            if ((strstr(line, pattern)) != NULL) {
                if (mflag) {
                    if (!count) {
                        break;
                    }
                    if (!lflag)
                        count--;
                }
                if (lflag == 1) {
                    if (!matchFound) {
                        printf("%s\n", argv[i]);
                        count--;
                        matchFound = 1;
                    }
                } else if (hflag != 1 && argc > optind + 2) {
                    pattern_prefix = argv[i];
                    printf("%s:%s", pattern_prefix, line);
                } else {
                    printf("%s", line);
                }
            }
        }
    }

    fclose(fp);

    return (status);
}
