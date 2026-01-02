#include<bits/stdc++.h>
using namespace std;

class TimeMap {
public:
    struct Entry {
        int ts;
        string val;
    };
    unordered_map<string, vector<Entry>> ds;
    TimeMap() {
    }
    
    void set(string key, string value, int timestamp) {
        if (ds.find(key) == ds.end()) {
            ds[key].reserve(2e5); //reserving a capacity in order to avoid reallocation due to vec size increase
        }
        ds[key].push_back({timestamp, value});
    }
    
    string get(string key, int timestamp) {
        string res = "";
        if(ds.find(key) == ds.end()) return res;

        //umap.find() returns an iterator to that pair<> in the map
        //so in order to access the vector<Entry> part, we use it->second
        //using arrow operator since iterator is stl's pointer, gotta deref_ it
        //it->second === (*it).second;

        //storing the iterator as a const type& so copy by value doesnt happen
        //we can perform all ops on a vector<T>& vec (similar to a vector<T> v) since 
        //           'vec' is an alias to the actual vector inside of that iterator
        //using a const type& reference variable since its a get function (gotta be idempotent)
        const vector<Entry>& v = ds.find(key)->second;

        int l = 0, r = v.size()-1;
        //Explaining how binary search is used for CP
        //Instead of finding an exact point inside of the search space,
        //      you look for a boundary in the searchSpace where something stops holding true
        /*
        You aren't just looking for an exact match; you are looking for the best valid candidate.
        Think of it this way: Every time your mid points to a timestamp that is less than or equal to t, that element is a "candidate." It might be the answer, or there might be something even closer to t further to the right.
        Here is the logic to get over that wall:
            -Instead of stopping when you don't find exact match, use res to keep track of  most recent "good" value you've seen.
                -If vec[mid].timestamp <= t:This is good! Save this value to res.
                    -But could there be a larger timestamp that is still < t?
                    -Move right: l = mid + 1.If vec[mid].timestamp > t:This is too large. We can't use this.Move left: r = mid - 1.
                -If vec[mid].timestamp > t:
                    -This is too large. We can't use this.
                    -Move left: r = mid - 1.
        */
        while(l<=r) {
            int mid = l + (r-l) / 2; //avoids int overflow
            if(v[mid].ts == timestamp) return v[mid].val;
            if(v[mid].ts < timestamp) {
                l = mid+1;
                res = v[mid].val;
            }
            else r = mid-1;
        }

        return res;
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */