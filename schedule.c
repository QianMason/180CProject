#include "project.h"

int FCFS(struct data * head)
{
    struct data * temp = head;
    int sum = abs(start-(head->cylinder));
    while(temp->next!=NULL)
    {
        sum+=abs((temp->cylinder)-(temp->next->cylinder));
        temp=temp->next;
    }
    return sum;
}


int SSTF(struct data * head)
{
    struct data *temp = head;
    temp=insert(&temp, start);
    int sum=0;


    while(temp!=NULL){
    if(temp->next==NULL && temp->prev==NULL)
    {
        return sum;
    }
    else if((temp->prev==NULL) || (abs(temp->cylinder - temp->next->cylinder) < abs(temp->cylinder - temp->prev->cylinder)))
    {
        sum+=abs(temp->cylinder - temp->next->cylinder);
        temp=temp->next;
        delete(&head,temp->prev);
    }
    else
    {
        sum+=abs(temp->cylinder - temp->prev->cylinder);
        temp=temp->prev;
        delete(&head,temp->next);
    }
    }
    return sum;
}

int LOOK(struct data * head)
{
    struct data *temp = head;
    temp=insert(&temp,start);
    int sum=0;

    while(temp!=NULL)
    {
        if(temp->next==NULL && temp->prev==NULL)
        {
            return sum;
        }
        else if(temp->prev!=NULL)
        {
            temp=temp->prev;
            sum+=abs(temp->cylinder - temp->next->cylinder);
            delete(&head,temp->next);
        }
        else
        {
            sum+=abs(temp->cylinder - temp->next->cylinder);
            temp=temp->next;
            delete(&head,temp->prev);
        }
    }
    return sum;
}

int CLOOK(struct data* head)
{
    struct data* temp = head;
    temp=insert(&temp,start);
    int sum=0;

    while(temp!=NULL)
    {
        if(temp->next==NULL && temp->prev==NULL)
        {
            return sum;
        }
        else if(temp->next==NULL)
        {
            temp=temp->prev;
            delete(&head,temp->next);
            while(temp->prev!=NULL)
                temp=temp->prev;
        }
        else
        {
            temp=temp->next;
            sum+=abs(temp->cylinder - temp->prev->cylinder);
            delete(&head,temp->prev);
        }
    }
    return sum;
}

