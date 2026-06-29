#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t {
  int data;
  struct node_t *lnode;
  struct node_t *rnode;
} node_t;

typedef struct tree_t {
  node_t *root;
} tree_t;

// Best practice: always pass the true root and never a subtree's root
node_t *get_parent(node_t *root, const int data) {
  node_t *next;

  if (data > root->data) {
    next = root->rnode;
  } else if (data < root->data) {
    next = root->lnode;
  } else {
    return NULL;
  }

  if (next != NULL) {
    return get_parent(next, data);
  }

  return root;
}

int delete(tree_t *tree, const int data) {
  if (tree == NULL) {
    fprintf(stderr, "Error: Param 'tree' is not nullable\n");
    return EXIT_FAILURE;
  }

  node_t *parent = get_parent(tree->root, data);

  node_t *match;
  if (data > parent->data) {
    match = parent->rnode;

    // if (match->lnode == NULL && match->rnode == NULL) {
    //
    // }

    // if (match->rnode == NULL) {
    //   parent->rnode = match->lnode; // TODO: review tomorrow, I'm tired.
    // }

    // parent->rnode = match->rnode;
    // node_t *lmost = get_parent(match->rnode, match->lnode->data);
    // lmost->lnode = match->lnode;
  } else if (data < parent->data) {
    match = parent->lnode;
  }

  // Also free(match->data) if pointing to dynamic memory
  free(match);

  return EXIT_FAILURE;
}

int insert(tree_t *tree, const int data) {
  if (tree == NULL) {
    fprintf(stderr, "Error: Param 'tree' is not nullable\n");
    return EXIT_FAILURE;
  }

  node_t *node = malloc(sizeof(node_t));
  if (node == NULL) {
    fprintf(stderr, "Error: Failed to allocate memory\n");
    return EXIT_FAILURE;
  }

  node->data = data;
  node->lnode = NULL;
  node->rnode = NULL;

  if (tree->root == NULL) {
    tree->root = node;
    return EXIT_SUCCESS;
  }

  node_t *parent = get_parent(tree->root, data);

  if (data > parent->data) {
    parent->rnode = node;
  } else if (node->data < parent->data) {
    parent->lnode = node;
  }

  fprintf(stderr, "Error: Do not store the same data\n");
  free(node);
  return EXIT_FAILURE;
}

int main(int argc, char *argv[]) {
  tree_t tree = {NULL};

  insert(&tree, 10);
  insert(&tree, 05);
  insert(&tree, 50);
  insert(&tree, 25);
  insert(&tree, 20);
  insert(&tree, 30);

  return EXIT_SUCCESS;
}
