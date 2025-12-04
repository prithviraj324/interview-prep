#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        //neetcode's soln
        int n=nums.size();
        vector<int> ans(n,1);
        for(int i=1;i<n;i++)
            ans[i]=ans[i-1]*nums[i-1];
        int suffix=1;
        for(int j=n-2;j>=0;j--) {
            suffix*=nums[j+1];
            ans[j]*=suffix;
        }
        
        return ans;
    }
};

//Own Soln -- O(n) time and O(2n) space

class Solution2 {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> soln(n);

        //creating a left and right subarray
        //left_prod[i] = product of all elements left of i (exclusing i'th element), same with right
        vector<int> left_prod(n), right_prod(n);
        left_prod[0] = 1, right_prod[n-1] = 1;
        for(int i=1; i<n; i++) {
            left_prod[i] = left_prod[i-1] * nums [i-1];
            right_prod[n-i-1] = right_prod[n-i] * nums[n-i];
        }

        for(int i=0; i<n; i++) {
            if(i == 0)
                soln[i] = right_prod[i];
            else if(i == n-1)
                soln[i] = left_prod[i];
            else
                soln[i] = left_prod[i] * right_prod[i];
        }

        return soln;
    }
};

// Neetcode's soln is better as it uses O(1) space and O(n) time (excluding the output array)
// Prefix and postfix product subarray values just need to contain product of all values to the left and right respectively,
// Hence modifying the result vector inplace instead 
class Solution3 {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, 1);

        for (int i = 1; i < n; i++) {
            res[i] = res[i - 1] * nums[i - 1];
        }

        int postfix = 1;
        for (int i = n - 1; i >= 0; i--) {
            res[i] *= postfix;
            postfix *= nums[i];
        }
        return res;
    }
};