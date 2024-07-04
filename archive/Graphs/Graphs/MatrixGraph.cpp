#include "MatrixGraph.h"
#include <cassert>

MatrixGraph::MatrixGraph(unsigned short int size)
    {
        this->size = size;

        matrix = new bool* [size];
        for (int i = 0; i < size; ++i) {
            matrix[i] = new bool[size];
            for (int j = 0; j < size; ++j) {
                matrix[i][j] = false;
            }
        }
    }

MatrixGraph::MatrixGraph(const IGraph& graph)
    {
        this->size = graph.VerticesCount();

        matrix = new bool* [size];
        for (int i = 0; i < size; ++i) {
            matrix[i] = new bool[size];
            for (int j = 0; j < size; ++j) {
                matrix[i][j] = false;
            }
        }
        for (int from = 0; from < graph.VerticesCount(); ++from)
        {
            for (int to : graph.GetNextVertices(from)) {
                matrix[from][to] = true;
            }
        }
    }

MatrixGraph::~MatrixGraph()
    {
    }

    void MatrixGraph::AddEdge(int from, int to) 
    {
        assert(0 <= from && from < size);
        assert(0 <= to && to < size);
        matrix[from][to] = true;
    }

    int MatrixGraph::VerticesCount() const 
    {
        return size;
    }

    std::vector<int> MatrixGraph::GetNextVertices(int vertex) const
    {
        assert(0 <= vertex && vertex < size);

        std::vector<int> res;
        for (int to = 0; to < size; to++) {
            //if (to != vertex) мб петли есть

            if (matrix[vertex][to]) {
                res.push_back(to);
            }

        }

        return res;
    }

    std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const
    {
        assert(0 <= vertex && vertex < size);
        std::vector<int> prevVertices;

        for (int from = 0; from < size; ++from)
        {
            if (matrix[from][vertex]) {
                prevVertices.push_back(from);
            }
        }
        return prevVertices;
    }

