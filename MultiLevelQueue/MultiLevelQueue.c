#include <stdio.h>
#define MAX 20
struct process{
    int pid,at,bt,rt,ct,tat,wt,type;
};
int main(){
    struct process p[MAX];
    int n,tq;
    printf("Ahmad Lucky Gold\n");
    printf("Enter number of processes:");
    scanf("%d",&n);
    printf("Enter Time Quantum (Q1 - RR):");
    scanf("%d",&tq);
    for(int i=0;i<n;i++){
        printf("Process %d\n",i+1);
        p[i].pid=i+1;
        printf("Arrival Time: ");
        scanf("%d",&p[i].at);
        printf("Burst Time: ");
        scanf("%d",&p[i].bt);
        printf("Type (1=Q1/System,2=Q2/User):");
        scanf("%d",&p[i].type);
        p[i].rt=p[i].bt;
        p[i].ct=0;
    }
    int time=0,completed=0;
    int queue[MAX],front=0,rear=0;
    int inQueue[MAX]={0};
    int q2_index=-1;
    while(completed<n){
        for(int i=0;i<n;i++){
            if(p[i].type==1 && p[i].at<=time && p[i].rt>0 && !inQueue[i]){
                queue[rear++]=i;
                inQueue[i]=1;
            }
        }
        if(front<rear){
            int i=queue[front++];
            int exec=(p[i].rt>tq)?tq:p[i].rt;
            p[i].rt-=exec;
            time+=exec;
            for(int j=0;j<n;j++){
                if(p[j].type==1 && p[j].at<=time && p[j].rt>0 && !inQueue[j]){
                    queue[rear++]=j;
                    inQueue[j]=1;
                }
            }
            if(p[i].rt>0){
                queue[rear++]=i;
            }else{
                p[i].ct=time;
                completed++;
            }
            q2_index=-1;
        }
        else{
            if(q2_index==-1){
                int earliest=9999;
                for(int i=0;i<n;i++){
                    if(p[i].type==2 && p[i].rt>0 && p[i].at<=time){
                        if(p[i].at<earliest){
                            earliest=p[i].at;
                            q2_index=i;
                        }
                    }
                }
            }
            if(q2_index!=-1){
                p[q2_index].rt--;
                time++;
                if(p[q2_index].rt==0){
                    p[q2_index].ct=time;
                    completed++;
                    q2_index=-1;
                }
            }else{
                time++;
            }
        }
    }
    float avg_tat=0,avg_wt=0;
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++){
        p[i].tat=p[i].ct-p[i].at;
        p[i].wt=p[i].tat-p[i].bt;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
        avg_tat+=p[i].tat;
        avg_wt+=p[i].wt;
    }
    printf("Average Turnaround Time=%.2f",avg_tat/n);
    printf("\nAverage Waiting Time=%.2f\n",avg_wt/n);
    return 0;
}