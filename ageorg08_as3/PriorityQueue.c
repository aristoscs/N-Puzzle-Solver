#include "PriorityQueue.h"

//#define DEBUG
#if defined (DEBUG)

static void test_priorityQueue() {
    // PriorityQueue testing by sorting an array of Nodes based on f value
    Node *array[6];
    int grid1[] = {1, 2, 3, 4, 5, 6, 7, 8, 0};

    array[0] = initNode(grid1, 3, 4, 2, 2);
    array[1] = initNode(grid1, 3, 2, 2, 2);
    array[2] = initNode(grid1, 3, 1, 2, 2);
    array[3] = initNode(grid1, 3, 2, 2, 2);
    array[4] = initNode(grid1, 3, 8, 2, 2);
    array[5] = initNode(grid1, 3, 7, 2, 2);

    PriorityQueue *queue = initPriorityQueue(compareF);
    int i;
    for (i = 0; i < 6; i++)
        priorityEnqueue(queue, array[i]);

    // Reconstruct array
    for (i = 0; i < 6; i++)
        array[i] = priorityPoll(queue);

    // Now they should be in sorted order based on g value since h is same
    // Before sorted: 4, 2, 1, 2, 8, 7
    // Check if array is sorted
    for (i = 0; i < 5; i++)
        if (array[i]->g > array[i + 1]->g)
            printf("Not sorted.\n");

    // Queue size should be 0 because we polled 6 times for the sort
    if(queue->size != 0)
        printf("Size should be 0\n");
}

int main(void) {
    test_priorityQueue();
    return 0;
}

#endif

PriorityQueue *initPriorityQueue(comparator compareTo) {
    PriorityQueue *new = malloc(sizeof(PriorityQueue));
    new->heap = malloc(2048 * sizeof(Node));
    new->size = 0;
    new->capacity = 2048;
    new->compare = *compareTo;
    return new;
}

void priorityEnqueue(PriorityQueue *queue, Node *node) {
    if (heapFull(queue))
        expand(queue);

    queue->heap[queue->size++] = node;
    promote(queue, queue->size - 1);
}

Node *priorityPoll(PriorityQueue *queue) {
    Node *toReturn = queue->heap[0];
    queue->heap[0] = queue->heap[queue->size - 1];
    queue->size -= 1;
    demote(queue, 0);
    return toReturn;
}

bool heapEmpty(PriorityQueue *queue) {
    return queue->size == 0;
}

bool heapFull(PriorityQueue *queue) {
    return queue->size == queue->capacity;
}

void expand(PriorityQueue *queue) {
    Node **larger = realloc(queue->heap, queue->size * 2 * sizeof(Node));
    queue->heap = larger;
    queue->capacity *= 2;
}

void promote(PriorityQueue *queue, int index) {
    Node *element = queue->heap[index];
    while (index > 0 &&
           queue->compare(element, queue->heap[getParent(index)]) < 0) {
        queue->heap[index] = queue->heap[getParent(index)];
        index = getParent(index);
    }
    queue->heap[index] = element;
}

void demote(PriorityQueue *queue, int index) {
    Node *element = queue->heap[index];
    while (kthChild(index, 1) < queue->size) {
        int min = minChild(queue, index);

        if (queue->compare(element, queue->heap[min]) < 0)
            break;

        queue->heap[index] = queue->heap[min];
        index = min;
    }
    queue->heap[index] = element;
}

int minChild(PriorityQueue *queue, int index) {
    int i = kthChild(index, 1);
    Node *c1 = queue->heap[i];
    Node *c2 = queue->heap[i + 1];
    if (queue->compare(c1, c2) <= 0)
        return i;
    else
        return i + 1;
}

int getParent(int index) {
    return (index - 1) >> 1;
}

int kthChild(int index, int childNumber) {
    return (index << 1) + childNumber;
}

void destructPriorityQueue(PriorityQueue *queue) {
    int i;
    for (i = 0; i < queue->size; i++) {
        destructNode(&queue->heap[i]);
    }
    free(queue->heap);
    free(queue);
}