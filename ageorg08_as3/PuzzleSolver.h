#ifndef AS3_PUZZLESOLVER_H
#define AS3_PUZZLESOLVER_H

#include <time.h>
#include "Node.h"
#include "Queue.h"
#include "PriorityQueue.h"
#include "SuffixTree.h"

/**
 * Will attempt to solve a puzzle based on chosen method.
 *
 * @param puzzle
 * @param N, size of puzzle
 * @param choice, algorithm of choice
 * @param outputFile, name of file to write to the possible solution.
 * @return EXIT code for method.
 */
int solvePuzzle(int *puzzle, int N, char *choice, char *outputFile);

/**
 * Finds the zero coordinates in given puzzle.
 *
 * @param zeroX
 * @param zeroY
 * @param puzzle
 * @param N, size of puzzle
 * @return EXIT code for method.
 */
int findZero(int *zeroX, int *zeroY, int *puzzle, int N);

/**
 * Solves the puzzle by exploring the possible states with the breadth
 * first search algorithm.
 *
 * f(node) = 0
 *
 * @param puzzle
 * @param N, size of puzzle
 * @param zeroX
 * @param zeroY
 * @param outputFile, where to write the solution
 */
void breadth(int *puzzle, int N, int zeroX, int zeroY, char *outputFile);

/**
 * Solves the puzzle by exploring the possible states with the best first search
 * algorithm which chooses which Node to explore based on the smallest heuristic
 * value(supposedly closer to solution).
 *
 * f(node) = node.h
 *
 * @param puzzle
 * @param N, size of puzzle
 * @param zeroX
 * @param zeroY
 * @param outputFile, where to write the solution
 */
void best(int *puzzle, int N, int zeroX, int zeroY, char *outputFile);

/**
 * Solves the puzzle by exploring the possible states with the a-star
 * algorithm which chooses which Node to explore based on the smallest heuristic
 * value combined with the number of moves taken to get to each Node.
 *
 * f(node) = node.g + node.h
 *
 * @param puzzle
 * @param N, size of puzzle
 * @param zeroX
 * @param zeroY
 * @param outputFile, where to write the solution
 */
void a_star(int *puzzle, int N, int zeroX, int zeroY, char *outputFile);

/**
 * Prints the path of the solution to the screen and to denoted output file.
 *
 * @param node
 * @param outputFile
 */
void printPath(Node *node, char *outputFile);

#endif //AS3_PUZZLESOLVER_H
