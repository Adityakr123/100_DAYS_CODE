#include<iostream>
using namespace std;
int main(){
    int *arr = new int[5];
    for(int i=0;i<5;i++){
        arr[i]=i;
    }
    *(arr++);
    cout<<*arr;
    delete [] arr;
    return 0;
}