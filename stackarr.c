//stack using array
#include <stdio.h>
#include <stdlib.h>
struct stack
{
  int *arr;
  int capacity, size, top;
};
void initialize(struct stack *s1, int cap)
{
  s1->capacity = cap;
  s1->size = 0;
  s1->top = -1;
  s1->arr = (int *)malloc(sizeof(int) * cap);
  if (s1->arr == NULL)
  {
    printf("memory allocation failed\n");
    exit(1);
  }
}
void push(struct stack *s1, int val)
{
  if (s1->capacity == s1->size)
  {
    printf("The stack is full, increasing the size.\n");
    s1->capacity *= 2;
    s1->arr = (int *)realloc(s1->arr, sizeof(int) * s1->capacity);
    if (s1->arr == NULL)
    {
      printf("Memory reallocation failed.\n");
      exit(1);
    }
  }
    s1->arr[++s1->top] = val;
    s1->size++;
  }

void top_element(struct stack *s1)
{
  if (s1->top == -1)
  {
    printf("Stack underflow\n");
    return;
  }
  printf("%d\n", s1->arr[s1->top]);
}
void pop(struct stack *s1)
{

  if (s1->top == -1)
  {
    printf("im underflow\n");
    return;
  }
  printf("the pop element is:%d\n", s1->arr[s1->top--]);
  s1->size--;
}
void display(struct stack *s1)
{
  if (s1->top == -1)
  {
    printf("underflow\n");
    return;
  }
  int i = s1->top;
  printf("stack elements are\n");
  while (i >= 0)
  {
    printf("%d\n", s1->arr[i]);
    i--;
  }
}
int size(struct stack *s1)
{
  return s1->size;
}
int main()
{
  int n;
  struct stack s1;
  printf("Enter the capacity of the stack: ");
  scanf("%d", &n);
  initialize(&s1, n);
  int j=1;
    printf("for push:0\nfor pop:1\n for display:2\n for size:3\nfor exit:4\n");
while (j)
{
  int k;
  scanf("%d",&k);
  if (k==0)
  {
    int val;
    printf("Enter the element to push:");
    scanf("%d",&val);
    push(&s1,val);
    j++;
  }
  else if(k==1){
    pop(&s1);
    j--;
  }
  else if(k==2){
    printf("Displaying the stack\n");
    display(&s1);
  }
  else if (k==3)
   {
     printf("the size of the stack is %d\n",size(&s1));
   }
   else if (k==4)
   {
    break;
   }
   else{
    printf("Invalid statement\n");
   }
}

  free(s1.arr); 
  return 0;
}