
#include "ArcGraph.h"
#include <cassert>


    Edge::Edge(int from, int to) :from(from), to(to)
    {

    }

    bool Edge::operator==(const Edge& e) const
    {
        return (this->from == e.from && this->to == e.to);
    }




ArcGraph::ArcGraph(int size)
        : size(size)
    {
    }

ArcGraph::ArcGraph(const IGraph& graph) :size(graph.VerticesCount())
    {
        for (int i = 0; i < graph.VerticesCount(); ++i)
        {
            for (int to : graph.GetNextVertices(i)) {
                this->AddEdge(i, to);
            }
        }
    }

ArcGraph::~ArcGraph()
    {
    }

    void ArcGraph::AddEdge(int from, int to)
    {
        assert(0 <= from && from < size);
        assert(0 <= to && to < size);
        unordered_edges.insert(Edge(from, to));
    }

    int ArcGraph::VerticesCount() const
    {
        return size;
    }

    std::vector<int> ArcGraph::GetNextVertices(int vertex) const
    {
        assert(0 <= vertex && vertex < size);
        std::vector<int> nextVertices(size);

        for (int to = 0; to < size; to++) {
            if (to != vertex) {
                if (unordered_edges.find(Edge(vertex, to)) != unordered_edges.end()) {
                    nextVertices.push_back(to);
                }
            }
        }

        return nextVertices;
    }

    std::vector<int> ArcGraph::GetPrevVertices(int vertex) const
    {
        assert(0 <= vertex && vertex < size);
        std::vector<int> prevVertices;

        for (int from = 0; from < size; ++from)
        {
            if (from != vertex) {
                if (unordered_edges.find(Edge(from, vertex)) != unordered_edges.end()) {
                    prevVertices.push_back(from);
                }
            }
        }
        return prevVertices;
    }
