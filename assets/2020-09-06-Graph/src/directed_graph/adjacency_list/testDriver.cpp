#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include "AdjacencyListDirectedGraph.h"

using std::cout;
using std::endl;
using std::vector;
using std::string;

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
    graph_3.displayAdjList();
    cout << "numberOfVertices = " << graph_3.getNumberOfVertices() << endl;
    cout << "numberOfEdges = " << graph_3.getNumberOfEdges() << endl;
    try {
        graph_3.addVertex(AdjacencyListDirectedGraph<string>::GraphVertex(4, "Hong Kong"));
        graph_3.displayAdjList();
        graph_3.addEdge(AdjacencyListDirectedGraph<string>::GraphEdge(2, 4, 11));
        graph_3.addEdge(AdjacencyListDirectedGraph<string>::GraphEdge(4, 5, 19));
        graph_3.addEdge(AdjacencyListDirectedGraph<string>::GraphEdge(4, 9, 16));
        graph_3.displayAdjList();
    } catch (const std::runtime_error &e) {
        cout << e.what() << endl;
    }
    cout << "numberOfVertices = " << graph_3.getNumberOfVertices() << endl;
    cout << "numberOfEdges = " << graph_3.getNumberOfEdges() << endl;
    cout << "=============================================================\n";

    // test removeVertexById
    const int vertexId2Remove = 5;
    cout << "Before removing vertex id " << vertexId2Remove << ": " << endl;
    graph_3.displayAdjList();
    graph_3.removeVertexById(vertexId2Remove);
    cout << "After removing vertex id " << vertexId2Remove << ": " << endl;
    graph_3.displayAdjList();
    cout << "=============================================================\n";

    // test removeVertexByValue
    const string vertexValue2Remove = "San Francisco";
    cout << "Before removing vertex value " << vertexValue2Remove << ": " << endl;
    graph_3.displayAdjList();
    graph_3.removeVertexByValue(vertexValue2Remove);
    cout << "After removing vertex value " << vertexValue2Remove << ": " << endl;
    graph_3.displayAdjList();
    cout << "=============================================================\n";

    return 0;
}

