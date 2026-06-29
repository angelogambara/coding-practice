#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// data out <- [queue] <- data in

typedef struct node_t {
  char *data;
  struct node_t *next;
} node_t;

typedef struct queue_t {
  node_t *head;
  node_t *tail;
} queue_t;

int enqueue(queue_t *queue_ref, char *data) {
  if (queue_ref == NULL) {
    fprintf(stderr, "Error: Param 'queue_ref' is not nullable\n");
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

  if (queue_ref->tail == NULL) {
    queue_ref->tail = node;
    queue_ref->head = node;
    return EXIT_SUCCESS;
  }

  queue_ref->tail->next = node;
  queue_ref->tail = node;

  return EXIT_SUCCESS;
}

int dequeue(queue_t *queue_ref) {
  if (queue_ref == NULL) {
    fprintf(stderr, "Error: Param 'queue_ref' is not nullable\n");
    return EXIT_FAILURE;
  }

  if (queue_ref->head != NULL) {
    node_t *next = queue_ref->head->next;
    free(queue_ref->head->data);
    free(queue_ref->head);
    queue_ref->head = next;

    if (queue_ref->head == NULL) {
      queue_ref->tail = NULL;
    }

    return EXIT_SUCCESS;
  }

  return EXIT_FAILURE;
}

int print_queue(queue_t *queue_ref) {
  node_t *current = queue_ref->head;

  if (queue_ref == NULL) {
    fprintf(stderr, "Error: Param 'queue_ref' is not nullable\n");
    return EXIT_FAILURE;
  }

  while (current != NULL) {
    printf("%s -> ", current->data);
    current = current->next;
  }
  printf("NULL\n");

  return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
  queue_t queue = {NULL, NULL};

  enqueue(&queue, "foo");
  enqueue(&queue, "bar");
  enqueue(&queue, "baz");
  print_queue(&queue);

  dequeue(&queue);
  print_queue(&queue);
  dequeue(&queue);
  print_queue(&queue);
  dequeue(&queue);
  print_queue(&queue);

  return EXIT_SUCCESS;
}
