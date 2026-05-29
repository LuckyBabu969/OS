#include<stdio.h>
void fifo(int pages[], int n, int frames) {
    int frame[frames], faults = 0;
    for(int i=0;i<frames;i++)
        frame[i] = -1;
    int index = 0;
    printf("\nFIFO:\n");
    for(int i=0;i<n;i++) {
        int found = 0;
        for(int j=0;j<frames;j++) {
            if(frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if(found == 0) {
            frame[index] = pages[i];
            index = (index + 1) % frames;
            faults++;
        }
        printf("page %d->",pages[i]);
        for(int j=0;j<frames;j++) {
            if(frame[j] != -1)
                printf("%d ",frame[j]);
            else
                printf("- ");
        }
        printf("\n");
    }
    printf("Page Faults = %d\n",faults);
}
void lru(int pages[], int n, int frames) {
    int frame[frames], time[frames];
    int faults = 0, counter = 0;
    for(int i=0;i<frames;i++) {
        frame[i] = -1;
        time[i] = 0;
    }
    printf("\nLRU:\n");
    for(int i=0;i<n;i++) {
        int found = 0;
        for(int j=0;j<frames;j++) {
            if(frame[j] == pages[i]) {
                counter++;
                time[j] = counter;
                found = 1;
                break;
            }
        }
        if(found == 0) {
            int pos = 0;
            for(int j=1;j<frames;j++) {
                if(time[j] < time[pos])
                    pos = j;
            }
            frame[pos] = pages[i];
            counter++;
            time[pos] = counter;
            faults++;
        }
        printf("page %d->",pages[i]);
        for(int j=0;j<frames;j++) {
            if(frame[j] != -1)
                printf("%d ",frame[j]);
            else
                printf("- ");
        }
        printf("\n");
    }
    printf("Page Faults = %d\n",faults);
}

void optimal(int pages[], int n, int frames) {
    int frame[frames], faults = 0;
    for(int i=0;i<frames;i++)
        frame[i] = -1;
    printf("\nOptimal:\n");
    for(int i=0;i<n;i++) {
        int found = 0;
        for(int j=0;j<frames;j++) {
            if(frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if(found == 0) {
            int pos = -1, farthest = i + 1;
            for(int j=0;j<frames;j++) {
                int k;
                for(k=i+1;k<n;k++) {
                    if(frame[j] == pages[k]) {
                        if(k > farthest) {
                        farthest = k;
                            pos = j;
                        }
                        break;
                    }
                }
                if(k == n) {
                    pos = j;
                    break;
                }
            }
            if(pos == -1)
                pos = 0;
            frame[pos] = pages[i];
            faults++;
        }
        printf("page %d->",pages[i]);
        for(int j=0;j<frames;j++) {
            if(frame[j] != -1)
                printf("%d ",frame[j]);
            else
                printf("- ");
        }
        printf("\n");
    }
    printf("Page Faults = %d\n",faults);
}
int main() {
    printf("Ahmad Lucky Gold\n");
    int n, frames;
    printf("Enter number of pages: ");
    scanf("%d",&n);
    int pages[n];
    printf("Enter page reference string:\n");
    for(int i=0;i<n;i++)
        scanf("%d",&pages[i]);
    printf("Enter number of frames: ");
    scanf("%d",&frames);
    fifo(pages, n, frames);
    lru(pages, n, frames);
    optimal(pages, n, frames);
    return 0;
}
