#include "FlowNetwork.h"
#include <iostream>
#include <GraphException.h>
#include <algorithm>
#include <fstream>
#include <queue>
#include <climits>


int iRand(const int min, const int max) {
    return rand() % max + min;
}

FlowNetwork::FlowNetwork(const int layersNumber) {
    try {
        if ( layersNumber < 2 )
            throw ( GraphException("Flow network cannot has less than 2 layers."));
    }
    catch (GraphException &er) {
        std::cerr << er.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Random Flow network with " << layersNumber << " layers." << std::endl << std::endl;

    FillAdjList(layersNumber);
    CreateConnections();
    adjMatrix.ConvertFromAdjList(adjList.GetAdjList());
    vertices = adjList.NumOfVertices();
}

void FlowNetwork::FillAdjList(const int layersNumber) {
    // Adding the source
    layers.emplace_back(std::vector<int>());
    adjList.GetAdjList().emplace_back(std::vector<int>());
    layers[0].emplace_back(0);
    capacity.emplace_back(std::vector<int>());

    for (int i = 1; i <= layersNumber; ++i) {
        int verticesInLayer = iRand(2, layersNumber);

        layers.emplace_back(std::vector<int>(verticesInLayer));

        for (int j = 0; j < verticesInLayer; ++j) {
            adjList.GetAdjList().emplace_back(std::vector<int>());
            capacity.emplace_back(std::vector<int>());
            layers[i][j] = adjList.NumOfVertices() - 1;
        }
    }

    // Adding the sink
    layers.emplace_back(std::vector<int>());
    adjList.GetAdjList().emplace_back(std::vector<int>());
    capacity.emplace_back(std::vector<int>());
    ( layers.end() - 1 )->emplace_back(adjList.NumOfVertices() - 1);

    std::cout << "Nodes in alternating layers:\n";
    for (std::vector<int> layer : layers) {
        for (int vertex : layer)
            std::cout << vertex + 1 << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void FlowNetwork::CreateConnections() {
    for (int layer = 0; layer < layers.size() - 1; ++layer) {
        if ( layers[layer].size() < layers[layer + 1].size())
            ConnectLesserBiggerLayers(layer, layer + 1);
        else
            ConnectBiggerLesserLayers(layer, layer + 1);
    }

    CreateRandomConnections(2 * ( layers.size() - 2 )); // layers has size N+2, including 0 and N+1 layer
}

void FlowNetwork::ConnectLesserBiggerLayers(int lesser, int bigger) {
    const int biggerLayerSize = layers[bigger].size();
    const int lesserLayerSize = layers[lesser].size();

    for (int i = 0; i < biggerLayerSize; ++i) {
        int edgeStart = layers[lesser][i % lesserLayerSize];
        adjList[edgeStart].emplace_back(layers[bigger][i]);
        std::sort(adjList[edgeStart].begin(), adjList[edgeStart].end());

        capacity[edgeStart].emplace_back(iRand(1, 10));
    }
}

void FlowNetwork::ConnectBiggerLesserLayers(int bigger, int lesser) {
    const int biggerLayerSize = layers[bigger].size();
    const int lesserLayerSize = layers[lesser].size();

    for (int i = 0; i < biggerLayerSize; ++i) {
        int edgeEnd = layers[lesser][i % lesserLayerSize];
        adjList[layers[bigger][i]].emplace_back(edgeEnd);
        std::sort(adjList[layers[bigger][i]].begin(), adjList[layers[bigger][i]].end());

        capacity[layers[bigger][i]].emplace_back(iRand(1, 10));
    }
}

void FlowNetwork::CreateRandomConnections(unsigned long connectionsNumber) {
    int edgeStart;
    int edgeEnd;

    for (int i = 0; i < connectionsNumber; ++i) {
        do {
            edgeStart = iRand(0, adjList.NumOfVertices() - 2); // without the sink

            do {
                edgeEnd = iRand(1, adjList.NumOfVertices() - 1); // without the source
            } while (edgeStart == edgeEnd);

        } while (AreVerticesConnected(edgeStart, edgeEnd));

        adjList[edgeStart].emplace_back(edgeEnd);
        std::sort(adjList[edgeStart].begin(), adjList[edgeStart].end());
        capacity[edgeStart].emplace_back(iRand(1, 10));
    }
}

bool FlowNetwork::AreVerticesConnected(int start, int end) {
    return std::find(adjList[start].begin(), adjList[start].end(), end) != adjList[start].end();
}

void FlowNetwork::Draw() const {
    IncMatrix incMatrix = adjList.ConvertToIncMatrix();
    incMatrix.PrintToFile();
    SaveCapacityToFile("Wagi.txt");
    SaveLayersToFile("Warstwy.txt");

    std::string command = "python3 ../FlowNetworksVisualization.py MacierzIncydencji.txt Wagi.txt Warstwy.txt";
    system(command.c_str());
}

void FlowNetwork::Print() const {
    adjList.Print();
    PrintCapacity();
}

void FlowNetwork::PrintCapacity() const {
    std::cout << "Capacities in corresponding connection:\n";
    for (std::vector<int> vertexCapacity : capacity) {
        for (int bandwidth : vertexCapacity)
            std::cout << bandwidth << " ";
        std::cout << std::endl;
    }
}

void FlowNetwork::SaveCapacityToFile(const char *fileName) const {
    std::ofstream capacityFile;

    if ( !capacityFile.is_open()) {
        capacityFile.open(fileName, std::ios::out);
        if ( !capacityFile ) {
            std::cerr << "Failed to open " << fileName << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    for (auto row : capacity) {
        //sort(row.begin(), row.end());
        for (auto &item : row) {
            capacityFile << item << std::endl;
        }
    }

    capacityFile.close();
}

void FlowNetwork::ConvertCapacityToMatrix(std::vector<std::vector<int>> &residualCapacity) {
    for (unsigned i = 0; i < capacity.size(); ++i) {
        for (unsigned j = 0; j < capacity[i].size(); ++j) {
            residualCapacity[i][adjList[i][j]] = capacity[i][j];
        }
    }
}

bool FlowNetwork::BFS(AdjMatrix &residualGraph, unsigned int path[]) {
    bool ifVisited[vertices]{true};
    std::queue<unsigned int> q;
    q.push(0);
    while (!q.empty()) {
        unsigned int i = q.front();
        q.pop();
        for (unsigned int j = 0; j < residualGraph.Size(); ++j) {
            if ( residualGraph[i][j] && !ifVisited[j] ) {
                q.push(j);
                path[j] = i;
                ifVisited[j] = true;
            }
        }
    }
    return ifVisited[vertices - 1];
}

void FlowNetwork::FordFulkerson() {
    //matrix containing current residual capacities
    std::vector<std::vector<int>> residualCapacity(vertices, std::vector<int>(vertices, 0));
    //residual graph initialized with values from original adjacency matrix
    AdjMatrix residualGraph = adjMatrix;
    //converting original capacity vector to matrix
    ConvertCapacityToMatrix(residualCapacity);

    unsigned int maxFlow = 0;
    unsigned int path[vertices]{0};

    while (BFS(residualGraph, path)) {
        int minResidualCapacity = INT_MAX;

        for (unsigned int i = vertices - 1; i != 0; i = path[i]) {
            int flow = residualCapacity[path[i]][i];
            minResidualCapacity = std::min(flow, minResidualCapacity);
        }

        for (unsigned int i = vertices - 1; i != 0; i = path[i]) {
            int flow = residualCapacity[path[i]][i] - minResidualCapacity;

            if ( flow == 0 ) {
                //deleting egde if maximal current flow is equal to capacity and updating residualCapacity matrix
                residualGraph[path[i]][i] = 0;
                residualCapacity[path[i]][i] -= minResidualCapacity;

                //adding reverse egde with value equals to minResidualCapacity
                residualGraph[i][path[i]] = 1;
                residualCapacity[i][path[i]] += minResidualCapacity;
            } else {
                //updating residualCapacity matrix
                residualCapacity[path[i]][i] -= minResidualCapacity;

                //adding reverse egde with value equals to minResidualCapacity
                residualGraph[i][path[i]] = 1;
                residualCapacity[i][path[i]] += minResidualCapacity;
            }
        }
        maxFlow += minResidualCapacity;
    }

    std::cout << std::endl << "Maximal flow: " << maxFlow << std::endl;
}

void FlowNetwork::SaveLayersToFile(const char *fileName) const {
    std::ofstream layersFile;

    if ( !layersFile.is_open()) {
        layersFile.open(fileName, std::ios::out);
        if ( !layersFile ) {
            std::cerr << "Failed to open " << fileName << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    for (auto &row : layers) {
            layersFile << row.size() << std::endl;
    }

    layersFile.close();
}
