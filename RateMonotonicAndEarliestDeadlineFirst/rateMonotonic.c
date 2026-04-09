#include <stdio.h>
#include <math.h>
struct Process{
    int pid;
    int burst;
    int period;
    int remaining_burst;
};
int gcd(int a,int b){
    if (b==0)return a;
    return gcd(b,a%b);
}
int lcm(int a,int b) {
    return(a*b)/gcd(a,b);
}
int main(){
    int n;
    printf("Ahmad Lucky Gold\n");
    printf("Enter the number of processes:");
    scanf("%d",&n);
    struct Process p[10];
    printf("Enter the CPU burst times:\n");
    for(int i=0;i<n;i++){
        scanf("%d",&p[i].burst);
        p[i].pid=i+1;
    }
    printf("Enter the time periods:\n");
    int hyperperiod=1;
    double utilization=0;
    for(int i=0;i<n;i++){
        scanf("%d",&p[i].period);
        p[i].remaining_burst=0;
        hyperperiod=lcm(hyperperiod, p[i].period);
        utilization+=(double)p[i].burst/p[i].period;
    }
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(p[i].period>p[j].period){
                struct Process temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
    }
    printf("LCM=%d\n",hyperperiod);
    printf("Rate Monotone Scheduling:\n");
    printf("PID\tBurst\tPeriod\n");
    for(int i = 0; i < n; i++){
        printf("%d\t%d\t%d\n",p[i].pid,p[i].burst,p[i].period);
    }
    double bound=n*(pow(2.0,1.0/n)-1.0);
    printf("%f<=%f->%s\n",utilization,bound,(utilization<=bound)?"true":"false");
    if(utilization<=1)
        printf("schedulable\n");
    printf("Scheduling occurs for %d ms\n",hyperperiod);
    int current_process=-1;
    for(int time=0;time<hyperperiod;time++){
        for(int i=0;i<n;i++){
            if(time%p[i].period==0){
                p[i].remaining_burst=p[i].burst;
            }
        }
        int next_process=-1;
        for(int i=0;i<n;i++){
            if(p[i].remaining_burst>0){
                next_process=i;
                break;
            }
        }
        if(next_process!=current_process){
            if(next_process==-1) {
                printf("%dms onwards: CPU is idle\n",time);
            } else{
                printf("%dms onwards: Process %d running\n",time,p[next_process].pid);
            }
            current_process=next_process;
        }
        if(current_process!=-1){
            p[current_process].remaining_burst--;
        }
    }
    return 0;
}