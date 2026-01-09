//HARD
#include<bits/stdc++.h>
using namespace std;
//initial naive solution, barely makes to TC cut (top 9%)
class Solution1 {
public:
    bool mapcomp(unordered_map<char, int>& m1, unordered_map<char,int>& m2){
        for(auto p: m1)
            if(m2[p.first] < p.second) return false;
        return true;
    }

    string minWindow(string str, string t) {
        if(t.size() > str.size()) return "";
        if(t.size() == str.size() && str==t) return t;

        int minlen = INT_MAX, n = str.size();
        int start_idx=-1, end_idx=-1;
        unordered_map<char, int> smap, tmap;
        for(char c: t)
            tmap[c]++;

        int l=0, r=0;
        while(l<n && r<n) {
            smap[str[r]]++;
            if(r-l+1 >= t.size()) {
                while(l<=r && mapcomp(tmap, smap)) {
                    if(r-l+1 < minlen) {    //if smaller valid substr found
                        minlen = r-l+1; //note the lenght and start and end indices
                        start_idx = l;
                        end_idx = r;
                    }
                    //try shrinking left window to see if valid substr bcms invalid
                    smap[str[l]]--; 
                    l++;
                }
            }
            r++;
        }

        if(start_idx < 0) return "";
        return str.substr(start_idx, end_idx-start_idx+1);
    }
};

/*
    Sliding window + hash map {char -> count}
    Move j until valid, move i to find smaller
    Time: O(m + n)
    Space: O(m + n)
*/
class Solution {
public:
    string minWindow(string s, string t) {
        // count of char in t
        unordered_map<char, int> m;
        for (int i = 0; i < t.size(); i++) {
            m[t[i]]++;
        }
        
        int i = 0;
        int j = 0;
        
        // # of chars in t that must be in s
        int counter = t.size();
        
        int minStart = 0;
        int minLength = INT_MAX;
        
        while (j < s.size()) {
            // if char in s exists in t, decrease
            if (m[s[j]] > 0) {
                counter--;
            }
            // if char doesn't exist in t, will be -'ve
            m[s[j]]--;
            // move j to find valid window
            j++;
            
            // when window found, move i to find smaller
            while (counter == 0) {
                if (j - i < minLength) {
                    minStart = i;
                    minLength = j - i;
                }
                
                m[s[i]]++;
                // when char exists in t, increase
                if (m[s[i]] > 0) {
                    counter++;
                }
                i++;
            }
        }
        
        if (minLength != INT_MAX) {
            return s.substr(minStart, minLength);
        }
        return "";
    }
};

//Same soln as above, explained better
class Solution3 {
public:
    string minWindow(string s, string t) {
        int n = s.size(), minlen = INT_MAX;
        unordered_map<char, int> cmap;
        int counter = t.size(); //number of chars we need
        for(char c: t) cmap[c]++;

        int start=0, end = 0, startidx = -1;
        while(end < s.size()) {
            if(cmap[s[end]] > 0)   //if this char was needed
                counter--; //one less REQUIRED_CHAR needed
             
            cmap[s[end]]--; //decrement charNeeded count
            end++;

            while(counter == 0) {   //if no more chars needed, window is valid, try shrinking to find smaller
                if(end-start < minlen) {  //since we moved 'end' already
                    minlen = end-start;
                    startidx = start;
                }

                //now, to move left wall ->
                // We are about to remove s[start]. 
                // If cmap[s[start]] == 0, it means this char was exactly necessary.
                // (It wasn't negative/extra). So we are losing a needed char.
                if (cmap[s[start]] == 0) {
                    counter++;
                }
                
                // Add it back to the map (make it "wanted" again) (see first line of loop)
                cmap[s[start]]++;
                start++;
            }
        }

        return minlen == INT_MAX ? "" : s.substr(startidx, minlen);
    }
};