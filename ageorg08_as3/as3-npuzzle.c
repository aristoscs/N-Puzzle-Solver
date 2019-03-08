#include "PuzzleReader.h"
#include "PuzzleSolver.h"

int main(int args, char *argv[]) {
    if (args != 4) {
        printf("Incorrect arguments, expected example:$ ./a3 a-star test3x3_6.txt solution.txt");
        return EXIT_FAILURE;
    }

    int min = 3;
    int max = 4;

    int n = 0;
    int *puzzle = NULL;

    if (readPuzzle(argv[2], &puzzle, &n, min, max) == EXIT_FAILURE) {
        printf("Puzzle not well defined or file cannot be found: %s\n", argv[2]);
        return EXIT_FAILURE;
    }

    if (solvePuzzle(puzzle, n, argv[1], argv[3]) == EXIT_FAILURE) {
        printf("Puzzle cannot be solved.\n");
        return EXIT_FAILURE;
    }

    free(puzzle);
    return EXIT_SUCCESS;
}