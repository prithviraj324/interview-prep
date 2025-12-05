#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int countPartitions(vector<int>& nums) {
        int res = 0, n = nums.size();
        // maintain prefix and postfix[i] such that prefix[i] = sum of left subarray, same with suffix[i]
        vector<int> prefix(n, 0), suffix(n, 0);
        for(int i=1; i<n; i++) {
            prefix[i] = prefix[i-1] + nums[i-1];
            suffix[n-i-1] = suffix[n-i] + nums[n-i];
        }
        for(int i=1; i<n; i++) {
            if((prefix[i]-suffix[i]+nums[i]) % 2 == 0)
                res++;
        }

        return res;
    }
};

//Much more optimised solution, O(n) time and O(1) space
class Solution2 {
public:
    int countPartitions(vector<int>& nums) {
        int n = nums.size();
        int totalSum = 0;
        for (int i : nums) totalSum += i;
        int currentSum = 0;     // Prfefix sum
        int count = 0;
        for (int i = 0; i < n - 1; i++) {
            currentSum += nums[i];
            totalSum -= nums[i];    // Suffix sum = total - all that came before
            if ((totalSum - currentSum) % 2 == 0) count++;
        }
        return count;
    }
};