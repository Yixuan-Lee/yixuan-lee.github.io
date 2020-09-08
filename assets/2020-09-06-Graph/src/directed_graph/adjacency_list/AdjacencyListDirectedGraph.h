#ifndef ADJACENCYLISTDIRECTEDGRAPH_H
#define ADJACENCYLISTDIRECTEDGRAPH_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <map>

using std::cout;
using std::endl;
using std::map;
using std::multimap;
using std::vector;
using std::pair;

/**
 * A class that implements a directed weighted graph using adjacency list
 *
 * @tparam T
 * @tparam initValue
 */
template<typename T>
class AdjacencyListDirectedGraph {
public:
    // represent a vertex in graph
    struct GraphVertex {
        int id;
        T value;
        GraphVertex *next;
        // default constructor
        GraphVertex() : id{-1}, next{nullptr} {
        }

        // constructor
        GraphVertex(int id, T data, GraphVertex *next = nullptr)
                : id{id}, value{data}, next{next} {
        }
    };

    // represents an edge in graph
    struct GraphEdge {
        int startVertexId;
        int endVertexId;
        int weight;
        // default constructor
        GraphEdge() = default;
        // constructor
        GraphEdge(int startId, int endId, int weight = 1)
                : startVertexId{startId}, endVertexId{endId}, weight{weight} {
        }
    };

private:
    struct AdjacencyListNode : public GraphVertex {
        AdjacencyListNode *nextAdjNode;
        // default constructor
        AdjacencyListNode() : GraphVertex(-1), nextAdjNode{nullptr} {
        }

        // constructor
        AdjacencyListNode(int id, T data, GraphVertex *next = nullptr, AdjacencyListNode *nextAdjNode = nullptr)
            : GraphVertex(id, data, next), nextAdjNode{nextAdjNode} {
        }
    };

public:
    // default constructor
    AdjacencyListDirectedGraph();

    // constructor
    AdjacencyListDirectedGraph(const vector<GraphVertex> vertices, const vector<GraphEdge> edges, int numberOfVertices, int numberOfEdges);

    /////////////////////////// Big Five  ////////////////////////////
    // 1. destructor
    virtual ~AdjacencyListDirectedGraph();

    // 2. copy constructor

    // 3. copy assignment operator=

    // 4. move constructor

    // 5. move assignment operator=

    //////////////////////////////////////////////////////////////////

    ////////////////////// Principle Operations //////////////////////
    void addVertex(const AdjacencyListDirectedGraph<T>::GraphVertex &vertex);

    void addEdge(const AdjacencyListDirectedGraph<T>::GraphEdge &edge);

    void removeVertexById(int vertexId);

    void removeVertexByValue(T value);

    void removeEdge(int startVertexId, int endVertexId);

    void updateEdgeWeight(int startVertexId, int endVertexId, int weight);

    void displayAdjList();

    int getNumberOfVertices() const;

    int getNumberOfEdges() const;

    //////////////////////////////////////////////////////////////////

    ////////////////////// Auxiliary Operations //////////////////////
    bool isEmpty() const;

    //////////////////////////////////////////////////////////////////

private:
    // a pointer pointing to the head node in adjacency list
    AdjacencyListNode *adjacencyListHead;

    // a pointer pointing to the tail node in adjacency list
    AdjacencyListNode *adjacencyListTail;

    // an map where the key is a pair of (startVertexId, endVertexId)
    // and the value is the GraphEdge object connecting the two vertices
    multimap<pair<int, int>, GraphEdge> edges;

    int numberOfVertices {};

    int numberOfEdges {};

    // a map where the key is the vertex id, and the value is flag
    map<int, AdjacencyListNode*> vertexId2AdjNode;

    /////////////////////// Auxiliary Function ///////////////////////

    //////////////////////////////////////////////////////////////////

};

/////////////////////// Function Implementation ///////////////////////
// default constructor
template<typename T>
AdjacencyListDirectedGraph<T>::AdjacencyListDirectedGraph() {
    adjacencyListHead = nullptr;
    adjacencyListTail = nullptr;
    numberOfVertices = 0;
    numberOfEdges = 0;
}

// constructor
template<typename T>
AdjacencyListDirectedGraph<T>::AdjacencyListDirectedGraph(
        const vector<AdjacencyListDirectedGraph<T>::GraphVertex> vertices,
        const vector<AdjacencyListDirectedGraph<T>::GraphEdge> edges,
        int numberOfVertices, int numberOfEdges) {
    if (vertices.size() != numberOfVertices || edges.size() != numberOfEdges) {
        throw std::runtime_error("invalid constructor: vertices mismatches with numberOfVertices, or edges mismatches with numberOfEdges.");
    }
    // keep references
    this->numberOfVertices = numberOfVertices;
    this->numberOfEdges = numberOfEdges;
    if (numberOfVertices == 0) {
        return;
    }
    // initialize adjacency nodes in main adjacency list
    adjacencyListHead = new AdjacencyListNode(vertices[0].id, vertices[0].value, vertices[0].next);
    adjacencyListTail = adjacencyListHead;
    vertexId2AdjNode[vertices[0].id] = adjacencyListHead;
    for (size_t i = 1; i < numberOfVertices; ++i) {
        AdjacencyListNode *newAdjNode = new AdjacencyListNode(vertices[i].id, vertices[i].value, vertices[i].next);
        // link the current adjacency node to the new adjacency node
        adjacencyListTail->nextAdjNode = newAdjNode;
        // update the tail adjacency node
        adjacencyListTail = newAdjNode;
        // update vertex checker
        vertexId2AdjNode[vertices[i].id] = newAdjNode;
    }
    // construct directed graph by adding GraphNodes
    for (size_t i = 0; i < numberOfEdges; ++i) {
        int startVertexId = edges[i].startVertexId;
        int endVertexId = edges[i].endVertexId;
        // check if starting and ending vertices exist
        if (!vertexId2AdjNode.count(startVertexId) || !vertexId2AdjNode.count(endVertexId)) {
            continue;
        }
        // add each edge
        this->edges.emplace(std::make_pair(startVertexId, endVertexId), edges[i]);
        // add vertex to adjacency list
        // insert a GraphVertex to the adjacency list of vertex startVertexId
        GraphVertex *newNode = new GraphVertex(endVertexId, vertexId2AdjNode[endVertexId]->value, vertexId2AdjNode[startVertexId]->next);
        vertexId2AdjNode[startVertexId]->next = newNode;
    }
}

/////////////////////////// Big Five  ////////////////////////////
// 1. destructor
template<typename T>
AdjacencyListDirectedGraph<T>::~AdjacencyListDirectedGraph() {
    for (AdjacencyListNode *adjIt = adjacencyListHead; adjIt != nullptr; adjIt = adjIt->nextAdjNode) {
        GraphVertex *vertexIt = adjIt->next;
        for (GraphVertex *vertexIt = adjIt->next; vertexIt != nullptr; vertexIt = adjIt->next) {
            adjIt->next = vertexIt->next;
            delete vertexIt;
        }
    }
    delete adjacencyListHead;
    delete adjacencyListTail;
    adjacencyListHead = nullptr;
    adjacencyListTail = nullptr;
}


////////////////////// Principle Operations //////////////////////
template<typename T>
void AdjacencyListDirectedGraph<T>::addVertex(const AdjacencyListDirectedGraph<T>::GraphVertex &vertex) {
    if (isEmpty()) {
        adjacencyListHead = new AdjacencyListNode(vertex.id, vertex.value, vertex.next);
        adjacencyListTail = adjacencyListHead;
        numberOfVertices++;
        vertexId2AdjNode[vertex.id] = adjacencyListHead;
    } else {
        // check if the vertex with the same id exists
        if (vertexId2AdjNode.count(vertex.id) > 0) {
            throw std::runtime_error("invalid addVertex: vertex id already exists in the graph.");
        } else {
            AdjacencyListNode *newAdjNode = new AdjacencyListNode(vertex.id, vertex.value, vertex.next, adjacencyListTail->nextAdjNode);
            adjacencyListTail->nextAdjNode = newAdjNode;
            adjacencyListTail = newAdjNode;
            vertexId2AdjNode[vertex.id] = newAdjNode;
            numberOfVertices++;
        }
    }
}

template<typename T>
void AdjacencyListDirectedGraph<T>::addEdge(const AdjacencyListDirectedGraph<T>::GraphEdge &edge) {
    int startVertexId = edge.startVertexId;
    int endVertexId = edge.endVertexId;
    // check if two vertices exist
    if (!vertexId2AdjNode.count(startVertexId) || !vertexId2AdjNode.count(endVertexId)) {
        throw std::runtime_error("invalid addEdge: one of the vertices of the edge does not exist.");
    }
    // add each edge
    this->edges.emplace(std::make_pair(startVertexId, endVertexId), edge);
    this->numberOfEdges++;
    // update adjacency list
    GraphVertex* newNode = new GraphVertex(endVertexId, vertexId2AdjNode[endVertexId]->value, vertexId2AdjNode[startVertexId]->next);
    vertexId2AdjNode[startVertexId]->next = newNode;
}

template<typename T>
void AdjacencyListDirectedGraph<T>::removeVertexById(int vertexId) {
    // check if the vertex id exists in the graph
    if (vertexId2AdjNode.count(vertexId) == 0) {
        return;
    }
    // 1. remove all the out-edges from the vertex
    AdjacencyListNode *vertexAdjNode = vertexId2AdjNode[vertexId];
    for (GraphVertex *vertexIt = vertexAdjNode->next; vertexIt != nullptr; vertexIt = vertexIt->next) {
        vertexAdjNode->next = vertexIt->next;
        delete vertexIt;
    }

    // 2. remove the adjacency node in main adjacency list
    // 2.1 link the previous adjacency node of the vertex's adjacency node to the next adjacency node of it
    AdjacencyListNode *adjNode = adjacencyListHead;
    while (adjNode->nextAdjNode != vertexAdjNode) {
        adjNode = adjNode->nextAdjNode;
    }
    adjNode->nextAdjNode = vertexAdjNode->nextAdjNode;
    // 2.2 remove the adjacency node of the vertex
    vertexAdjNode->nextAdjNode = nullptr;
    delete vertexAdjNode;
    vertexAdjNode = nullptr;

    // 3. remove all the in-edges to the vertex from other vertices
    for (AdjacencyListNode *adjIt = adjacencyListHead; adjIt != nullptr; adjIt = adjIt->nextAdjNode) {
        // check if the first few vertex nodes is the vertex
        GraphVertex *vertexIt = adjIt->next;
        while (vertexIt != nullptr && vertexIt->id == vertexId) {
            // update the first vertex node in the current adjacency list
            adjIt->next = vertexIt->next;
            // delete the first vertex node
            vertexIt->next = nullptr;
            delete vertexIt;
            // update the pointer to the first vertex node
            vertexIt = adjIt->next;
        }
        if (vertexIt == nullptr) {
            // current adjacency list is empty
            continue;
        }
        // so far, the first vertex node's id in the current adjacency list is not vertexId

        // remove the vertex node in the adjacency list of main adjacency node
        GraphVertex *prev = vertexIt;
        GraphVertex *curr = vertexIt->next;
        while (curr != nullptr) {
            if (curr->id == vertexId) {
                // update prev's next
                prev->next = curr->next;
                // delete the node with the vertexId
                curr->next = nullptr;
                delete curr;
                // update curr
                curr = prev->next;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }
    }
}

template<typename T>
void AdjacencyListDirectedGraph<T>::removeVertexByValue(T value) {
    // traverse vertexId2AdjNode and find the corresponding vertex id(s) with the value
    vector<int> vertexIds2Remove;
    for (typename map<int, AdjacencyListNode*>::const_iterator adjIt = vertexId2AdjNode.cbegin(); adjIt != vertexId2AdjNode.cend(); ++adjIt) {
        if (adjIt->second->value == value) {
            vertexIds2Remove.push_back(adjIt->first);
        }
    }
    // remove all vertices with the id in vertexIds2Remove
    for (vector<int>::const_iterator it = vertexIds2Remove.cbegin(); it != vertexIds2Remove.cend(); ++it) {
        removeVertexById(*it);
    }
}

template<typename T>
void AdjacencyListDirectedGraph<T>::displayAdjList() {
    cout << "Adjacency list of graph: \n";
    if (isEmpty()) {
        cout << "NULL" << endl;
        return;
    }
    for (AdjacencyListNode *adjIt = adjacencyListHead; adjIt != nullptr; adjIt = adjIt->nextAdjNode) {
        cout << "\t" << adjIt->id << " -> ";
        for (GraphVertex *vertexIt = adjIt->next; vertexIt != nullptr; vertexIt = vertexIt->next) {
            cout << vertexIt->id << "  ";
        }
        cout << endl;
    }
}

template<typename T>
int AdjacencyListDirectedGraph<T>::getNumberOfVertices() const {
    return numberOfVertices;
}

template<typename T>
int AdjacencyListDirectedGraph<T>::getNumberOfEdges() const {
    return numberOfEdges;
}

////////////////////// Auxiliary Operations //////////////////////
template<typename T>
bool AdjacencyListDirectedGraph<T>::isEmpty() const {
    return numberOfVertices == 0;
}


#endif //ADJACENCYLISTDIRECTEDGRAPH_H
