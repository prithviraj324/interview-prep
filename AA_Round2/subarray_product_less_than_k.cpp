#include<bits/stdc++.h>
using namespace std;
//Brute force is n^2
//Optimal is sliding window approach, move right every iteration if product_so_far < k, else move left pointer and divide product_so_far by nums[left]
//Trick is figuring out how many contiguous subarrays end with nums[j] given current window [i, j] -- ANS: (j - i + 1)
//My own implementation 
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int res=0;

        int i=0, j = i+1;
        long curr_prod = nums[i];
        if(curr_prod < k) res++;
        while(j<nums.size() && i<nums.size()) {
            if(i>=j) {
                curr_prod = 1;
                j = i;
            }
            if(curr_prod*nums[j] < k) {
                curr_prod *= nums[j];
                res += j-i+1;
                j++;
            } else {
                curr_prod /= nums[i];
                i++;
            }
        }

        return res;
    }
};

//Much simpler, straightforward implementation
class Solution2 {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {

        int res = 0;
        long curr_prod = 1;
        int i = 0;

        // 1. Always expand j (Outer Loop)
        for (int j = 0; j < nums.size(); j++) {
            curr_prod *= nums[j];

            // 2. Shrink i while invalid (Inner Loop)
            // If adding nums[j] made us >= k, remove from left until valid again
            while (curr_prod >= k && i <= j) {
                curr_prod /= nums[i];
                i++;
            }

            // 3. Count
            // The number of valid subarrays ending at 'j' is exactly the window size.
            // e.g., if window is [5, 2] (valid), subarrays ending at 2 are [5, 2] and [2].
            res += (j - i + 1);
        }

        return res;
    }
};