#include<stdio.h>
int main(){
int n,i;
printf("enter no of elemts:");
scanf("%d",&n);
int a[n];
for(i=0;i<n;i++){
    scanf("%d",&a[i]);
}
int key;
int found=0;
printf("\nenter the element to search:");
scanf("%d",&key);
printf("\nusing linear search");
for(i=0;i<n;i++){
    if(a[i]==key){
        printf("\nfound at index %d",i);
        found=1;
        break;
    }
}
if(found==0){
    printf("\nnot found");
}
printf("\nusing binary search");
int l=0,h=n-1,m=(h+l)/2;
while(l<=m && h>=m){
    if(a[m]==key){
        printf("\nfound at index %d",m);
        found=1;
        break;
    }
    else if(a[m]<key){
        l=m+1;
        m=(h+l)/2;
    }
    else {
        h=m-1;
        m=(h+l)/2;
    }
}
if(found==0){
    printf("\nnot found");
}
return 0;
}
