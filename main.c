#include "project.h"

int main()
{
    char name[256];
    char *fname = name;
    for (int i = 0; i < 256; i++) {
        name[i] = 0;
    }
    int nums[1000];
    int mode = 0;
    printf("Please enter 1 for interactive mode or 2 for batch mode:\n");
    scanf("%d", &mode);
    if (mode == 1) {
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
        //move head to the actual head after sorting
        // while (head->prev != NULL) {
        //     head = head->prev;
        // }
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
    }
    else {
        FILE *fptr;
        printf("Please enter name of file where numbers are stored: \n");
        scanf("%s",fname);
        fptr = fopen(fname, "r");
        if (!fptr) {
            printf("open fail\n");
            return (0);
        }
        int i=0;
        int num;
        while(fscanf(fptr, "%d", &num) == 1) {
            nums[i] = num;
            i++;
        }
        fclose(fptr);
        printf("Please enter max number of cylinders:\n");
        scanf("%d", &maxC);
        printf("Please enter size of testing set:\n");
        scanf("%d", &size);
        printf("Please enter starting point:\n");
        scanf("%d", &start);
        int value;
        struct data * head = NULL;

        for(i=0;i<size;i++)
        {
            value = nums[i];
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
    }

    return 0;
}
