// tree1.c
//
// CONCEPT
// A *binary search tree* is a node with a value and two children;
// everything in the left subtree is smaller, everything in the right is
// larger. Searching and inserting follow one path from the root, so
// they take time proportional to the height: log2(n) for a balanced
// tree, n for a degenerate one (insert sorted input and you get a
// linked list).
//
// Trees are where recursion earns its keep. Each operation is "handle
// this node, recurse into the relevant child(ren)":
//
//     insert(node **, v): if *node is NULL, allocate here; else recurse
//                         left or right by comparison
//     contains(node, v):  NULL -> false; equal -> true; else recurse
//     inorder(node):      inorder(left), visit, inorder(right)
//                         -> visits values in sorted order
//     free(node):         free(left), free(right), free(node)
//                         (post-order: children before the parent)
//
// WHEN YOU USE THIS
// Ordered maps and sets, symbol tables, range queries. Production code
// uses self-balancing variants (red-black, AVL) or B-trees, but they are
// this structure with rotations added.
//
// TASK
// Write insert (ignore duplicates), contains, inorder (prints values
// separated by spaces), height (empty tree is 0) and tree_free.
//
// EXPECTED OUTPUT
//     inorder: 1 3 4 6 7 8 10 13 14
//     height: 4
//     contains 6: yes
//     contains 5: no

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct tnode {
    int value;
    struct tnode *left;
    struct tnode *right;
};

bool insert(struct tnode **root, int value)
{
    // TODO: return false only if malloc fails.
    (void)root;
    (void)value;
    return false;
}

bool contains(const struct tnode *root, int value)
{
    // TODO
    (void)root;
    (void)value;
    return false;
}

void inorder(const struct tnode *root)
{
    // TODO: print " %d" for each value in sorted order.
    (void)root;
}

int height(const struct tnode *root)
{
    // TODO
    (void)root;
    return -1;
}

void tree_free(struct tnode *root)
{
    // TODO
    (void)root;
}

int main(void)
{
    struct tnode *root = NULL;
    int values[] = {8, 3, 10, 1, 6, 14, 4, 7, 13, 6};

    for (size_t i = 0; i < sizeof values / sizeof values[0]; i++) {
        if (!insert(&root, values[i])) {
            tree_free(root);
            return 1;
        }
    }
    printf("inorder:");
    inorder(root);
    printf("\n");
    printf("height: %d\n", height(root));
    printf("contains 6: %s\n", contains(root, 6) ? "yes" : "no");
    printf("contains 5: %s\n", contains(root, 5) ? "yes" : "no");
    tree_free(root);
    return 0;
}
