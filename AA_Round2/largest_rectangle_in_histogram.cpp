#include<bits/stdc++.h>;
using namespace std;


class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int largest_area = 0;
        int n=heights.size();
        stack<int> st;
        //left and right_shortest[i] will hold the index till which max rectangle formed
        //using entire height of heights[i] can be extended to the left/right, including left/right_shortest[i]
        vector<int> left_shortest(n, 0), right_shortest(n, 0);
        
        st.push(0);
        left_shortest[0] = 0;
        for(int i = 1; i<n; i++) {
            if(heights[i] > heights[st.top()]) {
                st.push(i);
                left_shortest[i] = i;
            } else {
                while(!st.empty() && heights[i] <= heights[st.top()]) {
                    st.pop();
                }
                if(st.empty()) left_shortest[i] = 0;
                else left_shortest[i] = st.top()+1; //+1 bc we cant extend the rectangle with heights[i] to anything lower
                st.push(i);
            }
        }

        while(!st.empty()) st.pop();
        st.push(n-1);
        right_shortest[n-1] = n-1;
        for(int i = n-2; i>=0; i--) {
            if(heights[i] > heights[st.top()]) {
                st.push(i);
                right_shortest[i] = i;
            } else {
                while(!st.empty() && heights[i] <= heights[st.top()]) {
                    st.pop();
                }
                if(st.empty()) right_shortest[i] = n-1;
                else right_shortest[i] = st.top()-1; //-1 bc we cant extend the rectangle with heights[i] to anything lower
                st.push(i);
            }
        }

        for(int i=0; i<n; i++) {
            int width = right_shortest[i] - left_shortest[i] + 1;
            int curr_area = heights[i] * width;
            largest_area = max(largest_area, curr_area);
        }

        return largest_area;
    }
};