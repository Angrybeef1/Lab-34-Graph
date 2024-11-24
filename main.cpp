//COMSC 210 | Lab 34 | Robert Stonemetz

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <iomanip>


using namespace std;

const int SIZE = 9;

struct Edge {
    int src, dest, weight;
};

struct Station {
    string name;
    string type;
};

typedef pair<int, int> Pair;

class MetroNetwork {
private:
    vector<vector<Pair>> adjList;
    vector<Station> stations;

public:
    // a vector of vectors of Pairs to represent an adjacency list
    //vector<vector<Pair>> adjList;

    // Graph Constructor
    MetroNetwork(vector<Edge> const &edges, vector<Station> const &stationInfo) {
        // resize the vector to hold SIZE elements of type vector<Edge>
        adjList.resize(SIZE);
        stations = stationInfo;

        // add edges to the directed graph
        for (auto &edge: edges) {
            //int src = edge.src;
            //int dest = edge.dest;
            //int weight = edge.weight;

            // insert at the end
            adjList[edge.src].push_back(make_pair(edge.dest, edge.weight));
            // for an undirected graph, add an edge from dest to src also
            adjList[edge.dest].push_back(make_pair(edge.src, edge.weight));
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

    return 0;
}
