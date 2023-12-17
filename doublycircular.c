//doubly circular linked list
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next_node;
    struct node* prev_node;
};

void display(struct node* head) {
    struct node* current_node = head;

    if (head == NULL) {
        printf("The list is empty\n");
        return;
    }

    printf("Doubly Circular Linked List: ");
    
    do {
        printf("%d ", current_node->data);
        current_node = current_node->next_node;
    } while (current_node != head);
    
    printf("\n");
}

void insert_at_end(struct node** head, int data) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = data;

    if (*head == NULL) {
        new_node->prev_node = new_node;
        new_node->next_node = new_node;
        *head = new_node;
    } else {
        struct node* last_node = (*head)->prev_node;
        new_node->prev_node = last_node;
        new_node->next_node = *head;
        last_node->next_node = new_node;
        (*head)->prev_node = new_node;
    }
}

void insert_at_begin(struct node** head, int data) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = data;

    if (*head == NULL) {
        new_node->prev_node = new_node;
        new_node->next_node = new_node;
        *head = new_node;
    } else {
        struct node* last_node = (*head)->prev_node;
        new_node->prev_node = last_node;
        new_node->next_node = *head;
        last_node->next_node = new_node;
        (*head)->prev_node = new_node;
        *head = new_node;
    }
}

void insert_before_pos(struct node** head, int data, int position) {
    if (position <= 1) {
        insert_at_begin(head, data);
    } else {
        struct node* current_node = *head;
        int i = 1;

        while (i < position && current_node != NULL) {
            current_node = current_node->next_node;
            i++;
        }

        if (current_node == NULL) {
            printf("Position %d is beyond the end of the list\n", position);
        } else {
            struct node* new_node = (struct node*)malloc(sizeof(struct node));
            new_node->data = data;
            new_node->prev_node = current_node->prev_node;
            new_node->next_node = current_node;
            current_node->prev_node->next_node = new_node;
            current_node->prev_node = new_node;
        }
    }
}

void insert_after_pos(struct node** head, int data, int position) {
    struct node* current_node = *head;
    int i = 1;

    while (i < position && current_node != NULL) {
        current_node = current_node->next_node;
        i++;
    }

    if (current_node == NULL) {
        printf("Position %d is beyond the end of the list\n", position);
    } else {
        struct node* new_node = (struct node*)malloc(sizeof(struct node));
        new_node->data = data;
        new_node->prev_node = current_node;
        new_node->next_node = current_node->next_node;
        current_node->next_node->prev_node = new_node;
        current_node->next_node = new_node;
    }
}

int delete_from_begin(struct node** head) {
    if (*head == NULL) {
        printf("The list is empty\n");
        return -1;
    } else {
        struct node* current_node = *head;
        int deleted_data = current_node->data;

        if (current_node->next_node == current_node) {
            *head = NULL;
        } else {
            current_node->prev_node->next_node = current_node->next_node;
            current_node->next_node->prev_node = current_node->prev_node;
            *head = current_node->next_node;
        }

        free(current_node);
        return deleted_data;
    }
}

int delete_from_end(struct node** head) {
    if (*head == NULL) {
        printf("The list is empty\n");
        return -1;
    } else {
        struct node* current_node = (*head)->prev_node;
        int deleted_data = current_node->data;

        if (current_node->prev_node == current_node) {
            *head = NULL;
        } else {
            current_node->prev_node->next_node = *head;
            (*head)->prev_node = current_node->prev_node;
        }

        free(current_node);
        return deleted_data;
    }
}

void delete_from_pos(struct node** head, int position) {
    int i = 1;

    if (position < 1) {
        printf("Invalid position\n");
        return;
    } else if (position == 1) {
        delete_from_begin(head);
    } else {
        struct node* current_node = *head;

        while (i < position && current_node != NULL) {
            current_node = current_node->next_node;
            i++;
        }

        if (current_node == NULL) {
            printf("Position %d is beyond the end of the list\n", position);
            return;
        }

        current_node->prev_node->next_node = current_node->next_node;
        current_node->next_node->prev_node = current_node->prev_node;
        free(current_node);
    }
}

void delete_after_pos(struct node** head, int position) {
    if (*head == NULL) {
        printf("The list is empty\n");
        return;
    }

    struct node* current_node = *head;
    int i = 1;

    while (i < position && current_node != NULL) {
        current_node = current_node->next_node;
        i++;
    }

    if (current_node == NULL || current_node->next_node == *head) {
        printf("Position %d is beyond the end of the list or no node to delete after\n", position);
        return;
    }

    struct node* node_to_delete = current_node->next_node;
    current_node->next_node = node_to_delete->next_node;
    node_to_delete->next_node->prev_node = current_node;
    free(node_to_delete);
}

void delete_before_pos(struct node** head, int position) {
    if (*head == NULL || position <= 1) {
        printf("No node to delete before position %d\n", position);
        return;
    }

    if (position == 2) {
        delete_from_begin(head);
        return;
    }

    struct node* current_node = *head;
    int i = 1;

    while (i < position - 2 && current_node != NULL) {
        current_node = current_node->next_node;
        i++;
    }

    if (current_node == NULL || current_node->next_node == *head) {
        printf("Position %d is beyond the end of the list or no node to delete before\n", position);
        return;
    }

    struct node* node_to_delete = current_node->next_node;
    current_node->next_node = node_to_delete->next_node;
    node_to_delete->next_node->prev_node = current_node;
    free(node_to_delete);
}

int main() {
    struct node* head = NULL;
    int choice, data, position;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Display data\n");
        printf("2. Insert data at the end\n");
        printf("3. Insert data at the beginning\n");
        printf("4. Insert data before a position\n");
        printf("5. Insert data after a position\n");
        printf("6. Delete from beginning\n");
        printf("7. Delete from end\n");
        printf("8. Delete from a specific position\n");
        printf("9. Delete from after a specific position\n");
        printf("10. Delete from before a specific position\n");
        printf("11. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                display(head);
                break;
            case 2:
                printf("Enter data to insert at the end: ");
                scanf("%d", &data);
                insert_at_end(&head, data);
                break;
            case 3:
                printf("Enter data to insert at the beginning: ");
                scanf("%d", &data);
                insert_at_begin(&head, data);
                break;
            case 4:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                printf("Enter position before which to insert: ");
                scanf("%d", &position);
                insert_before_pos(&head, data, position);
                break;
            case 5:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                printf("Enter position after which to insert: ");
                scanf("%d", &position);
                insert_after_pos(&head, data, position);
                break;
            case 6:
                {
                    int deleted_data = delete_from_begin(&head);
                    if (deleted_data != -1) {
                        printf("Deleted element from beginning: %d\n", deleted_data);
                    }
                }
                break;
            case 7:
                {
                    int deleted_data = delete_from_end(&head);
                    if (deleted_data != -1) {
                        printf("Deleted element from end: %d\n", deleted_data);
                    }
                }
                break;
            case 8:
                printf("Enter the position to delete: ");
                scanf("%d", &position);
                delete_from_pos(&head, position);
                break;
            case 9:
                printf("Enter the position to delete after: ");
                scanf("%d", &position);
                delete_after_pos(&head, position);
                break;
            case 10:
                printf("Enter the position to delete before: ");
                scanf("%d", &position);
                delete_before_pos(&head, position);
                break;
            case 11:
                while (head != NULL) {
                    struct node* current_node = head;
                    head = head->next_node;
                    free(current_node);
                }
                exit(0);

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
