#include <bits/stdc++.h>
using namespace std;

void addSolution(vector<vector<int>>&ans, vector<vector<int>>&board, int n){
    vector<int> temp;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            temp.push_back(board[i][j]);
        }
    }
    ans.push_back(temp); 
}

bool isSafe(int row, int col, vector<vector<int>>&board, int n){
    // check for the row
    for(int i=0; i<col; i++){
        if(board[row][i] == 1){
            return false;
        }
    }

    // check for the upper diagonal
    for(int i=row, j=col; i>=0 && j>=0; i--, j--){
        if(board[i][j] == 1){
            return false;
        }
    }

    // check for the lower diagonal
    for(int i=row, j=col; i<n && j>=0; i++, j--){
        if(board[i][j] == 1){
            return false;
        }
    }

    return true;
}

void solve(int col, vector<vector<int>>&ans, vector<vector<int>>&board, int n){
    // base case
    if(col == n){
        addSolution(ans, board, n);
        return;
    }

    for(int row=0; row<n; row++){
        if(isSafe(row, col, board, n)){
            board[row][col] = 1;
            solve(col+1, ans, board, n);
            // backtrack
            board[row][col] = 0;
        }
    }
}

void display(vector<vector<int>> &ans, int n){
    for(int i=0; i<ans.size(); i++){
        for(int j=0; j<ans[i].size(); j++){
            cout << ans[i][j] << " ";
            if((j+1)%n == 0){
                cout << endl;
            }
        }
        cout << endl;
    }
}

int main(){
    int n;
    cout << "Enter the value of n: ";
    cin >> n;
    vector<vector<int>> board(n, vector<int>(n, 0));
    vector<vector<int>> ans;
    solve(0, ans, board, n);
    cout << "Total number of solutions: " << ans.size() << endl << endl;
    display(ans, n);
    return 0;
}