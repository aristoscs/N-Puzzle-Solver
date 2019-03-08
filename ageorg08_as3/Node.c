#include "Node.h"

//#define DEBUG
#if defined (DEBUG)

static void test_computeChildren() {
    // Sequence is UP(0), DOWN(1), LEFT(2), RIGHT(3)

    // Suppose grid with children UP and LEFT
    int grid1[] = {1, 2, 3,
                   4, 5, 6,
                   7, 8, 0};
    Node *node = initNode(grid1, 3, 3, 2, 2);
    Node **children = computeChildren(node);
    if(children[0] == NULL)
        printf("Expected a children UP\n");
    if(children[2] == NULL)
        printf("Expected a children LEFT\n");

    // Suppose grid with children RIGHT and DOWN
    int grid2[] = {0, 2, 3,
                   4, 5, 6,
                   7, 8, 1};
    node = initNode(grid2, 3, 3, 0, 0);
    children = computeChildren(node);
    if(children[1] == NULL)
        printf("Expected a children DOWN\n");
    if(children[3] == NULL)
        printf("Expected a children RIGHT\n");
}

static void test_newGrid() {
    int grid1[] = {1, 2, 3,
                   4, 5, 6,
                   7, 8, 0};
    Node *node = initNode(grid1, 3, 3, 2, 2);

    if(memcmp(grid1, newGrid(node), 9) != 0) {
       printf("Copying of grid did not happen correctly.\n");
    }
}

static void test_manhattan() {
    // Suppose grid with manhattan distance = 2
    int grid1[] = {1, 2, 0,
                   4, 5, 6,
                   7, 8, 3};
    Node *node = initNode(grid1, 3, 3, 2, 2);
    node->h = manhattan(node);
    if(node->h != 2)
        printf("Expected node->h to be 2, h: %d\n", node->h);

    // Suppose grid with manhattan distance = 6
    int grid2[] = {3, 2, 0,
                   4, 5, 6,
                   7, 8, 1};
    node = initNode(grid2, 3, 3, 0, 2);
    node->h = manhattan(node);
    if(node->h != 6)
        printf("Expected node->h to be 6, h: %d\n", node->h);
}

static void test_reHash() {
    // Suppose grid with hash: 120456783
    int grid1[] = {1, 2, 0,
                   4, 5, 6,
                   7, 8, 3};
    Node *node = initNode(grid1, 3, 3, 0, 2);
    if(strcmp("120456783", node->hash) != 0)
        printf("Expected node->hash to be: 120456783, hash: %s\n", node->hash);

    // Suppose grid with hash: 1209456107831112131415
    int grid2[] = {1, 2, 0, 9,
                   4, 5, 6, 10,
                   7, 8, 3, 11,
                   12, 13, 14, 15};

    node = initNode(grid2, 4, 3, 0, 2);
    if(strcmp("1209456107831112131415", node->hash) != 0)
        printf("Expected node->hash to be: 1209456107831112131415, hash: %s\n", node->hash);
}

int main(void) {
    test_computeChildren();
    test_newGrid();
    test_manhattan();
    test_reHash();
    return 0;
}

#endif

Node *initNode(int *grid, int n, int g, int x, int y) {
    Node *new = malloc(sizeof(Node));
    new->parent = NULL;
    new->f = g;
    new->h = 0;
    new->grid = grid;
    new->n = n;
    new->g = g;
    new->x = x;
    new->y = y;
    reHash(new);
    return new;
}

void destructNode(Node **node) {
    free((*node)->grid);
    free((*node)->hash);
}

Node **computeChildren(Node *node) {
    Node **children = calloc((size_t) 4, sizeof(node));
    int x = node->x;
    int y = node->y;
    int n = node->n;
    int g = node->g;

    // UP
    if (x - 1 >= 0) {
        int *child = newGrid(node);
        int oldManhattan = singleManhattan(child[(x - 1) * n + y], (x - 1), y, n);
        child[x * n + y] = child[(x - 1) * n + y];
        child[(x - 1) * n + y] = 0;
        int newManhattan = singleManhattan(child[x * n + y], x, y, n);
        children[0] = initNode(child, n, g + 1, x - 1, y);
        children[0]->parent = node;
        children[0]->move = "UP";

        children[0]->h = newManhattan - oldManhattan + node->h;
        children[0]->f = children[0]->g + children[0]->h;
    }
    // DOWN
    if (x + 1 < n) {
        int *child = newGrid(node);
        int oldManhattan = singleManhattan(child[(x + 1) * n + y], (x + 1), y, n);
        child[x * n + y] = child[(x + 1) * n + y];
        child[(x + 1) * n + y] = 0;
        int newManhattan = singleManhattan(child[x * n + y], x, y, n);
        children[1] = initNode(child, n, g + 1, x + 1, y);
        children[1]->parent = node;
        children[1]->move = "DOWN";

        children[1]->h = newManhattan - oldManhattan + node->h;
        children[1]->f += children[1]->h;
    }
    // LEFT
    if (y - 1 >= 0) {
        int *child = newGrid(node);
        int oldManhattan = singleManhattan(child[x * n + (y - 1)], x, (y - 1), n);
        child[x * n + y] = child[x * n + (y - 1)];
        child[x * n + (y - 1)] = 0;
        int newManhattan = singleManhattan(child[x * n + y], x, y, n);
        children[2] = initNode(child, n, g + 1, x, y - 1);
        children[2]->parent = node;
        children[2]->move = "LEFT";

        children[2]->h = newManhattan - oldManhattan + node->h;
        children[2]->f += children[2]->h;
    }
    // RIGHT
    if (y + 1 < n) {
        int *child = newGrid(node);
        int oldManhattan = singleManhattan(child[x * n + (y + 1)], x, (y + 1), n);
        child[x * n + y] = child[x * n + (y + 1)];
        child[x * n + (y + 1)] = 0;
        int newManhattan = singleManhattan(child[x * n + y], x, y, n);
        children[3] = initNode(child, n, g + 1, x, y + 1);
        children[3]->parent = node;
        children[3]->move = "RIGHT";

        children[3]->h = newManhattan - oldManhattan + node->h;
        children[3]->f += children[3]->h;
    }
    return children;
}

int singleManhattan(int v, int i, int j, int n) {
    return abs(i - ((v - 1) / n)) + abs(j - ((v - 1) % n));
}

int *newGrid(Node *node) {
    int *child = malloc(node->n * node->n * sizeof(int));
    int i;
    for (i = 0; i < node->n * node->n; i++) {
        child[i] = node->grid[i];
    }
    return child;
}

int manhattan(Node *node) {
    int n = node->n;
    int *grid = node->grid;

    int manhattan = 0;
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (grid[i * n + j] != 0 && grid[i * n + j] != (n * i + j + 1)) {
                int v = grid[i * n + j];
                manhattan += abs(i - ((v - 1) / n)) + abs(j - ((v - 1) % n));
            }
        }
    }
    return manhattan;
}

void reHash(Node *node) {
    node->hash = calloc((size_t) ((node->n * node->n) * 2 + 1), sizeof(char));
    int c = 0;
    int i;
    for (i = 0; i < node->n * node->n; i++) {
        int j = 0;
        int temp = node->grid[i];
        char buffer[16] = "";
        do {
            buffer[j++] = (char) (temp % 10 + '0');
            temp /= 10;
        } while (temp != 0);
        for (j = j - 1; j >= 0; j--) {
            node->hash[c++] = buffer[j];
        }
    }
    node->hash[c] = '\0';
}

int compareH(Node *a, Node *b) {
    int fx = a->h - b->h;
    if(fx == 0) {
        return b->g - a->g;
    }
    return fx;
}

int compareF(Node *a, Node *b) {
	int fx = a->f - b->f;
	if(fx == 0) {
		return b->g - a->g;
	}
    return fx;
}

















