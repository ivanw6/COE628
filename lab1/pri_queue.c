#include <stdlib.h>
#include <stdio.h>
#include "pri_queue.h"
/** @file pri_queue.c */
static Node_ptr_t head = NULL;
/**
 * Insert a Node into a priority queue.
 * @param priority
 * @param data
 * @author Ivan Wang - 501086429
 */
void PQ_insert(int priority, char * data) {
    // Initialize new node
    Node_ptr_t new = (Node_ptr_t)malloc(sizeof(Node_t));
    // Base case
    if (new == NULL) {
        fprintf(stderr, "Error: Cannot Insert NULL Node.\n");
        exit(0);
    }

    // Set the properties of the new node
    new->priority = priority;
    new->data = data;
    new->next = NULL;

    // Insert the new node into the priority queue based on priority
    if (head == NULL || priority > head->priority) {
        new->next = head;
        head = new;
    } else {
        Node_ptr_t current = head;
        while (current->next != NULL && priority <= current->next->priority) {
            current = current->next;
        }
        new->next = current->next;
        current->next = new;
    }
}
/**
 * Delete and return the node with the highest priority.
 * @return The highest priority Node.
 */
Node_ptr_t PQ_delete() {
    // Base case
    if (head == NULL) {
        // Priority queue is empty
        fprintf(stderr, "Error: Queue is Empty.\n");
        return NULL;
    }

    // Retrieve the highest priority node
    Node_ptr_t deleted = head;
    head = head->next;
    deleted->next = NULL;

    return deleted;
}

/**
 * Do NOT modify this function.
 * @return A pointer to the head of the list.  (NULL if list is empty.)
 */
Node_ptr_t PQ_get_head() {
    return head;
}

/**
 * Do NOT modify this function.
 * @return the number of items in the queue
 */
int PQ_get_size() {
    int size = 0;
    Node_ptr_t tmp;
    for(tmp = head; tmp != NULL; tmp = tmp->next, size++)
        ;
    return size;
}


