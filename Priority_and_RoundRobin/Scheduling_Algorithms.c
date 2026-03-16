#include<stdio.h>
#define Max 20
struct process{
    int pid,at,bt,pr,ct,tat,wt;
};
void print_table(struct process p[],int n){
    int i;
    float avg_tat=0,avg_wt=0;
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
        avg_tat+=p[i].tat;
        avg_wt+=p[i].wt;
    }
    printf("\nAverage TAT=%.2f",avg_tat/n);
    printf("\nAverage WT=%.2f\n",avg_wt/n);
}
void fcfs(struct process p[],int n){
    int i,j,time=0;
    for(i=0;i<n-1;i++)
        for(j=i+1;j<n;j++)
            if(p[i].at>p[j].at){
                struct process t=p[i];
                p[i]=p[j];
                p[j]=t;
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
        for(i=0;i<n;i++)
            if(p[i].at<=time && visited[i]==0 && p[i].bt<min){
                min=p[i].bt;
                idx=i;
            }
        if(idx!=-1){
            time+=p[idx].bt;
            p[idx].ct=time;
            p[idx].tat=p[idx].ct-p[idx].at;
            p[idx].wt=p[idx].tat-p[idx].bt;
            visited[idx]=1;
            completed++;
        }
        else
            time++;
    }
    print_table(p,n);
}
void srtf(struct process p[],int n){
    int rt[Max],i,time=0,completed=0,min,idx;
    for(i=0;i<n;i++)
        rt[i]=p[i].bt;
    while(completed<n){
        min=9999;
        idx=-1;
        for(i=0;i<n;i++)
            if(p[i].at<=time && rt[i]>0 && rt[i]<min){
                min=rt[i];
                idx=i;
            }
        if(idx!=-1){
            rt[idx]--;
            time++;
            if(rt[idx]==0){
                completed++;
                p[idx].ct=time;
                p[idx].tat=p[idx].ct-p[idx].at;
                p[idx].wt=p[idx].tat-p[idx].bt;
            }
        }
        else
            time++;
    }
    print_table(p,n);
}
void priority_np(struct process p[],int n){
    int i,type;
    printf("\nPriority Type\n");
    printf("1.Higher number=Higher priority\n");
    printf("2.Lower number=Higher priority\n");
    scanf("%d",&type);
    for(i=0;i<n;i++){
        printf("Enter priority for P%d:",p[i].pid);
        scanf("%d",&p[i].pr);
    }
    int completed=0,time=0,idx;
    int visited[Max]={0};
    while(completed<n){
        idx=-1;
        for(i=0;i<n;i++){
            if(p[i].at<=time && visited[i]==0){
                if(idx==-1)
                    idx=i;
                else{
                    if(type==1 && p[i].pr>p[idx].pr)
                        idx=i;
                    if(type==2 && p[i].pr<p[idx].pr)
                        idx=i;
                }
            }
        }
        if(idx!=-1){
            time+=p[idx].bt;
            p[idx].ct=time;
            p[idx].tat=p[idx].ct-p[idx].at;
            p[idx].wt=p[idx].tat-p[idx].bt;
            visited[idx]=1;
            completed++;
        }
        else
            time++;
    }
    print_table(p,n);
}
void priority_p(struct process p[],int n){
    int i,type;
    printf("\nPriority Type\n");
    printf("1 Higher number = Higher priority\n");
    printf("2 Lower number = Higher priority\n");
    scanf("%d",&type);
    for(i=0;i<n;i++){
        printf("Enter P%d:",p[i].pid);
        scanf("%d",&p[i].pr);
    }
    int rt[Max],time=0,completed=0,idx;
    for(i=0;i<n;i++)
        rt[i]=p[i].bt;
    while(completed<n){
        idx=-1;
        for(i=0;i<n;i++){
            if(p[i].at<=time && rt[i]>0){
                if(idx==-1)
                    idx=i;
                else{
                    if(type==1 && p[i].pr>p[idx].pr)
                        idx=i;
                    if(type==2 && p[i].pr<p[idx].pr)
                        idx=i;
                }
            }
        }
        if(idx!=-1){
            rt[idx]--;
            time++;
            if(rt[idx]==0){
                completed++;
                p[idx].ct=time;
                p[idx].tat=p[idx].ct-p[idx].at;
                p[idx].wt=p[idx].tat-p[idx].bt;
            }
        }
        else
            time++;
    }
    print_table(p,n);
}
void round_robin(struct process p[], int n){
    int tq, time=0, completed=0;
    int rt[Max], queue[Max], front=-1, rear=-1;
    printf("Enter Time Quantum: ");
    scanf("%d",&tq);
    for(int i=0;i<n;i++) {
        rt[i]=p[i].bt;
        p[i].pid=i+1;
    }
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(p[i].at > p[j].at){
                struct process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
                int tmp = rt[i]; rt[i]=rt[j]; rt[j]=tmp;
            }
        }
    }
    front=0; rear=0; queue[rear]=0;
    time = p[0].at;
    while(completed<n){
        int idx = (front<=rear)? queue[front++]:-1;
        if(idx==-1){ time++; continue; }
        if(rt[idx]>tq){
            time+=tq;
            rt[idx]-=tq;
        } else {
            time+=rt[idx];
            rt[idx]=0;
            p[idx].ct=time;
            p[idx].tat=p[idx].ct-p[idx].at;
            p[idx].wt=p[idx].tat-p[idx].bt;
            completed++;
        }
        for(int i=0;i<n;i++){
            if(p[i].at<=time && rt[i]>0){
                int already=0;
                for(int j=front;j<=rear;j++){
                    if(queue[j]==i){ already=1; break; }
                }
                if(!already && i!=idx) queue[++rear]=i;
            }
        }
        if(rt[idx]>0) queue[++rear]=idx;
        if(front>rear){
            for(int i=0;i<n;i++){
                if(rt[i]>0){
                    front=0; rear=0; queue[rear]=i;
                    time = (time<p[i].at)?p[i].at:time;
                    break;
                }
            }
        }
    }
    print_table(p,n);
}
int main(){
    struct process p[Max];
    int i,n,ch;
    printf("Ahmad Lucky Gold\n");
    printf("Enter number of processes:");
    scanf("%d",&n);
    for(i=0;i<n;i++){
        p[i].pid=i+1;
        printf("Enter AT%d:",i+1);
        scanf("%d",&p[i].at);
        printf("Enter BT%d:",i+1);
        scanf("%d",&p[i].bt);
        p[i].pr=0;
    }
    printf("\nChoose Algorithm\n");
    printf("1.FCFS\t2.SJF\t3.SRTF\t4.Priority(non premptive)\t5.Priority(premptive)\t6.Round Robin\n");
    scanf("%d",&ch);
    if(ch==1) fcfs(p,n);
    else if(ch==2)
        sjf(p,n);
    else if(ch==3)
        srtf(p,n);
    else if(ch==4)
        priority_np(p,n);
    else if(ch==5)
        priority_p(p,n);
    else if(ch==6)
        round_robin(p,n);
    else printf("Invalid Input");
    return 0;
}

