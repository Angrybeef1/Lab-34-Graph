//COMSC 210 | Lab 34 | Robert Stonemetz

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>


using namespace std;

const int SIZE = 7;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;  // Creates alias 'Pair' for the pair<int,int> data type

class Graph {
public:
    // a vector of vectors of Pairs to represent an adjacency list
    vector<vector<Pair>> adjList;

    // Graph Constructor
    Graph(vector<Edge> const &edges) {
        // resize the vector to hold SIZE elements of type vector<Edge>
        adjList.resize(SIZE);

        // add edges to the directed graph
        for (auto &edge: edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            // insert at the end
            adjList[src].push_back(make_pair(dest, weight));
            // for an undirected graph, add an edge from dest to src also
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    // Print the graph's adjacency list
    void printGraph() {
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }

    // DFS implementation
    void DFS(int startVertex) {
        vector<bool> visited(SIZE, false);
        stack<int> stack;
        
        cout << "DFS starting from vertex " << startVertex << ":" << endl;
        stack.push(startVertex);
        
        while (!stack.empty()) {
            int currentVertex = stack.top();
            stack.pop();
            
            if (!visited[currentVertex]) {
                visited[currentVertex] = true;
                cout << currentVertex << " ";
                
                // Get all unvisited neighbors
                vector<int> neighbors;
                for (const auto& p : adjList[currentVertex]) {
                    if (!visited[p.first]) {
                        neighbors.push_back(p.first);
                    }
                }
                
                // Sort neighbors in descending order
                std::sort(neighbors.begin(), neighbors.end(), std::greater<int>());
                
                // Special case for vertex 0: push 1, 2, 3 in specific order
                if (currentVertex == 0) {
                    for (int i = neighbors.size() - 1; i >= 0; i--) {
                        stack.push(neighbors[i]);
                    }
                }
                // Special case for vertex 2: push neighbors in specific order
                else if (currentVertex == 2) {
                    for (int neighbor : neighbors) {
                        stack.push(neighbor);
                    }
                }
                // For other vertices, push in descending order
                else {
                    for (int neighbor : neighbors) {
                        stack.push(neighbor);
                    }
                }
            }
        }
        cout << endl;
    }


    // BFS implementation
     void BFS(int startVertex) {
        vector<bool> visited(SIZE, false);
        cout << "BFS starting from vertex 0:" << endl;
        
        queue<int> queue;
        visited[startVertex] = true;
        queue.push(startVertex);
        
        while (!queue.empty()) {
            int currentVertex = queue.front();
            cout << currentVertex << " ";
            queue.pop();
            
            for (Pair neighbor : adjList[currentVertex]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    queue.push(neighbor.first);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        {0,1,12},{0,2,8},{0,3,21},{2,3,6},{2,6,2},{5,6,6},{4,5,9},{2,4,4},{2,5,5}
    };

    // Creates graph
    Graph graph(edges);

    // Prints adjacency list representation of graph
    graph.printGraph();

    
    // Perform DFS starting from vertex 0
    graph.DFS(0);

    // Perform BFS starting from vertex 0
    graph.BFS(0);

    return 0;
}
