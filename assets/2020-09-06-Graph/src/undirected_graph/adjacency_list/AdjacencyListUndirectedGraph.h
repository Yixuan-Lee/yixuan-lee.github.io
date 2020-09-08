//
// Created by  liyixuan on 2020-09-06.
//

#ifndef ADJACENCYLISTUNDIRECTEDGRAPH_H
#define ADJACENCYLISTUNDIRECTEDGRAPH_H

class AdjacencyListUndirectedGraph {
private:
    struct GraphVertex {
        int id;
        T data;
        int weight;
        GraphNode *next;
    };

    struct GraphEdge {
        int startVertexId;
        int endVertexId;
        int weight;
    };
public:
    /////////////////////////// Big Five  ////////////////////////////
    // 1. destructor

    // 2. copy constructor

    // 3. copy assignment operator=

    // 4. move constructor

    // 5. move assignment operator=

    //////////////////////////////////////////////////////////////////

    ////////////////////// Principle Operations //////////////////////

    //////////////////////////////////////////////////////////////////

    ////////////////////// Auxiliary Operations //////////////////////

    //////////////////////////////////////////////////////////////////

private:


    /////////////////////// Auxiliary Function ///////////////////////

    //////////////////////////////////////////////////////////////////

};

#endif //ADJACENCYLISTUNDIRECTEDGRAPH_H
