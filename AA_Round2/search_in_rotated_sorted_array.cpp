#include<bits/stdc++.h>
using namespace std;

//My solution, its very brittle and seems like i was fixing bugs one by one instead of handling it right from the get go
//Gemini's explanation of my approach
//Why is it "Messy"?
//Violation of DRY (Don't Repeat Yourself): 
//   You have written the binary search logic (while(l<=r)) three separate times. If you wanted to change how mid is calculated (e.g., to avoid overflow), you would have to fix it in three places.
//  "Patching" Logic: The line inflexionPoint = min(...) ? l : ... and the complex if condition (target>=nums[0] && ...) suggest you were finding bugs and "patching" them with specific fixes rather than designing a flow that naturally handles those cases.
//  Hard-to-Read Control Flow: A reader has to keep track of state across three different large blocks. The break inside the first loop is also a "code smell" in this specific context—it implies the loop condition itself wasn't descriptive enough.
//Level Assessment: Junior / Entry Level
//  Strengths: You clearly understand the mechanics of pointers (l, r, mid) and the concept of time complexity ($O(\log N)$). You correctly identified the strategy (find pivot -> search subarray).
//  Weaknesses: The implementation struggles with abstraction. A Senior engineer focuses on reducing "surface area for bugs." By writing the loop 3 times and having complex entry conditions, you created a massive surface area where off-by-one errors can hide.

//The "Senior" Solution: 
//  One-Pass Binary Search- Senior code is often characterized by invariant checking. Instead of finding the pivot first, we use the property that at least one half of the array is always sorted.
//  We check: "Is the left half sorted?"Yes: Is the target in that sorted range? If so, go left. If not, go right.No: Then the right half must be sorted. Is the target in that sorted range?
//  This handles the rotation implicitly without ever needing to find the inflection point explicitly.

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int inflexionPoint = n-1;

        int l = 0, r = n-1;
        while(l<=r) {
            int mid = (l+r)/2;
            if(nums[mid] < nums[l]) {
                r = mid-1;
                inflexionPoint = mid;
            }
            else if(nums[r] < nums[mid]) {
                l = mid+1;
                inflexionPoint = mid;
            }
            else {
                inflexionPoint = min(nums[inflexionPoint], nums[l]) == nums[l] ? l : inflexionPoint;
                break;
            }
        }

        if(target>=nums[0] && inflexionPoint!=0 && target<=nums[inflexionPoint-1]) {
            l = 0, r = inflexionPoint-1;
            while(l<=r) {
                int mid = (l+r) / 2;
                if(target < nums[mid])
                    r = mid-1;
                else if(target > nums[mid])
                    l = mid+1;
                else return mid;
            }
        }
        else {
            l = inflexionPoint, r = n-1;
            while(l<=r) {
                int mid = (l+r) / 2;
                if(target < nums[mid])
                    r = mid-1;
                else if(target > nums[mid])
                    l = mid+1;
                else return mid;
            }
        }
        return -1;
    }
};

//Proper senior solution:
class Solution2 {
public:
    int search(vector<int>& nums, int target) {
        int n =nums.size();
        int l = 0, r = n-1;
        while(l <= r) {
            int mid = (l+r) / 2;
            if(nums[mid] == target) return mid;
            if(nums[l] <= nums[mid]) { //if left array is sorted
                if(nums[l]<=target && target<=nums[mid])    //if target in sorted left array
                    r = mid-1; // continue searching in sorted left array
                else l = mid + 1; // else continue searching in right array (sorted or not - check in next iteration)
            }
            else { // else right array is sorted
                if(nums[mid]<=target && target<=nums[r]) //if target in sorted right array
                    l = mid+1;  // continue searching in sorted right array
                else r = mid-1; // else continue searching in left array
            }
        }
        return -1;
    }
};