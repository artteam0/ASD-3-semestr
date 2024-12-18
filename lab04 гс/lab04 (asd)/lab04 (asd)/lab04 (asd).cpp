#include <iostream>
#include <vector>
using namespace std;

const int INF = 1e9;

void printPath(int u, int v, const vector<vector<int>>& dist, const vector<vector<int>>& from)
{
    if (from[u][v] == v + 1) {
        cout << " -> " << v + 1;
        return;
    }
    printPath(u, from[u][v] - 1, dist, from);
    cout << " -> " << v + 1 ;
}

int main() {
    setlocale(LC_ALL, "ru");
    int vertexCount = 6;

    vector<vector<int>> dist = {
        { 0,  28,  21,  59,  12,  27 },
        { 7,  0,   24,  INF, 21,  9  },
        { 9,  32,  0,   13,  11,  INF},
        { 8,  INF, 5,   0,   16,  INF},
        { 14, 13,  15,  10,  0,   22 },
        { 15, 18,  INF, INF, 6,   0  }
    };

    vector<vector<int>> from = {
        { 0,  2,  3,  4,  5,  6 },
        { 1,  0,  3,  4,  5,  6,},
        { 1,  2,  0,  4,  5,  6,},
        { 1,  2,  3,  0,  5,  6 },
        { 1,  2,  3,  4,  0,  6 },
        { 1,  2,  3,  4,  5,  0 }
    };

    int c = 0;

    while (c < vertexCount) {
        for (int i = 0; i < vertexCount; i++) {
            for (int j = 0; j < vertexCount; j++) {
                if (dist[i][c] + dist[c][j] < dist[i][j] && i != j && j != c && i != c)
                {
                    dist[i][j] = dist[i][c] + dist[c][j];
                    from[i][j] = c + 1;
                }
            }
        }
        c += 1;
    }

    std::cout << "Обновленная матрица кратчайших путей: " << endl;
    for (int i = 0; i < vertexCount; i++) {
        for (int j = 0; j < vertexCount; j++) {
                std::cout << " " << dist[i][j] << " ";
        }
        std::cout << endl;
    }

    std::cout << "Обновленная матрица последовательности вершин: " << endl;
    for (int i = 0; i < vertexCount; ++i) {
        for (int j = 0; j < vertexCount; ++j) {
                std::cout << " " << from[i][j] << " ";
        }
        std::cout << endl;
    }

    int start, end;
    cout << "Введите начальную вершину (1 - 6): ";
    cin >> start;
    cout << "Введите конечную вершину (1 - 6): ";
    cin >> end;

    cout << "Кратчайший путь из " << start << " в " << end << ": " << start;
    printPath(start - 1, end - 1, dist, from);
    cout << endl;

    cout << "Общая длина пути: " << dist[start - 1][end - 1] << endl;


    return 0;
}
