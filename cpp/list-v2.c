#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t {
  char *data;
  struct node_t *next;
} node_t;

typedef struct list_t {
  node_t *head;
} list_t;

node_t *get_last(node_t *current) {
  if (current == NULL) {
    return NULL;
  }

  while (current->next != NULL) {
    current = current->next;
  }

  return current;
}

int append(list_t *list_ref, const char *data) {
  if (list_ref == NULL) {
    fprintf(stderr, "Error: Param 'list_ref' is not nullable\n");
    return EXIT_FAILURE;
  }

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

  if (list_ref->head == NULL) {
    list_ref->head = node;
    return EXIT_SUCCESS;
  }

  node_t *last = get_last(list_ref->head);
  last->next = node;

  return EXIT_SUCCESS;
}

int prepend(list_t *list_ref, const char *data) {
  if (list_ref == NULL) {
    fprintf(stderr, "Error: Param 'list_ref' is not nullable\n");
    return EXIT_FAILURE;
  }

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

  node->next = list_ref->head;
  list_ref->head = node;

  return EXIT_SUCCESS;
}

int print_list(list_t *list_ref) {
  node_t *current = list_ref->head;

  if (list_ref == NULL) {
    fprintf(stderr, "Error: Param 'list_ref' is not nullable\n");
    return EXIT_FAILURE;
  }

  while (current != NULL) {
    printf("%s -> ", current->data);
    current = current->next;
  }
  printf("NULL\n");

  return EXIT_SUCCESS;
}

int free_list(list_t *list_ref) {
  node_t *current = list_ref->head;

  if (list_ref == NULL) {
    fprintf(stderr, "Error: Param 'list_ref' is not nullable\n");
    return EXIT_FAILURE;
  }

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
  list_ref->head = NULL;

  return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
  list_t list = {NULL};

  append(&list, "foo");
  append(&list, "bar");
  append(&list, "baz");

  print_list(&list);
  free_list(&list);

  return EXIT_SUCCESS;
}
