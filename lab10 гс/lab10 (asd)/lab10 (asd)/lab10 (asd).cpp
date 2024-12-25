#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <math.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(0));
	int N;

	cout << "Введите количество городов: ";

	while (true)
	{
		cin >> N;
		if (N <= 1)
		{
			cout << "Вы ввели неправильное значение!" << endl;
			continue;
		}
		break;
	}

	cout << endl;

	int** graph = new int* [N];
	for (int i = 0; i < N; i++)
	{
		graph[i] = new int[N];
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (i == j)
			{
				graph[i][j] = 0;
			}
			else if (i < j)
			{
				graph[i][j] = rand() % 100 + 1;
				graph[j][i] = graph[i][j];
			}
			cout << setw(4) << graph[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	float alpha;
	float beta;
	float ferCount;
	int iterCount;

	cout << "Введите альфа: ";

	while (true)
	{
		cin >> alpha;
		if (alpha < 0)
		{
			cout << "Вы ввели неправильное значение!" << endl;
			continue;
		}
		break;
	}

	cout << "Введите бета: ";

	while (true)
	{
		cin >> beta;
		if (beta < 0)
		{
			cout << "Вы ввели неправильное значение!" << endl;
			continue;
		}
		break;
	}

	cout << "Введите количество феромонов: ";

	while (true)
	{
		cin >> ferCount;
		if (ferCount <= 0 || ferCount >= 1)
		{
			cout << "Вы ввели неправильное значение!" << endl;
			continue;
		}
		break;
	}

	cout << "Введите количество итераций: ";

	while (true)
	{
		cin >> iterCount;
		if (iterCount < 1)
		{
			cout << "Вы ввели неправильное значение!" << endl;
			continue;
		}
		break;
	}

	double** pheromones = new double* [N];

	for (int i = 0; i < N; i++)
	{
		pheromones[i] = new double[N];
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (i == j)
			{
				pheromones[i][j] = 0;
			}
			else if (i < j)
			{
				pheromones[i][j] = ferCount;
				pheromones[j][i] = pheromones[i][j];
			}
		}
	}

	int* bestWay = new int[N + 1];
	int bestDistance = INT_MAX;

	for (int iteration = 0; iteration < iterCount; iteration++)
	{
		int** ways = new int* [N]; //маршрут каждого муравья
		bool** visited = new bool* [N]; //города которые посетил каждый
		int* distances = new int[N]; //длина маршрута, пройденного каждым муравьём

		for (int i = 0; i < N; i++)
		{
			ways[i] = new int[N + 1];
			visited[i] = new bool[N];
			distances[i] = 0;

			for (int j = 0; j < N; j++)
			{
				visited[i][j] = false;
			}

			ways[i][0] = i;
			visited[i][i] = true;
		}

		for (int ant = 0; ant < N; ant++)
		{
			int currentCity = ant;

			for (int step = 1; step < N; step++)
			{
				double* probabilities = new double[N]; //вероятности
				double sumProb = 0;

				for (int nextCity = 0; nextCity < N; nextCity++)
				{
					if (!visited[ant][nextCity])
					{
						probabilities[nextCity] = pow(graph[currentCity][nextCity], alpha) *
							pow(10.0 / pheromones[currentCity][nextCity], beta);

						sumProb += probabilities[nextCity]; //все возможные переходы (сумма)
					}
					else
					{
						probabilities[nextCity] = 0;
					}
				}

				double randChoice = (double)rand() / RAND_MAX * sumProb;
				double bufProb = 0; //накапливаются вероятности
				int nextCity = -1;
				for (int city = 0; city < N; city++)
				{
					bufProb += probabilities[city];
					if (randChoice <= bufProb)
					{
						nextCity = city;
						break;
					}
				}

				visited[ant][nextCity] = true;
				ways[ant][step] = nextCity;
				distances[ant] += graph[currentCity][nextCity];
				currentCity = nextCity;

				delete[] probabilities;
			}
			distances[ant] += graph[currentCity][ways[ant][0]]; //добавление к общему расстоянию
			ways[ant][N] = ways[ant][0]; //стартовый город

			if (distances[ant] < bestDistance) //лучший
			{
				bestDistance = distances[ant];
				for (int i = 0; i <= N; i++)
				{
					bestWay[i] = ways[ant][i];
				}
			}
		}
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				pheromones[i][j] *= 0.90;
			}
		}

		for (int ant = 0; ant < N; ant++)
		{
			for (int step = 0; step < N; step++)
			{
				int from = ways[ant][step];
				int to = ways[ant][step + 1];
				pheromones[from][to] += 1.0 / distances[ant];
				pheromones[to][from] += 1.0 / distances[ant];
			}
		}

		for (int i = 0; i < N; i++)
		{
			delete[] ways[i];
			delete[] visited[i];
		}
		delete[] ways;
		delete[] visited;
		delete[] distances;

		cout << "Итерация " << iteration + 1 << ":" << endl;
		cout << "Лучший маршрут: ";
		for (int i = 0; i <= N; i++)
		{
			cout << bestWay[i] << " ";
		}
		cout << endl;
		cout << "Длина маршрута: " << bestDistance << endl;
	}

	for (int i = 0; i < N; i++) {
		delete[] graph[i];
		delete[] pheromones[i];
	}
	delete[] graph;
	delete[] pheromones;
	delete[] bestWay;

	return 0;
}