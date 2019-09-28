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
            sum+=abs(temp->cylinder - temp->prev->cylinder);
            temp=temp->prev;
            delete(&head,temp->next);
        }
        else if( (temp->prev==NULL) || (abs(temp->cylinder - temp->next->cylinder) < abs(temp->cylinder - temp->prev->cylinder)))
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
    if (maxC - temp->cylinder < temp->cylinder) {
        while(temp!=NULL)
        {
            if(temp->next==NULL && temp->prev==NULL)
            {
                return sum;
            }
            else if(temp->prev!=NULL && temp->next == NULL)
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
    }
    else {
        while(temp!=NULL)
        {
            if(temp->next==NULL && temp->prev==NULL)
            {
                return sum;
            }
            else if(temp->next!=NULL && temp->prev == NULL)
            {
                temp=temp->next;
                sum+=abs(temp->cylinder - temp->prev->cylinder);
                delete(&head,temp->prev);
            }
            else
            {
                sum+=abs(temp->cylinder - temp->prev->cylinder);
                temp=temp->prev;
                delete(&head,temp->next);
            }
        }
    }
    return sum;
}

int CLOOK(struct data* head)
{
    struct data* temp = head;
    temp=insert(&temp,start);
    int sum=0;

    if (maxC - temp->cylinder < temp->cylinder) {
        while(temp!=NULL)
        {
            if(temp->next==NULL && temp->prev==NULL)
            {
                return sum;
            }
            else if(temp->next==NULL)
            {
                temp=temp->prev;
                //sum+=abs(temp->cylinder - temp->next->cylinder);
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
    }
    else {
        while (temp!=NULL)
        {
            if(temp->next==NULL && temp->prev==NULL)
            {
                return sum;
            }
            else if(temp->prev==NULL)
            {
                temp=temp->next;
                //sum+=abs(temp->cylinder - temp->prev->cylinder);
                delete(&head,temp->prev);
                while(temp->next!=NULL)
                    temp=temp->next;
            }
            else
            {
                temp=temp->prev;
                sum+=abs(temp->cylinder - temp->next->cylinder);
                delete(&head,temp->next);
            }
        }
    }
    return sum;
}

int SCAN(struct data* head)
{
    struct data *temp = head,*t;


    //explicitly add one of two end values to list to handle SCAN because it bounces to the bounds and we have to repeat the first end value again on the bounce
    temp=insert(&temp,start);

    int sum=0;
    if (maxC - temp->cylinder < temp->cylinder)
    {
        t = insert(&head, maxC);
        while(temp!=NULL)
        {
            if(temp->next==NULL && temp->prev==NULL)
            {
                return sum;
            }
            else if(temp->next==NULL)
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
    }
    else
    {
        t=insert(&head,0);
        while(temp!=NULL)
        {
            if(temp->next==NULL && temp->prev==NULL)
            {
                return sum;
            }
            else if(temp->prev==NULL)
            {
                temp=temp->next;
                sum+=abs(temp->cylinder - temp->prev->cylinder);
                delete(&head,temp->prev);
            }
            else
            {
                sum+=abs(temp->cylinder - temp->prev->cylinder);
                temp=temp->prev;
                delete(&head,temp->next);
            }
        }
    }
    return sum;
}

int CSCAN(struct data* head)
{
    struct data* temp = head,*d;

    temp=insert(&temp,start);
    int sum=0;

    if (maxC - temp->cylinder < temp->cylinder) {
        while(temp!=NULL)
        {
            if(temp->next==NULL && temp->prev==NULL)
            {
                return sum;
            }
            else if(temp->next==NULL)
            {
                sum+=abs(temp->cylinder - maxC);
                d=temp;
                while(temp->prev!=NULL)
                {
                    temp=temp->prev;
                }
                delete(&head,d);
                sum+=temp->cylinder;
            }
            else
            {
                temp=temp->next;
                sum+=abs(temp->cylinder - temp->prev->cylinder);
                delete(&head,temp->prev);
            }
        }
    }
    else {
        while(temp!=NULL)
        {
            if(temp->next==NULL && temp->prev==NULL)
            {
                return sum;
            }
            else if(temp->prev==NULL) //evaluates once
            {
                sum+=abs(temp->cylinder);
                d=temp;
                while(temp->next!=NULL)
                {
                    temp=temp->next;
                }
                delete(&head,d);
                sum+=abs(temp->cylinder - maxC);
            }
            else
            {
                temp=temp->prev;
                sum+=abs(temp->cylinder - temp->next->cylinder);
                delete(&head,temp->next);
            }
        }
    }
    return sum;
}
