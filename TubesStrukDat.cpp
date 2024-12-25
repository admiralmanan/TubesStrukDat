#include "TubesStrukDat.h"

void createVertex(char newVertexID, adrVertex &v) {
    v = new Vertex;
    idVertex(v) = newVertexID;
    nextVertex(v) = nullptr;
    firstEdge(v) = nullptr;
}

void initGraph(Graph &G) {
    firstVertex(G) = nullptr;
}

void addVertex(Graph &G, char newVertexID) {
    adrVertex newVertex;
    createVertex(newVertexID, newVertex);

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

adrVertex findVertex(Graph G, char id) {
    adrVertex temp = firstVertex(G);
    while (temp != nullptr) {
        if (idVertex(temp) == id) {
            return temp;
        }
        temp = nextVertex(temp);
    }
    return nullptr;
}

void addEdge(Graph &G, char fromID, char toID, int weight) {
    adrVertex fromVertex = findVertex(G, fromID);
    adrVertex toVertex = findVertex(G, toID);

    if (fromVertex != nullptr && toVertex != nullptr) {
        adrEdge newEdge = new Edge;
        newEdge->destVertexID = toID;
        newEdge->weight = weight;
        newEdge->nextEdge = firstEdge(fromVertex);
        firstEdge(fromVertex) = newEdge;

        adrEdge reverseEdge = new Edge;
        reverseEdge->destVertexID = fromID;
        reverseEdge->weight = weight;
        reverseEdge->nextEdge = firstEdge(toVertex);
        firstEdge(toVertex) = reverseEdge;
    } else {
        cout << "Vertex tidak ditemukan: " << fromID << " atau " << toID << endl;
    }
}

void removeEdge(Graph &G, char fromID, char toID) {
    adrVertex fromVertex = findVertex(G, fromID);
    adrVertex toVertex = findVertex(G, toID);

    if (fromVertex != nullptr && toVertex != nullptr) {
        // Hapus edge dari fromID ke toID
        adrEdge prev = nullptr, current = firstEdge(fromVertex);
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

        // Hapus edge dari toID ke fromID
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

void printGraph(Graph G) {
    adrVertex v = firstVertex(G);
    while (v != nullptr) {
        cout << "Vertex " << idVertex(v) << ": ";
        adrEdge e = firstEdge(v);
        while (e != nullptr) {
            cout << "-> " << e->destVertexID << "(" << e->weight << ") ";
            e = e->nextEdge;
        }
        cout << endl;
        v = nextVertex(v);
    }
}

void DFSUtil(adrVertex currentVertex, char endVertexID, unordered_map<char, bool> &visited,
             vector<char> &currentPath, vector<char> &shortestPath, int currentWeight,
             int &minWeight, Graph G) {
    // Tandai vertex ini sebagai dikunjungi
    visited[idVertex(currentVertex)] = true;
    currentPath.push_back(idVertex(currentVertex));

    // Jika mencapai tujuan, periksa apakah jalur ini lebih pendek
    if (idVertex(currentVertex) == endVertexID) {
        if (currentWeight < minWeight) {
            minWeight = currentWeight;
            shortestPath = currentPath; // Perbarui jalur terpendek
        }
    } else {
        // Telusuri semua tetangga
        adrEdge edge = firstEdge(currentVertex);
        while (edge != nullptr) {
            char nextVertexID = edge->destVertexID;
            if (!visited[nextVertexID]) {
                DFSUtil(findVertex(G, nextVertexID), endVertexID, visited, currentPath, shortestPath,
                        currentWeight + edge->weight, minWeight, G);
            }
            edge = edge->nextEdge;
        }
    }

    // Backtracking
    visited[idVertex(currentVertex)] = false;
    currentPath.pop_back();
}

void DFS(Graph G, char startVertexID, char endVertexID) {
    adrVertex startVertex = findVertex(G, startVertexID);
    adrVertex endVertex = findVertex(G, endVertexID);

    if (startVertex == nullptr || endVertex == nullptr) {
        cout << "Salah satu atau kedua vertex tidak ditemukan." << endl;
        return;
    }

    // Variabel untuk DFS
    unordered_map<char, bool> visited;
    vector<char> currentPath;
    vector<char> shortestPath;
    int minWeight = INT_MAX;

    // Inisialisasi visited
    for (adrVertex v = firstVertex(G); v != nullptr; v = nextVertex(v)) {
        visited[idVertex(v)] = false;
    }

    // Mulai DFS
    DFSUtil(startVertex, endVertexID, visited, currentPath, shortestPath, 0, minWeight, G);

    // Tampilkan hasil
    if (!shortestPath.empty()) {
        cout << "Jalur tercepaT: ";
        for (char vertex : shortestPath) {
            cout << vertex << " ";
        }
        cout << "\nTotal bobot: " << minWeight << endl;
    } else {
        cout << "Tidak ada jalur dari " << startVertexID << " ke " << endVertexID << endl;
    }
}

void DFSLongestUtil(adrVertex currentVertex, char endVertexID, unordered_map<char, bool> &visited,
                    vector<char> &currentPath, vector<char> &longestPath, int currentWeight,
                    int &maxWeight, Graph G) {
    // Tandai vertex sebagai dikunjungi
    visited[idVertex(currentVertex)] = true;
    currentPath.push_back(idVertex(currentVertex));

    // Jika mencapai tujuan, periksa apakah jalur ini memiliki bobot terbesar
    if (idVertex(currentVertex) == endVertexID) {
        if (currentWeight > maxWeight) {
            maxWeight = currentWeight;
            longestPath = currentPath; // Perbarui jalur terlama
        }
    } else {
        // Telusuri semua tetangga
        adrEdge edge = firstEdge(currentVertex);
        while (edge != nullptr) {
            char nextVertexID = edge->destVertexID;
            if (!visited[nextVertexID]) {
                DFSLongestUtil(findVertex(G, nextVertexID), endVertexID, visited, currentPath, longestPath,
                               currentWeight + edge->weight, maxWeight, G);
            }
            edge = edge->nextEdge;
        }
    }

    // Backtracking
    visited[idVertex(currentVertex)] = false;
    currentPath.pop_back();
}

void DFSLongest(Graph G, char startVertexID, char endVertexID) {
    adrVertex startVertex = findVertex(G, startVertexID);
    adrVertex endVertex = findVertex(G, endVertexID);

    if (startVertex == nullptr || endVertex == nullptr) {
        cout << "Salah satu atau kedua vertex tidak ditemukan." << endl;
        return;
    }

    // Variabel untuk DFS
    unordered_map<char, bool> visited;
    vector<char> currentPath;
    vector<char> longestPath;
    int maxWeight = INT_MIN;

    // Inisialisasi visited
    for (adrVertex v = firstVertex(G); v != nullptr; v = nextVertex(v)) {
        visited[idVertex(v)] = false;
    }

    // Mulai DFSLongest
    DFSLongestUtil(startVertex, endVertexID, visited, currentPath, longestPath, 0, maxWeight, G);

    // Tampilkan hasil
    if (!longestPath.empty()) {
        cout << "Rute Terlama: ";
        for (char vertex : longestPath) {
            cout << vertex << " ";
        }
        cout << "\nTotal bobot: " << maxWeight << endl;
    } else {
        cout << "Tidak ada jalur dari " << startVertexID << " ke " << endVertexID << endl;
    }
}

int totalHarga(Graph G, char startVertexID, char endVertexID) {
    adrVertex startVertex = findVertex(G, startVertexID);
    if (startVertex == nullptr) {
        cout << "Vertex awal tidak ditemukan: " << startVertexID << endl;
        return -1;
    }

    adrEdge edge = firstEdge(startVertex);
    while (edge != nullptr) {
        if (edge->destVertexID == endVertexID) {
            return edge->weight * 2000; // Bobot dikalikan harga per menit
        }
        edge = edge->nextEdge;
    }

    cout << "Edge dari " << startVertexID << " ke " << endVertexID << " tidak ditemukan.\n";
    return -1;
}
void DFSTerjauh(Graph G, char startVertexID, char endVertexID) {
    adrVertex startVertex = findVertex(G, startVertexID);
    adrVertex endVertex = findVertex(G, endVertexID);

    if (startVertex == nullptr || endVertex == nullptr) {
        cout << "Salah satu atau kedua vertex tidak ditemukan.\n";
        return;
    }

    // Variabel untuk DFS
    unordered_map<char, bool> visited;
    vector<char> currentPath;
    vector<char> longestPath;
    int maxWeight = INT_MIN;

    // Inisialisasi visited
    for (adrVertex v = firstVertex(G); v != nullptr; v = nextVertex(v)) {
        visited[idVertex(v)] = false;
    }

    // Mulai pencarian jalur terjauh
    DFSLongestUtil(startVertex, endVertexID, visited, currentPath, longestPath, 0, maxWeight, G);

    // Tampilkan hasil
    if (!longestPath.empty()) {
        cout << "Rute Terjauh: ";
        for (char vertex : longestPath) {
            cout << vertex << " ";
        }
        cout << "\nTotal bobot (menit): " << maxWeight << endl;
    } else {
        cout << "Tidak ada jalur dari " << startVertexID << " ke " << endVertexID << endl;
    }
}



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
                DFSLongest(G, startVertex, endVertex);
                break;

            case 4: {
                int menit;
                cout << "Masukkan waktu perjalanan (menit): ";
                cin >> menit;
                int harga = totalHarga(G, startVertex, endVertex, menit);
                if (harga != -1) {
                    cout << "Total harga perjalanan: " << harga << endl;
                }
                break;
            }

            case 5: {
                char fromID, toID;
                cout << "Masukkan titik awal jalur yang akan dihapus: ";
                cin >> fromID;
                cout << "Masukkan titik tujuan jalur yang akan dihapus: ";
                cin >> toID;
                removeEdge(G, fromID, toID);
                break;
            }

            case 6:
                DFSTerjauh(G, startVertex, endVertex);
                break;

            case 7:
                cout << "Keluar dari program. Terima kasih!\n";
                jalan = false;
                break;

            default:
                cout << "Pilihan tidak valid. Coba lagi.\n";
                break;
        }

        cout << endl;
    }
}
