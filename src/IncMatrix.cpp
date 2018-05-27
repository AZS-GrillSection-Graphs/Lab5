#include <vector>
#include <IncMatrix.h>
#include <iostream>
#include <iomanip>
#include <fstream>


IncMatrix::IncMatrix(const std::vector <std::vector<int>> incMatrix)
{
    m_incMatrix = incMatrix;
}

IncMatrix IncMatrix::ConstructIncMatrixFromAdjMatrix(std::vector<std::vector<int>> adjMatrix)
{
    IncMatrix incMatrix;

    int numberOfEdges = 0;

    for(int i = 0; i < adjMatrix.size(); ++i)
    {
        for(int j = 0; j < adjMatrix[i].size(); ++j)
        {
            if(adjMatrix[i][j] == 1)
                ++numberOfEdges;
        }
    }

    for(int i = 0; i < adjMatrix.size(); ++i)
    {
        std::vector<int> row;

        for(int j = 0; j < numberOfEdges; ++j)
        {
            row.emplace_back(0);
        }

        incMatrix.m_incMatrix.emplace_back(row);
    }

    int edge = 0;

    for(int i = 0; i < adjMatrix.size(); ++i)
    {
        for(int j = 0; j < adjMatrix[i].size(); ++j)
        {
            if(adjMatrix[i][j] == 1)
            {
                incMatrix.m_incMatrix[i][edge] = -1;
                incMatrix.m_incMatrix[j][edge] = 1;
                ++edge;
            }
        }
    }

    return incMatrix;
}

IncMatrix IncMatrix::ConstructIncMatrixFromAdjList(std::vector<std::vector<int>> adjList)
{
    std::vector<std::vector<int>> adjMatrix (adjList.size(), std::vector<int>(adjList.size(), 0));

    for(int i = 0; i < adjMatrix.size(); ++i)
    {
        for (int j = 0; j < adjList[i].size(); ++j)
        {
            adjMatrix[i][adjList[i][j]] = 1;
        }
    }

    return IncMatrix::ConstructIncMatrixFromAdjMatrix(adjMatrix);
}

void IncMatrix::Print() const
{
    PrintToFile();

    std::cout << "Incidence Matrix:" << std::endl;

    for(auto & row : m_incMatrix)
    {
        for(auto & item : row)
        {
            std::cout << std::setw(2) << item << " ";
        }

        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void IncMatrix::PrintToFile() const
{
    std::ofstream incMatrixFile;

    if (!incMatrixFile.is_open())
    {
        incMatrixFile.open("MacierzIncydencji.txt", std::ios::out);

        if(!incMatrixFile)
        {
            std::cerr << "Failed to open " << "MacierzIncydencji.txt" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    incMatrixFile << "MI" << std::endl;

    for(auto & row : m_incMatrix)
    {
        for(auto & item : row)
        {
            incMatrixFile << std::setw(2) << item << " ";
        }

        incMatrixFile << std::endl;
    }
    incMatrixFile << std::endl;

    incMatrixFile.close();
}
