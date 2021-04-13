#include <stdio.h>
#include <stdlib.h>

#define DELETE_FAILURE -32768
//The value is to be choosen such that the value is never equal to any permissible element in the list
struct node
{
    struct node *prev;
    int data;
    struct node *next;
};
void display(struct node **headerPtr);
void insert_beg(struct node **headerPtr, int value);
void insert_at_pos(struct node **headerPtr, int value, int pos);
void insert_end(struct node **headerPtr, int value);
int delete_beg(struct node **headerPtr);
int delete_at_pos(struct node **headerPtr, int pos);
int delete_end(struct node **headerPtr);

int main()
{
    struct node *header = NULL;
    int ch, value, pos;
    while (1)
    {
        printf("\n\n\t***CIRCULAR DOUBLY LINKED LIST***");
        printf("\n1.DISPLAY");
        printf("\n2.INSERT AT BEGINNING");
        printf("\n3.INSERT AT POSITION");
        printf("\n4.INSERT AT END");
        printf("\n5.DELETE FROM BEGINNING");
        printf("\n6.DELETE FROM POSITION");
        printf("\n7.DELETE FROM END");
        printf("\n0.EXIT");

        printf("\n\nEnter your choice:");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("\n\tCIRCULAR DOUBLY LINKED LIST : DISPLAY");
            display(&header);
            break;

        case 2:
            printf("\n\tCIRCULAR DOUBLY LINKED LIST : INSERT AT BEGINNING");
            printf("\nEnter data:");
            scanf("%d", &value);
            insert_beg(&header, value);
            printf("\n\nThe list after this operation is displayed below:");
            display(&header);
            break;

        case 3:
            printf("\n\tCIRCULAR DOUBLY LINKED LIST : INSERT AT POSITION");
            printf("\nEnter data:");
            scanf("%d", &value);
            printf("\nEnter position(The position of the node at the beginning is 1):");
            scanf("%d", &pos);
            insert_at_pos(&header, value, pos);
            printf("\n\nThe list after this operation is displayed below:");
            display(&header);
            break;

        case 4:
            printf("\n\tCIRCULAR DOUBLY LINKED LIST : INSERT AT END");
            printf("\nEnter data:");
            scanf("%d", &value);
            insert_end(&header, value);
            printf("\n\nThe list after this operation is displayed below:");
            display(&header);
            break;

        case 5:
            printf("\n\tCIRCULAR DOUBLY LINKED LIST : DELETE FROM BEGINNING");
            delete_beg(&header);
            printf("\n\nThe list after this operation is displayed below:");
            display(&header);
            break;

        case 6:
            printf("\n\tCIRCULAR DOUBLY LINKED LIST : DELETE FROM POSITION");
            printf("\nEnter position(The position of the node at the beginning is 1):");
            scanf("%d", &pos);
            delete_at_pos(&header, pos);
            printf("\n\nThe list after this operation is displayed below:");
            display(&header);
            break;

        case 7:
            printf("\n\tCIRCULAR DOUBLY LINKED LIST : DELETE FROM END");
            delete_end(&header);
            printf("\n\nThe list after this operation is displayed below:");
            display(&header);
            break;

        case 0:
            exit(0);

        default:
            printf("\nInvalid Entry! Please try again.");
            break;
        }
    }

    return 0;
}

void display(struct node **headerPtr)
{
    struct node *ptr;
    if ((*headerPtr) == NULL)
    {
        printf("\nCircular doubly linked list is empty.");
        return;
    }
    else
    {
        ptr = (*headerPtr);
        printf("\nThe elements in the list are:\n");
        do
        {
            printf("%d<->", ptr->data);
            ptr = ptr->next;
        } while (ptr != *headerPtr);
        printf("repeats");
    }
}

void insert_beg(struct node **headerPtr, int value)
{
    struct node *ptr, *newn;
    newn = (struct node *)malloc(sizeof(struct node));
    newn->data = value;
    if ((*headerPtr) == NULL)
    {
        newn->next = newn;
        newn->prev = newn;
        (*headerPtr) = newn;
    }
    else
    {
        newn->prev = (*headerPtr)->prev;
        newn->next = (*headerPtr);

        (*headerPtr)->prev->next = newn;
        (*headerPtr)->prev = newn;
        (*headerPtr) = newn;
    }
    printf("\n%d inserted at the beginning of the list", value);
}

void insert_at_pos(struct node **headerPtr, int value, int pos)
{
    int ptrpos;
    struct node *ptr, *newn;

    if (pos < 1)
    {
        printf("\nPosition must be greater than zero.");
        return;
    }
    else if (pos == 1)
    {
        insert_beg(headerPtr, value);
        return;
    }
    else
    {
        if ((*headerPtr) == NULL)
        {
            printf("\nPosition not found in the list as list is empty.");
        }
        else
        {
            newn = (struct node *)malloc(sizeof(struct node));
            newn->data = value;
            ptr = (*headerPtr);
            ptrpos = 1;
            while (ptrpos < pos - 1)
            {
                ptr = ptr->next;
                ptrpos++;
                if (ptr == (*headerPtr))
                {
                    printf("\nPosition not found in the list.");
                    return;
                }
            }
            newn->next = ptr->next;
            newn->prev = ptr;
            ptr->next->prev = newn;
            ptr->next = newn;
            printf("\n%d inserted at position %d of the list", value, pos);
        }
    }
}

void insert_end(struct node **headerPtr, int value)
{
    struct node *newn, *ptr;
    newn = (struct node *)malloc(sizeof(struct node));
    newn->data = value;
    if ((*headerPtr) == NULL)
    {
        newn->next = newn;
        newn->prev = newn;
        (*headerPtr) = newn;
    }
    else
    {
        newn->prev = (*headerPtr)->prev;
        newn->next = (*headerPtr);

        (*headerPtr)->prev->next = newn;
        (*headerPtr)->prev = newn;
    }
    printf("\n%d inserted at the end of the list", value);
}

int delete_beg(struct node **headerPtr)
{
    int value;
    struct node *ptr;
    if ((*headerPtr) == NULL)
    {
        printf("\nUnderflow : Circular doubly linked list is empty. Nothing to delete.");
        return DELETE_FAILURE;
    }
    else if ((*headerPtr)->next == *(headerPtr))
    {
        ptr = (*headerPtr);
        (*headerPtr) = NULL;
        value = ptr->data;
        free(ptr);
        ptr = NULL;
        printf("\nThe deleted element is %d.", value);
        return value;
    }
    else
    {
        (*headerPtr)->prev->next = (*headerPtr)->next;
        (*headerPtr)->next->prev = (*headerPtr)->prev;
        ptr = (*headerPtr);
        (*headerPtr) = (*headerPtr)->next;
        value = ptr->data;
        free(ptr);
        ptr = NULL;
        printf("\nThe deleted element is %d.", value);
        return value;
    }
}

int delete_at_pos(struct node **headerPtr, int pos)
{
    int ptrpos, value;
    struct node *ptr, *ptr2;
    if (pos < 1)
    {
        printf("\nPosition must be greater than zero.");
        return DELETE_FAILURE;
    }
    else if (pos == 1)
    {
        return delete_beg(headerPtr);
    }

    else
    {
        if ((*headerPtr) == NULL)
        {
            printf("\nUnderflow : Circular doubly linked list is empty. Nothing to delete.");
            return DELETE_FAILURE;
        }
        else
        {
            ptr = (*headerPtr);
            ptrpos = 1;
            if (ptr->next == (*headerPtr))
            {
                printf("\nPosition not found in the list.");
                return DELETE_FAILURE;
            }
            while (ptrpos < pos - 1)
            {
                ptr = ptr->next;
                ptrpos++;
                if (ptr->next == (*headerPtr))
                {
                    printf("\nPosition not found in the list.");
                    return DELETE_FAILURE;
                }
            }
            ptr2 = ptr->next;
            ptr->next = ptr->next->next;
            ptr->next->prev = ptr;
            value = ptr2->data;
            free(ptr2);
            ptr2 = NULL;
            printf("\nThe deleted element is %d.", value);
            return value;
        }
    }
}

int delete_end(struct node **headerPtr)
{
    int value;
    struct node *ptr, *ptr2;
    if ((*headerPtr) == NULL)
    {
        printf("\nUnderflow : Circular doubly linked list is empty");
        return DELETE_FAILURE;
    }
    else if ((*headerPtr)->next == (*headerPtr))
    {
        ptr = (*headerPtr);
        (*headerPtr) = NULL;
        value = ptr->data;
        free(ptr);
        ptr = NULL;
        printf("\nThe deleted element is %d.", value);
        return value;
    }
    else
    {
        ptr = (*headerPtr)->prev->prev;
        ptr2 = ptr->next;
        ptr->next = (*headerPtr);
        (*headerPtr)->prev = ptr;
        value = ptr2->data;
        free(ptr2);
        ptr2 = NULL;
        printf("\nThe deleted element is %d.", value);
        return value;
    }
}
