#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

class Graph
{
    int V;                       // Number of vertices
    vector<vector<int>> adj;     // Adjacency list

public:
    Graph(int V)
    {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v)    // Function to add an edge to the graph
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void sequentialBFS(int source)    // Sequential Breadth First Search
    {
        vector<bool> visited(adj.size(), false);
        queue<int> q;
        visited[source] = true;
        q.push(source);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            cout << u << " ";
            for (int i = 0; i < adj[u].size(); ++i)
            {
                int v = adj[u][i];
                if (!visited[v])
                {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }

    void sequentialDFSUtil(int v, vector<bool> &visited)    // Sequential Depth First Search
    {
        visited[v] = true;
        cout << v << " ";
        for (int i = 0; i < adj[v].size(); ++i)
        {
            int u = adj[v][i];
            if (!visited[u])
            {
                sequentialDFSUtil(u, visited);
            }
        }
    }

    void sequentialDFS(int source)
    {
        vector<bool> visited(V, false);
        sequentialDFSUtil(source, visited);
    }

    void parallelBFS(int source)       // Parallel Breadth First Search
    {
       vector<bool> visited(adj.size(), false);
        queue<int> q;
        visited[source] = true;
        q.push(source);
        while (!q.empty())
        {
            int u;
            #pragma omp parallel shared(q, visited)
            {
#                pragma omp single
                {
                    u = q.front();
                    q.pop();
                    cout << u << " ";
                }
                if (!(adj[u].size() == 0))
                {
                    #pragma omp for
                    for (int i = 0; i <= adj[u].size() - 1; ++i)
                    {
                        if (!visited[adj[u][i]])
                        {
                            #pragma omp critical
                            {
                                q.push(adj[u][i]);
                                visited[adj[u][i]] = true;
                            }
                        }
                    }
                }
            }
        }
    }
    
    void parallelDFSUtil(int v, vector<bool> &visited)    // Parallel Depth First Search
    {
        visited[v] = true;
        cout << v << " ";

        #pragma omp parallel for            // Traverse all adjacent vertices
        for (int i = 0; i < adj[v].size(); ++i)
        {
            int u = adj[v][i];
            if (!visited[u])
            {
                parallelDFSUtil(u, visited);
            }
        }
    }

    void parallelDFS(int source)
    {
        vector<bool> visited(V, false);
        parallelDFSUtil(source, visited);
    }
};

int main()
{
    omp_set_num_threads(4);  
    int num_vertices, num_edges, source;
    cout << "Enter the number of vertices in the graph: ";
    cin >> num_vertices;
    Graph g(num_vertices);

    cout << "Enter the number of edges in the graph: ";
    cin >> num_edges;

    cout << "Enter the edges (u v): " << endl;
    for (int i = 0; i < num_edges; ++i)
    {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    cout << "Enter the starting vertex for BFS and DFS: ";
    cin >> source;

    cout << "\nNumber of threads : " << omp_get_max_threads() << endl << endl;

    // Sequential BFS
    double start = omp_get_wtime();  
    cout << "Sequential Breadth First Search (BFS) starting from vertex " << source << ": ";
    g.sequentialBFS(source);
    cout << endl;
    double stop = omp_get_wtime();   
    
    double duration = stop - start;  
    cout << "Time taken by sequential BFS: " << duration * 1e6 << " microseconds" << endl << endl;;  
    

    // Sequential DFS
    start = omp_get_wtime();
    cout << "Sequential Depth First Search (DFS) starting from vertex " << source << ": ";
    g.sequentialDFS(source);
    cout << endl;
    stop = omp_get_wtime();
    duration = stop - start;
    cout << "Time taken by sequential DFS: " << duration * 1e6 << " microseconds" << endl << endl;;

    // Parallel BFS
    start = omp_get_wtime();
    cout << "Parallel Breadth First Search (BFS) starting from vertex " << source << ": ";
    g.parallelBFS(source);
    cout << endl;
    stop = omp_get_wtime();
    duration = stop - start;
    cout << "Time taken by parallel BFS: " << duration * 1e6 << " microseconds" << endl << endl;

    // Parallel DFS
    start = omp_get_wtime();
    cout << "Parallel Depth First Search (DFS) starting from vertex " << source << ": ";
    g.parallelDFS(source);
    cout << endl;
    stop = omp_get_wtime();
    duration = stop - start;
    cout << "Time taken by parallel DFS: " << duration * 1e6 << " microseconds" << endl << endl;

    return 0;
}