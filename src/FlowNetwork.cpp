#include "FlowNetwork.h"
#include <iostream>
#include <GraphException.h>
#include <algorithm>
#include <fstream>


int iRand(const int min, const int max)
{
    return rand() % max + min;
}

FlowNetwork::FlowNetwork(const int layersNumber) {
    try
    {
        if(layersNumber < 2)
            throw(GraphException("Flow network cannot has less than 2 layers."));
    }
    catch(GraphException & er)
    {
        std::cerr << er.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Random Flow network with " << layersNumber << " layers." << std::endl << std::endl;

    FillAdjList(layersNumber);
    CreateConnections();
}

void FlowNetwork::FillAdjList(const int layersNumber) {
    // Adding the source
    layers.emplace_back(std::vector<int>());
    adjList.GetAdjList().emplace_back(std::vector<int>());
    layers[0].emplace_back(0);
    bandwidths.emplace_back(std::vector<int>());

    for(int i=1; i<=layersNumber; ++i) {
        int verticesInLayer = iRand(2, layersNumber);

        layers.emplace_back(std::vector<int>(verticesInLayer));

        for(int j=0; j<verticesInLayer; ++j) {
            adjList.GetAdjList().emplace_back(std::vector<int>());
            bandwidths.emplace_back(std::vector<int>());
            layers[i][j] = adjList.NumOfVertices()-1;
        }
    }

    // Adding the sink
    layers.emplace_back(std::vector<int>());
    adjList.GetAdjList().emplace_back(std::vector<int>());
    bandwidths.emplace_back(std::vector<int>());
    (layers.end()-1)->emplace_back(adjList.NumOfVertices()-1);

    std::cout << "Węzły w kolejnych warstwach:\n";
    for(std::vector<int> layer : layers) {
        for (int vertex : layer)
            std::cout << vertex + 1<< " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void FlowNetwork::CreateConnections() {
    for(int layer=0; layer<layers.size()-1; ++layer) {
        if(layers[layer].size() < layers[layer+1].size())
            ConnectLesserBiggerLayers(layer, layer+1);
        else
            ConnectBiggerLesserLayers(layer, layer+1);
    }

    CreateRandomConnections(2*(layers.size()-2)); // layers has size N+2, including 0 and N+1 layer
}

void FlowNetwork::ConnectLesserBiggerLayers(int lesser, int bigger) {
    const int biggerLayerSize = layers[bigger].size();
    const int lesserLayerSize = layers[lesser].size();

    for(int i=0; i<biggerLayerSize; ++i) {
        int edgeStart = layers[lesser][i%lesserLayerSize];
        adjList[edgeStart].emplace_back(layers[bigger][i]);

        bandwidths[edgeStart].emplace_back(iRand(1, 10));
    }
}

void FlowNetwork::ConnectBiggerLesserLayers(int bigger, int lesser) {
    const int biggerLayerSize = layers[bigger].size();
    const int lesserLayerSize = layers[lesser].size();

    for(int i=0; i<biggerLayerSize; ++i) {
        int edgeEnd = layers[lesser][i%lesserLayerSize];
        adjList[layers[bigger][i]].emplace_back(edgeEnd);

        bandwidths[layers[bigger][i]].emplace_back(iRand(1, 10));
    }
}

void FlowNetwork::CreateRandomConnections(unsigned long connectionsNumber) {
    int edgeStart;
    int edgeEnd;

    for(int i=0; i<connectionsNumber; ++i) {
        do {
            edgeStart = iRand(0, adjList.NumOfVertices()-2); // without the sink

            do {
                edgeEnd = iRand(1, adjList.NumOfVertices()-1); // without the source
            }while(edgeStart == edgeEnd);

        }while(AreVerticesConnected(edgeStart, edgeEnd));

        adjList[edgeStart].emplace_back(edgeEnd);
        bandwidths[edgeStart].emplace_back(iRand(1, 10));
    }
}

bool FlowNetwork::AreVerticesConnected(int start, int end) {
    return std::find(adjList[start].begin(), adjList[start].end(), end) != adjList[start].end();
}

void FlowNetwork::Draw() const {
    IncMatrix incMatrix = adjList.ConvertToIncMatrix();
    incMatrix.PrintToFile();
    PrintBandwidthsToFile("Wagi.txt");

    std::string command = "python3 ../FlowNetworksVisualization.py MacierzIncydencji.txt Wagi.txt";
    system(command.c_str());
}

void FlowNetwork::Print() const {
    adjList.Print();
    PrintBandwidths();
}

void FlowNetwork::PrintBandwidths() const {
    std::cout << "Bandwidths in corresponding connection\n\n";
    for(std::vector<int> vertexBandwiths : bandwidths) {
        for(int bandwidth : vertexBandwiths)
            std::cout << bandwidth << " ";
        std::cout << std::endl;
    }
}

void FlowNetwork::PrintBandwidthsToFile(const char * fileName) const
{
    std::ofstream bandwidthsFile;

    if (!bandwidthsFile.is_open())
    {
        bandwidthsFile.open(fileName, std::ios::out);
        if(!bandwidthsFile)
        {
            std::cerr << "Failed to open " << fileName << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    for(auto & row : bandwidths)
    {
        for(auto & item : row)
        {
            bandwidthsFile << item << std::endl;
        }
    }

    bandwidthsFile.close();
}
