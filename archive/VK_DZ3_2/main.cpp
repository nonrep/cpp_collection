#include <iostream>
#include <vector>
#include <cassert>
#include <functional>
#include <queue>
#include <deque>
#include <limits>

struct IGraph {
    virtual ~IGraph() {}
        
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

struct ListGraph: public IGraph
{
public:
    ListGraph(int size)
    : adjacencyLists(size)
    {
    }
    
    ListGraph(const IGraph &graph)
    {
        for (int i = 0; i < graph.VerticesCount(); ++i)
        {
            adjacencyLists[i] = graph.GetNextVertices(i);
        }
    }
    
    ListGraph& operator=(const ListGraph &other)
    {
         if (this != &other)
         {
            adjacencyLists = other.adjacencyLists;
        }
        return *this;
    }

    ~ListGraph()
    {
    }
    
    void AddEdge(int from, int to) override
    {
        assert(0 <= from && from < adjacencyLists.size());
        assert(0 <= to && to < adjacencyLists.size());
        adjacencyLists[from].push_back(to);
    }
    
    int VerticesCount() const override
    {
        return (int)adjacencyLists.size();
    }
    
    std::vector<int> GetNextVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        return adjacencyLists[vertex];
    }
    
    std::vector<int> GetPrevVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        std::vector<int> prevVertices;
        
        for (int from = 0; from < adjacencyLists.size(); ++from)
        {
            for (int to: adjacencyLists[from])
            {
                if (to == vertex)
                    prevVertices.push_back(from);
            }
        }
        return prevVertices;
    }
    
private:
    std::vector<std::vector<int>> adjacencyLists;
};


void BFS(const IGraph &graph, int startVertex, int targetVertex, std::vector<int> &shortestPathCounts)
{
    std::vector<int> d(graph.VerticesCount(), std::numeric_limits<int>::max()); // кратчайшие расстояния от стартовой вершины
    std::vector<int> k(graph.VerticesCount(), 0); // счетчик кратчайших путей

    d[startVertex] = 0;
    k[startVertex] = 1;

    std::queue<int> qu;
    qu.push(startVertex);

    while (!qu.empty())
    {
        int currentVertex = qu.front();
        qu.pop();
        
        if (currentVertex == targetVertex) {
            break;
        }

        for (int nextVertex: graph.GetNextVertices(currentVertex))
        {
            if (d[currentVertex] + 1 < d[nextVertex])
            {
                d[nextVertex] = d[currentVertex] + 1;
                k[nextVertex] = k[currentVertex];
                qu.push(nextVertex);
            }
            else if (d[currentVertex] + 1 == d[nextVertex])
            {
                k[nextVertex] += k[currentVertex];
            }
        }
    }
    shortestPathCounts[targetVertex] = k[targetVertex];
}

int main() {
    int v, n;
    std::cin >> v >> n;

    ListGraph graph(v);

    for (int i = 0; i < n; ++i)
    {
        int from, to;
        std::cin >> from >> to;
        graph.AddEdge(from, to);
        graph.AddEdge(to, from);
    }

    int startVertex, targetVertex;
    std::cin >> startVertex >> targetVertex;

    std::vector<int> shortestPathCounts(v, 0);
    BFS(graph, startVertex, targetVertex, shortestPathCounts);

    std::cout << shortestPathCounts[targetVertex] << std::endl;

    return 0;
}