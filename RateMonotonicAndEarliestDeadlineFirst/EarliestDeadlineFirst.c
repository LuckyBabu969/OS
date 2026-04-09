#include <stdio.h>
struct Process {
    int pid;
    int burst;
    int deadline;
    int period;
    int remaining_burst;
    int absolute_deadline;
};
int gcd(int a,int b){
    if(b==0) return a;
    return gcd(b,a%b);
}
int lcm(int a,int b){
    return(a*b)/gcd(a,b);
}
int main(){
    int n;
    double utilization=0;
    printf("Ahmad Lucky Gold\n");
    printf("Enter the number of processes:");
    scanf("%d",&n);
    struct Process p[10];
    int hyperperiod = 1;
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Process %d - Enter Burst, Deadline, Period: ", p[i].pid);
        scanf("%d %d %d", &p[i].burst, &p[i].deadline, &p[i].period);
        p[i].remaining_burst = 0;
        hyperperiod = lcm(hyperperiod, p[i].period);
        utilization+=(double)p[i].burst/p[i].period;
    }
    printf("\nPID\tBurst\tDeadline\tPeriod\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t\t%d\n", p[i].pid, p[i].burst, p[i].deadline, p[i].period);
    }
    if(utilization<=1)
        printf("schedulable\n");
    printf("Scheduling occurs for %d ms\n", hyperperiod);
    for (int time = 0; time < hyperperiod; time++) {
        for (int i = 0; i < n; i++) {
            if (time % p[i].period == 0) {
                p[i].remaining_burst = p[i].burst;
                p[i].absolute_deadline = time + p[i].deadline;
            }
        }
        int min_deadline = 999999;
        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].remaining_burst > 0) {
                if (p[i].absolute_deadline < min_deadline) {
                    min_deadline = p[i].absolute_deadline;
                    selected = i;
                }
            }
        }
        if (selected == -1) {
            printf("%dms: CPU is idle.\n", time);
        } else {
            printf("%dms: Task %d is running.\n", time, p[selected].pid);
            p[selected].remaining_burst--;
        }
    }
    return 0;
}