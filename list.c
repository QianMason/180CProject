#include "project.h"

void add(struct data ** head, int val)
{
    struct data* new_node = (struct data*)malloc(sizeof(struct data));
    struct data* last = *head;

    new_node->cylinder = val;
    new_node->next = NULL;

    if (*head == NULL) {
        new_node->prev = NULL;
        *head = new_node;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new_node;
    new_node->prev = last;
    return;
}

struct data * insert(struct data ** head, int val)
{
    struct data* new_node = (struct data*)malloc(sizeof(struct data));
    new_node->cylinder = val;

    struct data * temp = *head;
    if(temp->cylinder>val)
    {
        new_node->next=temp;
        *head = new_node;
        return new_node;
    }
    while(temp->next->cylinder<val)
    {
        temp=temp->next;
    }


    new_node->next = temp->next;


    temp->next = new_node;


    new_node->prev = temp;


    if (new_node->next != NULL)
        new_node->next->prev = new_node;

    return new_node;
}

void delete(struct data ** head, struct data * del)
{
    if (*head == NULL || del == NULL)
        return;

    if (*head == del)
        *head = del->next;

    if (del->next != NULL)
        del->next->prev = del->prev;

    if (del->prev != NULL)
        del->prev->next = del->next;

    free(del);
    return;
}

void sort(struct data * head)
{
    struct data *ptr1, *ptr2;
    int i, j, temp;
    ptr1 = head;
    ptr2 = head;

    for (i = 0; i < size; i++)
    {
        temp = ptr1->cylinder;
        for (j = 0; j < i; j++)
            ptr2 = ptr2->next;
        for (j = i; j > 0 && ptr2->prev->cylinder > temp; j--)
        {
            ptr2->cylinder = ptr2->prev->cylinder;
            ptr2 = ptr2->prev;
        }
        ptr2->cylinder = temp;
        ptr2 = head;
        ptr1 = ptr1->next;
    }
}

struct data* copy(struct data *head)
{
    struct data * new = NULL, *temp =head;
    int i;

    for(i=0;i<size;i++)
    {
        add(&new,temp->cylinder);
        temp=temp->next;
    }
    return new;
}
