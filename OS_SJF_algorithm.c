#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
    char pname[50];
    int btime;
    int atime;
};

void insert(struct node a[], int n){
    int i;
    for(i = 0; i < n; i++){
        printf("Enter burst time of %dth process:", i + 1);
        scanf("%d", &a[i].btime);
        a[i].atime = 0;
    }
}

int btimeSort(const void *a, const void *b){
    return ((struct node *)a)->btime - ((struct node *)b)->btime;
}

int atimeSort(const void *a, const void *b){
    return ((struct node *)a)->atime - ((struct node *)b)->atime;
}

void disp(struct node a[], int n){
    qsort(a, n, sizeof(struct node), atimeSort);
    int ttime = 0, i, j;
    int tArray[n];
    for(i = 0; i < n; i++){
        j = i;
        while(a[j].atime <= ttime && j != n){
            j++;
        }
        qsort(a + i, j - i, sizeof(struct node), btimeSort);
        tArray[i] = ttime;
        ttime += a[i].btime;
    }
    tArray[i] = ttime;
    float averageWaitingTime = 0;
    float averageResponseTime = 0;
    float averageTAT = 0;
    printf("\nP.Name\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for(i = 0; i < n; i++){
        printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n", a[i].pname, a[i].atime, a[i].btime, tArray[i + 1], tArray[i] - a[i].atime + a[i].btime, tArray[i] - a[i].atime, tArray[i] - a[i].atime);
        averageTAT += tArray[i] - a[i].atime + a[i].btime;
        averageWaitingTime += tArray[i] - a[i].atime;
        averageResponseTime += tArray[i] - a[i].atime;
    }
    printf("\n");
    printf("\nGantt Chart\n");
    for(i = 0; i < n; i++){
        printf("| %s ", a[i].pname);
    }
    printf("\n");
    for(i = 0; i < n + 1; i++){
        printf("%d\t", tArray[i]);
    }
    printf("\n");
    printf("Average Response time: %.2f\n", (float)averageResponseTime / (float)n);
    printf("Average Waiting time: %.2f\n", (float)averageWaitingTime / (float)n);
    printf("Average TAT time: %.2f\n", (float)averageTAT / (float)n);
}

int main(){
    int nop, i;
    printf("Enter number of processes:\n");
    scanf("%d", &nop);
    struct node a[nop];
    insert(a, nop);
    disp(a, nop);
    return 0;
}
