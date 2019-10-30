#include "project.h"

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
    FILE *fcfsfile = fopen("fcfs.txt", "w");
    FILE *sstffile = fopen("sstf.txt", "w");
    FILE *scanfile = fopen("scan.txt", "w");
    FILE *cscanfile = fopen("cscan.txt", "w");
    FILE *lookfile = fopen("look.txt", "w");
    FILE *clookfile = fopen("clook.txt", "w");

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
