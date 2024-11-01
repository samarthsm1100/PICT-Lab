#include <bits/stdc++.h>
using namespace std;

int solve(vector<int> &weight, vector<int> &value, int index, int capacity, vector<vector<int>> &dp){
    if(index == 0){
        if(weight[index] <= capacity){
            return value[index];
        }
        else{
            return 0;
        }
    }

    if(dp[index][capacity] != -1){
        return dp[index][capacity];
    }

    int include = 0, exclude = 0;
    if(weight[index] <= capacity){
        include = value[index] + solve(weight, value, index-1, capacity-weight[index], dp);
    }
    exclude = solve(weight, value, index-1, capacity, dp);

    return dp[index][capacity] = max(include, exclude);
}

int main(){
    vector<int>weight = {3, 4, 6, 5};
    vector<int>value = {2, 3, 1, 4};
    int capacity = 8;
    vector<vector<int>> dp(weight.size(), vector<int>(capacity+1, -1));
    cout << "Maximum value: " << solve(weight, value, weight.size()-1, capacity, dp) << endl;
}