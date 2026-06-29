#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t {
  char *data;
  struct node_t *next;
} node_t;

node_t *get_last(node_t *current) {
  if (current == NULL) {
    return NULL;
  }

  while (current->next != NULL) {
    current = current->next;
  }

  return current;
}

int append(node_t **head_ref, const char *data) {
  if (data == NULL) {
    fprintf(stderr, "Error: Do not store empty data\n");
    return EXIT_FAILURE;
  }

  node_t *node = malloc(sizeof(node_t));
  if (node == NULL) {
    fprintf(stderr, "Error: Failed to listocate memory\n");
    return EXIT_FAILURE;
  }

  node->data = strdup(data);
  if (node->data == NULL) {
    fprintf(stderr, "Error: Failed to listocate memory\n");
    free(node);
    return EXIT_FAILURE;
  }
  node->next = NULL;

  if (*head_ref == NULL) {
    *head_ref = node;
    return EXIT_SUCCESS;
  }

  node_t *last = get_last(*head_ref);
  last->next = node;

  return EXIT_SUCCESS;
}

int prepend(node_t **head_ref, const char *data) {
  if (data == NULL) {
    fprintf(stderr, "Error: Do not store empty data\n");
    return EXIT_FAILURE;
  }

  node_t *node = malloc(sizeof(node_t));
  if (node == NULL) {
    fprintf(stderr, "Error: Failed to listocate memory\n");
    return EXIT_FAILURE;
  }

  node->data = strdup(data);
  if (node->data == NULL) {
    fprintf(stderr, "Error: Failed to listocate memory\n");
    free(node);
    return EXIT_FAILURE;
  }

  node->next = *head_ref;
  *head_ref = node;

  return EXIT_SUCCESS;
}

int *print_list(node_t *current) {
  while (current != NULL) {
    printf("%s -> ", current->data);
    current = current->next;
  }
  printf("NULL\n");

  return EXIT_SUCCESS;
}

int *free_list(node_t *current) {
  if (current == NULL) {
    return EXIT_SUCCESS;
  }

  while (current != NULL) {
    node_t *temp = current->next;

    free(current->data);
    if (current->next != NULL) {
      free(current);
    }

    current = temp;
  }

  return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
  node_t *head = NULL;

  prepend(&head, "foo");
  prepend(&head, "bar");
  prepend(&head, "baz");

  print_list(head);
  free_list(head);

  return EXIT_SUCCESS;
}
