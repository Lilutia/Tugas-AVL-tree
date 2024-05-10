#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* newNode(int data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Error creating a new node.\n");
        exit(0);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void push(Node** head, int data) {
    Node* new_node = newNode(data);
    new_node->next = *head;
    *head = new_node;
}

int pop(Node** head) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return -1;
    }
    Node* temp = *head;
    int popped = temp->data;
    *head = temp->next;
    free(temp);
    return popped;
}

void printList(Node* node) {
    while (node != NULL) {
        printf(" %d", node->data);
        node = node->next;
    }
    printf("\n");
}

int main() {
    Node* head = NULL;

    push(&head, 10);
    push(&head, 20);
    push(&head, 30);
    push(&head, 40);
    push(&head, 50);

    printf("List: ");
    printList(head);
    
    printf("\n");

    pop(&head);
    printf("List after popping: ");
    printList(head);

    return 0;
}

