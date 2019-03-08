#ifndef Queue_H
#define Queue_H

#include "Node.h"

/**
 * QNode represents a generic queue Node with data(in our case a Node or state)
 * and a pointer to the next QNode.
 */
typedef struct QNode {

    Node *data;
    struct QNode *next;

} QNode;

/**
 * Queue struct with the head and tail of the Queue.
 */
typedef struct Queue {
    struct QNode *head, *tail;
} Queue;

/**
 * Constructor of a Queue.
 * @return pointer to the newly constructed Queue.
 */
Queue *initQueue();

/**
 * Enqueues given Node to given Queue.
 *
 * @param queue
 * @param node
 */
void enqueue(Queue *queue, Node *node);

/**
 * Initialises a QNode from a Node.
 *
 * @param node
 * @return pointer to newly constructed QNode.
 */
QNode *initQNode(Node *node);

/**
 * @param queue
 * @return if Queue has no element.
 */
bool isEmpty(Queue *queue);

/**
 * Removes and returns the head of the queue.
 *
 * @param queue
 * @return head of the queue.
 */
Node *poll(Queue *queue);

/**
 * Free the memory that this Queue allocates.
 *
 * @param queue
 */
void destructQueue(Queue *queue);

#endif