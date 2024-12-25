#include "TubesStrukDat.h"

// Fungsi untuk membuat vertex baru
void createVertex(char newVertexID, Vertex* &v) {
    v = new Vertex;
    idVertex(v) = newVertexID;
    nextVertex(v) = nullptr;
    firstEdge(v) = nullptr;
}

// Inisialisasi graph (kosong)
void initGraph(Graph &G) {
    firstVertex(G) = nullptr;
}

// Menambahkan vertex baru ke dalam graph
void addVertex(Graph &G, char newVertexID) {
    Vertex* newVertex;
    createVertex(newVertexID, newVertex);

    if (firstVertex(G) == nullptr) {
        firstVertex(G) = newVertex;
    } else {
        Vertex* temp = firstVertex(G);
        while (nextVertex(temp) != nullptr) {
            temp = nextVertex(temp);
        }
        nextVertex(temp) = newVertex;
    }
}

// Mencari vertex berdasarkan ID
Vertex* findVertex(Graph G, char id) {
    Vertex* temp = firstVertex(G);
    while (temp != nullptr) {
        if (idVertex(temp) == id) {
            return temp;
        }
        temp = nextVertex(temp);
    }
    return nullptr;
}

// Menambahkan edge antara dua vertex
void addEdge(Graph &G, char fromID, char toID, int weight) {
    Vertex* fromVertex = findVertex(G, fromID);
    Vertex* toVertex = findVertex(G, toID);

    if (fromVertex != nullptr && toVertex != nullptr) {
        Edge* newEdge = new Edge;
        newEdge->destVertexID = toID;
        newEdge->weight = weight;
        newEdge->nextEdge = firstEdge(fromVertex);
        firstEdge(fromVertex) = newEdge;

        Edge* reverseEdge = new Edge;
        reverseEdge->destVertexID = fromID;
        reverseEdge->weight = weight;
        reverseEdge->nextEdge = firstEdge(toVertex);
        firstEdge(toVertex) = reverseEdge;
    } else {
        cout << "Vertex tidak ditemukan: " << fromID << " atau " << toID << endl;
    }
}

// Menghapus edge antara dua vertex
void removeEdge(Graph &G, char fromID, char toID) {
    Vertex* fromVertex = findVertex(G, fromID);
    Vertex* toVertex = findVertex(G, toID);

    if (fromVertex != nullptr && toVertex != nullptr) {
        // Menghapus edge dari fromID ke toID
        Edge* prev = nullptr, *current = firstEdge(fromVertex);
        while (current != nullptr && current->destVertexID != toID) {
            prev = current;
            current = current->nextEdge;
        }
        if (current != nullptr) {
            if (prev == nullptr) {
                firstEdge(fromVertex) = current->nextEdge;
            } else {
                prev->nextEdge = current->nextEdge;
            }
            delete current;
        }

        // Menghapus edge dari toID ke fromID
        prev = nullptr, current = firstEdge(toVertex);
        while (current != nullptr && current->destVertexID != fromID) {
            prev = current;
            current = current->nextEdge;
        }
        if (current != nullptr) {
            if (prev == nullptr) {
                firstEdge(toVertex) = current->nextEdge;
            } else {
                prev->nextEdge = current->nextEdge;
            }
            delete current;
        }

        cout << "Jalur antara " << fromID << " dan " << toID << " telah dihapus.\n";
    } else {
        cout << "Vertex tidak ditemukan: " << fromID << " atau " << toID << endl;
    }
}

// Menampilkan isi graph
void printGraph(Graph G) {
    Vertex* v = firstVertex(G);
    while (v != nullptr) {
        cout << "Vertex " << idVertex(v) << ": ";
        Edge* e = firstEdge(v);
        while (e != nullptr) {
            cout << "-> " << e->destVertexID << "(" << e->weight << ") ";
            e = e->nextEdge;
        }
        cout << endl;
        v = nextVertex(v);
    }
}

// Menghitung total harga berdasarkan edge yang ada
int totalHarga(Graph G, char startVertexID, char endVertexID) {
    Vertex* startVertex = findVertex(G, startVertexID);
    if (startVertex == nullptr) {
        cout << "Vertex awal tidak ditemukan: " << startVertexID << endl;
        return -1;
    }

    Edge* edge = firstEdge(startVertex);
    while (edge != nullptr) {
        if (edge->destVertexID == endVertexID) {
            return edge->weight * 2000; // Bobot dikalikan harga per menit
        }
        edge = edge->nextEdge;
    }

    cout << "Edge dari " << startVertexID << " ke " << endVertexID << " tidak ditemukan.\n";
    return -1;
}

// Fungsi rekursif DFS untuk mencari jalur terpanjang
void DFSRec(Vertex* current, char endVertexID, int currentWeight, int &maxWeight, bool visited[], Graph G) {
    // Jika mencapai tujuan, perbarui maxWeight jika perlu
    if (idVertex(current) == endVertexID) {
        maxWeight = max(maxWeight, currentWeight);
        return;
    }

    visited[current->idVertex - 'A'] = true;

    Edge* edge = firstEdge(current);
    while (edge != nullptr) {
        Vertex* nextVertex = findVertex(G, edge->destVertexID);
        if (nextVertex != nullptr && !visited[nextVertex->idVertex - 'A']) {
            DFSRec(nextVertex, endVertexID, currentWeight + edge->weight, maxWeight, visited, G);
        }
        edge = edge->nextEdge;
    }

    visited[current->idVertex - 'A'] = false; // Membatalkan penandaan vertex sebagai sudah dikunjungi
}

// Fungsi DFS untuk mencari jalur terpanjang
void DFS(Graph G, char startVertexID, char endVertexID) {
    Vertex* startVertex = findVertex(G, startVertexID);
    Vertex* endVertex = findVertex(G, endVertexID);

    if (startVertex == nullptr || endVertex == nullptr) {
        cout << "Vertex tidak ditemukan!" << endl;
        return;
    }

    // Inisialisasi array visited dan variabel maxWeight
    bool visited[26] = {false};  // Mengasumsikan hanya menggunakan huruf besar A-Z
    int maxWeight = -1;

    DFSRec(startVertex, endVertexID, 0, maxWeight, visited, G);

    if (maxWeight == -1) {
        cout << "Tidak ada jalur ditemukan antara " << startVertexID << " dan " << endVertexID << endl;
    } else {
        cout << "Jalur terpanjang dari " << startVertexID << " ke " << endVertexID << " memiliki bobot: " << maxWeight << endl;
    }
}

// Fungsi untuk mencari jalur terjauh (menggunakan DFS)
void DFSTerjauh(Graph G, char startVertexID, char endVertexID) {
    DFS(G, startVertexID, endVertexID);  // Implementasi DFS bisa digunakan untuk DFSTerjauh
}

// Fungsi untuk menampilkan menu dan memilih aksi yang akan dilakukan
void tampilkanMenu(Graph &G) {
    char startVertex, endVertex;
    bool jalan = true;
    while (jalan) {
        cout << "-------- Menu --------" << endl;
        cout << "1. Lihat Map" << endl;
        cout << "2. Masukkan Titik Awal dan Tujuan" << endl;
        cout << "3. Tampilkan Rute Tercepat dan Terlama" << endl;
        cout << "4. Hitung Total Harga" << endl;
        cout << "5. Hapus Jalur" << endl;
        cout << "6. Rute Terjauh" << endl;
        cout << "7. Keluar" << endl;
        cout << "Masukkan menu: ";

        int pilihan;
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                printGraph(G);
                break;

            case 2:
                cout << "Masukkan titik awal: ";
                cin >> startVertex;
                cout << "Masukkan titik tujuan: ";
                cin >> endVertex;
                break;

            case 3:
                DFS(G, startVertex, endVertex);
                DFSTerjauh(G, startVertex, endVertex);
                break;

            case 4:
                cout << "Total harga: " << totalHarga(G, startVertex, endVertex) << endl;
                break;

            case 5:
                removeEdge(G, startVertex, endVertex);
                break;

            case 6:
                DFSTerjauh(G, startVertex, endVertex);
                break;

            case 7:
                jalan = false;
                break;

            default:
                cout << "Pilihan tidak valid!" << endl;
                break;
        }
    }
}
