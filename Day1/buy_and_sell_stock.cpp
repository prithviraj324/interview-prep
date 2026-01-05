#include<bits/stdc++.h>
using namespace std;
//2 ptrs, one is at end(right ptr) and the other is end-1(left ptr)
//keep decrementing leftptr till u reach beginning of array
//pricemax stores value of max price thus far seen in subarray [l,r]
//at each step, calculate (leftptr - pricemax), ie buy at day leftptr and sell at day pricemax for max profit
//update maxprofit and pricemax accordingly
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int maxprofit=0, pricemax=*(prices.rbegin()), pnew=-1;
        for(auto i=prices.rbegin()+1; i!=prices.rend(); i++) {
            pnew = pricemax - (*i);
            if(pnew >= maxprofit)
                maxprofit = pnew;
            if(pricemax < *i)
                pricemax = *i;
        }
        return maxprofit;
    }
};

//Direct dp soln (just remember minprice so far and calculate maxprofit at each step)
//This is Kadane's algorithm apparently
class Solution2 {
public:
    int maxProfit(vector<int>& prices) {
        int lowest_prev_price = prices[0], res = 0;
        for(int i=0; i<prices.size(); i++) {
            res = max(res, prices[i]-lowest_prev_price);
            lowest_prev_price = min(lowest_prev_price, prices[i]);
        }
        return res;
    }
};

//Some cringe sliding window soln:
//Let i hunt for local minima, j hunt for local maxima once i is found, calculate profit and update res
//glorified linear scan
class Solutione {
public:
    int maxProfit(vector<int>& prices) {
        int res = 0;

        int i=0, j=1;
        while(i<prices.size() && j<prices.size()) {
            if(prices[j] < prices[i]) {
                i=j;
                j++;
                continue;
            }
            res = max(res, prices[j] - prices[i]);
            j++;
        }
        return res;
    }
};