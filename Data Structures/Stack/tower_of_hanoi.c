// C Program for Tower of Hanoi using stack
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DELETE_FAILURE -1
//The above value is to be chosen such that the value is never equal to any permissible element in the stack

struct node
{
    int data;
    struct node *next;
};

void tower_of_hanoi(int no_of_discs, struct node **src, struct node **aux, struct node **dest, char s, char a, char d);
void move_disc_between_two_poles(struct node **pole1, struct node **pole2, char p1, char p2);
void push(struct node **topPtr, int value);
int pop(struct node **topPtr);
void display_movement(char fromPole, char toPole, int disc);

int main()
{
    int no_of_discs;
    struct node *src = NULL, *aux = NULL, *dest = NULL;//top pointers for the stacks for the 3 rods
    char s = 'A', a = 'B', d = 'C';//Names of the rods
    printf("\n\t\tTOWER OF HANOI\n");
    printf("\nEnter the number of discs (an integer greater than zero) : ");
    scanf("%d", &no_of_discs);
    if (no_of_discs <= 0)
    {
        printf("\nNumber of discs should be an integer greater than zero.");
        exit(0);
    }
    tower_of_hanoi(no_of_discs, &src, &aux, &dest, s, a, d);

    return 0;
}

void tower_of_hanoi(int no_of_discs, struct node **src, struct node **aux, struct node **dest, char s, char a, char d)
{
    long long int i, total_no_of_moves;
    char temp;
    printf("\nNote: Discs having larger values are larger in size. So disc 1 is the smallest disc.");
    printf("\nSource rod=%c, Auxiliary rod=%c, Destination rod=%c.", s, a, d);

    //If number of discs is even, then destination rod and auxiliary rod are interchanged
    if (no_of_discs % 2 == 0)
    {
        temp = d;
        d = a;
        a = temp;
    }
    total_no_of_moves = pow(2, no_of_discs) - 1;
    printf("\n\nTotal number of moves=%d", total_no_of_moves);
    for (i = no_of_discs; i >= 1; i--) //Filling up the source rod
        push(src, i);

    printf("\n\nThe steps are as follows:\n");
    for (i = 1; i <= total_no_of_moves; i++) //Moving the discs
    {
        if (i % 3 == 1)
            move_disc_between_two_poles(src, dest, s, d);

        else if (i % 3 == 2)
            move_disc_between_two_poles(src, aux, s, a);

        else if (i % 3 == 0)
            move_disc_between_two_poles(aux, dest, a, d);
    }
}

void move_disc_between_two_poles(struct node **pole1, struct node **pole2, char p1, char p2)
{
    int pole1TopDisc = pop(pole1);
    int pole2TopDisc = pop(pole2);

    if (pole1TopDisc == DELETE_FAILURE)// When pole 1 is empty
    {
        push(pole1, pole2TopDisc);
        display_movement(p2, p1, pole2TopDisc);
    }

    else if (pole2TopDisc == DELETE_FAILURE)// When pole 2 is empty
    {
        push(pole2, pole1TopDisc);
        display_movement(p1, p2, pole1TopDisc);
    }

    else if (pole1TopDisc > pole2TopDisc)// When top disc of pole1 is larger than top disc of pole2
    {
        push(pole1, pole1TopDisc);
        push(pole1, pole2TopDisc);
        display_movement(p2, p1, pole2TopDisc);
    }

    else // When top disc of pole1 is smaller than top disc of pole2
    {
        push(pole2, pole2TopDisc);
        push(pole2, pole1TopDisc);
        display_movement(p1, p2, pole1TopDisc);
    }
}

void push(struct node **topPtr, int value)
{
    struct node *newn;
    newn = (struct node *)malloc(sizeof(struct node));
    newn->data = value;
    newn->next = (*topPtr);
    (*topPtr) = newn;
}

int pop(struct node **topPtr)
{
    int value;
    struct node *ptr;
    if ((*topPtr) == NULL)
    {
        return DELETE_FAILURE;
    }
    else
    {
        ptr = (*topPtr);
        (*topPtr) = (*topPtr)->next;
        value = ptr->data;
        free(ptr);
        ptr = NULL;
        return value;
    }
}

void display_movement(char fromPole, char toPole, int disc)
{
    printf("Move disc %d from rod \'%c\' to rod \'%c\'\n", disc, fromPole, toPole);
}