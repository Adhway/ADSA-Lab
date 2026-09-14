#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *data;
    int top;
    int capacity;

    int totalCost;
    int operations;
} Stack;

/* Initialize Stack */
void initStack(Stack *s)
{
    s->capacity = 1;
    s->top = -1;

    s->data = (int *)malloc(s->capacity * sizeof(int));

    s->totalCost = 0;
    s->operations = 0;
}

/* PUSH */
void push(Stack *s, int value)
{
    int i;

    /* If table is full, double its size */
    if (s->top == s->capacity - 1)
    {
        int oldCapacity = s->capacity;

        s->capacity = s->capacity * 2;

        s->data = (int *)realloc(
            s->data,
            s->capacity * sizeof(int)
        );

        /* Cost of copying old elements */
        for (i = 0; i < oldCapacity; i++)
        {
            s->totalCost++;
        }

        printf("Table resized: %d -> %d\n",
               oldCapacity, s->capacity);
    }

    /* Insert element */
    s->top++;
    s->data[s->top] = value;

    s->totalCost++;
    s->operations++;

    printf("Pushed %d\n", value);
}

/* POP */
void pop(Stack *s)
{
    int value;

    if (s->top == -1)
    {
        printf("Stack Underflow!\n");
        return;
    }

    value = s->data[s->top];

    s->top--;

    s->totalCost++;
    s->operations++;

    printf("Popped %d\n", value);
}

/* DISPLAY */
void display(Stack *s)
{
    int i;

    if (s->top == -1)
    {
        printf("Stack is empty!\n");
        return;
    }

    printf("\nStack: ");

    for (i = s->top; i >= 0; i--)
    {
        printf("%d ", s->data[i]);
    }

    printf("\n");
    printf("Top = %d\n", s->top);
    printf("Capacity = %d\n", s->capacity);
}

/* Aggregate Analysis */
void analysis(Stack *s)
{
    if (s->operations == 0)
    {
        printf("\nNo operations performed yet.\n");
        return;
    }

    printf("\n========== AGGREGATE ANALYSIS ==========\n");

    printf("Total operations = %d\n",
           s->operations);

    printf("Total actual cost = %d\n",
           s->totalCost);

    printf("Average cost = %.2f\n",
           (float)s->totalCost / s->operations);

    printf("\nAmortized cost of PUSH = O(1)\n");
    printf("Amortized cost of POP  = O(1)\n");
    printf("Overall amortized cost = O(1)\n");
}

/* MAIN */
int main()
{
    Stack s;
    int choice;
    int value;
    int n, i;

    initStack(&s);

    while (1)
    {
        printf("\n==============================\n");
        printf("        DYNAMIC STACK\n");
        printf("==============================\n");
        printf("1. PUSH\n");
        printf("2. POP\n");
        printf("3. DISPLAY\n");
        printf("4. AGGREGATE ANALYSIS\n");
        printf("5. EXIT\n");
        printf("==============================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            /* Multiple PUSH */
            case 1:
                printf("How many elements do you want to push? ");
                scanf("%d", &n);

                for (i = 0; i < n; i++)
                {
                    printf("Enter value %d: ", i + 1);
                    scanf("%d", &value);

                    push(&s, value);
                }
                break;
            /* Multiple POP */
            case 2:
                printf("How many elements do you want to pop? ");
                scanf("%d", &n);

                for (i = 0; i < n; i++)
                {
                    pop(&s);
                }
                break;
            /* DISPLAY */
            case 3:
                display(&s);
                break;
            /* AGGREGATE ANALYSIS */
            case 4:
                analysis(&s);
                break;
            /* EXIT */
            case 5:
                free(s.data);
                printf("Program terminated.\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}