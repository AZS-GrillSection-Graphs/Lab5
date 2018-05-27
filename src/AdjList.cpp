#include "AdjList.h"
#include <iostream>
#include <iomanip>


AdjList::AdjList(const std::vector<std::vector<int>> adjList)
{
    m_adjList = adjList;
}

unsigned AdjList::NumOfVertices() const
{
    return static_cast<unsigned int>(m_adjList.size());
}

std::vector<int> &AdjList::operator[](const int index)
{
    return m_adjList[index];
}

std::vector<int> AdjList::operator[](const int index) const
{
    return m_adjList[index];
}

void AdjList::Print() const
{
    std::cout << "Adjacency List:" << std::endl;


    for(int i = 0; i < m_adjList.size(); ++i)
    {
        std::cout << i + 1 << ": ";
        for(int j = 0; j < m_adjList[i].size(); ++j)
        {
            std::cout << m_adjList[i][j] + 1 << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

std::vector<std::vector<int>>& AdjList::GetAdjList()
{
    return m_adjList;
}

void AdjList::RemoveEdgesInVertical(const int vertical, const int verticalToDelete)
{
    std::vector<int> newVertical;

    for(int i = 0; i < m_adjList[vertical].size(); ++i)
    {
        if(m_adjList[vertical][i] != verticalToDelete)
            newVertical.emplace_back(m_adjList[vertical][i]);
    }

    m_adjList[vertical].swap(newVertical);
}

IncMatrix AdjList::ConvertToIncMatrix() const
{
    return IncMatrix::ConstructIncMatrixFromAdjList(m_adjList);
}
