#include "SuffixTree.h"

//#define DEBUG
#if defined (DEBUG)

static void test_treeContains() {
    SuffixTree *tree = initTree();

    addTree(tree, "12343");
    if(!treeContains(tree, "12343"))
        printf("Tree does not contain 12343\n");

    addTree(tree, "12343312");
    if(!treeContains(tree, "12343312"))
        printf("Tree does not contain 12343312\n");

    addTree(tree, "9");
    if(!treeContains(tree, "9"))
        printf("Tree does not contain 9\n");
}


int main(void) {
    test_treeContains();
    return 0;
}

#endif

SuffixTree *initTree() {
    SuffixTree *new = malloc(sizeof(SuffixTree));
    new->root = initTreeNode();
    return new;
}

TreeNode *initTreeNode() {
    TreeNode *new = malloc(sizeof(TreeNode));
    int i;
    for (i = 0; i < 10; i++)
        new->children[i] = NULL;
    return new;
}

bool treeContains(SuffixTree *tree, char *string) {
    TreeNode *current = tree->root;
    int i;
    for (i = 0; i < strlen(string); i++) {
        int index = (int) string[i];
        if (current->children[index - 48] == NULL)
            return false;
        current = current->children[index - 48];
    }
    return true;
}

void addTree(SuffixTree *tree, char *string) {
    TreeNode *current = tree->root;
    int i;
    for (i = 0; i < strlen(string); i++) {
        int index = (int) string[i];
        if (current->children[index - 48] == NULL) {
            current->children[index - 48] = initTreeNode();
        }
        current = current->children[index - 48];
    }
}

void destructTree(SuffixTree *tree) {
    destructTreeNode(tree->root);
    free(tree);
}

void destructTreeNode(TreeNode *node) {
    if (node != NULL) {
        int i;
        for (i = 0; i < 10; i++) {
            destructTreeNode(node->children[i]);
        }
        free(node);
    }
}
