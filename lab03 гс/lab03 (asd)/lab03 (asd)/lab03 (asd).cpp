#include <iostream>
#include <vector>
using namespace std;

const int INF = 1e9;

vector<int> dijkstra(vector<vector<pair<int, int>>>& graph, int start) {
    vector<int> dist(graph.size(), INF);
    dist[start] = 0;
    vector<bool> visited(graph.size());

    for (int i = 0; i < graph.size(); i++) {
        int nearest = -1;
        for (int v = 0; v < graph.size(); v++) {
            if (!visited[v] && (nearest == -1 || dist[nearest] > dist[v])) {
                nearest = v;
            }
        }

        visited[nearest] = true;

        for (const auto& neighbor : graph[nearest]) {
            int to = neighbor.first;     
            int weight = neighbor.second; 

            if (dist[to] > dist[nearest] + weight) {
                dist[to] = dist[nearest] + weight;
            }
        }
    }
    return dist;
}

int main() {
    setlocale(LC_ALL, "ru");
    const int v = 9;
    vector<vector<int>> matrix = {
        // A  B   C   D   E   F   G   H   I
        { 0,  7, 10,  0,  0,  0,  0,  0,  0 }, // A
        { 7,  0,  0,  0,  0,  9,  27, 0,  0 }, // B
        { 10, 0,  0,  0,  31, 8,  0,  0,  0 }, // C
        { 0,  0,  0,  0,  32, 0,  0,  17, 21}, // D
        { 0,  0,  31, 32, 0,  0,  0,  0,  0 }, // E
        { 0,  9,  8,  0,  0,  0,  0,  11, 0 }, // F
        { 0,  27, 0,  0,  0,  0,  0,  0,  15}, // G
        { 0,  0,  0,  17, 0,  11, 0,  0,  15}, // H
        { 0,  0,  0,  21, 0,  0,  15, 15, 0 }  // I
    };

    vector<vector<pair<int, int>>> adjList(v);

    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            if (matrix[i][j] != 0) {
                adjList[i].push_back({ j, matrix[i][j] });
            }
        }
    }

    char start_let;
    while (true) {
        cout << "Введите стартовую вершину (A-I): ";
        cin >> start_let;
        start_let = toupper(start_let);

        if (start_let >= 'A' && start_let <= 'I') {
            break;
        }
        else {
            cout << "Неверный ввод." << endl;
            return 0;
        }
    }

    int start = start_let - 'A';
    vector<int> distances = dijkstra(adjList, start);

    cout << "Минимальные расстояния от вершины " << start_let << ":" << endl;
    for (int i = 0; i < v; i++) {
        cout << "До вершины " << char(i + 'A') << ": "
            << (distances[i] == INF ? -1 : distances[i]) << endl;
    }

    return 0;
}
