class Solution {
public:
    int maxFrequencyElements(vector<int>& nums) {
        vector<int> ans;
        sort(nums.begin(),nums.end());
        int j=1;
        int count=1;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i - 1]) {
                count++;
            } else {
                ans.push_back(count);
                count = 1;
            }
        }
        ans.push_back(count);
        sort(ans.begin(),ans.end());
        int temp=ans[ans.size()-1];
        int sum=temp;
        for(int k=0;k<(ans.size()-1);k++){
            if(ans[k]==temp){
                sum=sum+ans[k];
            }
        }
            
    return sum;
    }
    
};
// class Solution {
// public:
//     int maxFrequencyElements(vector<int>& nums) {
//         vector<int> ans;
//         sort(nums.begin(), nums.end());
//         int count = 1;
//         for (int i = 1; i < nums.size(); i++) {
//             if (nums[i] == nums[i - 1]) {
//                 count++;
//             } else {
//                 ans.push_back(count);
//                 count = 1;
//             }
//         }
//         ans.push_back(count); // Add the count for the last element
//         sort(ans.begin(), ans.end(), greater<int>()); // Sort in descending order
//         int sum = ans[0]; // Initialize sum with the frequency of the most frequent element
//         for (int k = 1; k < ans.size(); k++) {
//             if (ans[k] == ans[0]) {
//                 sum += ans[k];
//             } else {
//                 break; // No need to continue if we find a frequency smaller than the maximum
//             }
//         }
//         return sum;
//     }
// };