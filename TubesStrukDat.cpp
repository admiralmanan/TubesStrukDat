#include "TubesStrukDat.h"
void createVertex(char newVertexID, adrVertex &v) {
    v = new Vertex;
    idVertex(v) = newVertexID;
    nextVertex(v) = nullptr;
    firstEdge(v) = nullptr;
}

void addVertex(Graph &G, char newVertexID) {
    adrVertex newVertex;
    createVertex_103022300060(newVertexID, newVertex);

    if (firstVertex(G) == nullptr) {
        firstVertex(G) = newVertex;
    } else {
        adrVertex temp = firstVertex(G);
        while (nextVertex(temp) != nullptr) {
            temp = nextVertex(temp);
        }
        nextVertex(temp) = newVertex;
    }
}

void initGraph(Graph &G) {
    firstVertex(G) = nullptr;
}

void buildGraph(Graph &G) {
    char vertexID;
    cout << "Masukkan ID simpul (A-Z, berhenti dengan karakter non-huruf): ";
    while (cin >> vertexID && isalpha(vertexID)) {
        addVertex_103022300060(G, vertexID);
        cout << "Simpul " << vertexID << " telah ditambahkan.\n";
    }
}
  void inDegree(..){
    
  }
  void outDegree(...){
  
  }
  //tambah fungsi buat gedung teramai dikunjungi 
  gedungTeramai(..){
    
  }
  hargaTermurah(..){
    
  }
  ruteAlternatif(...){
    
  }
  ruteTercepat(...){
    
  }
}
