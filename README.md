Project Report
Title: Graph Operations and Management System

Abstract
This project focuses on designing and implementing a Graph Operations and Management System. The program enables users to create, display, save, and load graphs while supporting undirected weighted edges. The system is implemented in C++ using standard data structures.

Introduction
Graphs are powerful data structures representing complex systems such as transportation networks, social connections, and communication systems. This project provides a user-friendly interface for managing graphs with features like adding edges, visualizing graphs, and saving/loading data to/from files.
This system is particularly useful for understanding the fundamentals of graph theory, file I/O operations, and working with data structures in C++.

Objectives
1.To develop a system for managing graph structures with undirected weighted edges.
2.To provide functionalities for creating, displaying, saving, and loading graphs.
3.To design an efficient and modular C++ implementation using dynamic data structures.

Features
The project includes the following features:
1.Add Edge: Users can add an edge between two nodes with a specified weight.
2.Display Graph: Visualize the graph structure with nodes and their connected edges.
3.Save Graph to File: Save the graph data to an external file for future use.
4.Load Graph from File: Load graph data from a previously saved file.

System Design
Data Structures Used
1.Adjacency List: The graph is represented using an adjacency list stored in an unordered map for efficient space utilization and fast access.
○Key: Node ID (integer)
○Value: A vector of Edge structures representing the node's neighbors.
2.Edge Structure:
○to: Destination node.
○weight: Weight of the edge.
Core Components
1.Graph Class: Encapsulates all graph-related operations such as adding edges, displaying the graph, and file operations.
2.File Operations: Provides functionality to save and load graph data using standard file I/O in C++.
3.Command-Line Interface: A simple menu-driven interface for user interaction.

Implementation
The project was implemented in C++ using modular programming principles. Key functions include:
1.Adding an Edge:
○Ensures bidirectional connectivity for undirected graphs.
2.Displaying the Graph:
○Outputs all nodes along with their neighbors and edge weights.
3.Saving to File:
○Write the graph data in a space-separated format: node1 node2 weight.
4.Loading from File:
○Reads the graph data and reconstructs the adjacency list.

Technologies and Tools
●Programming Language: C++
●Compiler: GCC
●Development Environment: Visual Studio 2022
●Version Control: Git

Results
The program successfully provides all the core functionalities for graph management:
1.Users can create complex graphs with undirected weighted edges.
2.Graph data can be stored and retrieved using text files, ensuring persistence.
3.The system efficiently handles dynamic memory using C++ standard library components.

Limitations
1.No support for directed graphs or negative edge weights.
2.Lacks advanced graph algorithms (e.g., shortest path, minimum spanning tree).

Future Enhancements
1.Add support for directed graphs.
2.Implement graph traversal algorithms (e.g., BFS, DFS).
3.Extend functionality with advanced algorithms like Dijkstra’s, Prim’s, and Kruskal’s.
4.Integrate a graphical user interface for better visualization.

Conclusion
This project demonstrates the implementation of a robust Graph Operations and Management System in C++. It provides an excellent foundation for exploring more advanced graph algorithms and applications, showcasing the versatility of C++ data structures and file I/O.

Appendices
Sample Input and Output
Input:
1.Add edge: 1 2 10
2.Add edge: 1 3 5
3.Display graph.
4.Save graph to graph.txt.
Output:
Node 1: (2, 10) (3, 5)  
Node 2: (1, 10)  
Node 3: (1, 5)  

Saved File (graph.txt):
1 2 10  
1 3 5  

