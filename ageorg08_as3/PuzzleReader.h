#ifndef AS3_PUZZLEREADER_H
#define AS3_PUZZLEREADER_H

#include <ctype.h>
#include "Node.h"

/**
 * Reads from a txt containing the N puzzle.
 * Will perform various checks to confirm that puzzle read is valid.
 *
 * @param file, input file name.
 * @param puzzle, 2D array to be initialised with the contents of the file.
 * @param n, size of the puzzle.
 * @param min, min size allowed.
 * @param max, max size allowed.
 * @return EXIT CODE for method.
 */
int readPuzzle(char *file, int **puzzle, int *n, int min, int max);

/**
 * Reads all the numbers in a line and assigns the count to n
 * @param line
 * @param n
 * @return EXIT CODE for method.
 */
int getNumCount(char *line, int *n);

/**
 * Appends the numbers in a line to the puzzle.
 * @param line
 * @param puzzle
 * @param index for the next empty cell in the puzzle
 * @param n
 * @return EXIT CODE for method.
 */
int putNums(char *line, int *puzzle, int *index, int n);

#endif
