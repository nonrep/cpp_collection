#include <iostream>
#include <vector>
#include <queue>
#include <limits>

const int MAX = std::numeric_limits<int>::max();

class Graph {
public:
    Graph(int size) : size(size), adjacencyLists(size) {}

    void addEdge(int u, int v, int w) {
        adjacencyLists[u].push_back({v, w});
    }

    int dijkstra(int s, int t) {
        std::vector<int> dist(size, MAX);
        dist[s] = 0;
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
        pq.push({0, s});

        while (!pq.empty()) {
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();

            if (d > dist[u]) continue;

            for (auto edge : adjacencyLists[u]) {
                int v = edge.first;
                int w = edge.second;
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }

        return dist[t];
    }
private:
    int size;
    std::vector<std::vector<std::pair<int, int>>> adjacencyLists;
};

int main() {
    int n, m;
    std::cin >> n >> m;

    Graph graph(n);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        graph.addEdge(u, v, w);
        graph.addEdge(v, u, w);
    }

    int s, t;
    std::cin >> s >> t;

    std::cout << graph.dijkstra(s, t) << std::endl;

    return 0;
}