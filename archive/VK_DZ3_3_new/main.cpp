#include <iostream>
#include <vector>
#include <set>
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
        std::set<std::pair<int, int>> set;
        set.insert({0, s});

        while (!set.empty()) {
            auto top = *set.begin();
            int u = top.second;
            int d = top.first;
            set.erase(set.begin());

            if (d > dist[u]) continue;

            for (auto edge : adjacencyLists[u]) {
                int v = edge.first;
                int w = edge.second;
                if (dist[u] + w < dist[v]) {
                    auto search = set.find({dist[v], v});
                    if (search != set.end()) 
                        set.erase(search);
                    dist[v] = dist[u] + w;
                    set.insert({dist[v], v});
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