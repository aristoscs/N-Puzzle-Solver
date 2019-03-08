#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#ifndef Node_H
#define Node_H

/**
 * Node represents each internal state of the puzzle.
 *
 * The grid and its size.
 * The moves it took to get to this state: g
 * The heuristic from this state to expected state: h
 * Total cost: g + h, calculated in constructor.
 * x, y: the coordinates of the zero.
 * hash: a string form of the grid.
 * move: a string representing the direction the zero moved to get this state.
 * parent: the previous state of the grid.
 *
 */
typedef struct Node {

    int *grid;
    int n;

    int f;
    int g;
    int h;

    int x;
    int y;

    char *hash;
    char *move;

    struct Node *parent;

} Node;

/**
 * Constructor for a Node.
 *
 * @param grid, puzzle.
 * @param n, size of puzzle.
 * @param g, moves to get to this state.
 * @param x, zero row position.
 * @param y, zero col position.
 * @return Node pointer to the newly created Node.
 */
Node *initNode(int *grid, int n, int g, int x, int y);

/**
 * Frees the memory from this Node.
 * @param node
 */
void destructNode(Node **node);

/**
 * @param node
 * @return manhattan heuristic for this Node.
 */
int manhattan(Node *node);

/**
 * Calculates the manhattan distance of just one number.
 * @param num
 * @param x
 * @param y
 * @param n
 * @return manhattan distance of just one number.
 */
int singleManhattan(int v, int i, int j, int n);

/**
 * Originally children was a field of struct Node but we don't have to save
 * them.
 *
 * @param node
 * @return array of Nodes which represent the children of this Node.
 */
Node **computeChildren(Node *node);

/**
 * @param node
 * @return copy of grid of this Node.
 */
int *newGrid(Node *node);

/**
 * Creates the hash from the grid of this Node for this Node.
 * @param node
 */
void reHash(Node *node);

/**
 * @param a, Node.
 * @param b, other Node.
 * @return negative if: a.h < b.h, positive if a.h > b.h
 */
int compareH(Node *a, Node *b);

/**
 * @param a, Node.
 * @param b, other Node.
 * @return negative if: a.f < b.f, positive if a.f > b.f
 */
int compareF(Node *a, Node *b);

#endif