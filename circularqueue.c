//circular queue
#include <stdio.h>
#include <stdlib.h>

struct CircularQueue {
    int* it;
    int f;
    int r;
    int cap;
};
int ISFULL(struct CircularQueue* cq) {
    return ((cq->r + 1) % cq->cap == cq->f);
}

int ISEMPTY(struct CircularQueue* cq) {
    return (cq->f == -1);
}
struct CircularQueue* createCircularQueue(int capacity) {
    struct CircularQueue* cq = (struct CircularQueue*)malloc(sizeof(struct CircularQueue));
    cq->cap = capacity;
    cq->f = -1;
    cq->r = -1;
    cq->it = (int*)malloc(sizeof(int) * capacity);
    return cq;
}



void enqueue(struct CircularQueue* cq, int item) {
    if (ISFULL(cq)) {
        printf("Circular Queue is full. Cannot enqueue %d.\n", item);
        return;
    }
    if (ISEMPTY(cq)) {
        cq->f = 0;
    }
    cq->r = (cq->r + 1) % cq->cap;
    cq->it[cq->r] = item;
    printf("Enqueued: %d\n", item);
}

void dequeue(struct CircularQueue* cq) {
    if (ISEMPTY(cq)) {
        printf("Circular Queue is empty. Cannot dequeue.\n");
        return;
    }
    int item = cq->it[cq->f];
    if (cq->f == cq->r) {
        cq->f = -1;
        cq->r = -1;
    } else {
        cq->f = (cq->f + 1) % cq->cap;
    }
    printf("Dequeued: %d\n", item);
}

void display(struct CircularQueue* cq) {
    if (ISEMPTY(cq)) {
        printf("Circular Queue is empty.\n");
        return;
    }
    printf("Circular Queue elements: ");
    int i = cq->f;
    do {
        printf("%d ", cq->it[i]);
        i = (i + 1) % cq->cap;
    } while (i != (cq->r + 1) % cq->cap);
    printf("\n");
}

int main() {
    int capacity;
    printf("Enter the capacity of the Circular Queue: ");
    scanf("%d", &capacity);
    
    struct CircularQueue* cq = createCircularQueue(capacity);
    
    int choice, item;
    
    while (1) {
        printf("\nCircular Queue Operations:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter element to enqueue: ");
                scanf("%d", &item);
                enqueue(cq, item);
                break;
            case 2:
                dequeue(cq);
                break;
            case 3:
                display(cq);
                break;
            case 4:
                free(cq->it);
                free(cq);
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    
    return 0;
}
