#ifndef AS3_SUFFIXTREE_H
#define AS3_SUFFIXTREE_H

#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

/**
 * TreeNode represents each Node of the tree that will have 10 children
 * (the numeric digits base10) to help create the SuffixTree
 */
typedef struct TreeNode {

    struct TreeNode *children[10];

} TreeNode;

/**
 * SuffixTree is represented by a TreeNode which will be the starting point
 * of everything(root).
 */
typedef struct SuffixTree {

    TreeNode *root;

} SuffixTree;

/**
 * Constructor of a SuffixTree.
 *
 * @return pointer to newly created SuffixTree.
 */
SuffixTree *initTree();

/**
 * Constructor of a TreeNode.
 *
 * @return
 */
TreeNode *initTreeNode();

/**
 * Free the memory that this SuffixTree allocates.
 *
 * @param tree
 */
void destructTree(SuffixTree *tree);

/**
 * Free the memory that this TreeNode allocates.
 *
 * @param node
 */
void destructTreeNode(TreeNode *node);

/**
 * Will walk the path down the tree according to given string and if could
 * walk the whole path without finding NULL pointer that means this string
 * is contained withing the tree.
 *
 * @param tree
 * @param string
 * @return if tree contains given string.
 */
bool treeContains(SuffixTree *tree, char *string);

/**
 * Will create the path down the tree from given string.
 *
 * @param tree
 * @param string
 */
void addTree(SuffixTree *tree, char *string);

#endif //AS3_SUFFIXTREE_H
