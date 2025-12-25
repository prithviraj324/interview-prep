#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m=matrix.size(),n=matrix[0].size();
        
        int cl=0,cr=m-1;//column left, column right
        int cm,rm;//column middle, row middle 
        
        while (cl<=cr) {
            cout<<cl<<","<<cr<<endl;
            cm=(cl+cr)/2;
            
            if(matrix[cm][n-1]==target)
                return true;
            
            else if(matrix[cm][n-1]>target) {
                if(matrix[cm][0]<=target)
                    return binary_search(matrix[cm].begin(),matrix[cm].end(),target);
                else
                    cr=cm-1;
            }
            
            else 
                cl=cm+1;
        }
        return false;
    }
};
//----------------------------------------------------------------
//solution might look like its O(logm * logn) but its actually not because:
//there's only one case where target>col[first] AND target<col[last] hence its O(logm + logn)=O(log(mn))

//Much more intuitive soln, treat matrix as a 1D sorted array and translate mid to 2D indices
class Solution2 {
public:
    bool searchMatrix(vector<vector<int>>& mat, int target) {
        int m = mat.size(), n = mat[0].size();

        int linear_arr_idx = (m-1)*(n-1);
        //row = idx/n, col = idx%n
        int l = 0, r = m*n - 1;
        
        while(l<=r) {
            int mid = (l+r) / 2;
            int mid_r = mid/n, mid_c = mid%n;

            if(target < mat[mid_r][mid_c]) 
                r = (n*mid_r) + mid_c - 1;
            if(target > mat[mid_r][mid_c]) 
                l = (n*mid_r) + mid_c + 1;

            if(mat[mid_r][mid_c] == target)
                return true;
        }
        return false;
    }
};