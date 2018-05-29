#ifndef GRAPHS5_ADJMATRIX_H
#define GRAPHS5_ADJMATRIX_H


#include <vector>


class AdjList;
class IncMatrix;


class AdjMatrix
{
public:
    AdjMatrix() {}
    AdjMatrix(const int numberOfVertices, const double probability);
    ~AdjMatrix() = default;
    void Print() const;
    static int iRand(const int min, const int max);
    void ConvertFromAdjList(const std::vector<std::vector<int>> & adjList);
    unsigned Size() const;
    std::vector<int> & operator[](const int index);
    std::vector<int> operator[](const int index) const;

private:
    std::vector<std::vector<int>> m_adjMatrix;
};

#endif //GRAPHS5_ADJMATRIX_H
