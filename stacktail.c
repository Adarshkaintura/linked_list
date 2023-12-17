//stack using linked list 
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Stack {
    struct Node* tail;
};

struct Stack* initialize() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (!stack) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    stack->tail = NULL;
    return stack;
}

int isEmpty(struct Stack* stack) {
    return stack->tail == NULL;
}

void push(struct Stack* stack, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->data = data;
    newNode->next = NULL;
    if (isEmpty(stack)) {
        stack->tail = newNode;
    } else {
        struct Node* current = stack->tail;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return -1;
    }
    struct Node* current = stack->tail;
    int data = current->data;
    if (stack->tail->next == NULL) {
        stack->tail = NULL;
    } else {
        while (current->next->next != NULL) {
            current = current->next;
        }
        free(current->next);
        current->next = NULL;
    }
    return data;
}

int peek(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return -1;
    }
    return stack->tail->data;
}

void display(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return;
    }
    struct Node* current = stack->tail;
    printf("Stack elements (tail to head): ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void destroy(struct Stack* stack) {
    while (!isEmpty(stack)) {
        pop(stack);
    }
    free(stack);
}

int main() {
    struct Stack* s1 = initialize();
    int choice, data;

    while (1) {
        printf("\nStack Operations:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to push: ");
                scanf("%d", &data);
                push(s1, data);
                break;

            case 2:
                data = pop(s1);
                if (data != -1) {
                    printf("Popped element: %d\n", data);
                }
                break;

            case 3:
                data = peek(s1);
                if (data != -1) {
                    printf("Top element: %d\n", data);
                }
                break;

            case 4:
                display(s1);
                break;

            case 5:
                destroy(s1);
                exit(0);

            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    
    return 0;
}
