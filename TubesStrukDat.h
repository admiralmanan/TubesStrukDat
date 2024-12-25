#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

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
void bfs(Graph G, char startVertexID, char endVertexID);
void dfs(Vertex* current, char endVertexID, int currentWeight, int &maxWeight, bool visited[], bool &foundLongest, Graph G, string path);
void tampilkanMenu(Graph &G);
int totalHarga(Graph G, char startVertexID, char endVertexID);
void dfsTotalHarga(Vertex* current, char endVertexID, int currentWeight, bool visited[], int &totalWeight, Graph G);

#endif // GRAPH_H_INCLUDED
