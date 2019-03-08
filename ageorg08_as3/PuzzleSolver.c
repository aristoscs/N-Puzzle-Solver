#include "PuzzleSolver.h"

#define TICK(X) clock_t X = clock()
#define TOCK(X) printf("time %g sec.\n", (double)(clock() - (X)) / CLOCKS_PER_SEC)

int solvePuzzle(int *puzzle, int n, char *choice, char *outputFile) {
    int zeroX = 0;
    int zeroY = 0;
    if (findZero(&zeroX, &zeroY, puzzle, n) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    if (strcmp(choice, "breadth") == 0) {
        breadth(puzzle, n, zeroX, zeroY, outputFile);
    } else if (strcmp(choice, "best") == 0) {
        best(puzzle, n, zeroX, zeroY, outputFile);
    } else if (strcmp(choice, "a-star") == 0) {
        a_star(puzzle, n, zeroX, zeroY, outputFile);
    }
    return EXIT_SUCCESS;
}

int findZero(int *zeroX, int *zeroY, int *puzzle, int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (puzzle[i * n + j] == 0) {
                *zeroX = i;
                *zeroY = j;
                return EXIT_SUCCESS;
            }
        }
    }
    return EXIT_FAILURE;
}

void breadth(int *puzzle, int n, int zeroX, int zeroY, char *outputFile) {
    TICK(x);
    Node *first = initNode(puzzle, n, 0, zeroX, zeroY);
    first->h = manhattan(first);
    first->f = first->h;

    Queue *open = initQueue();
    SuffixTree *closed = initTree();

    enqueue(open, first);
    while (!isEmpty(open)) {
        Node *current = poll(open);
        if (current->h == 0) {
            TOCK(x);
            printPath(current, outputFile);
            destructQueue(open);
            destructTree(closed);
            return;
        }

        Node **children = computeChildren(current);
        int i;
        for (i = 0; i < 4; i++) {
            Node *child = children[i];
            if (child == NULL)
                continue;
            if (!treeContains(closed, child->hash))
                enqueue(open, child);
        }
        addTree(closed, current->hash);
        free(children);
    }
    destructQueue(open);
    destructTree(closed);
}

void best(int *puzzle, int n, int zeroX, int zeroY, char *outputFile) {
    TICK(X);
    Node *first = initNode(puzzle, n, 0, zeroX, zeroY);

    first->h = manhattan(first);
    first->f = first->h;

    PriorityQueue *open = initPriorityQueue(compareH);
    SuffixTree *closed = initTree();

    priorityEnqueue(open, first);
    while (!heapEmpty(open)) {
        Node *current = priorityPoll(open);
        if (current->h == 0) {
            TOCK(X);
            printPath(current, outputFile);
            destructPriorityQueue(open);
            destructTree(closed);
            return;
        }

        Node **children = computeChildren(current);
        int i;
        for (i = 0; i < 4; i++) {
            Node *child = children[i];
            if (child == NULL)
                continue;
            if (!treeContains(closed, child->hash))
                priorityEnqueue(open, child);
        }
        addTree(closed, current->hash);
        free(children);
    }
    destructPriorityQueue(open);
    destructTree(closed);
}

void a_star(int *puzzle, int n, int zeroX, int zeroY, char *outputFile) {
    TICK(X);
    Node *first = initNode(puzzle, n, 0, zeroX, zeroY);
    first->h = manhattan(first);
    first->f = first->h;

    PriorityQueue *open = initPriorityQueue(compareF);
    SuffixTree *closed = initTree();

    priorityEnqueue(open, first);
    while (!heapEmpty(open)) {
        Node *current = priorityPoll(open);
        if (current->h == 0) {
            TOCK(X);
            printPath(current, outputFile);
            destructTree(closed);
            destructPriorityQueue(open);
            return;
        }

        Node **children = computeChildren(current);
        int i;
        for (i = 0; i < 4; i++) {
            Node *child = children[i];
            if (child == NULL)
                continue;
            if (!treeContains(closed, child->hash))
                priorityEnqueue(open, child);
        }
        addTree(closed, current->hash);
        free(children);
    }
    destructPriorityQueue(open);
    destructTree(closed);
}

void printPath(Node *node, char *outputFile) {
    if (node == NULL) {
        printf("No solution!\n");
        return;
    }
    int size = node->g;
    char *path[size];

    int i;
    for (i = size - 1; i >= 0; i--) {
        path[i] = node->move;
        node = node->parent;
    }
    char *buffer = calloc((size_t) size * 5, sizeof(char));

    printf("%d\n", size);
    for (i = 0; i < size; i++) {
        strcat(buffer, path[i]);
        strcat(buffer, "\n");
    }
    printf("%s", buffer);

    FILE *fp = fopen(outputFile, "w");

    fprintf(fp, "%d\n", size);
    fprintf(fp, "%s", buffer);

    printf("\n%s has been created with the solution to the puzzle.\n",
           outputFile);
    free(buffer);
    fclose(fp);
}