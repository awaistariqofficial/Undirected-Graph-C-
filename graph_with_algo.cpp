#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <set>
#include <fstream>

using namespace std;

// Constants
const int INF = numeric_limits<int>::max();

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
        for (const auto& pair : adjList) { //for each loop
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
            
            adjList[u].push_back({ v, weight }); // line written here instead of calling addEdge func due to file written manner. 
        }
        file.close();
    }
};

// Dijkstra's algorithm for shortest path 
// taken from GPT
vector<int> dijkstra(const Graph& graph, int start, int end) {
    unordered_map<int, int> dist;
    unordered_map<int, int> prev;
    set<pair<int, int>> pq; // Min-heap (distance, node)

    // Initialize distances
    for (const auto& node : graph.getNeighbors(start)) {
        dist[node.to] = INF;
    }
    dist[start] = 0;
    pq.insert({ 0, start });

    while (!pq.empty()) {
        int current = pq.begin()->second;
        pq.erase(pq.begin());

        if (current == end) break;

        for (const auto& edge : graph.getNeighbors(current)) {
            int neighbor = edge.to;
            int newDist = dist[current] + edge.weight;

            if (newDist < dist[neighbor]) {
                pq.erase({ dist[neighbor], neighbor });
                dist[neighbor] = newDist;
                prev[neighbor] = current;
                pq.insert({ newDist, neighbor });
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

// Command-line interface
void menu() {
    Graph graph;
    int choice;

    do {
        cout << "\nRoute Planning Menu\n";
        cout << "1. Add Edge\n";
        cout << "2. Display Graph\n";
        cout << "3. Find Shortest Path (Dijkstra's Algorithm)\n";
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
            vector<int> path = dijkstra(graph, start, end);
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
