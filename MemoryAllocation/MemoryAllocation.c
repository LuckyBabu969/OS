#include <stdio.h>

void firstFit(int blocks[], int m, int processes[], int n)
{
    int allocated[10] = {0};

    printf("\nFirst Fit:\n");
    printf("Process No\tProcess Size\tBlock No\tBlock Size\n");

    for(int i = 0; i < n; i++)
    {
        int flag = 0;

        for(int j = 0; j < m; j++)
        {
            if(allocated[j] == 0 && blocks[j] >= processes[i])
            {
                printf("%d\t\t%d\t\t%d\t\t%d\n",
                       i + 1, processes[i], j + 1, blocks[j]);

                allocated[j] = 1;
                flag = 1;
                break;
            }
        }

        if(flag == 0)
        {
            printf("%d\t\t%d\t\tNot Allocated\n",
                   i + 1, processes[i]);
        }
    }
}

void bestFit(int blocks[], int m, int processes[], int n)
{
    int allocated[10] = {0};

    printf("\nBest Fit:\n");
    printf("Process No\tProcess Size\tBlock No\tBlock Size\n");

    for(int i = 0; i < n; i++)
    {
        int best = -1;

        for(int j = 0; j < m; j++)
        {
            if(allocated[j] == 0 && blocks[j] >= processes[i])
            {
                if(best == -1 || blocks[j] < blocks[best])
                {
                    best = j;
                }
            }
        }

        if(best != -1)
        {
            printf("%d\t\t%d\t\t%d\t\t%d\n",
                   i + 1, processes[i], best + 1, blocks[best]);

            allocated[best] = 1;
        }
        else
        {
            printf("%d\t\t%d\t\tNot Allocated\n",
                   i + 1, processes[i]);
        }
    }
}

void worstFit(int blocks[], int m, int processes[], int n)
{
    int allocated[10] = {0};

    printf("\nWorst Fit:\n");
    printf("Process No\tProcess Size\tBlock No\tBlock Size\n");

    for(int i = 0; i < n; i++)
    {
        int worst = -1;

        for(int j = 0; j < m; j++)
        {
            if(allocated[j] == 0 && blocks[j] >= processes[i])
            {
                if(worst == -1 || blocks[j] > blocks[worst])
                {
                    worst = j;
                }
            }
        }

        if(worst != -1)
        {
            printf("%d\t\t%d\t\t%d\t\t%d\n",
                   i + 1, processes[i], worst + 1, blocks[worst]);

            allocated[worst] = 1;
        }
        else
        {
            printf("%d\t\t%d\t\tNot Allocated\n",
                   i + 1, processes[i]);
        }
    }
}

int main()
{
    printf("Ahmad Lucky Gold\n");
    int blocks[10], processes[10];
    int m, n;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);

    printf("Enter sizes of %d memory blocks:\n", m);
    for(int i = 0; i < m; i++)
    {
        scanf("%d", &blocks[i]);
    }

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter sizes of %d processes:\n", n);
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &processes[i]);
    }

    firstFit(blocks, m, processes, n);
    bestFit(blocks, m, processes, n);
    worstFit(blocks, m, processes, n);

    return 0;
}