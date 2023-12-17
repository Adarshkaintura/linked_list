//doubly linked list
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
    struct node* prev;
};

void display(struct node* head) {
    struct node* temp = head;
    printf("Doubly Linked List: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void insert_at_end(struct node** head, int a) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = a;
    newnode->next = NULL;

    if (*head == NULL) {
        newnode->prev = NULL;
        *head = newnode;
    } else {
        struct node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newnode;
        newnode->prev = temp;
    }
}

void insert_at_begin(struct node** head, int a) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = a;
    newnode->next = *head;
    newnode->prev = NULL;

    if (*head != NULL) {
        (*head)->prev = newnode;
    }
    *head = newnode;
}

void insert_before_pos(struct node** head, int a, int pos) {
    if (pos <= 1) {
        insert_at_begin(head, a);
    } else {
        struct node* temp = *head;
        struct node* prev = NULL;
        int i = 1;

        while (i < pos && temp != NULL) {
            prev = temp;
            temp = temp->next;
            i++;
        }

        if (temp == NULL) {
            printf("Position %d is beyond the end of the list\n", pos);
        } else {
            struct node* newnode = (struct node*)malloc(sizeof(struct node));
            newnode->data = a;
            newnode->next = temp;
            newnode->prev = prev;
            prev->next = newnode;
            temp->prev = newnode;
        }
    }
}

void insert_after_pos(struct node** head, int a, int pos) {
    struct node* temp = *head;
    int i = 1;

    while (i < pos && temp != NULL) {
        temp = temp->next;
        i++;
    }

    if (temp == NULL) {
        printf("Position %d is beyond the end of the list\n", pos);
    } else {
        struct node* newnode = (struct node*)malloc(sizeof(struct node));
        newnode->data = a;
        newnode->next = temp->next;
        newnode->prev = temp;
        temp->next = newnode;
        if (newnode->next != NULL) {
            newnode->next->prev = newnode;
        }
    }
}

int del_from_begin(struct node** head) {
    if (*head == NULL) {
        printf("The list is empty\n");
        return -1;
    } else {
        struct node* temp = *head;
        int deleted_data = temp->data;
        *head = (*head)->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
        free(temp);
        return deleted_data;
    }
}

int del_from_end(struct node** head) {
    if (*head == NULL) {
        printf("The list is empty\n");
        return -1;
    } else if ((*head)->next == NULL) {
        int deleted_data = (*head)->data;
        free(*head);
        *head = NULL;
        return deleted_data;
    } else {
        struct node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        int deleted_data = temp->data;
        if (temp->prev != NULL) {
            temp->prev->next = NULL;
        }
        free(temp);
        return deleted_data;
    }
}

void del_from_pos(struct node** head, int pos) {
    int i = 1;
    if (pos < 1) {
        printf("Invalid position\n");
        return;
    } else if (pos == 1) {
        del_from_begin(head);
    } else {
        struct node* temp = *head;
        struct node* prev = NULL;

        while (i < pos && temp != NULL) {
            prev = temp;
            temp = temp->next;
            i++;
        }

        if (temp == NULL) {
            printf("Position %d is beyond the end of the list\n", pos);
            return;
        }

        prev->next = temp->next;
        if (temp->next != NULL) {
            temp->next->prev = prev;
        }
        free(temp);
    }
}

void delete_after_pos(struct node** head, int pos) {
    if (*head == NULL) {
        printf("The list is empty\n");
        return;
    }

    struct node* temp = *head;
    int i = 1;

    while (i < pos && temp != NULL) {
        temp = temp->next;
        i++;
    }

    if (temp == NULL || temp->next == NULL) {
        printf("Position %d is beyond the end of the list or no node to delete after\n", pos);
        return;
    }

    struct node* node_to_delete = temp->next;
    temp->next = node_to_delete->next;
    if (node_to_delete->next != NULL) {
        node_to_delete->next->prev = temp;
    }
    free(node_to_delete);
}

void delete_before_pos(struct node** head, int pos) {
    if (*head == NULL || pos <= 1) {
        printf("No node to delete before position %d\n", pos);
        return;
    }

    if (pos == 2) {
        struct node* node_to_delete = *head;
        *head = (*head)->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
        free(node_to_delete);
        return;
    }

    struct node* temp = *head;
    int i = 1;

    while (i < pos - 2 && temp != NULL) {
        temp = temp->next;
        i++;
    }

    if (temp == NULL || temp->next == NULL) {
        printf("Position %d is beyond the end of the list or no node to delete before\n", pos);
        return;
    }

    struct node* node_to_delete = temp->next;
    temp->next = node_to_delete->next;
    if (node_to_delete->next != NULL) {
        node_to_delete->next->prev = temp;
    }
    free(node_to_delete);
}

int main() {
    struct node* head = NULL;
    int choice, data, pos;

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
                scanf("%d", &pos);
                insert_before_pos(&head, data, pos);
                break;
            case 5:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                printf("Enter position after which to insert: ");
                scanf("%d", &pos);
                insert_after_pos(&head, data, pos);
                break;
            case 6:
                {
                    int deleted_data = del_from_begin(&head);
                    if (deleted_data != -1) {
                        printf("Deleted element from beginning: %d\n", deleted_data);
                    }
                }
                break;
            case 7:
                {
                    int deleted_data = del_from_end(&head);
                    if (deleted_data != -1) {
                        printf("Deleted element from end: %d\n", deleted_data);
                    }
                }
                break;
            case 8:
                printf("Enter the position to delete: ");
                scanf("%d", &pos);
                del_from_pos(&head, pos);
                break;
            case 9:
                printf("Enter the position to delete after: ");
                scanf("%d", &pos);
                delete_after_pos(&head, pos);
                break;
            case 10:
                printf("Enter the position to delete before: ");
                scanf("%d", &pos);
                delete_before_pos(&head, pos);
                break;
            case 11:
                while (head != NULL) {
                    struct node* temp = head;
                    head = head->next;
                    free(temp);
                }
                exit(0);

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
