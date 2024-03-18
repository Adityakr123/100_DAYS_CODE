#include<iostream>
using namespace std;
int pow2(int n){
    if(n==0){
        return 1;
    }
    int ans=2*pow2(n-1);
    return ans;
}
int main(){
    int n;
    cin>>n;
    int ans = pow2(n);
    cout<<ans;
    return 0;
}