#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0, r = nums.size()-1;
        int res = INT_MAX;
        while(l<=r) {
            int mid = (l+r) / 2;
            res = min(res, nums[mid]);
            if(nums[l] > nums[mid]) 
                r = mid-1;
            else if(nums[mid] > nums[r])
                l = mid+1;
            else return min(res, nums[l]);
        }
        return res;
    }
};