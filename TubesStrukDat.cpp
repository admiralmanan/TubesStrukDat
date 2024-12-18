#include "TubesStrukDat.h"
#ifndef TubesStrukDat_h
#define TubesStrukDat_h

#define idVertex(v) v->idVertex
#define nextVertex(v) v->nextVertex
#define firstEdge(v) v->firstEdge
#define firstVertex(L) L.firstVertex
#include <climits>
#include <iostream>
using namespace std;

// Definisi tipe data
struct Edge;
struct Vertex;

typedef Vertex* adrVertex;
typedef Edge* adrEdge;

struct Vertex {
    char idVertex;
    adrVertex nextVertex;
    adrEdge firstEdge;
};

struct Edge {
    char destVertexID;
    int weight;
    adrEdge nextEdge;
};

struct Graph {
    adrVertex firstVertex;
};

// Deklarasi fungsi dan prosedur
void createVertex(char newVertexID, adrVertex &v);
void initGraph(Graph &G);
void addVertex(Graph &G, char newVertexID);
adrVertex findVertex(Graph G, char id);
void addEdge(Graph &G, char fromID, char toID, int weight);
void removeEdge(Graph &G, char fromID, char toID);
void printGraph(Graph G);
void tampilkanMenu(Graph &G);
void DFS(Graph G, char startVertexID, char endVertexID);

#endif /* tGraph_h */

