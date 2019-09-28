#include<stdio.h>
#include<stdlib.h>

struct data
{
    struct data * prev;
    int cylinder;
    struct data * next;
};

int size,start,maxC;

void sort(struct data*);
void add(struct data**, int value);
struct data* insert(struct data **,int);
void delete(struct data **,struct data *);
struct data* copy(struct data *);

int FCFS(struct data*);
int SSTF(struct data*);
int SCAN(struct data*);
int CSCAN(struct data*);
int LOOK(struct data*);
int CLOOK(struct data*);


int main()
{
    printf("Enter the total number of cylinders:");
    scanf("%d",&maxC);
    printf("Enter the starting position of disk head:");
    scanf("%d",&start);
    printf("Enter the size of the list:");
    scanf("%d",&size);
    printf("Enter the cylinder values\n");

    int i,value;
    struct data * head = NULL;

    for(i=0;i<size;i++)
    {
        scanf("%d",&value);
        add(&head,value);
    }

    struct data * fcfs = copy(head);
    printf("FCFS=%d",FCFS(fcfs));


    sort(head);
    printf("\n");


    struct data * sstf = copy(head);
    printf("SSTF=%d",SSTF(sstf));
    printf("\n");



    struct data * scan = copy(head);
    printf("SCAN=%d",SCAN(scan));
    printf("\n");

    struct data * cscan = copy(head);
    printf("CSCAN=%d",CSCAN(cscan));
    printf("\n");

    struct data * look = copy(head);
    printf("LOOK=%d",LOOK(look));
    printf("\n");

    struct data * clook = copy(head);
    printf("CLOOK=%d",CLOOK(clook));
    printf("\n");

    return 0;
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
        temp->prev=new_node;
        *head = new_node;
        return new_node;
    }
    while(temp->next!=NULL && temp->next->cylinder<val)
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
    //code case where we are passed a list of size 1
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
    printf("A");
    fflush(stdout);
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
