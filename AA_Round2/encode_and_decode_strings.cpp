#include<bits/stdc++.h>
using namespace std;
class Solution {
public:

    string encode(vector<string>& strs) {
        string res;
        for(string s: strs) 
            res += to_string(s.size()) + "#" + s; 
        return res;
    }

    vector<string> decode(string s) {
        vector<string> soln;
        int i = 0, j = 0;
        while(i < s.length()) {
            j=i;
            while(j < s.length() && s[j] != '#')
                j++;
            string len_str = s.substr(i, j-i);
            int len = stoi(len_str); // found the length of current string
            i = j + 1;  // move i to first char of string
            if(len == 0) {
                soln.push_back(""); // push empty string and continue parsing
                j++;
                continue;
            }
            soln.push_back(s.substr(i, len));
            i += len;

        }

        return soln;
    }
};