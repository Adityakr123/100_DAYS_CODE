#include<iostream>
#include <vector>
using namespace std;
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> vect;
        
        int count=0;
        int n = numbers.size();
        int arr[n];
        // int m=n/2;
    
        for (int i = 0; i < n; i++) {
            arr[i] = numbers[i];
        }
//         while(m<=n){
            
            // if(arr[m]>target&&arr[m]!=0){
            //     n=m;
            // }
            // m=(m+n)/2;
//         }
        for(int i=n-1;i>=1;i--){
            
            for(int j=n-2;j>=0;j--){
                if((arr[i]+arr[j])==target && i!=j ){
                    
                        vect.push_back(j);
                        vect.push_back(i);
                        
                        count++;
                        break;
                        
                        
                }
                
            }
            if(count>0){
                break;
            }
        }
    return vect;
    
    }   
    
};