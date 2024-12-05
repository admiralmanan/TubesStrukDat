#ifndef TUBESSTRUKDAT_H_INCLUDED
#define TUBESSTRUKDAT_H_INCLUDED

#define idVertex(v) v->idVertex
#define nextVertex(v) v->nextVertex
#define firstEdge(v) v->firstEdge
#define firstVertex(L) L.firstVertex
#include <iostream>
using namespace std;


typedef struct Vertex *adrVertex;
typedef struct Edge *adrEdge;

struct Edge
{
    char destVertexID;
    int weight;
    adrEdge nextEdge;
};

struct Vertex
{
    char idVertex;
    adrVertex nextVertex;
    adrEdge firstEdge;
};

struct Graph
{
    adrVertex firstVertex;
};


void createVertex_103022300060(char newVertexID, adrVertex &v);
void addVertex_103022300060(Graph &G, char newVertexID);
void initGraph_103022300060(Graph &G);
void buildGraph_103022300060(Graph &G);



#endif // TUBESSTRUKDAT_H_INCLUDED
