#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* head = NULL;

void insert(int data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = head;
    head = new_node;
}

void delete(int data) {
    struct Node* current = head;
    struct Node* previous = NULL;
    while (current != NULL) {
        if (current->data == data) {
            if (previous == NULL) {
                head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

void display() {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    insert(5);
    insert(10);
    insert(15);
    insert(20);
    printf("Linked list: ");
    display();
    delete(10);
    printf("Linked list after deletion: ");
    display();
    return 0;
}
