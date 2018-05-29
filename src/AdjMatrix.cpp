#include <iostream>
#include <iomanip>
#include <AdjMatrix.h>

#include "AdjList.h"


int AdjMatrix::iRand(const int min, const int max)
{
    return rand() % max + min;
}

AdjMatrix::AdjMatrix(const int numberOfVertices, const double probability)
{
    for(int i = 0; i < numberOfVertices; ++i)
    {
        std::vector<int>row;

        for(int j = 0; j < numberOfVertices; ++j)
        {
            row.emplace_back(0);
        }

        m_adjMatrix.emplace_back(row);
    }

    for(int i = 0; i < numberOfVertices; ++i)
    {
        for(int j = 0; j < numberOfVertices; ++j)
        {
            int random = AdjMatrix::iRand(1, 100);
            int prob = static_cast<int>(probability * 100);

            if(i != j && prob >= random)
            {
                m_adjMatrix[i][j] = 1;
            }
        }
    }

}

void AdjMatrix::Print() const
{
    std::cout << "Adjacency Matrix:" << std::endl;

    for(auto & row : m_adjMatrix)
    {
        for(auto & item : row)
        {
            std::cout << std::setw(2) << item << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void AdjMatrix::ConvertFromAdjList(const std::vector<std::vector<int>> & adjList)
{
    int matrixSize = adjList.size();
    m_adjMatrix = std::vector<std::vector<int>>(matrixSize, std::vector<int>(matrixSize, 0));

    for(int i = 0; i < adjList.size(); ++i)
    {
        for(int j = 0; j < adjList[i].size(); ++j)
        {
            m_adjMatrix[i][adjList[i][j]] = 1;
        }
    }
}

unsigned AdjMatrix::Size() const
{
    return static_cast<unsigned int>(m_adjMatrix.size());
}

std::vector<int> & AdjMatrix::operator[](const int index)
{
    return m_adjMatrix[index];
}

std::vector<int> AdjMatrix::operator[](const int index) const
{
    return m_adjMatrix[index];
}
