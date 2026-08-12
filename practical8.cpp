#include <iostream>
#include <vector>
#include <queue>
#include <chrono>

using namespace std;
using namespace chrono;

class Graph
{
private:
    int vertices;
    vector<vector<int>> graph;

public:
    Graph(int n)
    {
        vertices = n;
        graph.resize(n);
    }

    void insertEdge(int a, int b)
    {
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    void performDFS(int current, vector<bool>& marked)
    {
        marked[current] = true;
        cout << current << " ";

        for (int next : graph[current])
        {
            if (!marked[next])
            {
                performDFS(next, marked);
            }
        }
    }

    void runDFS(int source)
    {
        vector<bool> marked(vertices, false);
        performDFS(source, marked);
    }

    void runBFS(int source)
    {
        vector<bool> marked(vertices, false);
        queue<int> nodes;

        marked[source] = true;
        nodes.push(source);

        while (!nodes.empty())
        {
            int current = nodes.front();
            nodes.pop();

            cout << current << " ";

            for (int next : graph[current])
            {
                if (!marked[next])
                {
                    marked[next] = true;
                    nodes.push(next);
                }
            }
        }
    }
};

int main()
{
    int vertices, edges;

    cout << "Enter number of vertices: ";
    cin >> vertices;

    Graph g(vertices);

    cout << "Enter number of edges: ";
    cin >> edges;

    cout << "Enter edges (u v): ";

    for (int i = 0; i < edges; ++i)
    {
        int from, to;
        cin >> from >> to;

        g.insertEdge(from, to);
    }

    int source;
    cout << "Enter starting vertex: ";
    cin >> source;

    // DFS timing
    auto dfsBegin = high_resolution_clock::now();

    cout << "\nDFS Traversal: ";
    g.runDFS(source);

    auto dfsEnd = high_resolution_clock::now();

    auto dfsDuration =
        duration_cast<nanoseconds>(dfsEnd - dfsBegin);

    // BFS timing
    auto bfsBegin = high_resolution_clock::now();

    cout << "\nBFS Traversal: ";
    g.runBFS(source);

    auto bfsEnd = high_resolution_clock::now();

    auto bfsDuration =
        duration_cast<nanoseconds>(bfsEnd - bfsBegin);

    cout << "\n\nExecution Time:";
    cout << "\nDFS: " << dfsDuration.count() << " ns";
    cout << "\nBFS: " << bfsDuration.count() << " ns";

    return 0;
}
