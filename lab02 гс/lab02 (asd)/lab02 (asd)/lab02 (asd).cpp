#include <iostream>
#include <queue>
#include <vector>
#include <stack>

using namespace std;

void BFSMatrix(int startVertex);
void DFSMatrix(int startVertex);
void BFSList(queue<int>& q);
void DFSList(stack<int>& q);
void BFSEdge(queue<int>& q);
void DFSEdge(stack<int>& q);


bool visitedA[10] = { false };
bool visitedB[10] = { false };
bool visitedC[10] = { false };
bool visitedD[10] = { false };

const int MAX = 10;
int adjMatrix[MAX][MAX] = {

    {0, 1, 0, 0, 1, 1, 0, 0, 0, 0},  
    {1, 0, 0, 0, 0, 0, 1, 1, 0, 0},  
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},  
    {0, 0, 0, 0, 0, 1, 0, 0, 1, 0},  
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0},  
    {1, 0, 0, 1, 1, 0, 0, 0, 1, 0},  
    {0, 1, 0, 0, 0, 0, 0, 1, 0, 0},  
    {0, 1, 1, 0, 0, 0, 1, 0, 0, 0},  
    {0, 0, 0, 1, 0, 1, 0, 0, 0, 1},  
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0}   
};

vector<vector<int>> list = {
    {2, 5},
    {1, 7, 8},
    {8},
    {6, 9},
    {1, 6},
    {4, 9},
    {2, 8},
    {2, 3, 7},
    {4, 6, 10},
    {9}
};

vector<pair<int, int>> pairList = {
    {1, 2},
    {2, 7},
    {2, 8},
    {1, 5},
    {5, 6},
    {7, 8},
    {8, 3},
    {6, 4},
    {4, 9},
    {9, 6},
    {9, 10}
};

int main() {
    setlocale(LC_ALL, "ru");

    /*add(0, 1); add(0, 5);
    add(1, 6); add(1, 7);
    add(2, 7);
    add(3, 5); add(3, 8);
    add(4, 0); add(4, 5);
    add(5, 3); add(5, 4); add(5, 8);
    add(6, 1); add(6, 7);
    add(7, 6); add(7, 1); add(7, 2);
    add(8, 3); add(8, 5); add(8, 9);
    add(9, 8);*/

    BFSMatrix(0);

    DFSMatrix(0);

    cout << "BFS Список смежности: ";
    queue<int>q1;
    int index = 1;
    q1.push(index);
    cout << index;
    BFSList(q1);
    cout << endl;

    cout << "DFS Список смежности: ";
    stack<int>s1;
    index = 1;
    s1.push(index);
    cout << index;
    DFSList(s1);
    cout << endl;

    cout << "BFS Список рёбер ";
    queue<int>q2;
    index = 1;
    q2.push(index);
    cout << index;
    BFSEdge(q2);
    cout << endl;

    cout << "DFS Список рёбер: ";
    stack<int>s2;
    index = 1;
    s2.push(index);
    cout << index;
    DFSEdge(s2);
    cout << endl;

    cout << "Большое О" << endl;
    cout << "Матрица смежности: " << 10 * 10 << endl;
    cout << "Список смежности: " << list.size() + 1 + 10 << endl;
    cout << "Список рёбер: " << list.size() + 1 + 10 << endl;

    return 0;
}

void BFSMatrix(int startVertex) {
    bool visited[MAX] = { false }; //какие вершины посещены
    queue<int> q; //какие нужно посетить

    visited[startVertex] = true; //стартовая посещена
    q.push(startVertex); //добавляется в очередь

    cout << "BFS Matrix: ";
    while (!q.empty()) {
        int v = q.front();
        q.pop(); //извлекается
        cout << v + 1 << " "; //нумерует с 1

        for (int i = 0; i < MAX; i++) {
            if (adjMatrix[v][i] == 1 && !visited[i]) { //если смежная
                visited[i] = true; //то посещается
                q.push(i); //в очередь
            }
        }
    }
    cout << endl;
}

void VspomMatrix(int v, bool visited[]) {
    visited[v] = true;
    cout << v + 1 << " "; //нумерует с 1

    for (int i = 0; i < MAX; i++) {
        if (adjMatrix[v][i] == 1 && !visited[i]) { //есть ли ребро
            VspomMatrix(i, visited);
        }
    }
}

void DFSMatrix(int startVertex) {
    bool visited[MAX] = { false }; //посещ верш
    cout << "DFS Matrix: ";
    VspomMatrix(startVertex, visited);
    cout << endl;
}

void BFSList(queue<int>& q) {

    while (!q.empty()) {
        int index = q.front(); //извлекает текущую вершину и удаляет
        q.pop();

        if (!visitedA[index - 1]) {

            if (index != 1) { //если вершина начальная
                cout << " " << index;
            }

            visitedA[index - 1] = true;

            for (int i = 0; i < list[index - 1].size(); i++) {
                q.push(list[index - 1][i]);
            }
        }
    }
}

void DFSList(stack<int>& s) {

    while (!s.empty()) {
        int index = s.top(); //извлекаем текущий и удаляем
        s.pop();

        if (!visitedB[index - 1]) {

            if (index != 1) { //начальная
                cout << " " << index;
            }

            visitedB[index - 1] = true;

            for (int i = 0; i < list[index - 1].size(); i++) {
                s.push(list[index - 1][i]);
            }
        }
    }
}

void BFSEdge(queue<int>& q) {

    while (!q.empty()) {
        int index = q.front();
        q.pop();

        if (!visitedC[index - 1]) {

            if (index != 1) {
                cout << " " << index;
            }

            visitedC[index - 1] = true;

            for (int i = 0; i < pairList.size(); i++) {

                if (pairList[i].first == index) { //если связано с вершиной
                    q.push(pairList[i].second);
                }

                else if (pairList[i].second == index) {
                    q.push(pairList[i].first);
                }
            }
        }
    }
}

void DFSEdge(stack<int>& s) {

    while (!s.empty()) {
        int index = s.top();
        s.pop(); 

        if (!visitedD[index - 1]) {

            if (index != 1) {
                cout << " " << index;
            }

            visitedD[index - 1] = true;

            for (int i = 0; i < pairList.size(); i++) {

                if (pairList[i].first == index) {
                    s.push(pairList[i].second);
                }
                else if (pairList[i].second == index) {
                    s.push(pairList[i].first);
                }
            }
        }
    }
}



//#include <iostream>
//#include <queue>
//#include <vector>
//
//using namespace std;
//
//const int MAX_VERTICES = 10;
//
//vector<pair<int, int>> edges; // Список рёбер
//
//void add(int u, int v) {
//    edges.push_back({ u, v });
//    edges.push_back({ v, u });
//}
//
//vector<int> getAdjVertices(int v) {
//    vector<int> adjVertices;
//    for (auto edge : edges) {
//        if (edge.first == v) {
//            adjVertices.push_back(edge.second);
//        }
//    }
//    return adjVertices;
//}
//
//void BFS(int startVertex) {
//    bool visited[MAX_VERTICES] = { false };
//    queue<int> q;
//
//    visited[startVertex] = true;
//    q.push(startVertex);
//
//    cout << "BFS: ";
//    while (!q.empty()) {
//        int v = q.front();
//        q.pop();
//        cout << v + 1 << " "; // Нумерация с 1
//
//        vector<int> adjVertices = getAdjVertices(v);
//        for (int u : adjVertices) {
//            if (!visited[u]) {
//                visited[u] = true;
//                q.push(u);
//            }
//        }
//    }
//    cout << endl;
//}
//
//void Vspom(int v, bool visited[]) {
//    visited[v] = true;
//    cout << v + 1 << " "; // Нумерация с 1
//
//    vector<int> adjVertices = getAdjVertices(v);
//    for (int u : adjVertices) {
//        if (!visited[u]) {
//            Vspom(u, visited);
//        }
//    }
//}
//
//void DFS(int startVertex) {
//    bool visited[MAX_VERTICES] = { false };
//    cout << "DFS: ";
//    Vspom(startVertex, visited);
//    cout << endl;
//}
//
//int main() {
//    add(0, 1); add(0, 5);
//    add(1, 6); add(1, 7);
//    add(2, 7);
//    add(3, 5); add(3, 8);
//    add(4, 0); add(4, 5);
//    add(5, 3); add(5, 4); add(5, 8);
//    add(6, 1); add(6, 7);
//    add(7, 6); add(7, 1); add(7, 2);
//    add(8, 3); add(8, 5); add(8, 9);
//    add(9, 8);
//
//    BFS(0);
//    DFS(0);
//
//    return 0;
//}
