#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int V = 8;

struct Edge {
	int u, v, weight;
};

int minKey(vector<int>& key, vector<bool>& prim)
{
	int min = INT_MAX, min_index;
	for (int v = 0; v < V; v++) {
		if (!prim[v] && key[v] < min) { //если вершина еще не в прима
			min = key[v];
			min_index = v;
		}
	}
	return min_index;
}

void Prim(int graph[V][V])
{
	vector<bool> prim(V, false);
	vector<int> parent(V);
	parent[0] = -1;
	vector<int> key(V, INT_MAX);
	key[0] = 0;

	for (int i = 0; i < V - 1; i++) {
		int u = minKey(key, prim);
		prim[u] = true;

		for (int v = 0; v < V; v++) {
			if (graph[u][v] && !prim[v] && graph[u][v] < key[v]) { //еще не в прим
				parent[v] = u;
				key[v] = graph[u][v];
			}
		}
	}

	cout << "Ребро \tВес" << endl;
	for (int i = 1; i < V; i++) {
		cout << parent[i] + 1 << " - " << i + 1 << "\t" << graph[i][parent[i]] << "\n";
	}
}

int Root(vector<int>& parent, int node)
{
	if (parent[node] != node) //если вершина не явл своим корнем
		parent[node] = Root(parent, parent[node]);
	return parent[node];
}

void Union(vector<int>& parent, vector<int>& rang, int x, int y) {
	int rootX = Root(parent, x);
	int rootY = Root(parent, y);
	if (rang[rootX] < rang[rootY]) {
		parent[rootX] = rootY;
	}
	else if (rang[rootX] > rang[rootY]) {
		parent[rootY] = rootX;
	}
	else {
		parent[rootY] = rootX;
		rang[rootX]++;
	}
}

void Kraskal(int graph[V][V]) {
	vector<Edge> edges;

	for (int i = 0; i < V; i++) {
		for (int j = i + 1; j < V; j++) { 
			if (graph[i][j] != 0) { //если есть ребро
				edges.push_back({ i, j, graph[i][j] });
			}
		}
	}

	vector<int> parent(V);
	vector<int> rank(V, 0);

	for (int i = 0; i < V; i++) {
		parent[i] = i;
	}

	sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
		return a.weight < b.weight;
		});

	cout << "Ребро \tВес" << endl;
	int mst_weight = 0;
	for (auto& edge : edges) {
		int rootU = Root(parent, edge.u);
		int rootV = Root(parent, edge.v);

		if (rootU != rootV) {
			cout << edge.u + 1 << " - " << edge.v + 1 << "\t" << edge.weight << endl;
			mst_weight += edge.weight;
			Union(parent, rank, rootU, rootV);
		}
	}
	cout << "Вес минимального остовного дерева: " << mst_weight << endl;
}

int main()
{
	setlocale(LC_ALL, "ru");
	int graph[V][V] = {
		{ 0,  2,  0,  8,  0,  0,  0,  0 },
		{ 2,  0,  3,  10, 5,  0,  0,  0 },
		{ 0,  3,  0,  0,  12, 0,  0,  7 },
		{ 8,  10, 0,  0,  14, 3,  1,  0 },
		{ 2,  5,  12, 14, 0,  11, 4,  8 },
		{ 0,  0,  0,  3,  11, 6,  0,  0 },
		{ 0,  0,  0,  1,  4,  6,  0,  9 },
		{ 0,  0,  7,  0,  8,  0,  9,  0 }
	};

	Prim(graph);
	Kraskal(graph);
	return 0;
}