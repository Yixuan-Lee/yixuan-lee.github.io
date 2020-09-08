#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "AdjacencyListDirectedGraph.h"

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::ostream;

template<typename T>
ostream& operator<<(ostream& os, const vector<T> &vec) {
    for (typename vector<T>::const_iterator it = vec.cbegin(); it != vec.cend(); ++it) {
        os << *it << " ";
    }
    return os;
}


int main() {
    // test default constructor, isEmpty
    AdjacencyListDirectedGraph<int> graph_1;
    assert(graph_1.isEmpty() == true);
    graph_1.displayAdjList();
    cout << "=============================================================\n";

    // create vertices
    vector<AdjacencyListDirectedGraph<char>::GraphVertex> vertices_2 = {
            {0, 'A'}, {1, 'B'}, {2, 'C'}, {3, 'D'}, {4, 'E'}, {5, 'F'}, {6, 'G'}
    };
    // create edges
    vector<AdjacencyListDirectedGraph<char>::GraphEdge> edges_2 = {
            {0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 3}, {2, 4}, {2, 5}, {3, 5}, {3, 6}
    };
//    // test constructor, isEmpty
    AdjacencyListDirectedGraph<char> graph_2(vertices_2, edges_2, vertices_2.size(), edges_2.size());
    graph_2.displayAdjList();
    assert(graph_2.isEmpty() == false);
    cout << "=============================================================\n";

    // test addVertex, addEdge, getNumberOfVertices, getNumberOfEdges
    vector<AdjacencyListDirectedGraph<string>::GraphVertex> vertices_3 = {
            {0, "Montreal"}, {1, "Toronto"}, {2, "Beijing"}, {3, "Ottawa"},
            {5, "New York"}, {6, "Shanghai"}, {7, "Vancouver"},
            {8, "Los Angeles"}, {9, "San Francisco"}
    };
    vector<AdjacencyListDirectedGraph<string>::GraphEdge> edges_3 = {
            {0, 1, 2}, {0, 3, 1},
            {1, 2, 18}, {1, 5, 4},
            {2, 5, 20},
            {3, 1, 1}, {3, 7, 6}, {3, 6, 15},
            {5, 8, 10}, {5, 9, 12},
            {6, 5, 20},
            {7, 6, 12},
            {8, 6, 13},
            {9, 8, 13}
    };
    AdjacencyListDirectedGraph<string> graph_3(vertices_3, edges_3, vertices_3.size(), edges_3.size());
    cout << "Before adding vertices and edges: " << endl;
    graph_3.displayAdjList();
    cout << "numberOfVertices = " << graph_3.getNumberOfVertices() << endl;
    cout << "numberOfEdges = " << graph_3.getNumberOfEdges() << endl;
    try {
        graph_3.addVertex(AdjacencyListDirectedGraph<string>::GraphVertex(4, "Hong Kong"));
        graph_3.addEdge(AdjacencyListDirectedGraph<string>::GraphEdge(3, 1, 1));
        graph_3.addEdge(AdjacencyListDirectedGraph<string>::GraphEdge(2, 4, 11));
        graph_3.addEdge(AdjacencyListDirectedGraph<string>::GraphEdge(4, 5, 19));
        graph_3.addEdge(AdjacencyListDirectedGraph<string>::GraphEdge(4, 9, 16));
    } catch (const std::runtime_error &e) {
        cout << e.what() << endl;
    }
    cout << "After adding vertices and edges: " << endl;
    graph_3.displayAdjList();
    cout << "numberOfVertices = " << graph_3.getNumberOfVertices() << endl;
    cout << "numberOfEdges = " << graph_3.getNumberOfEdges() << endl;
    cout << "=============================================================\n";

    // test removeVertexById
    const int vertexId2Remove = 5;
    cout << "Before removing vertex id " << vertexId2Remove << ": " << endl;
    graph_3.displayAdjList();
    try {
        graph_3.removeVertexById(vertexId2Remove);
    } catch (const std::runtime_error &e) {
        cout << e.what() << endl;
    }
    cout << "After removing vertex id " << vertexId2Remove << ": " << endl;
    graph_3.displayAdjList();
    cout << "numberOfVertices = " << graph_3.getNumberOfVertices() << endl;
    cout << "numberOfEdges = " << graph_3.getNumberOfEdges() << endl;
    cout << "=============================================================\n";

    // test removeVertexByValue
    const string vertexValue2Remove = "San Francisco";
    cout << "Before removing vertex value " << vertexValue2Remove << ": " << endl;
    graph_3.displayAdjList();
    graph_3.removeVertexByValue(vertexValue2Remove);
    cout << "After removing vertex value " << vertexValue2Remove << ": " << endl;
    graph_3.displayAdjList();
    cout << "numberOfVertices = " << graph_3.getNumberOfVertices() << endl;
    cout << "numberOfEdges = " << graph_3.getNumberOfEdges() << endl;
    cout << "=============================================================\n";

    // test getEdgeWeight, updateEdgeWeight
    const std::pair<int, int> edge2update = std::make_pair(3, 1);
    cout << "Before updating the weight on edge 3->1: " << endl;
    try {
        // print the weight(s) of the edge(s)
        cout << graph_3.getEdgeWeight(edge2update) << endl;
    }  catch (const std::runtime_error &e) {
        cout << e.what() << endl;
    }
    try {
        // update the weight(s) of the edge(s)
        graph_3.updateEdgeWeight(edge2update, 3);
    }  catch (const std::runtime_error &e) {
        cout << e.what() << endl;
    }
    cout << "After updating the weight on edge 3->1: " << endl;
    try {
        // print the weight(s) of the edge(s)
        cout << graph_3.getEdgeWeight(edge2update) << endl;
    }  catch (const std::runtime_error &e) {
        cout << e.what() << endl;
    }
    cout << "=============================================================\n";

    // test removeEdge
    cout << "Before removing edge 7->6 and edges 3->1: " << endl;
    graph_3.displayAdjList();
    try {
        graph_3.removeEdge(std::make_pair(7, 6));
        graph_3.removeEdge(std::make_pair(3, 1));
    } catch (const std::runtime_error &e) {
        cout << e.what() << endl;
    }
    cout << "After removing edge 7->6: " << endl;
    graph_3.displayAdjList();
    cout << "numberOfVertices = " << graph_3.getNumberOfVertices() << endl;
    cout << "numberOfEdges = " << graph_3.getNumberOfEdges() << endl;
    cout << "=============================================================\n";

    return 0;
}

