#include<bits/stdc++.h>
using namespace std;
//TC:O(26*N), SC:O(26)
class Solution {
public:
    char maxc(unordered_map<char, int>& m) {
        int mx=-1;
        char maxchar;
        for(auto p: m) {
            if(p.second > mx) {
                maxchar = p.first;
                mx=max(mx, p.second);
            }
        }
        return maxchar;
    }
    int characterReplacement(string s, int k) {   
        int n=s.size(), len=-1;
        if(n == 1) return 1;
        int i=0, j=0;
        unordered_map<char,int> m;
        
        while(j<n) {
            m[s[j]]++;  //incrementing count of char in map
            char big=maxc(m);   //get char w most occurences in substr [i..j]
            if(j-i+1 - m[big] <= k)   //big->most occurred char, and the difference gives number of chars that need replacing
                len=max(len, j-i+1);
            else 
                m[s[i++]]--;  //shift window left ptr by 1 and deduct its char count in map
            j++;
        }
        return len;
    }
};
//better solution with no space complexity
class Solution2 {
public:
    int characterReplacement(string s, int k) {
        int n = s.size();
        int i = 0, j = 0, maxi = 0;
        unordered_map<char,int>mp;
        int ans = -1;
        while(j < n)
        {
            mp[s[j]]++;
            maxi = max(maxi, mp[s[j]]);
            if((j-i+1) - maxi > k){
                mp[s[i]]--;
                i++;
            }
            ans = max(ans, (j-i+1));
            j++;   
        }
        return ans;
    }
};
//Round2 soln using array of 26elements, much more understandable
class Solution3 {
public:
    int characterReplacement(string s, int k) {
        int n = s.size(), res = 0;
        vector<int> cmap(26, 0);

        int l=0, maxf = 0; 
        for(int r=0; r<n; r++) {
            cmap[s[r] - 'A']++; //increase freq of char in window's charmap
            maxf = max(maxf, cmap[s[r]-'A']);   //update maxfreq, we dont care which char was most frequent,
                                                //just that some char is most frequent with freq = maxf

            while((r-l+1) - maxf > k) { //if chars to replace exceed k, shrink window from left
                cmap[s[l]-'A']--;   //decrement freq of char going out of window
                l++;
            }
            res = max(res, r-l+1);  //on every valid window, update result
        }

        return res;
    }
};