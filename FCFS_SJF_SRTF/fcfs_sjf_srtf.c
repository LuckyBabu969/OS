#include<stdio.h>
#define Max 20
struct process{
int pid,at,bt,ct,tat,wt;
};
void print_table(struct process p[],int n){
    int i;
    float avg_tat=0,avg_wt=0;
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for(i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].tat,
               p[i].wt);
        avg_tat+=p[i].tat;
        avg_wt+=p[i].wt;
    }
    avg_tat/=n;
    avg_wt/=n;
    printf("Average TAT=%.2f\n",avg_tat);
    printf("Average WT=%.2f\n",avg_wt);
}
void fcfs(struct process p[],int n){
int i,j,time=0;
for(i=0;i<n-1;i++){
    for(j=i+1;j<n;j++){
        if(p[i].at>p[j].at){
            struct process t=p[i];
            p[i]=p[j];
            p[j]=t;
        }
    }
}
for(i=0;i<n;i++){
    if(time<p[i].at)
        time=p[i].at;
    time+=p[i].bt;
    p[i].ct=time;
    p[i].tat=p[i].ct-p[i].at;
    p[i].wt=p[i].tat-p[i].bt;
}
print_table(p,n);
}
void sjf(struct process p[],int n){
    int completed=0,time=0,i,min,idx;
    int visited[Max]={0};
    while(completed<n){
        min=9999;
        idx=-1;
        for(i=0;i<n;i++){
            if(p[i].at<=time && visited[i]==0 && p[i].bt<min){
                min=p[i].bt;
                idx=i;
            }
        }
        if(idx!=-1){
            time+=p[idx].bt;
            p[idx].ct=time;
            p[idx].tat=p[idx].ct-p[idx].at;
            p[idx].wt=p[idx].tat-p[idx].bt;
            visited[idx]=1;
            completed++;
        }else{
            time++;
        }
    }
    print_table(p,n);
}
void srtf(struct process p[],int n){
    int rt[Max];
    int completed=0,time=0,i,min,idx;
    int finish;
    for(i=0;i<n;i++)
        rt[i]=p[i].bt;
    while(completed<n){
        min=9999;
        idx=-1;
        for(i=0;i<n;i++){
            if(p[i].at<=time && rt[i]>0 && rt[i]<min){
                min=rt[i];
                idx=i;
            }
        }
        if(idx!=-1){
            rt[idx]--;
            time++;
            if(rt[idx]==0){
                completed++;
                finish=time;
                p[idx].ct=finish;
                p[idx].tat=p[idx].ct-p[idx].at;
                p[idx].wt=p[idx].tat-p[idx].bt;
            }
        }
        else{
            time++;
        }
    }
    print_table(p,n);
}
int main(){
struct process p[Max];
int i,n,ch;
printf("Ahmad Lucky Gold\n");
printf("enter no of processes:");
scanf("%d",&n);
for(i=0;i<n;i++){
    p[i].pid=i+1;
    printf("enter at%d:",i+1);
    scanf("%d",&p[i].at);
    printf("enter bt%d:",i+1);
    scanf("%d",&p[i].bt);
}
printf("\nenter the algorithm:");
printf("\n1:FCFS    ");
printf("2:SJF   ");
printf("3:SRTF\n");
scanf("%d",&ch);
if(ch==1)
    fcfs(p,n);
else if(ch==2)
    sjf(p,n);
else if(ch==3)
    srtf(p,n);
else
    printf("\n invalid input");
return 0;
}