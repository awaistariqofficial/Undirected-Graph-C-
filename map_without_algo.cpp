#include <iostream>
#include <vector>
#include <unordered_map>
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
            adjList[u].push_back({ v, weight });
        }
        file.close();
    }
};

//Menu
void menu() {
    Graph graph;
    int choice;

    do {
        cout << "\nGraph Operations Menu\n";
        cout << "1. Add Edge\n";
        cout << "2. Display Graph\n";
        cout << "3. Save Graph to File\n";
        cout << "4. Load Graph from File\n";
        cout << "5. Exit\n";
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
            string filename;
            cout << "Enter filename to save graph: ";
            cin >> filename;
            graph.saveToFile(filename);
            break;
        }
        case 4: {
            string filename;
            cout << "Enter filename to load graph: ";
            cin >> filename;
            graph.loadFromFile(filename);
            break;
        }
        case 5:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);
}

int main() {
    menu();
    return 0;
}
