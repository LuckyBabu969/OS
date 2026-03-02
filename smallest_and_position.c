#include<stdio.h>
int main(){
int n,i;
printf("enter no of elemts:");
scanf("%d",&n);
int a[n];
printf("\nenter elements:\n");
for(i=0;i<n;i++){
    scanf("%d",&a[i]);
}
int s=a[0];
int in=0;
for(i=0;i<n;i++){
    if(a[i]<s){
        s=a[i];
        in=i;
    }
}
printf("\nsmallest=%d",s);
printf("\nfound at index %d",in);

return 0;
}
