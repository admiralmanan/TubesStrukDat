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

// Fungsi untuk menghapus edge antara dua vertex
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

        // Menghapus edge dari toID ke fromID (karena ini adalah graph tak terarah)
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

// BFS untuk mencari jalur tercepat
void bfs(Graph G, char startVertexID, char endVertexID) {
    Vertex* startVertex = findVertex(G, startVertexID);
    Vertex* endVertex = findVertex(G, endVertexID);

    if (startVertex == nullptr || endVertex == nullptr) {
        cout << "Vertex tidak ditemukan!" << endl;
        return;
    }

    bool visited[26] = {false};  // Mengasumsikan hanya menggunakan huruf besar A-Z
    int distance[26];  // Menyimpan jarak dari start
    char previous[26];  // Menyimpan previous vertex untuk rekonstruksi jalur

    for (int i = 0; i < 26; ++i) {
        distance[i] = -1;
        previous[i] = '\0';
    }

    Vertex* queue[26];
    int front = 0, rear = 0;

    // Mulai BFS dari startVertex
    distance[startVertexID - 'A'] = 0;
    queue[rear++] = startVertex;

    while (front != rear) {
        Vertex* current = queue[front++];
        Edge* edge = firstEdge(current);

        while (edge != nullptr) {
            Vertex* nextVertex = findVertex(G, edge->destVertexID);

            if (!visited[nextVertex->idVertex - 'A']) {
                visited[nextVertex->idVertex - 'A'] = true;
                distance[nextVertex->idVertex - 'A'] = distance[current->idVertex - 'A'] + 1;
                previous[nextVertex->idVertex - 'A'] = current->idVertex;

                queue[rear++] = nextVertex;

                if (nextVertex->idVertex == endVertexID) {
                    // Rekonstruksi jalur
                    string path = "";
                    Vertex* pathVertex = endVertex;

                    while (pathVertex != nullptr) {
                        path = pathVertex->idVertex + path;
                        pathVertex = findVertex(G, previous[pathVertex->idVertex - 'A']);
                    }
                    cout << "Rute tercepat: " << path << endl;
                    cout << "Jumlah langkah: " << distance[endVertexID - 'A'] << endl;
                    return;
                }
            }
            edge = edge->nextEdge;
        }
    }

    cout << "Tidak ada jalur ditemukan antara " << startVertexID << " dan " << endVertexID << endl;
}

// DFS untuk mencari jalur terlama
void dfs(Vertex* current, char endVertexID, int currentWeight, int &maxWeight, bool visited[], bool &foundLongest, Graph G, string path) {
    if (idVertex(current) == endVertexID) {
        if (!foundLongest || currentWeight > maxWeight) {
            maxWeight = currentWeight;
            path += current->idVertex; // Menambahkan vertex tujuan ke jalur
            cout << "Rute terlama: " << path << endl;
            foundLongest = true;
        }
        return;
    }

    visited[current->idVertex - 'A'] = true;
    path += current->idVertex; // Menambahkan vertex ke jalur

    Edge* edge = firstEdge(current);
    while (edge != nullptr) {
        Vertex* nextVertex = findVertex(G, edge->destVertexID);
        if (nextVertex != nullptr && !visited[nextVertex->idVertex - 'A']) {
            dfs(nextVertex, endVertexID, currentWeight + edge->weight, maxWeight, visited, foundLongest, G, path);
        }
        edge = edge->nextEdge;
    }

    visited[current->idVertex - 'A'] = false; // Membatalkan penandaan vertex sebagai sudah dikunjungi
    path.pop_back(); // Menghapus vertex terakhir dari jalur
}

// Fungsi untuk mencari jalur tercepat dan terlama
void DFS(Graph G, char startVertexID, char endVertexID, bool findFastest, bool findLongest) {
    Vertex* startVertex = findVertex(G, startVertexID);
    Vertex* endVertex = findVertex(G, endVertexID);

    if (startVertex == nullptr || endVertex == nullptr) {
        cout << "Vertex tidak ditemukan!" << endl;
        return;
    }

    // Inisialisasi array visited dan variabel untuk jalur tercepat dan terlama
    bool visited[26] = {false};
    int maxWeight = -1;
    bool foundLongest = false;

    string path = "";  // Inisialisasi jalur kosong

    // Panggil DFS untuk jalur terlama
    dfs(startVertex, endVertexID, 0, maxWeight, visited, foundLongest, G, path);

    if (!foundLongest) {
        cout << "Tidak ada rute terlama ditemukan antara " << startVertexID << " dan " << endVertexID << endl;
    }
}

int totalHarga(Graph G, char startVertexID, char endVertexID) {
    Vertex* startVertex = findVertex(G, startVertexID);
    Vertex* endVertex = findVertex(G, endVertexID);

    if (startVertex == nullptr || endVertex == nullptr) {
        cout << "Vertex tidak ditemukan!" << endl;
        return -1; // Mengembalikan nilai error jika vertex tidak ditemukan
    }

    bool visited[26] = {false}; // Mengasumsikan hanya menggunakan huruf besar A-Z
    int totalWeight = -1; // Untuk menyimpan total bobot dari jalur yang ditemukan

    // Fungsi DFS untuk menghitung total bobot
    dfsTotalHarga(startVertex, endVertexID, 0, visited, totalWeight, G);

    return totalWeight;
}

// Fungsi DFS untuk menghitung total bobot dari jalur yang ditemukan
void dfsTotalHarga(Vertex* current, char endVertexID, int currentWeight, bool visited[], int &totalWeight, Graph G) {
    if (idVertex(current) == endVertexID) {
        totalWeight = currentWeight;  // Menyimpan bobot jalur yang ditemukan
        return;
    }

    visited[current->idVertex - 'A'] = true;

    Edge* edge = firstEdge(current);
    while (edge != nullptr) {
        Vertex* nextVertex = findVertex(G, edge->destVertexID);
        if (nextVertex != nullptr && !visited[nextVertex->idVertex - 'A']) {
            dfsTotalHarga(nextVertex, endVertexID, currentWeight + edge->weight, visited, totalWeight, G);
            // Jika jalur ditemukan, berhenti
            if (totalWeight != -1) {
                return;
            }
        }
        edge = edge->nextEdge;
    }

    visited[current->idVertex - 'A'] = false; // Membatalkan penandaan vertex sebagai sudah dikunjungi
}


// Menampilkan menu
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
                DFS(G, startVertex, endVertex, true, true);  // Tampilkan rute tercepat dan terlama
                break;

            case 4:
                cout << "Total harga: " << totalHarga(G, startVertex, endVertex) << endl;
                break;

            case 5:
                removeEdge(G, startVertex, endVertex);
                break;

            case 6:
                // Tampilkan rute terjauh (bisa diimplementasikan dengan logika DFS khusus)
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
