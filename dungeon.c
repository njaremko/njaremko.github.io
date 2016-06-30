#include<stdio.h>
#include<stdlib.h>
#include<string.h> //strtok

#define DUNGEONSIZE 10

char *map[DUNGEONSIZE][DUNGEONSIZE];
int i = 0, j = 0;
static char *progname;
char input[80];
char *command;
int x = 0, y = 0;
FILE *fp;
char *line;
size_t len = 0;
ssize_t read_line;

// Used to set the map to a value at a given x and y
void setMap(int x, int y, char *value) {
    if ((map[x][y] = malloc(strlen(value) + 1)) == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    strcpy(map[x][y], value);
}

int main(int argc, char **argv) {
    int status = 0;

    progname = argv[0];

    if (argc != 2) {
        fprintf(stderr, "usage: %s filename\n", progname);
        return(status);
    }



    if ((fp = fopen(argv[1], "r")) == NULL) {
        perror(argv[1]);
        exit(1);
    }

    char *token;
    while ((read_line = getline(&line, &len, fp)) != EOF) {
        if (i < DUNGEONSIZE) {
            token = strtok(line, " \t");
            for (j = 0; j < DUNGEONSIZE; j++) {
                if(token) {
                    if (strcmp(token, " ")) {
                        // if a token contains a newline char, remove it...
                        token[strcspn(token, "\r\n")] = 0;
                        setMap(i,j, token);
                    }
                    token = strtok(NULL, " \t");
                } else {
                    // No more tokens for this row, so fill it with "pass"
                    setMap(i,j, "pass");
                }
            }
            i += 1;
        }
    }


    // Fill the remainder of the dungeon if we're out of tokens...
    for (i=i; i < DUNGEONSIZE; i++) {
        for (j = 0; j < DUNGEONSIZE; j++) {
            setMap(i,j, "pass");
        }
    }

    printf("Your currently in room %s:\n", map[x][y]);
    while (fgets(input, 80, stdin) != NULL) {
        if ((command = strchr(input, 'm')) != NULL) {
            // print the dunegeon for debugging purposes...
            for (i=0; i < DUNGEONSIZE; i++) {
                for (j=0; j < DUNGEONSIZE; j++) {
                    printf("%s\t", map[i][j]);
                }
                printf("\n");
            }
        } else if ((command = strchr(input, 'n')) != NULL) {
            if (x == 0) {
                x = DUNGEONSIZE-1;
            } else {
                x -= 1;
            }
            while(!strcmp(map[x][y], "pass")) {
                if (x == 0) {
                    x = DUNGEONSIZE-1;
                } else {
                    x -= 1;
                }
            }
        } else if ((command = strchr(input, 'e')) != NULL) {
            if (y == DUNGEONSIZE-1) {
                y = 0;
            } else {
                y += 1;
            }
            while(!strcmp(map[x][y], "pass")) {
                if (y == DUNGEONSIZE-1) {
                    y = 0;
                } else {
                    y += 1;
                }
            }
        } else if ((command = strchr(input, 's')) != NULL) {
            if (x == DUNGEONSIZE-1) {
                x = 0;
            } else {
                x += 1;
            }
            while(!strcmp(map[x][y], "pass")) {
                if (x == DUNGEONSIZE-1) {
                    x = 0;
                } else {
                    x += 1;
                }
            }
        } else if ((command = strchr(input, 'w')) != NULL) {
            if (y == 0) {
                y = DUNGEONSIZE-1;
            } else {
                y -= 1;
            }
            while(!strcmp(map[x][y], "pass")) {
                if (y == 0) {
                    y = DUNGEONSIZE-1;
                } else {
                    y -= 1;
                }
            }
        }
        printf("\nYour currently in room %s:\n", map[x][y]);
    }

    fclose(fp);

    return (status);
}
