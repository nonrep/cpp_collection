#include <iostream>
#include <vector>
#include <cassert>
#include <functional>
#include <queue>
#include <deque>
#include <set>

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
    
    ListGraph& operator=(const ListGraph& other)
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

struct MatrixGraph : public IGraph {
public:
    MatrixGraph(int size)
    : matrix(size, std::vector<int>(size, 0))
    {
    }
    
    MatrixGraph(const IGraph& graph)
    {
        int size = graph.VerticesCount();
        matrix.resize(size, std::vector<int>(size, 0));

        for (int from = 0; from < size; ++from) {
            for (int to : graph.GetNextVertices(from)) {
                matrix[from][to] = 1;
            }
        }
    }

    MatrixGraph& operator=(const MatrixGraph& other)
    {
        if (this != &other)
        {
            matrix = other.matrix;
        }
        return *this;
    }

    ~MatrixGraph()
    {      
    }
    
    void AddEdge(int from, int to) override
    {
        assert(0 <= from && from < matrix.size());
        assert(0 <= to && to < matrix[0].size());
        matrix[from][to] = 1;
    }
    
    int VerticesCount() const override
    {
        return static_cast<int>(matrix.size());
    }
    
    std::vector<int> GetNextVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex < matrix.size());
        std::vector<int> nextVertices;
        for (int i = 0; i < matrix[vertex].size(); ++i)
        {
            if (matrix[vertex][i] == 1)
            {
                nextVertices.push_back(i);
            }
        }
        return nextVertices;
    }
    
    std::vector<int> GetPrevVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex < matrix.size());
        std::vector<int> prevVertices;
        for (int i = 0; i < matrix.size(); ++i)
        {
            if (matrix[i][vertex] == 1)
            {
                prevVertices.push_back(i);
            }
        }
        return prevVertices;
    }
    
private:
    std::vector<std::vector<int>> matrix;
};

struct ArcGraph : public IGraph {
public:
    ArcGraph(int size)
    {
        adjacencyLists.resize(size);
    }
    
    ArcGraph(const IGraph& graph) 
    {
        int size = graph.VerticesCount();
        adjacencyLists.resize(size);

        for (int from = 0; from < size; ++from) {
            for (int to : graph.GetNextVertices(from)) {
                if (to < adjacencyLists.size()) {
                    adjacencyLists[from].push_back(to);
                }
            }
        }
    }

    ArcGraph& operator=(const ArcGraph& other)
    {
        if (this != &other)
        {
            adjacencyLists = other.adjacencyLists;
        }
        return *this;
    }

    ~ArcGraph()
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
        return static_cast<int>(adjacencyLists.size());
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
            for (int to : adjacencyLists[from])
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

struct SetGraph : public IGraph {
public:
    SetGraph(int size)
    {
        adjacencySets.resize(size);
    }
    
    SetGraph(const IGraph& graph) 
    {
        int size = graph.VerticesCount();
        adjacencySets.resize(size);

        for (int from = 0; from < size; ++from) {
            for (int to : graph.GetNextVertices(from)) {
                if (to < adjacencySets.size()) {
                    adjacencySets[from].insert(to);
                }
            }
        }
    }

    SetGraph& operator=(const SetGraph& other)
    {
        if (this != &other)
        {
            adjacencySets = other.adjacencySets;
        }
        return *this;
    }

    ~SetGraph()
    {
    }
    
    void AddEdge(int from, int to) override
    {
        assert(0 <= from && from < adjacencySets.size());
        assert(0 <= to && to < adjacencySets.size());
        adjacencySets[from].insert(to);
    }
    
    int VerticesCount() const override
    {
        return static_cast<int>(adjacencySets.size());
    }
    
    std::vector<int> GetNextVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex < adjacencySets.size());
        return std::vector<int>(adjacencySets[vertex].begin(), adjacencySets[vertex].end());
    }
    
    std::vector<int> GetPrevVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex < adjacencySets.size());
        std::vector<int> prevVertices;
        
        for (int from = 0; from < adjacencySets.size(); ++from)
        {
            if (adjacencySets[from].count(vertex) > 0)
                prevVertices.push_back(from);
        }
        return prevVertices;
    }
    
private:
    std::vector<std::set<int>> adjacencySets;
};

void BFS(const IGraph &graph, int vertex, std::vector<bool> &visited, const std::function<void(int)> &func)
{
    std::queue<int> qu;
    qu.push(vertex);
    visited[vertex] = true;
    
    while (!qu.empty())
    {
        int currentVertex = qu.front();
        qu.pop();
        
        func(currentVertex);
        
        for (int nextVertex: graph.GetNextVertices(currentVertex))
        {
            if (!visited[nextVertex])
            {
                visited[nextVertex] = true;
                qu.push(nextVertex);
            }
        }
    }
}

void mainBFS(const IGraph &graph, const std::function<void(int)> &func)
{
    std::vector<bool> visited(graph.VerticesCount(), false);
    
    for (int i = 0; i < graph.VerticesCount(); ++i)
    {
        if (!visited[i])
        {
            BFS(graph, i, visited, func);
        }
    }
}

void DFS(const IGraph &graph, int vertex, std::vector<bool> &visited, const std::function<void(int)> &func)
{
    visited[vertex] = true;
    func(vertex);
    
    for (int nextVertex: graph.GetNextVertices(vertex))
    {
        if (!visited[nextVertex])
        {
            DFS(graph, nextVertex, visited, func);
        }
    }
}

void mainDFS(const IGraph &graph, const std::function<void(int)> &func)
{
    std::vector<bool> visited(graph.VerticesCount(), false);
    
    for (int i = 0; i < graph.VerticesCount(); ++i)
    {
        if (!visited[i])
        {
            DFS(graph, i, visited, func);
        }
    }
}

void topologicalSortInternal(const IGraph &graph, int vertex, std::vector<bool> &visited, std::deque<int> &sorted)
{
    visited[vertex] = true;
    
    for (int nextVertex: graph.GetNextVertices(vertex))
    {
        if (!visited[nextVertex])
        {
            topologicalSortInternal(graph, nextVertex, visited, sorted);
        }
    }
    
    sorted.push_front(vertex);
}

std::deque<int> topologicalSort(const IGraph &graph)
{
    std::deque<int> sorted;
    std::vector<bool> visited(graph.VerticesCount(), false);
    
    for (int i = 0; i < graph.VerticesCount(); ++i)
    {
        if (!visited[i])
        {
            topologicalSortInternal(graph, i, visited, sorted);
        }
    }
    
    return sorted;
}

int main() {
    ListGraph listGraph(20);
    listGraph.AddEdge(0, 1);
    listGraph.AddEdge(0, 5);
    listGraph.AddEdge(1, 2);
    listGraph.AddEdge(1, 3);
    listGraph.AddEdge(1, 5);
    listGraph.AddEdge(1, 6);
    listGraph.AddEdge(2, 4);
    listGraph.AddEdge(2, 8);
    listGraph.AddEdge(3, 2);
    listGraph.AddEdge(3, 4);
    listGraph.AddEdge(3, 6);
    listGraph.AddEdge(3, 8);
    listGraph.AddEdge(4, 1);
    listGraph.AddEdge(5, 3);
    listGraph.AddEdge(5, 4);
    listGraph.AddEdge(5, 6);
    listGraph.AddEdge(6, 4);
    
    //listGraph
    mainBFS(listGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;
    mainDFS(listGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;
    for (int vertex : topologicalSort(listGraph)) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl << std::endl;
    
    //matrixGraph
    MatrixGraph matrixGraph(listGraph);
    mainBFS(matrixGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;
    mainDFS(matrixGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;
    for (int vertex : topologicalSort(listGraph)) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl << std::endl;

    //arcGraph
    ArcGraph arcGraph(matrixGraph);
    mainBFS(arcGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;
    mainDFS(arcGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;
    for (int vertex : topologicalSort(listGraph)) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl << std::endl;

    //setGraph
    SetGraph setGraph(arcGraph);
    mainBFS(setGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;
    mainDFS(setGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;
    for (int vertex : topologicalSort(listGraph)) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl << std::endl;
    
    return 0;
}