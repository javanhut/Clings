// tree1.c - solution

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
    if (*root == NULL) {
        struct tnode *n = malloc(sizeof *n);
        if (n == NULL) {
            return false;
        }
        n->value = value;
        n->left = NULL;
        n->right = NULL;
        *root = n;
        return true;
    }
    if (value < (*root)->value) {
        return insert(&(*root)->left, value);
    }
    if (value > (*root)->value) {
        return insert(&(*root)->right, value);
    }
    return true;
}

bool contains(const struct tnode *root, int value)
{
    while (root != NULL) {
        if (value == root->value) {
            return true;
        }
        root = value < root->value ? root->left : root->right;
    }
    return false;
}

void inorder(const struct tnode *root)
{
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf(" %d", root->value);
    inorder(root->right);
}

int height(const struct tnode *root)
{
    if (root == NULL) {
        return 0;
    }
    int l = height(root->left);
    int r = height(root->right);
    return 1 + (l > r ? l : r);
}

void tree_free(struct tnode *root)
{
    if (root == NULL) {
        return;
    }
    tree_free(root->left);
    tree_free(root->right);
    free(root);
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
