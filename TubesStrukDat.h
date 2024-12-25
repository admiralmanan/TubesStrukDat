#ifndef TUBESSTRUKDAT_H_INCLUDED
#define TUBESSTRUKDAT_H_INCLUDED

#define idVertex(v) v->idVertex
#define nextVertex(v) v->nextVertex
#define firstEdge(v) v->firstEdge
#define firstVertex(L) L.firstVertex

#include <iostream>
using namespace std;

// Struktur data untuk Edge dan Vertex
struct Edge {
    char destVertexID;
    int weight;
    Edge* nextEdge;
};

struct Vertex {
    char idVertex;
    Vertex* nextVertex;
    Edge* firstEdge;
};

struct Graph {
    Vertex* firstVertex;
};

// Deklarasi fungsi-fungsi
void createVertex(char newVertexID, Vertex* &v);
void initGraph(Graph &G);
void addVertex(Graph &G, char newVertexID);
Vertex* findVertex(Graph G, char id);
void addEdge(Graph &G, char fromID, char toID, int weight);
void removeEdge(Graph &G, char fromID, char toID);
void printGraph(Graph G);
int totalHarga(Graph G, char startVertexID, char endVertexID);
void DFSRec(Vertex* current, char endVertexID, int currentWeight, int &maxWeight, bool visited[], Graph G);
void DFS(Graph G, char startVertexID, char endVertexID);
void DFSTerjauh(Graph G, char startVertexID, char endVertexID);
void tampilkanMenu(Graph &G);

#endif // TUBESSTRUKDAT_H_INCLUDED
