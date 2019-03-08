#ifndef AS3_PRIORITYQUEUE_H
#define AS3_PRIORITYQUEUE_H

#include "Node.h"

typedef int (comparator)(Node *, Node *);

/**
 * PriorityQueue represents a min binary heap used for fast retrieval of the
 * Node with the smallest cost according to the comparator passed to its
 * constructor.
 *
 * The heap is the array used for the implementations of the data structure.
 * Size is the current size of the heap.
 * Capacity is the threshold at which when reached the array has to expand.
 * comparator is a pointer to a function in which the heap will use to
 * organise the heap of Nodes accordingly.
 *
 */
typedef struct PriorityQueue {

    Node **heap;
    int size;
    int capacity;

    comparator *compare;

} PriorityQueue;

/**
 * Constructor for a PriorityQueue.
 *
 * @param compare, comparator function.
 * @return PriorityQueue pointer to the newly created PriorityQueue.
 */
PriorityQueue *initPriorityQueue(comparator compare);

/**
 * Puts a Node into the given PriorityQueue.
 *
 * @param queue
 * @param node
 */
void priorityEnqueue(PriorityQueue *queue, Node *node);

/**
 * @param queue
 * @return if PriorityQueue has no elements.
 */
bool heapEmpty(PriorityQueue *queue);

/**
 * @param queue
 * @return if PriorityQueue is at max capacity.
 */
bool heapFull(PriorityQueue *queue);

/**
 * Removes and returns the head of the PriorityQueue.
 *
 * @param queue
 * @return the head of the PriorityQueue.
 */
Node *priorityPoll(PriorityQueue *queue);

/**
 * Expands the array of this PriorityQueue.
 *
 * @param queue
 */
void expand(PriorityQueue *queue);

/**
 * Promotes a Node "up" the heap until heap property is restored.
 *
 * @param queue
 * @param index
 */
void promote(PriorityQueue *queue, int index);

/**
 * Demotes a Node "down" the heap until heap property is restored.
 *
 * @param queue
 * @param index
 */
void demote(PriorityQueue *queue, int index);

/**
 * Finds the index of the smallest children of a Node at given index.
 *
 * @param queue
 * @param index
 * @return index of the smallest children of a Node.
 */
int minChild(PriorityQueue *queue, int index);

/**
 * @param index of a Node.
 * @return index of the parent of a Node at given index.
 */
int getParent(int index);

/**
 * Calculates the position of the k-th child of any Node based on the
 * property that the heap looks like a full BST.
 *
 * @param index of a Node.
 * @param childNumber, which child of the Node you want.
 * @return index of k-th child of the Node.
 */
int kthChild(int index, int childNumber);

/**
 * Free the memory that this PriorityQueue allocates.
 *
 * @param queue
 */
void destructPriorityQueue(PriorityQueue *queue);

#endif //AS3_PRIORITYQUEUE_H
