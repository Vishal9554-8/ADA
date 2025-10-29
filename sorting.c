#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void merge(int arr[],int left,int mid,int right){
int i, j, k;
int n1=mid-left+1;
int n2=right-mid;
int *l=(int*)malloc(n1*sizeof(int));
int *r=(int*)malloc(n2*sizeof(int));
for(int i=0;i<n1;i++){
l[i]=arr[left+i];
}
for(int j=0;j<n2;j++){
r[j]=arr[mid+1+j];
}
k=left;
i=j=0;
while(i<n1 && j<n2){
if(l[i]<=r[j]){
arr[k]=l[i];
i++;
}

else{
arr[k]=r[j];
j++;
}
k++;
}
free(l);
free(r);
}
void merge_sort(int arr[],int left,int right){
if(left<right){
int mid=left+(right-left)/2;
merge_sort(arr,left,mid);
merge_sort(arr,mid+1,right);
merge(arr,left,mid,right);
}
}
void generaterandomnumbers(int arr[],int n){
for(int i=0;i<n;i++){
arr[i]=rand()%10000;
}
}
int main(){
int n;
printf("Enter a number: ");
scanf("%d",&n);
int *arr=(int*)malloc(n*sizeof(int));
if(arr==NULL){
return 1;
}

clock_t start=clock();
for(int i=0;i<1000;i++){
generaterandomnumbers(arr,n);
merge_sort(arr,0,n-1);
}
clock_t end=clock();
double time_taken=((double)(end-start))/CLOCKS_PER_SEC/1000.0;
printf("Time taken=%f",time_taken);
free(arr);
return 0;
}