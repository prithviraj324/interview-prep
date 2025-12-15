#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int trap(vector<int>& height) {
        int n=height.size();
        int amt=0;
        vector<int> lmax(n,0), rmax(n,0);
        lmax[0]=height[0];
        *rmax.rbegin()=height[n-1];
        
        for(int i=1;i<n;i++) //calculate max height on left and right of each index in the grid
            lmax[i]=max(lmax[i-1], height[i]);
        for(int j=n-2;j>=0;j--)
            rmax[j]=max(rmax[j+1], height[j]);
        
        //amt of water stored at index i->
        //  min(lmax[i], rmax[i]) - h[i], if this is +ve, add it to amt
        // has to be positive bcz if either lmax[i] or rmax[i] is < h[i], then no water will be stored at index i
        
        for(int i=0;i<n;i++)
            if(min(lmax[i], rmax[i]) - height[i] > 0)
                amt+=min(lmax[i], rmax[i]) - height[i];

        return amt;
    }
};

//Time Complexity: O(n)
//Space Complexity: O(1)
//Since water trapped at 'i' is decided by min of max height on left and right of 'i', we can use 2 pointers to keep track of maxL and maxR while traversing the array from both ends.
//Depending on which of maxL or maxR is smaller, we can move that pointer inward and calculate water trapped at that index, since we're sure of maxL or maxR being the limiting factor.
//Assume maxL <= maxR, then water trapped at index 'l' is decided by maxL only, as there definitely exists a bar on right which is >= maxL (i.e. maxR).
//Hence water trapped at 'l' = maxL - h[l], if this is +ve, add it to amt.
class Solution {
public:
    int trap(vector<int>& height) {
        int amt = 0;
        int maxL = height[0], maxR = height.back();
        int l = 0, r = height.size()-1;
        while(l<r) {
            if(maxL <= maxR) {
                l++;
                if(maxL - height[l] < 0) { 
                    maxL = max(maxL, height[l]);
                    continue;
                }
                amt += maxL - height[l];
            } else {
                r--;
                if(maxR - height[r] < 0) {
                    maxR = max(maxR, height[r]);
                    continue;
                }
                amt += maxR - height[r];
            }
        }

        return amt;
    }
};