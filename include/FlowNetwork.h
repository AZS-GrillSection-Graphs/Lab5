#ifndef GRAPHS5_FLOWNETWORK_H
#define GRAPHS5_FLOWNETWORK_H


#include "AdjList.h"
#include "AdjMatrix.h"

class FlowNetwork {
public:
    explicit FlowNetwork(const int layersNumber);
    void Draw() const;
    void Print() const;
    void FordFulkerson();

private:

    void FillAdjList(const int layersNumber);
    void CreateConnections();
    void ConnectLesserBiggerLayers(int lesser, int bigger);
    void ConnectBiggerLesserLayers(int bigger, int lesser);
    void CreateRandomConnections(unsigned long connectionsNumber);
    bool BFS(AdjMatrix & residualGraph, unsigned int path[]);

    void PrintCapacityToFile(const char *fileName) const;
    void ConvertCapacityToMatrix(std::vector<std::vector<int>> & residualCapacity);

    AdjList adjList;
    AdjMatrix adjMatrix;
    unsigned int vertices;
    std::vector<std::vector<int>> layers;
    std::vector<std::vector<int>> capacity;

    bool AreVerticesConnected(int start, int end);

    void PrintCapacity() const;
};

#endif //GRAPHS5_FLOWNETWORK_H
