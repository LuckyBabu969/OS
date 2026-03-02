#include<stdio.h>
int main(){
int n,i;
printf("enter no of elemts:");
scanf("%d",&n);
int a[n];
for(i=0;i<n;i++){
    scanf("%d",&a[i]);
}
int dup=0;
for(i=0;i<n;i++){
    for(int j=i+1;j<n;j++){
        if(a[i]==a[j]){
            dup=1;
            break;
        }
    }
    if(dup==1){
        break;
    }
}
if(dup==1){
    printf("\nduplicates are found");
}
else{
    printf("\nduplicates are not found");
}
}
