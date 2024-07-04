#include "SetGraph.h"
#include <cassert>

SetGraph::SetGraph(int size)
        : setArray(size)
    {
    }

SetGraph::SetGraph(const IGraph& graph) :setArray(graph.VerticesCount())
    {
        for (int from = 0; from < graph.VerticesCount(); ++from)
        {
            for (int to : graph.GetNextVertices(from)) {
                setArray[from].insert(to);
            }
        }
    }

SetGraph::~SetGraph()
    {
    }

    void SetGraph::AddEdge(int from, int to) 
    {
        assert(0 <= from && from < setArray.size());
        assert(0 <= to && to < setArray.size());
        setArray[from].insert(to);
    }

    int SetGraph::VerticesCount() const 
    {
        return (int)setArray.size();
    }

    std::vector<int> SetGraph::GetNextVertices(int vertex) const 
    {
        assert(0 <= vertex && vertex < setArray.size());

        std::vector<int> output(VerticesCount());

        for (int i : setArray[vertex]) {
            output.push_back(i);
        }

        return output;
    }

    std::vector<int> SetGraph::GetPrevVertices(int vertex) const 
    {
        assert(0 <= vertex && vertex < setArray.size());
        std::vector<int> prevVertices;

        for (int from = 0; from < setArray.size(); ++from)
        {
            for (int to : setArray[from])
            {
                if (to == vertex)
                    prevVertices.push_back(from);
            }
        }
        return prevVertices;
    }
