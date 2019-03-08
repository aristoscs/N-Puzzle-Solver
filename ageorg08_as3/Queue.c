#include "Queue.h"

//#define DEBUG
#if defined (DEBUG)

static void test_enqueue() {
    Queue *queue = initQueue();

    int grid1[] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    enqueue(queue, initNode(grid1, 3, 3, 3, 3));
    // Head and Tail should be a node in which the hash should be the above grid
    if(strcmp(queue->head->data->hash, "123456780") != 0)
        printf("Head of queue is not initialised correctly.\n");
    if(strcmp(queue->tail->data->hash, "123456780") != 0)
        printf("Tail of queue is not initialised correctly.\n");

    // Tail should now change
    int grid2[] = {3, 2, 1, 5, 4, 7, 6, 0, 8};
    enqueue(queue, initNode(grid2, 3, 3, 3, 3));
    if(strcmp(queue->tail->data->hash, "321547608") != 0)
        printf("Tail of queue is not initialised correctly.\n");

    destructQueue(queue);
}

static void test_poll() {
    // Suppose we enqueue 2 nodes
    Queue *queue = initQueue();

    int grid2[] = {3, 2, 1, 5, 4, 7, 6, 0, 8};
    enqueue(queue, initNode(grid2, 3, 3, 3, 3));

    int grid1[] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    enqueue(queue, initNode(grid1, 3, 3, 3, 3));

    // We should be able to enqueue 2 times without a problem
    // Dequeue order should be FIFO

    Node *poll1 = poll(queue);
    if(strcmp("321547608", poll1->hash) != 0)
        printf("Queue gave wrong element: Expected: 321547608, Actual: %s", poll1->hash);

    Node *poll2 = poll(queue);
    if(strcmp("123456780", poll2->hash) != 0)
        printf("Queue gave wrong element: Expected: 123456780, Actual: %s", poll2->hash);

}

int main(void) {
    test_enqueue();
    test_poll();
    return 0;
}

#endif

Queue *initQueue() {
    Queue *queue = malloc(sizeof(Queue));
    queue->head = queue->tail = NULL;
    return queue;
}

QNode *initQNode(Node *node) {
    QNode *new = malloc(sizeof(QNode));
    new->data = node;
    new->next = NULL;
    return new;
}

void enqueue(Queue *queue, Node *node) {
    QNode *new = initQNode(node);
    if (queue->tail == NULL) {
        queue->head = queue->tail = new;
        return;
    }

    queue->tail->next = new;
    queue->tail = new;
}

bool isEmpty(Queue *queue) {
    return queue->head == NULL;
}

Node *poll(Queue *queue) {
    if (isEmpty(queue))
        return NULL;

    QNode *temp = queue->head;
    queue->head = queue->head->next;
    Node *node = temp->data;

    if (queue->head == NULL)
        queue->tail = NULL;

    free(temp);
    return node;
}

void destructQueue(Queue *queue) {
    while (!isEmpty(queue)) {
        poll(queue);
    }
    free(queue);
}