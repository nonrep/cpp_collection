#pragma once
#include "IGraph.h"

struct MatrixGraph : public IGraph
{
public:
    MatrixGraph(unsigned short int size);
    MatrixGraph(const IGraph& graph);
    ~MatrixGraph();

    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    unsigned short int size;
    bool** matrix;
};