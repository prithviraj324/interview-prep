//REVISE MONOTONIC STACK
#include<bits/stdc++.h>
using namespace std;
//My Solution - same as daily temperature, monotonic stack and calculate next greater element for each element in nums2
//Overdid calculations but couldnt find how to minimise them
//TC - O(nm) due to finding index of each nums1 element in nums2
//SC - O(n) for stack and res array
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        vector<int> res(nums2.size(), -1);
        vector<int> ans(nums1.size(), -1);
        stack<int> st;

        for(int x = 0; x<nums2.size(); x++) {
            while(!st.empty() && nums2[x] > nums2[st.top()]) {
                res[st.top()] = nums2[x];
                st.pop();
            }
            st.push(x);
        }

        for(int i = 0; i<nums1.size(); i++) {
            for(int j = 0; j<nums2.size(); j++) {
                if(nums1[i] == nums2[j])
                    ans[i] = res[j];
            }
        }
        return ans;
    }
};

//Acutal proper solution
class Solution2 {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> next;
        stack<int> s;

        for (int i = nums2.size() - 1; i >= 0; --i) {
            while (!s.empty() && s.top() <= nums2[i]) {
                s.pop();
            }
            next[nums2[i]] = s.empty() ? -1 : s.top();  //calculates for each element in nums2 too
            s.push(nums2[i]);
        }

        vector<int> res;
        for (int num : nums1) {
            res.push_back(next[num]);   //but only pushing back required elements into res array
        }
        return res;
    }
};