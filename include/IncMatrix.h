#ifndef GRAPHS4_INCMATRIX_H
#define GRAPHS4_INCMATRIX_H

#include <vector>


class IncMatrix
{
public:
    IncMatrix() {}
    explicit IncMatrix(const std::vector<std::vector<int>>  incMatrix);
    static IncMatrix ConstructIncMatrixFromAdjMatrix(std::vector<std::vector<int>> adjMatrix);
    static IncMatrix ConstructIncMatrixFromAdjList(std::vector<std::vector<int>> adjList);

    void Print() const;
    void PrintToFile() const;

private:
    std::vector<std::vector<int>>m_incMatrix;
};

#endif //GRAPHS4_INCMATRIX_H
