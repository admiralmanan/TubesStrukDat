#include "tGraph.h"

void initGraph(Graph &G) {
    G.firstVertex = nullptr;
}

void addVertex(Graph &G, string newVertexID) {
    adrVertex newVertex = new Vertex;
    newVertex->idVertex = newVertexID;
    newVertex->nextVertex = nullptr;
    newVertex->firstEdge = nullptr;

    if (G.firstVertex == nullptr) {
        G.firstVertex = newVertex;
    } else {
        adrVertex temp = G.firstVertex;
        while (temp->nextVertex != nullptr) {
            temp = temp->nextVertex;
        }
        temp->nextVertex = newVertex;
    }
}

adrVertex findVertex(Graph G, string id) {
    adrVertex temp = G.firstVertex;
    while (temp != nullptr) {
        if (temp->idVertex == id) {
            return temp;
        }
        temp = temp->nextVertex;
    }
    return nullptr;
}

void addEdge(Graph &G, string fromID, string toID, int weight) {
    adrVertex fromVertex = findVertex(G, fromID);
    adrVertex toVertex = findVertex(G, toID);

    if (fromVertex != nullptr && toVertex != nullptr) {
        
        adrEdge newEdge = new Edge;
        newEdge->destVertexID = toID;
        newEdge->weight = weight;
        newEdge->nextEdge = fromVertex->firstEdge;
        fromVertex->firstEdge = newEdge;

        adrEdge reverseEdge = new Edge;
        reverseEdge->destVertexID = fromID;
        reverseEdge->weight = weight;
        reverseEdge->nextEdge = toVertex->firstEdge;
        toVertex->firstEdge = reverseEdge;
    }
}

void removeEdge(Graph &G, string fromVertexID, string toVertexID) {
    adrVertex fromVertex = findVertex(G, fromVertexID);
    adrVertex toVertex = findVertex(G, toVertexID);

    if (fromVertex == nullptr || toVertex == nullptr) {
        // Jika salah satu vertex tidak ditemukan, tampilkan pesan yang sesuai
        cout << "Tidak ada rute dari Gedung " << fromVertexID << " ke Gedung " << toVertexID << endl;
        return;  // Hentikan eksekusi fungsi
    }

    // Cek apakah ada edge yang menghubungkan fromVertex ke toVertex
    adrEdge edge = fromVertex->firstEdge;
    bool foundEdge = false;  // Flag untuk mengecek apakah edge ditemukan
    adrEdge prev = nullptr;

    while (edge != nullptr) {
        if (edge->destVertexID == toVertexID) {
            foundEdge = true;  // Tandai bahwa edge ditemukan
            if (prev == nullptr) {
                fromVertex->firstEdge = edge->nextEdge;  // Hapus edge pertama
            } else {
                prev->nextEdge = edge->nextEdge;  // Hapus edge setelahnya
            }
            delete edge;
            break;
        }
        prev = edge;
        edge = edge->nextEdge;
    }

    // Jika tidak ada edge yang ditemukan, tampilkan pesan bahwa tidak ada rute
    if (!foundEdge) {
        cout << "Tidak ada rute dari Gedung " << fromVertexID << " ke Gedung " << toVertexID << endl;
        return;  // Hentikan eksekusi fungsi
    }

    // Jika Anda ingin menghapus juga edge sebaliknya (untuk graf tidak berarah)
    edge = toVertex->firstEdge;
    prev = nullptr;
    while (edge != nullptr) {
        if (edge->destVertexID == fromVertexID) {
            if (prev == nullptr) {
                toVertex->firstEdge = edge->nextEdge;  // Hapus edge pertama
            } else {
                prev->nextEdge = edge->nextEdge;  // Hapus edge setelahnya
            }
            delete edge;
            break;
        }
        prev = edge;
        edge = edge->nextEdge;
    }

    cout << "Rute antara " << fromVertexID << " dan " << toVertexID << " telah dihapus." << endl;
}




void printGraph(Graph G) {
    adrVertex temp = G.firstVertex;
    while (temp != nullptr) {
        cout << temp->idVertex << ": ";
        
        bool firstEdge = true;

        adrEdge edge = temp->firstEdge;
        while (edge != nullptr) {
            // Cek apakah ini edge pertama yang akan dicetak, agar formatnya sesuai
            if (!firstEdge) {
                cout << ", ";
            }
            cout << edge->destVertexID << " | Waktu: " << edge->weight << " Menit";
            firstEdge = false;
            edge = edge->nextEdge;
        }
        cout << endl;
        temp = temp->nextVertex;
    }
}


void ruteTerecepat(Graph G, string startVertexID, string endVertexID) {
    if (startVertexID == endVertexID) {
        cout << "Tidak ada rute di gedung yang sama." << endl;
        return; // Hentikan eksekusi fungsi jika titik awal dan tujuan sama
    }

    const int MAX_VERTEX = 100;
    string vertices[MAX_VERTEX];
    int distances[MAX_VERTEX];
    string predecessors[MAX_VERTEX];
    bool visited[MAX_VERTEX] = {false};
    int vertexCount = 0;

    // Menyusun daftar semua vertex dalam graph
    adrVertex v = G.firstVertex;
    while (v != nullptr) {
        vertices[vertexCount] = v->idVertex;
        distances[vertexCount] = -1; // Inisialisasi jarak
        predecessors[vertexCount] = "";
        vertexCount++;
        v = v->nextVertex;
    }

    // Temukan indeks dari startVertexID
    int startIndex = -1;
    for (int i = 0; i < vertexCount; i++) {
        if (vertices[i] == startVertexID) {
            startIndex = i;
            break;
        }
    }

    // Jika titik awal tidak ditemukan, beri pesan error
    if (startIndex == -1) {
        cout << "Titik awal tidak ditemukan!" << endl;
        return;
    }

    // Set jarak awal dari startVertexID ke 0
    distances[startIndex] = 0;

    // Proses Dijkstra untuk mencari jarak terpendek
    for (int count = 0; count < vertexCount; count++) {
        int minIndex = -1;
        for (int i = 0; i < vertexCount; i++) {
            if (!visited[i] && distances[i] != -1 &&
                (minIndex == -1 || distances[i] < distances[minIndex])) {
                minIndex = i;
            }
        }

        if (minIndex == -1) break; // Tidak ada jalur lagi
        visited[minIndex] = true;

        adrVertex current = findVertex(G, vertices[minIndex]);
        adrEdge edge = current->firstEdge;
        while (edge != nullptr) {
            // Menemukan indeks vertex tujuan dari edge yang sedang diproses
            for (int i = 0; i < vertexCount; i++) {
                if (vertices[i] == edge->destVertexID) {
                    int newDist = distances[minIndex] + edge->weight;
                    if (distances[i] == -1 || newDist < distances[i]) {
                        distances[i] = newDist;
                        predecessors[i] = vertices[minIndex];
                    }
                }
            }
            edge = edge->nextEdge;
        }
    }

    // Menyusun hasil akhir untuk titik tujuan
    int endIndex = -1;
    for (int i = 0; i < vertexCount; i++) {
        if (vertices[i] == endVertexID) {
            endIndex = i;
            break;
        }
    }

    if (endIndex == -1 || distances[endIndex] == -1) {
        cout << "Tidak ada jalur dari " << startVertexID << " ke " << endVertexID << endl;
    } else {
        cout << "Waktu Tempuh: " << distances[endIndex] << " Menit" << endl;
        string path = endVertexID;
        while (predecessors[endIndex] != "") {
            path = predecessors[endIndex] + " -> " + path;
            for (int i = 0; i < vertexCount; i++) {
                if (vertices[i] == predecessors[endIndex]) {
                    endIndex = i;
                    break;
                }
            }
        }
        cout << "Jalur: " << path << endl;
    }
}


int totalHarga(Graph G, string startVertexID, string endVertexID) {
    const int MAX_VERTEX = 100;
    string vertices[MAX_VERTEX];
    int distances[MAX_VERTEX];
    string predecessors[MAX_VERTEX];
    bool visited[MAX_VERTEX] = {false};
    int vertexCount = 0;

    adrVertex v = G.firstVertex;
    while (v != nullptr) {
        vertices[vertexCount] = v->idVertex;
        distances[vertexCount] = -1; // Inisialisasi jarak
        predecessors[vertexCount] = "";
        vertexCount++;
        v = v->nextVertex;
    }

    // Temukan indeks titik awal (startVertexID)
    int startIndex = -1;
    for (int i = 0; i < vertexCount; i++) {
        if (vertices[i] == startVertexID) {
            startIndex = i;
            break;
        }
    }

    if (startIndex == -1) {
        cout << "Titik awal tidak ditemukan" << endl;
        return -1;  // Jika titik awal tidak ditemukan
    }

    distances[startIndex] = 0; // Set jarak awal ke 0 untuk titik awal

    // Algoritma Dijkstra
    for (int count = 0; count < vertexCount; count++) {
        int minIndex = -1;
        for (int i = 0; i < vertexCount; i++) {
            if (!visited[i] && distances[i] != -1 &&
                (minIndex == -1 || distances[i] < distances[minIndex])) {
                minIndex = i;
            }
        }

        if (minIndex == -1) break; // Tidak ada jalur lagi
        visited[minIndex] = true;

        adrVertex current = findVertex(G, vertices[minIndex]);
        adrEdge edge = current->firstEdge;
        while (edge != nullptr) {
            for (int i = 0; i < vertexCount; i++) {
                if (vertices[i] == edge->destVertexID) {
                    int newDist = distances[minIndex] + edge->weight;
                    if (distances[i] == -1 || newDist < distances[i]) {
                        distances[i] = newDist;
                        predecessors[i] = vertices[minIndex];
                    }
                }
            }
            edge = edge->nextEdge;
        }
    }

    // Menentukan index vertex tujuan (endVertexID)
    int endIndex = -1;
    for (int i = 0; i < vertexCount; i++) {
        if (vertices[i] == endVertexID) {
            endIndex = i;
            break;
        }
    }

    // Cek apakah ada jalur ke vertex tujuan
    if (endIndex != -1 && distances[endIndex] != -1) {
        return distances[endIndex] * 1000;  // Kembalikan total harga
    } else {
        cout << "Tidak ada jalur ke " << endVertexID << endl;
        return -1;  // Tidak ada jalur atau vertex tujuan tidak ditemukan
    }
}


void tambahRute(Graph &G) {
    string newVertexID, connectedVertexID;
    int weight;

    // vertex baru
    cout << "Masukkan Gedung baru: ";
    cin >> newVertexID;

    // Periksa apakah vertex sudah ada
    adrVertex existingVertex = findVertex(G, newVertexID);
    if (existingVertex != nullptr) {
        cout << "Gedung " << newVertexID << " sudah ada.\n";
        return;  // Jika sudah ada, tidak lanjutkan menambahkan vertex baru
    }

    // Tambahkan vertex baru ke dalam graph
    addVertex(G, newVertexID);
    cout << "Gedung " << newVertexID << " telah ditambahkan." << endl;

    // pilihan apakah ingin menyambungkan vertex baru ke vertex lain
    cout << "Apakah Anda ingin menyambungkan gedung baru ke gedung lain?(ya/nanti): ";
    string choice;
    cin >> choice;

    if (choice == "ya") {
        cout << "Masukkan ID gedung yang akan disambungkan ke " << newVertexID << ": ";
        cin >> connectedVertexID;

        // cek apakah vertex yang ingin disambungkan ada
        adrVertex connectedVertex = findVertex(G, connectedVertexID);
        if (connectedVertex != nullptr) {
            // Masukkan edge yang menghubungkan kedua vertex
            cout << "Masukkan jarak waktu yang menghubungkan: "
                 << newVertexID << " ke " << connectedVertexID << ": ";
            cin >> weight;

            // Tambahkan edge yang menghubungkan kedua vertex
            addEdge(G, newVertexID, connectedVertexID, weight);
            cout << "rute antara " << newVertexID << " dan " << connectedVertexID
                 << " dengan waktu " << weight << " telah ditambahkan." << endl;
        } else {
            cout << "Gedung tujuan tidak ditemukan.\n";
        }
    } else if (choice == "nanti"){
        // Jika tidak menambahkan edge, beri pilihan untuk menambahkannya nanti
        cout << "Anda telah menambahkan Gedung " << newVertexID << " tanpa menyambungkannya.\n";
        cout << "Anda dapat menambahkan sambungan (edge) di menu berikutnya.\n";
    }else{
        cout << "Anda tidak memasukkan pilihan dengan benar";
        return;
    }
}

void tujuan(Graph &G, string &startVertex, string &endVertex) {
    cout << "\nMasukkan posisi awal (misal: Gedung_A): ";
    cin >> startVertex;
    cout << "Masukkan posisi tujuan (misal: Gedung_B): ";
    cin >> endVertex;
    
    // kondisi jika titik awal dan titik tujuan sama
    if (startVertex == endVertex) {
        cout << "Titik awal dan titik tujuan sama. Silakan masukkan gedung yang berbeda.\n";
        return; // Menghentikan proses jika titik awal dan tujuan sama
    }
    
    // kondisi jika vertex awal dan tujuan ada di graph
    adrVertex startVertexFound = findVertex(G, startVertex);
    adrVertex endVertexFound = findVertex(G, endVertex);
    
    if (startVertexFound == nullptr || endVertexFound == nullptr) {
        cout << "Tidak ada gedung tersebut dalam map.\n";
        return; // Menghentikan proses jika salah satu atau keduanya tidak ditemukan
    }
    
    // kondisi apakah ada jalur yang menghubungkan startVertex dan endVertex
    adrEdge edge = startVertexFound->firstEdge;
    bool edgeExists = false;
    while (edge != nullptr) {
        if (edge->destVertexID == endVertex) {
            edgeExists = true; // Jika ditemukan edge yang menghubungkan
            break;
        }
        edge = edge->nextEdge;
    }
    
        cout << "Titik awal dan titik tujuan telah diterima: " << startVertex << " ke " << endVertex << endl;

}

void tampilkanMenu(Graph &G) {
    string startVertex, endVertex;
    bool jalan = true;
    
    while (jalan) {
        cout << "-------- SELAMAT DATANG DI BEAM --------" << endl;
        cout << "1. Lihat Map" << endl;
        cout << "2. Masukkan Titik Awal dan Tujuan" << endl;
        cout << "3. Tampilkan Rute Tercepat" << endl;
        cout << "4. Tampilkan Harga" << endl;
        cout << "5. Tutup Jalur" << endl;
        cout << "6. Tambah Gedung & Sambungkan Rute" << endl;
        cout << "7. Sambungkan Gedung yang Sudah Ada" << endl;  // Opsi baru
        cout << "8. Keluar" << endl;
        cout << "Masukkan pilihan: ";

        int pilihan;
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "\nMenampilkan peta koneksi antar gedung:\n";
                printGraph(G);
                break;

            case 2:
                tujuan(G, startVertex, endVertex); // Panggil fungsi untuk input titik awal dan tujuan
                break;

            case 3:
                if (!startVertex.empty() && !endVertex.empty()) {
                    cout << "\nMenampilkan rute tercepat dari " << startVertex << " ke " << endVertex << ":\n";
                    ruteTerecepat(G, startVertex, endVertex); // Menampilkan rute tercepat
                } else {
                    cout << "\nSilakan masukkan titik awal dan tujuan terlebih dahulu.\n";
                }
                break;

            case 4:
                if (!startVertex.empty() && !endVertex.empty()) {
                    cout << "\nMenampilkan biaya total perjalanan:\n";
                    int harga = totalHarga(G, startVertex, endVertex); // Menampilkan biaya total
                    if (harga != -1) {
                        cout << "Estimasi Harga perjalanan dari " << startVertex
                             << " ke " << endVertex << ": Rp " << harga << endl;
                    } else {
                        cout << "Tidak dapat menghitung harga\n";
                    }
                } else {
                    cout << "\nSilakan masukkan titik awal dan tujuan terlebih dahulu.\n";
                }
                break;

            case 5: {
                string fromID, toID;
                cout << "\nMasukkan titik awal jalur yang akan dihapus: ";
                cin >> fromID;
                cout << "Masukkan titik tujuan jalur yang akan dihapus: ";
                cin >> toID;
                removeEdge(G, fromID, toID);
                break;
            }

            case 6:
                tambahRute(G);  // Fungsi untuk menambah gedung dan rute
                break;

            case 7: {
                string newVertexID, connectedVertexID;
                int weight;

                cout << "Masukkan Gedung yang ingin disambungkan: ";
                cin >> newVertexID;

                // Cek apakah gedung ada di graph
                adrVertex existingVertex = findVertex(G, newVertexID);
                if (existingVertex == nullptr) {
                    cout << "Gedung " << newVertexID << " tidak ditemukan.\n";
                } else {
                    // Masukkan vertex yang akan disambungkan
                    cout << "Masukkan ID gedung yang akan disambungkan ke " << newVertexID << ": ";
                    cin >> connectedVertexID;

                    adrVertex connectedVertex = findVertex(G, connectedVertexID);
                    if (connectedVertex != nullptr) {
                        cout << "Masukkan waktu tempu: ";
                        cin >> weight;
                        while (weight < 0) {
                            cin >> weight;
                        }

                        // Tambahkan edge
                        addEdge(G, newVertexID, connectedVertexID, weight);
                        cout << "Edge antara " << newVertexID << " dan " << connectedVertexID << " telah ditambahkan.\n";
                    } else {
                        cout << "Gedung tujuan tidak ditemukan.\n";
                    }
                }
                break;
            }

            case 8:
                cout << "\nKeluar dari program. Terima kasih telah menggunakan program ini!\n";
                jalan = false;
                break;

            default:
                cout << "\nPilihan tidak valid. Silakan coba lagi.\n";
                break;
        }
        cout << endl;
    }
}
