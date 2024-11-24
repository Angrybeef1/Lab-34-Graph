//COMSC 210 | Lab 34 | Robert Stonemetz

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <iomanip>
#include <limits>


using namespace std;

const int SIZE = 9;
const int INF = numeric_limits<int>::max();

struct Edge {
    int src, dest, weight;

    //for edge creation
    Edge (int s, int d, int w) : src(s), dest (d),weight(w){}

    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

struct Station {
    string name;
    string type;
};

typedef pair<int, int> Pair;

class Tree {
    vector<int> parent, rank;
public:
    Tree(int n){
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; i++){
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find (int x){
        if(parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
     void unite(int x, int y) {
        int px = find(x), py = find(y);
        if(rank[px] < rank[py])
            parent[px] = py;
        else if(rank[px] > rank[py])
            parent[py] = px;
        else {
            parent[py] = px;
            rank[px]++;
        }
    }
};

class MetroNetwork {
private:
    vector<vector<Pair>> adjList;
    vector<Station> stations;
    vector<Edge> allEdges;

public:
    // Graph Constructor
    MetroNetwork(vector<Edge> const &edges, vector<Station> const &stationInfo) {
        // resize the vector to hold SIZE elements of type vector<Edge>
        adjList.resize(SIZE);
        stations = stationInfo;

        // add edges to the directed graph
        for (auto &edge: edges) {
            // insert at the end
            adjList[edge.src].push_back(make_pair(edge.dest, edge.weight));
            // for an undirected graph, add an edge from dest to src also
            adjList[edge.dest].push_back(make_pair(edge.src, edge.weight));
            allEdges.push_back(Edge(edge.src, edge.dest, edge.weight));
        }
    }

    // Print the graph's adjacency list
   void printNetwork() {
        cout << "Metro Network Topology:" << endl;
        cout << string(80, '=') << endl;
        
        for (int i = 0; i < adjList.size(); i++) {
            cout << "Station " << i << " (" << stations[i].name << " - " << stations[i].type << ") connects to:" << endl;
            for (Pair v : adjList[i]) {
                cout << "  → Station " << v.first << " (" << stations[v.first].name 
                     << ") - Travel Time: " << v.second << " mins" << endl;
            }
            cout << endl;
        }
    }

    // DFS implementation
    void DFS(int startStation) {
        vector<bool> visited(SIZE, false);
        stack<int> stack;
        
        cout << "\nEmergency Route Inspection (DFS) from Station " << startStation 
             << " (" << stations[startStation].name << "):" << endl;
        cout << "Purpose: Emergency response route mapping" << endl;
        cout << string(80, '=') << endl;
        
        stack.push(startStation);
        
        while (!stack.empty()) {
            int current = stack.top();
            stack.pop();
            
            if (!visited[current]) {
                visited[current] = true;
                cout << "Checking Station " << current << " (" << stations[current].name 
                     << " - " << stations[current].type << ")" << endl;
                
                vector<int> neighbors;
                for (const auto& p : adjList[current]) {
                    if (!visited[p.first]) {
                        cout << "  → Emergency route to Station " << p.first 
                             << " (" << stations[p.first].name << ") - ETA: " 
                             << p.second << " mins" << endl;
                        neighbors.push_back(p.first);
                    }
                }
                
                sort(neighbors.begin(), neighbors.end(), greater<int>());
                for (int neighbor : neighbors) {
                    stack.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    // BFS implementation
    void BFS(int startStation) {
        vector<bool> visited(SIZE, false);
        cout << "Station Accessibility Analysis (BFS) from Station " << startStation 
             << " (" << stations[startStation].name << "):" << endl;
        cout << "Purpose: Analyzing passenger flow and accessibility" << endl;
        cout << string(80, '=') << endl;
        
        queue<int> queue;
        visited[startStation] = true;
        queue.push(startStation);
        
        while (!queue.empty()) {
            int current = queue.front();
            cout << "Analyzing Station " << current << " (" << stations[current].name 
                 << " - " << stations[current].type << ")" << endl;
            queue.pop();
            
            for (Pair neighbor : adjList[current]) {
                if (!visited[neighbor.first]) {
                    cout << "  → Connected to Station " << neighbor.first 
                         << " (" << stations[neighbor.first].name 
                         << ") - Travel Time: " << neighbor.second << " mins" << endl;
                    visited[neighbor.first] = true;
                    queue.push(neighbor.first);
                }
            }
        }
        cout << endl;
    }

    void shortestPaths (int source) {
        vector<int> dist(SIZE, INF);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        dist[source] = 0;
        pq.push(make_pair(0, source));

        while (!pq.empty()){
            int u = pq.top().second;
            pq.pop();

            for (const auto& neighbor : adjList[u]){
                int v = neighbor.first;
                int weight = neighbor.second;

                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist [u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
        cout << "Shortest path travel times from " << stations[source].name << " (Station " << source << "):" << endl;
        for (int i = 0; i < SIZE; i++) {
            cout << source << " -> " << i << " : " << dist[i] << endl;
        }
        cout << endl;
    }

    void findMST() {
        Tree tr(SIZE);
        vector<Edge> mst;
        int totalWeight = 0;
        
        // Sort edges by weight
        vector<Edge> sortedEdges = allEdges;
        sort(sortedEdges.begin(), sortedEdges.end());
        
        cout << "Minimum Cost Metro Network (MST):" << endl;
        cout << "Purpose: Identifying critical connections for maintenance" << endl;
        cout << string(80, '=') << endl;
        
        // Kruskal's algorithm
        for (const Edge& edge : sortedEdges) {
            if (tr.find(edge.src) != tr.find(edge.dest)) {
                tr.unite(edge.src, edge.dest);
                mst.push_back(edge);
                totalWeight += edge.weight;
                
                cout << "Edge from " << edge.src << " to " << edge.dest 
                     << " with travel time: " << edge.weight << " mins" << endl;
            }
        }
        
        cout << "\nTotal minimum network travel time: " << totalWeight << " minutes" << endl;
    }
};


int main() {
    // Creates a vector of graph edges/weights
    vector<Station> stations = {
        {"Central Terminal", "Major Hub"},
        {"City Square", "Transfer Station"},
        {"Business District", "Express Stop"},
        {"University", "Local Station"},
        {"Sports Complex", "Local Station"},
        {"Airport Express", "Major Hub"},
        {"Shopping District", "Transfer Station"},
        {"Tech Park", "Express Stop"},
        {"Medical Center", "Transfer Station"}
    };
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        {0,1,12},{0,2,8},{0,3,21},{2,3,6},{2,6,2},{5,6,6},{4,5,9},{1,1,1},{2,2,2},{3,3,3},{4,4,4},{5,5,5},{6,6,6}
    };

    // Creates graph
    MetroNetwork metro(edges, stations);

    // Prints adjacency list representation of graph
    metro.printNetwork();

    
    // Perform DFS starting from vertex 0
    metro.DFS(0);

    // Perform BFS starting from vertex 0
    metro.BFS(0);

    //shortest path
    metro.shortestPaths(0);

    //the tree
    metro.findMST();

    return 0;
}
