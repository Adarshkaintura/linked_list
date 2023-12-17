//queue using linked list
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Queue
{
    struct Node *f;
    struct Node *r;
};
void enq(struct Queue *q, int val)
{
    struct Node *newn = (struct Node *)malloc(sizeof(struct Node));
    if (!newn)
    {
        printf("Memory not allocated\n");
        return;
    }
    newn->data = val;
    newn->next = NULL;
    if (q->f == NULL)
    {
        q->f = newn;
        q->r = newn;
    }
    else
    {
        q->r->next = newn;
        q->r = newn;
    }
}
void disp(struct Queue *q)
{
    if (q->f == NULL)
    {
        printf("Queue is empty\n");
        return;
    }
    struct Node *temp = q->f;
    while (temp != NULL)
    {
        printf("%d\n", temp->data);
        temp = temp->next;
    }
}
struct Queue *init()
{
    struct Queue *q = (struct Queue *)malloc(sizeof(struct Queue));
    if (!q)
    {
        printf("Memory not allocated\n");
        return NULL;
    }
    q->f = NULL;
    q->r = NULL;
    return q;
}



void deq(struct Queue *q)
{
    if (q->f == NULL)
    {
        printf("Queue is empty\n");
        return;
    }

    struct Node *temp = q->f;
    q->f = q->f->next;
    free(temp);
}



int main()
{
    struct Queue *q = init();
    printf("Queue using linked list menu\n");
    while (1)
    {
        printf("1-enqueue\n");
        printf("2-dequeue\n");
        printf("3-display\n");
        printf("4-exit\n");
        int n, val;
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            printf("Enter data: ");
            scanf("%d", &val);
            enq(q, val);
            break;

        case 2:
            deq(q);
            break;

        case 3:
            disp(q);
            break;

        case 4:
            free(q);
            exit(1);

        default:
            printf("Invalid entry\n");
        }
    }
    return 0;
}
