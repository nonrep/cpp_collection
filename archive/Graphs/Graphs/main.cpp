#include <iostream>
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"
#include "ArcGraph.h"
#include <deque>
#include <queue>
#include <functional>

void BFS(const IGraph& graph, int vertex, std::vector<bool>& visited, const std::function<void(int)>& func)
{
    std::queue<int> qu;
    qu.push(vertex);
    visited[vertex] = true;

    while (!qu.empty())
    {
        int currentVertex = qu.front();
        qu.pop();

        func(currentVertex);

        for (int nextVertex : graph.GetNextVertices(currentVertex))
        {
            if (!visited[nextVertex])
            {
                visited[nextVertex] = true;
                qu.push(nextVertex);
            }
        }
    }
}

void mainBFS(const IGraph& graph, const std::function<void(int)>& func)
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

void DFS(const IGraph& graph, int vertex, std::vector<bool>& visited, const std::function<void(int)>& func)
{
    visited[vertex] = true;
    func(vertex);

    for (int nextVertex : graph.GetNextVertices(vertex))
    {
        if (!visited[nextVertex])
        {
            DFS(graph, nextVertex, visited, func);
        }
    }
}

void mainDFS(const IGraph& graph, const std::function<void(int)>& func)
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

void topologicalSortInternal(const IGraph& graph, int vertex, std::vector<bool>& visited, std::deque<int>& sorted)
{
    visited[vertex] = true;

    for (int nextVertex : graph.GetNextVertices(vertex))
    {
        if (!visited[nextVertex])
        {
            topologicalSortInternal(graph, nextVertex, visited, sorted);
        }
    }

    sorted.push_front(vertex);
}

std::deque<int> topologicalSort(const IGraph& graph)
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

void output(const IGraph& graph) {
    mainBFS(graph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;

    mainDFS(graph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;

    for (int vertex : topologicalSort(graph))
    {
        std::cout << vertex << " ";
    }
    std::cout << std::endl <<std::endl;
}

int main(int argc, const char* argv[]) {
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
    
    
    
    

    output(listGraph);

    MatrixGraph matrixGraph(listGraph);
    output(matrixGraph);

    SetGraph setGraph(matrixGraph);
    output(setGraph);

    ArcGraph arcGraph(setGraph);
    output(arcGraph);
    return 0;
}