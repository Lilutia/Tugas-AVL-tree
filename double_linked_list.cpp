#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

Node* newNode(int data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

void push(Node** head, int data) {
    Node* new_node = newNode(data);
    new_node->next = *head;  
    new_node->prev = NULL;   

    if (*head != NULL) {
        (*head)->prev = new_node;  
    }
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
    if (*head != NULL) {
        (*head)->prev = NULL;  
    }
    free(temp);  
    return popped;
}

Node* search(Node* head, int key) {
    Node* current = head;
    while (current != NULL) {
        if (current->data == key) {
            return current;
        }
        current = current->next;
    }
    return NULL;  
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

    printf("Initial List: ");
    printList(head);
    
    printf("\n");

    int poppedValue = pop(&head);
    printf("Popped value: %d\n", poppedValue);
    
    printf("\n");
    
    printf("List after popping: ");
    printList(head);
    
    printf("\n");

    Node* found = search(head, 30);
    if (found != NULL) {
        printf("Element %d found in the list.\n", found->data);
    } else {
        printf("Element not found in the list.\n");
    }

    return 0;
}

