#include <stdio.h>

int main()
{
    printf("Ahmad Lucky Gold\n");
    int n, m, i, j, k;
    int alloc[10][10], max[10][10], avail[10];
    int f[10] = {0}, ans[10], idx = 0, flag;

    printf("Enter no of processes: ");
    scanf("%d", &n);

    printf("Enter no of resources: ");
    scanf("%d", &m);

    printf("Enter allocation matrix:\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter max matrix:\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter available resources:\n");
    for(j = 0; j < m; j++)
    {
        scanf("%d", &avail[j]);
    }

    for(k = 0; k < n; k++)
    {
        for(i = 0; i < n; i++)
        {
            if(f[i] == 0)
            {
                flag = 0;

                for(j = 0; j < m; j++)
                {
                    if((max[i][j] - alloc[i][j]) > avail[j])
                    {
                        flag = 1;
                        break;
                    }
                }

                if(flag == 0)
                {
                    ans[idx++] = i;

                    for(j = 0; j < m; j++)
                    {
                        avail[j] += alloc[i][j];
                    }

                    f[i] = 1;
                }
            }
        }
    }

    if(idx == n)
    {
        printf("System is in safe state\n");
        printf("Safe sequence is: ");

        for(i = 0; i < n; i++)
        {
            printf("P%d", ans[i]);

            if(i != n - 1)
            {
                printf(" -> ");
            }
        }
    }
    else
    {
        printf("System is in unsafe state\n");
        printf("Deadlock may occur\n");
    }

    return 0;
}