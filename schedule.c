#include "project.h"

int FCFS(struct data * head)
{
    FILE *fcfsfile = fopen("fcfs.csv", "a");
    //fseek(fcfsfile, 0, SEEK_END);
    //fprintf(fcfsfile, "New Run:\n\n");
    struct data * temp = head;
    int sum = abs(start-(head->cylinder));
    fprintf(fcfsfile, "%d,", start);
    while(temp->next!=NULL)
    {
        fprintf(fcfsfile, "%d,", temp->cylinder);
        sum+=abs((temp->cylinder)-(temp->next->cylinder));
        temp=temp->next;
    }
    fprintf(fcfsfile, "%d", temp->cylinder);
    //fprintf(fcfsfile, "\n");
    fclose(fcfsfile);
    return sum;
}

int SSTF(struct data * head)
{
    FILE *sstffile = fopen("sstf.csv", "a");
    //fprintf(sstffile, "New Run:\n\n");
    struct data *temp = head;
    temp=insert(&temp,start);

    int sum=0;

    while(temp!=NULL)
    {
        if(temp->next==NULL && temp->prev==NULL)
        {
            fprintf(sstffile, "%d", temp->cylinder);
            fclose(sstffile);
            return sum;
        }
        else if(temp->next==NULL)
        {
            fprintf(sstffile, "%d,", temp->cylinder);
            sum+=abs(temp->cylinder - temp->prev->cylinder);
            temp=temp->prev;
            delete(&head,temp->next);
        }
        else if( (temp->prev==NULL) || (abs(temp->cylinder - temp->next->cylinder) < abs(temp->cylinder - temp->prev->cylinder)))
        {
            fprintf(sstffile, "%d,", temp->cylinder);
            sum+=abs(temp->cylinder - temp->next->cylinder);
            temp=temp->next;
            delete(&head,temp->prev);
        }
        else
        {
            fprintf(sstffile, "%d,", temp->cylinder);
            sum+=abs(temp->cylinder - temp->prev->cylinder);
            temp=temp->prev;
            delete(&head,temp->next);
        }
    }
    //fprintf(sstffile, "\n");
    fclose(sstffile);
    return sum;
}

int LOOK(struct data * head)
{
    FILE *lookfile = fopen("look.csv", "a");
    //fprintf(lookfile, "New Run:\n\n");
    struct data *temp = head;
    temp=insert(&temp,start);
    int sum=0;
    if (maxC - temp->cylinder < temp->cylinder) {
        while(temp!=NULL)
        {
            if(temp->next==NULL && temp->prev==NULL)
            {
                fprintf(lookfile, "%d", temp->cylinder);
                fclose(lookfile);
                return sum;
            }
            else if(temp->prev!=NULL && temp->next == NULL)
            {
                fprintf(lookfile, "%d,", temp->cylinder);
                temp=temp->prev;
                sum+=abs(temp->cylinder - temp->next->cylinder);
                delete(&head,temp->next);
            }
            else
            {
                fprintf(lookfile, "%d,", temp->cylinder);
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
                fprintf(lookfile, "%d", temp->cylinder);
                fclose(lookfile);
                return sum;
            }
            else if(temp->next!=NULL && temp->prev == NULL)
            {
                fprintf(lookfile, "%d,", temp->cylinder);
                temp=temp->next;
                sum+=abs(temp->cylinder - temp->prev->cylinder);
                delete(&head,temp->prev);
            }
            else
            {
                fprintf(lookfile, "%d,", temp->cylinder);
                sum+=abs(temp->cylinder - temp->prev->cylinder);
                temp=temp->prev;
                delete(&head,temp->next);
            }
        }
    }
    //fprintf(lookfile, "\n");
    fclose(lookfile);
    return sum;
}

int CLOOK(struct data* head)
{
    FILE *clookfile = fopen("clook.csv", "a");
    //fprintf(clookfile, "New Run:\n\n");
    struct data* temp = head;
    temp=insert(&temp,start);
    int sum=0;

    if (maxC - temp->cylinder < temp->cylinder) {
        while(temp!=NULL)
        {
            if(temp->next==NULL && temp->prev==NULL)
            {
                fprintf(clookfile, "%d", temp->cylinder);
                fclose(clookfile);
                return sum;
            }
            else if(temp->next==NULL)
            {
                fprintf(clookfile, "%d,", temp->cylinder);
                temp=temp->prev;
                //sum+=abs(temp->cylinder - temp->next->cylinder);
                delete(&head,temp->next);
                while(temp->prev!=NULL)
                    temp=temp->prev;
            }
            else
            {
                fprintf(clookfile, "%d,", temp->cylinder);
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
                fprintf(clookfile, "%d", temp->cylinder);
                fclose(clookfile);
                return sum;
            }
            else if(temp->prev==NULL)
            {
                fprintf(clookfile, "%d,", temp->cylinder);
                temp=temp->next;
                //sum+=abs(temp->cylinder - temp->prev->cylinder);
                delete(&head,temp->prev);
                while(temp->next!=NULL)
                    temp=temp->next;
            }
            else
            {
                fprintf(clookfile, "%d,", temp->cylinder);
                temp=temp->prev;
                sum+=abs(temp->cylinder - temp->next->cylinder);
                delete(&head,temp->next);
            }
        }
    }
    //fprintf(clookfile, "\n");
    fclose(clookfile);
    return sum;
}

int SCAN(struct data* head)
{
    FILE *scanfile = fopen("scan.csv", "a");
    //fprintf(scanfile, "New Run:\n\n");
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
                fprintf(scanfile, "%d", temp->cylinder);
                fclose(scanfile);
                return sum;
            }
            else if(temp->next==NULL)
            {
                fprintf(scanfile, "%d,", temp->cylinder);
                temp=temp->prev;
                sum+=abs(temp->cylinder - temp->next->cylinder);
                delete(&head,temp->next);
            }
            else
            {
                fprintf(scanfile, "%d,", temp->cylinder);
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
                fprintf(scanfile, "%d", temp->cylinder);
                fclose(scanfile);
                return sum;
            }
            else if(temp->prev==NULL)
            {
                fprintf(scanfile, "%d,", temp->cylinder);
                temp=temp->next;
                sum+=abs(temp->cylinder - temp->prev->cylinder);
                delete(&head,temp->prev);
            }
            else
            {
                fprintf(scanfile, "%d,", temp->cylinder);
                sum+=abs(temp->cylinder - temp->prev->cylinder);
                temp=temp->prev;
                delete(&head,temp->next);
            }
        }
    }
    //fprintf(scanfile, "\n");
    fclose(scanfile);
    return sum;
}

int CSCAN(struct data* head)
{
    FILE *cscanfile = fopen("cscan.csv", "a");
    //fprintf(cscanfile, "New Run:\n\n");
    struct data* temp = head,*d;

    temp=insert(&temp,start);
    int sum=0;

    if (maxC - temp->cylinder < temp->cylinder) {
        while(temp!=NULL)
        {
            if(temp->next==NULL && temp->prev==NULL)
            {
                fprintf(cscanfile, "%d", temp->cylinder);
                fclose(cscanfile);
                return sum;
            }
            else if(temp->next==NULL)
            {
                fprintf(cscanfile, "%d,", temp->cylinder);
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
                fprintf(cscanfile, "%d,", temp->cylinder);
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
                fprintf(cscanfile, "%d", temp->cylinder);
                fclose(cscanfile);
                return sum;
            }
            else if(temp->prev==NULL) //evaluates once
            {
                fprintf(cscanfile, "%d,", temp->cylinder);
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
                fprintf(cscanfile, "%d,", temp->cylinder);
                temp=temp->prev;
                sum+=abs(temp->cylinder - temp->next->cylinder);
                delete(&head,temp->next);
            }
        }
    }
    //fprintf(cscanfile, "\n");
    fclose(cscanfile);
    return sum;
}
