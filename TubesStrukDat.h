#ifndef tGraph_h
#define tGraph_h

#define idVertex(v) v->idVertex
#define nextVertex(v) v->nextVertex
#define firstEdge(v) v->firstEdge
#define firstVertex(L) L.firstVertex

#include <iostream>
#include <string>
using namespace std;

// Definisi tipe data
struct Edge;
struct Vertex;

typedef Vertex* adrVertex;
typedef Edge* adrEdge;

struct Vertex {
    string idVertex;
    adrVertex nextVertex;
    adrEdge firstEdge;
};

struct Edge {
    string destVertexID;
    int weight;
    adrEdge nextEdge;
};

struct Graph {
    adrVertex firstVertex;
};

// Deklarasi fungsi dan prosedur
void createVertex(string newVertexID, adrVertex &v);
void initGraph(Graph &G);
void addVertex(Graph &G, string newVertexID);
adrVertex findVertex(Graph G, string id);
void addEdge(Graph &G, string fromID, string toID, int weight);
void removeEdge(Graph &G, string fromVertexID, string toVertexID);
void printGraph(Graph G);
void ruteTerecepat(Graph G, string startVertexID, string endVertexID);
void tampilkanMenu(Graph &G);
void tambahRute(Graph &G);
void tujuan(Graph &G, string &startVertex, string &endVertex);

#endif /* tGraph_h */
