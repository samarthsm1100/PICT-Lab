#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono:

class Graph{

    int V;
    vector<vector<int>> adj;

    public:

    Graph(int V){
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void sequentialBFS(int start){
        vector<bool> visited(V, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);

        while(!q.empty()){
            int front = q.front(); q.pop();
            cout << front << " ";
            for(int i=0; i<adj[front].size(); i++) 
        }
    }

}