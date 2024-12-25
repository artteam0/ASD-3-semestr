#include <iostream>
#include <vector>
#include <random>
#include <numeric>
#include <iomanip>

using namespace std;


void addCity(int& size, vector<vector<int>>& matrix, pair<pair<int, int>, int>*& arr)
{
	cout << "\n Добавление города:\n";

	size += 1;
	vector<vector<int>> tempMatrix(size, (vector<int>(size, 0))); //с увеличенным размером

	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - 1; j++)
		{
			tempMatrix[i][j] = matrix[i][j]; //из старой
		}
	}


	for (int i = 1; i < size; i++)
	{
		cout << i << " -> " << size << ':'; //расстояние до нового
		cin >> tempMatrix[i - 1][size - 1];

	}


	for (int i = 1; i < size; i++)
	{
		cout << size << " -> " << i << ':'; //от нового
		cin >> tempMatrix[size - 1][i - 1];
	}

	matrix = vector<vector<int>>(size, (vector<int>(size, 0))); //обн
	matrix = tempMatrix;


	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << setw(3) << setfill(' ') << matrix[i][j] << " "; //вывод новой м
		}
		cout << '\n';
	}


	arr = new pair<pair<int, int>, int>[(size * size) - size]; 
	int k = 0;

	for (int i = 1; i <= size; i++)
	{
		for (int j = 1; j <= size; j++)
		{
			if (i == j) continue; //скип петли

			arr[k].first.first = i, arr[k].first.second = j, arr[k].second = matrix[i - 1][j - 1];

			k += 1;
		}
	}
	cout << "\n-------------------------------------------------------------------------------------\n";
	for (int i = 0; i < size * size - size; i++)
	{
		cout << arr[i].first.first << " -> " << arr[i].first.second << "  : " << arr[i].second << '\n'; //вывод 
	}

}




void deleteCity(int& size, vector<vector<int>>& matrix, pair<pair<int, int>, int>*& arr) {
	cout << "\nУдаление города: \n";
	if (size <= 1) {
		cout << "Удаление невозможно: в графе должен остаться хотя бы один город.\n";
		return;
	}

	cout << "Введите номер города для удаления (1-" << size << "): ";
	int cityToDelete;
	cin >> cityToDelete;

	if (cityToDelete < 1 || cityToDelete > size) {
		cout << "Ошибка: введен некорректный номер города.\n";
		return;
	}

	int newSize = size - 1; //уменьшаем размер
	vector<vector<int>> tempMatrix(newSize, vector<int>(newSize, 0));

	int offsetRow = 0, offsetCol = 0; 
	for (int i = 0; i < size; ++i) { //переносим данные, исключая удаляемый город
		if (i + 1 == cityToDelete) {
			offsetRow = 1; //строка
			continue;
		}
		offsetCol = 0;
		for (int j = 0; j < size; ++j) {
			if (j + 1 == cityToDelete) {
				offsetCol = 1; //скип удаляемого (столбец)
				continue;
			}
			tempMatrix[i - offsetRow][j - offsetCol] = matrix[i][j];
		}
	}

	matrix = tempMatrix;
	size = newSize;

	delete[] arr; 	//пересоздаем массив arr
	arr = new pair<pair<int, int>, int>[(size * size) - size];
	int k = 0;

	for (int i = 1; i <= size; i++) {
		for (int j = 1; j <= size; j++) {
			if (i == j) continue;
			arr[k].first.first = i;
			arr[k].first.second = j;
			arr[k].second = matrix[i - 1][j - 1];
			k++;
		}
	}

	cout << "\nОбновленная матрица смежности: \n";
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << setw(3) << setfill(' ') << matrix[i][j] << " ";
		}
		cout << '\n';
	}

	cout << "\nОбновленный список ребер:\n";
	for (int i = 0; i < size * size - size; i++) {
		cout << arr[i].first.first << " -> " << arr[i].first.second << "  : " << arr[i].second << '\n';
	}
	cout << "Город успешно удален!\n";
}

pair<vector<int>, int> crossoverOX(pair<vector<int>, int>& parent1, pair<vector<int>, int>& parent2, pair<pair<int, int>, int>* arr, int N) { //два родителя
	bool flag = false; //удалось ли создать
	int size = parent1.first.size(); //размер маршрута
	pair<vector<int>, int> child = make_pair(vector<int>(size, 0), 0); //потомок с пустым маршем

	do
	{
		child = make_pair(vector<int>(size, 0), 0); //ген случайного
		int start = rand() % size;
		int end = rand() % size;

		if (start > end) swap(start, end); //start <= end

		for (int i = start; i <= end; ++i) {
			child.first[i] = parent1.first[i]; //первая часть маршрута
		}

		int idx = (end + 1) % size; //вставка оставшихся городов
		for (int i = 0; i < size; ++i) {
			int gene = parent2.first[(end + 1 + i) % size]; //город в par2 с end+1+i
			if (find(child.first.begin(), child.first.end(), gene) == child.first.end()) { //не содержится в потомке
				child.first[idx] = gene; //добавляем
				idx = (idx + 1) % size;
			}
		}

		child.second = 0;
		for (int i = 0; i < child.first.size() - 1; i++)
		{
			flag = false;
			for (int j = 0; j < N; j++)
			{
				if (arr[j].first.first == child.first[i] && arr[j].first.second == child.first[i + 1]) //если ребро существует
				{
					flag = true;
					child.second += arr[j].second;
				}
			}
			if (flag == false) break; //марш false
		}
	} while (!flag);

	return child;
}

void mutate(pair<vector<int>, int>& individual, pair<pair<int, int>, int>* arr, int N) { //копирование маршрута
	int size = individual.first.size();
	int idx1 = rand() % size;
	int idx2 = rand() % size;
	swap(individual.first[idx1], individual.first[idx2]); //два рандомных индекса меняются

	individual.second = 0; //стоимость с нуля
	for (int i = 0; i < individual.first.size() - 1; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (arr[j].first.first == individual.first[i] && arr[j].first.second == individual.first[i + 1]) //пара город город
			{
				individual.second += arr[j].second;
			}
		}
	}

}


pair<vector<int>, int> selectParent(vector<pair<vector<int>, int>>& population, const vector<double>& fitness) { //хромосома +стоимость
	double totalFitness = accumulate(fitness.begin(), fitness.end(), 0.0); //сумма пригодности
	double randomValue = ((double)rand() / RAND_MAX) * totalFitness; //диапазон 0 - fitness

	double cumulativeFitness = 0.0;
	for (size_t i = 0; i < fitness.size(); ++i) {
		cumulativeFitness += fitness[i];
		if (cumulativeFitness >= randomValue) {
			return population[i];
		}
	}
	return population.back();
}


vector<pair<vector<int>, int>> generateInitialPopulation(int populationSize, int cityCount, pair<pair<int, int>, int>* arr, int N) {
	srand(time(NULL));

	vector<pair<vector<int>, int>> population(populationSize, make_pair(vector<int>(cityCount, 0), 0)); //инициализация популяции

	for (auto& solo : population) {
		bool valid = false;
		do {
			iota(solo.first.begin(), solo.first.end(), 1); //заполнение маршрута городами
			shuffle(solo.first.begin(), solo.first.end(), mt19937(random_device()())); //перемешивание

			solo.second = 0;
			valid = true; //изначально ок

			for (int i = 0; i < cityCount - 1; i++) {
				bool matchFound = false;

				for (int j = 0; j < N; j++) {
					if (arr[j].first.first == solo.first[i] && arr[j].first.second == solo.first[i + 1]) {
						matchFound = true;
						solo.second += arr[j].second;
						break;
					}
				}

				if (!matchFound) {
					valid = false;
					break;
				}
			}
		} while (!valid);
	}
	return population;
}


void main()
{
	setlocale(LC_ALL, "Rus");

	int size = 8;
	pair<pair<int, int>, int>* arr = new pair<pair<int, int>, int>[(size * size) - size];



	//vector<vector<int>> matrix = {
	//{ 0,  25, 19, 31, 27 },               //1
	//{ 5,  0,  17, 30, 25 },               //2
	//{ 19, 15, 0,  6,  1  },               //3
	//{ 9,  50, 24, 0,  6  },               //4
	//{ 22, 8,  7,  10, 0  },               //5
	//};

	vector<vector<int>> matrix = {
	{ 0,  8,  11, 12, 40, 22, 9,  5  }, //1
	{ 8,  0,  9,  8,  19, 23, 4,  11 }, //2
	{ 11, 9,  0,  1,  31, 16, 9,  5  }, //3
	{ 12, 8,  1,  0,  14, 11, 33, 24 }, //4
	{ 40, 19, 31, 14, 0,  30, 7,  20 }, //5
	{ 22, 23, 16, 11, 30, 0,  15, 2  }, //6
	{ 9,  4,  9,  33, 7,  15, 0,  2  }, //7
	{ 5,  11, 5,  24, 20, 2,  2,  0  } //8
	};

	int k = 0;
	for (int i = 1; i <= size; i++)
	{
		for (int j = 1; j <= size; j++)
		{
			if (i == j) continue;

			arr[k].first.first = i, arr[k].first.second = j, arr[k].second = matrix[i - 1][j - 1];

			k += 1;
		}
	}



	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << setw(3) << setfill(' ') << matrix[i][j] << " ";
		}
		cout << "\n\n";
	}

	cout << "\n\n";

	for (int i = 0; i < size * size - size; i++)
	{
		cout << arr[i].first.first << " -> " << arr[i].first.second << "  : " << arr[i].second << '\n';
	}


	while (true)
	{
		int choice;
		cout << endl << endl << endl << "1.Do" << endl << "2.AddCity" << endl << "3.Delete" << endl << "4.Choice:";
		cin >> choice;

		switch (choice)
		{
		case 1:
		{
			cout << "\nНачальная популяция:";
			int startPopualation;
			cin >> startPopualation;



			cout << "\nЧисло эволюций:";
			int generations;
			cin >> generations;

			cout << "\nМутация:";
			double mutation;
			cin >> mutation;

			auto population = generateInitialPopulation(startPopualation, size, arr, size * size - size);
			cout << "\n\n\n";


			for (int generation = 0; generation < generations; ++generation) {
				vector<double> fitness(population.size());
				for (size_t i = 0; i < population.size(); ++i) {
					fitness[i] = 1.0 / population[i].second;
				}

				int bestIndex = 0;
				for (size_t i = 1; i < population.size(); ++i) {
					if (population[i].second < population[bestIndex].second) {
						bestIndex = i;
					}
				}
				pair<vector<int>, int> bestIndividual = population[bestIndex];

				vector<pair<vector<int>, int>> newPopulation;
				newPopulation.push_back(bestIndividual); 

				for (size_t i = 0; i < (population.size() - 1) / 2; ++i) {
					pair<vector<int>, int> parent1 = selectParent(population, fitness);
					pair<vector<int>, int> parent2 = selectParent(population, fitness);

					pair<vector<int>, int> child1 = crossoverOX(parent1, parent2, arr, size * size - size);
					pair<vector<int>, int> child2 = crossoverOX(parent2, parent1, arr, size * size - size);

					if (((double)rand() / RAND_MAX) < mutation) mutate(child1, arr, size * size - size);
					if (((double)rand() / RAND_MAX) < mutation) mutate(child2, arr, size * size - size);

					newPopulation.push_back(child1);
					newPopulation.push_back(child2);
				}

				population = move(newPopulation);

				int minDistance = INT_MAX;
				pair<vector<int>, int> bestInGeneration;
				for (const auto& individual : population) {
					if (individual.second < minDistance) {
						minDistance = individual.second;
						bestInGeneration = individual;
					}
				}
				cout << generation + 1 << ": ";
				for (const auto& city : bestInGeneration.first) {
					cout << "->" << city;
				}
				cout << ": " << bestInGeneration.second << '\n';
			}


			double bestFitness = -numeric_limits<double>::infinity();
			pair<vector<int>, int> bestIndividual;
			for (const auto& individual : population)
			{
				double currentFitness = 1.0 / individual.second;
				if (currentFitness > bestFitness) {
					bestFitness = currentFitness;
					bestIndividual = individual;
				}
			}

			cout << "\n\n\n";
			for (auto i : bestIndividual.first)
			{
				cout << "->" << i;
			}
			cout << "  " << bestIndividual.second;
			exit(69);
		}
		case 2:
		{
			addCity(size, matrix, arr);
			break;
		}
		case 3: {
			deleteCity(size, matrix, arr);
			break;
		}
		}
	}
}




























































































//#include <iostream>
//#include <vector>
//#include <climits>
//#include <algorithm>
//using namespace std;
//
//int N = 8;
//
//void Print(int**& graph)
//{
//	for (int i = 0; i < N; i++)
//	{
//		for (int j = 0; j < N; j++)
//		{
//			cout << graph[i][j] << " ";
//		}
//		cout << endl;
//	}
//}
//
//void Add(int**& graph)
//{
//	if (N >= 9) {
//		cout << "Колличество городов не может быть больше 8." << endl;
//		return;
//	}
//
//	N++;
//	int** newGraph = new int* [N];
//
//	for (int i = 0; i < N; i++) {
//		newGraph[i] = new int[N];
//	}
//
//	for (int i = 0; i < N - 1; i++) {
//		for (int j = 0; j < N - 1; j++) {
//			newGraph[i][j] = graph[i][j];
//		}
//	}
//
//	cout << "Введите расстояния от нового города к каждому из существующих:" << endl;
//	for (int i = 0; i < N - 1; i++) {
//		cout << "Расстояние от нового города к городу " << N + 1 << ": ";
//		cin >> newGraph[N - 1][i];
//	}
//
//	cout << "Введите расстояния от каждого из существующих городов к новому городу:" << endl;
//	for (int i = 0; i < N - 1; i++)
//	{
//		cout << "Расстояние от города " << i + 1 << " к новому городу: ";
//		cin >> newGraph[i][N - 1];
//	}
//
//	newGraph[N - 1][N - 1] = INT_MAX;
//
//	for (int i = 0; i < N - 1; i++) {
//		delete[] graph[i];
//	}
//	delete[] graph;
//
//	graph = newGraph;
//
//	Print(graph);
//}
//
//void Remove(int**& graph)
//{
//	if (N > 8) {
//		cout << "Количество городов не может быть меньше 8." << endl;
//		return;
//	}
//
//	int index = 0;
//
//	while (true) {
//		cout << "Введите номер удаляемого города: ";
//		cin >> index;
//		if (index <= 0 || index > N) {
//			cout << "Введен неверный номер города." << endl;
//		}
//		break;
//	}
//
//	index--;
//	int** newGraph = new int* [N - 1];
//
//	for (int i = 0; i < N - 1; i++) {
//		newGraph[i] = new int[N - 1];
//	}
//
//	for (int i = 0, newIndex = 0; i < N; i++)
//	{
//		if (i == index) continue;
//		for (int j = 0, newJ = 0; j < N; j++)
//		{
//			if (j == index) continue;
//			newGraph[newIndex][newJ] = graph[i][j];
//			++newJ;
//		}
//		++newIndex;
//	}
//
//	for (int i = 0; i < N; i++)
//	{
//		delete[] graph[i];
//	}
//	delete[] graph;
//
//	graph = newGraph;
//
//	N--;
//
//	Print(graph);
//}
//
//struct Individ {
//	string chromosome;
//	int fitness;
//};
//
//bool proverka(string str, char ch) {
//	for (int i = 0; i < str.length(); i++) {
//		if (str[i] == ch) {
//			return true;
//		}
//	}
//	return false;
//}
//
//int Random(int min, int max) {
//	return min + rand() % (max - min + 1);
//}
//
//string Create() {
//	string chromosome = "1";
//
//	while (true) {
//		if (chromosome.length() == N) {
//			chromosome += chromosome[0];
//			break;
//		}
//		int temp = Random(1, N);
//
//		if (!proverka(chromosome, (char)(temp + '0')))
//			chromosome += (char)(temp + '0');
//	}
//	return chromosome;
//}
//
//string Mutation(string chromo) {
//	while (true) {
//		int gen1 = Random(1, N);
//		int gen2 = Random(1, N);
//
//		if (gen1 != gen2) {
//			swap(chromo[gen1], chromo[gen2]);
//			break;
//		}
//	}
//	return chromo;
//}
//
//int Fitness(string chromosome, int**& graph) {
//	int f = 0;
//	for (int i = 0; i < chromosome.length() - 1; i++) {
//		int from = chromosome[i] - '1'; 
//		int to = chromosome[i + 1] - '1';
//
//		if (graph[from][to] == INT_MAX)
//			return INT_MAX;
//
//		f += graph[from][to];
//	}
//	return f;
//}
//
//void bubbleSort(Individ* population, int populationSize) {
//	for (int i = 0; i < populationSize - 1; i++) {
//		for (int j = 0; j < populationSize - i - 1; j++) {
//			if (population[j].fitness > population[j + 1].fitness) {
//				swap(population[j], population[j + 1]);
//			}
//		}
//	}
//}
//
//bool wasFirst = false;
//
//string Child(string par1, string par2) {
//	int point = Random(1, N - 2); //tочка разделения хромосом
//	string chromo;
//
//	if (!wasFirst) {
//		chromo = par1.substr(0, point);
//
//		for (char gene : par2) {
//			if (chromo.find(gene) == string::npos) {
//				chromo += gene;
//			}
//		}
//		wasFirst = true;
//	}
//	else {
//		chromo = par2.substr(0, point);
//
//		for (char gene : par1) {
//			if (chromo.find(gene) == string::npos) {
//				chromo += gene;
//			}
//		}
//		wasFirst = false;
//	}
//	chromo += chromo[0];
//
//	return chromo;
//}
//
//void runGenetic(int**& graph, int populationSize, int childCount, int evolutionCount, int mutationPercent, int crossCount) {
//	int generationCount = 1;
//	int premStop = 0;
//	Individ* population = new Individ[populationSize];
//
//	for (int i = 0; i < populationSize; i++) {
//		Individ buf;
//		buf.chromosome = Create();
//		buf.fitness = Fitness(buf.chromosome, graph);
//		population[i] = buf;
//	}
//
//	bubbleSort(population, populationSize);
//	string best = population[0].chromosome;
//
//	for (int i = 0; i < evolutionCount && premStop < 25; i++) {
//		if (best != population[0].chromosome) {
//			best = population[0].chromosome;
//			premStop = 0;
//		}
//
//		Individ* newPopulation = new Individ[populationSize + crossCount * childCount];
//		int ind = 0;
//		for (ind = 0; ind < populationSize; ind++) {
//			newPopulation[ind] = population[ind];
//		}
//
//		for (int j = 0; j < crossCount; j++) {
//			while (true) {
//				int parent1 = Random(0, populationSize - 1);
//				int parent2 = Random(0, populationSize - 1);
//				if (parent1 != parent2) {
//					for (int k = 0; k < childCount; k++) {
//						string chromo = Child(population[parent1].chromosome, population[parent2].chromosome);
//						if (mutationPercent <= Random(0, 100)) {
//							chromo = Mutation(chromo);
//						}
//						int fitness = Fitness(chromo, graph);
//						newPopulation[ind++] = { chromo, fitness };
//					}
//					break;
//				}
//			}
//		}
//		bubbleSort(newPopulation, ind);
//		for (int j = 0; j < populationSize; j++) {
//			population[j] = newPopulation[j];
//		}
//		premStop++;
//	}
//	cout << "Лучшая хромосома: " << population[0].chromosome << ", с приспособленностью: " << population[0].fitness << endl;
//}
//
//
//int main()
//{
//	setlocale(LC_ALL, "rus");
//
//	int populationSize;
//	const int N = 8;
//
//	srand(time(0));
//	int gr[N][N] = {
//		{INT_MAX, 25, 40, 31, 27, 13, 56, 9},
//		{5, INT_MAX, 17, 30, 25, 6, 9, 34},
//		{19, 15, INT_MAX, 6, 9, 23, 8, 19},
//		{9, 50, 24, INT_MAX, 6, 24, 14, 9},
//		{22, 8, 7, 10, INT_MAX, 9, 18, 6},
//		{14, 18, 23, 40, 21, INT_MAX, 23, 67},
//		{25, 12, 34, 9, 12, 5, INT_MAX, 18},
//		{16, 12, 19, 27, 28, 31, 9, INT_MAX}
//	};
//
//	int** graph = new int* [N];
//	for (int i = 0; i < N; ++i) {
//		graph[i] = new int[N];
//		for (int j = 0; j < N; ++j) {
//			graph[i][j] = gr[i][j];
//		}
//	}
//
//	while (true)
//	{
//		cout << "Введите размер популяции: ";
//		cin >> populationSize;
//		if (populationSize < 2)
//		{
//			cout << "Популяция не может быть меньше 2!" << endl;
//			continue;
//		}
//		break;
//	}
//
//	Print(graph);
//
//	int answer = 0;
//
//	while (true)
//	{
//		cout << "Вы хотите изменить начальный граф? (0 - нет, 1 - да): ";
//		cin >> answer;
//		if (answer < 0 || answer > 1)
//		{
//			cout << "Вы ввели неправильное значение!" << endl;
//			continue;
//		}
//		break;
//	}
//
//	if (answer)
//	{
//		while (true)
//		{
//			int choice = 0;
//			cout << endl;
//			cout << "Что вы хотите сделать?" << endl;
//			cout << "1 - добавить город" << endl;
//			cout << "2 - удалить город" << endl;
//			cout << "0 - выход" << endl;
//			cout << endl;
//			cin >> choice;
//
//			if (choice == 0)
//			{
//				break;
//			}
//
//			switch (choice)
//			{
//			case 1:
//				Add(graph);
//				break;
//			case 2:
//				Remove(graph);
//				break;
//			default:
//				cout << "Вы ввели неправильное значение" << endl;
//			}
//		}
//	}
//
//	int childCount;
//	while (true)
//	{
//		cout << "Введите количество потомков при одном скрещивании: ";
//		cin >> childCount;
//		if (childCount < 1)
//		{
//			cout << "Количество потомков не может быть меньше 1!" << endl;
//			continue;
//		}
//		break;
//	}
//
//	int crossCount;
//	while (true)
//	{
//		cout << "Введите количество скрещиваний: ";
//		cin >> crossCount;
//		if (crossCount < 1)
//		{
//			cout << "Количество скрещиваний не может быть меньше 1!" << endl;
//			continue;
//		}
//		break;
//	}
//
//	int evolutionCount;
//	while (true)
//	{
//		cout << "Введите количество эволюций: ";
//		cin >> evolutionCount;
//		if (evolutionCount < 0)
//		{
//			cout << "Количество эволюций не может быть меньше 0!" << endl;
//			continue;
//		}
//		break;
//	}
//
//	int mutationPercent;
//	while (true)
//	{
//		cout << "Введите показатель по мутации: ";
//		cin >> mutationPercent;
//		if (mutationPercent < 0 || mutationPercent > 100)
//		{
//			cout << "Показатель по мутации должен находиться в пределах от 0 до 100!" << endl;
//			continue;
//		}
//		break;
//	}
//
//	runGenetic(graph, populationSize, childCount, evolutionCount, mutationPercent, crossCount);
//
//	for (int i = 0; i < N; ++i) {
//		delete[] graph[i];
//	}
//	delete[] graph;
//
//	return 0;
//}