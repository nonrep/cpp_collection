#pragma once
#include "IGraph.h"
#include <unordered_set>

struct Edge
{
    int from;
    int to;

    Edge(int from, int to);
    bool operator==(const Edge& e) const;
};

namespace std {
    template <> struct hash<Edge>
    {
        size_t operator()(const Edge& x) const
        {
            return hash<int>()(x.from * x.to);
        }
    };
}

struct ArcGraph : public IGraph
{
public:
    ArcGraph(int size);

    ArcGraph(const IGraph& graph);

    ~ArcGraph();

    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    int size;
    std::unordered_set<Edge> unordered_edges;
};
