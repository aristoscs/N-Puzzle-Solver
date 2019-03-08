#include "PuzzleReader.h"

// Reads puzzle from file with limiting inputs
int readPuzzle(char *file, int **puzzle, int *n, int min, int max) {
    FILE *fp = fopen(file, "r");
    // NULL FILE CHECK
    if (fp == NULL) {
        return EXIT_FAILURE;
    }
    // ASSUME N FROM FIRST LINE
    char line[256] = "\0";
    fgets(line, 256, fp);
    if (getNumCount(line, n) == EXIT_FAILURE) {
        fclose(fp);
        return EXIT_FAILURE;
    }
    // VALID N CHECK
    if (*n < min || *n > max) {
        fclose(fp);
        return EXIT_FAILURE;
    }

    int index = 0;
    int *temp = malloc(*n * *n * sizeof(int));

    int lines = 0;
    do {
        lines += 1;
        // FILE LINES CHECK
        if (lines > *n) {
            free(temp);
            fclose(fp);
            return EXIT_FAILURE;
        }
        // CORRECT LINE CHECK
        if (putNums(line, temp, &index, *n) == EXIT_FAILURE) {
            free(temp);
            fclose(fp);
            return EXIT_FAILURE;
        }
    } while (fgets(line, 256, fp));

    // REPEATED NUMBERS CHECK
    int *counts = calloc((size_t) *n * *n, sizeof(int));
    int i;
    for (i = 0; i < *n * *n; i++) {
        counts[temp[i]]++;
    }
    for (i = 0; i < *n * *n; i++) {
        if (counts[i] != 1) {
            free(counts);
            free(temp);
            fclose(fp);
            return EXIT_FAILURE;
        }
    }
    free(counts);

    // FINALLY WE CAN ASSIGN!
    *puzzle = temp;
    fclose(fp);
    return EXIT_SUCCESS;
}

int putNums(char *line, int *puzzle, int *index, int n) {
    int temp, j = 0, count = 0;
    char *i;
    for (i = line; *i; i += j) {
        j = 1;
        if (isdigit(*i)) {
            sscanf(i, "%d%n", &temp, &j);
            if (temp < 0 || temp >= n * n) {
                return EXIT_FAILURE;
            }
            puzzle[*index] = temp;
            *index += 1;
            count += 1;
        } else if (!isspace(*i)) {
            return EXIT_FAILURE;
        }
        if (count > n) {
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

int getNumCount(char *line, int *n) {
    int temp, j = 0;
    char *i;
    for (i = line; *i; i += j) {
        j = 1;
        if (isdigit(*i)) {
            sscanf(i, "%d%n", &temp, &j);
            *n += 1;
        } else if (!isspace(*i)) {
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}