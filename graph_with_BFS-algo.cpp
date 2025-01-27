#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <set>
#include <fstream>

using namespace std;

// Edge structure
struct Edge {
    int to, weight;
};

// Graph class
class Graph {
private:
    unordered_map<int, vector<Edge>> adjList;

public:
    // Add an edge to the graph
    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({ v, weight });
        adjList[v].push_back({ u, weight }); // For undirected graph
    }

    // Get neighbors of a node
    const vector<Edge>& getNeighbors(int node) const {
        return adjList.at(node);
    }

    // Check if a node exists
    bool containsNode(int node) const {
        return adjList.find(node) != adjList.end();
    }

    // Print graph
    void display() const {
        for (const auto& pair : adjList) {
            cout << "Node " << pair.first << ": ";
            for (const auto& edge : pair.second) {
                cout << "(" << edge.to << ", " << edge.weight << ") ";
            }
            cout << endl;
        }
    }

    // Save graph to file
    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file) {
            cout << "Error opening file for writing." << endl;
            return;
        }
        for (const auto& pair : adjList) {
            for (const auto& edge : pair.second) {
                file << pair.first << " " << edge.to << " " << edge.weight << endl;
            }
        }
        file.close();
    }

    // Load graph from file
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cout << "Error opening file for reading." << endl;
            return;
        }
        adjList.clear();
        int u, v, weight;
        while (file >> u >> v >> weight) {
            adjList[u].push_back({ v, weight });//not calling add edge function
        }
        file.close();
    }
};

// BFS for shortest path (unweighted graph)
vector<int> bfsShortestPath(const Graph& graph, int start, int end) {
    unordered_map<int, int> prev; // Stores the previous node for each visited node
    queue<int> q;
    set<int> visited;

    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        if (current == end) break;

        for (const auto& edge : graph.getNeighbors(current)) {
            int neighbor = edge.to;
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                prev[neighbor] = current;
                q.push(neighbor);
            }
        }
    }

    // Reconstruct path
    vector<int> path;
    for (int at = end; at != start; at = prev[at]) {
        if (prev.find(at) == prev.end()) {
            cout << "No path found!" << endl;
            return {};
        }
        path.push_back(at);
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}

// Menu func
void menu() {
    Graph graph;
    int choice;

    do {
        cout << "\nRoute Planning Menu\n";
        cout << "1. Add Edge\n";
        cout << "2. Display Graph\n";
        cout << "3. Find Shortest Path (BFS)\n";
        cout << "4. Save Graph to File\n";
        cout << "5. Load Graph from File\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int u, v, weight;
            cout << "Enter source, destination, and weight: ";
            cin >> u >> v >> weight;
            graph.addEdge(u, v, weight);
            break;
        }
        case 2:
            graph.display();
            break;

        case 3: {
            int start, end;
            cout << "Enter start and end nodes: ";
            cin >> start >> end;
            vector<int> path = bfsShortestPath(graph, start, end);
            if (!path.empty()) {
                cout << "Shortest Path: ";
                for (int node : path) cout << node << " ";
                cout << endl;
            }
            break;
        }
        case 4: {
            string filename;
            cout << "Enter filename to save graph: ";
            cin >> filename;
            graph.saveToFile(filename);
            break;
        }
        case 5: {
            string filename;
            cout << "Enter filename to load graph: ";
            cin >> filename;
            graph.loadFromFile(filename);
            break;
        }
        case 6:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 6);
}

int main() {
    menu();
    return 0;
}
