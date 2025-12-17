//REVISE MONOTONIC STACK 
#include<bits/stdc++.h>
using namespace std;
//OPTIMISED SOLUTION USING STACK, BRUTE FORCE WOULD BE N^2 CHECK FOR EACH ELEMENT
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temp) {
        int n=temp.size();
        vector<int> ans(n,0);
        stack<pair<int, int>> st; //st.top (temp[i], i)
        
        st.push({temp[0],0});
        for(int i=1;i<n;i++) {    
            if(st.empty()) {    //if stack is empty, just push value in
                st.push({temp[i], i});
                continue;
            }
            
            if(temp[i] <= st.top().first) { //if next day is colder
                st.push({temp[i], i});
                continue;
            }
            
            else if(temp[i] > st.top().first) { //if next day is warmer, cascade down the stack
                while(!st.empty() && temp[i] > st.top().first) {
                    ans[st.top().second] = i - st.top().second;
                    st.pop();
                }
                st.push({temp[i], i});
            }
        }
        //st.clear();
        return ans;
    }
};
//slightly better solution that stores only index of element onto stack, actually dumb to store pair of temp[i],i
class Solution2 {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        stack<int> s;
        vector<int> ans(T.size());
        for(int cur = 0; cur < T.size(); cur++) {
            while(T.size() and T[cur] > T[s.top()]) {    // pop till current temp < stack's top's temp. This maintains monotonic stack
                ans[s.top()] = cur - s.top();           // cur day will be next warmer day for each element that's popped
                s.pop();
            }
            s.push(cur);                                // push onto stack to find next warmer day for cur later on
        }
        return ans;
    }
};
//a better solution exists with TC:O(n) and SC:O(1), but is pretty tricky
//2025 me thinks it isnt that tricky anymore, its just DP and thinking about the problem bottom-up
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temp) {
        vector<int> res(temp.size(), 0);

        // Fill the result vector backwards
        //res[j] = number of days to wait from day j to get a hotter day
        for(int i = temp.size()-1; i>=0; i--) {
            int j = i+1; // j = some day in the future, start with tomorrow first
            while(j<temp.size() && temp[j] <= temp[i]) {    //while j in bounds and tomorrow(i.e. res[j]) isnt hotter
                if(res[j] > 0) j += res[j]; // if theres a hotter day than tomorrow(i.e. res[j]), go there
                else j = temp.size();   // else go out of bounds to end loop
            }
            //We're outside loop, so j'th day is either out of bounds or this is the next hottest day
            if(j < temp.size()) res[i] = j-i;   //if not out-of-bounds, j'th day is (j-i) days from i'th day and is the first hotter day since i'th day
            //if out-of-bounds, result vec is initialized with all 0's, so its valid
        }
        return res;
    }
};
