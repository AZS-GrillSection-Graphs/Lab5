#ifndef GRAPHS5_FLOWNETWORK_H
#define GRAPHS5_FLOWNETWORK_H


#include "AdjList.h"

class FlowNetwork {
public:
    explicit FlowNetwork(const int layersNumber);
    void Draw() const;
    void Print() const;

private:

    void FillAdjList(const int layersNumber);
    void CreateConnections();
    void ConnectLesserBiggerLayers(int lesser, int bigger);
    void ConnectBiggerLesserLayers(int bigger, int lesser);
    void CreateRandomConnections(unsigned long connectionsNumber);

    void PrintBandwidthsToFile(const char * fileName) const;

    AdjList adjList;
    std::vector<std::vector<int>> layers;
    std::vector<std::vector<int>> bandwidths;

    bool AreVerticesConnected(int start, int end);

    void PrintBandwidths() const;
};

#endif //GRAPHS5_FLOWNETWORK_H
