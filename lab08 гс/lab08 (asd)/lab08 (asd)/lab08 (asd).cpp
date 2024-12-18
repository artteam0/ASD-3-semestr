#include <string>
#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;

struct Item {
	string name;
	int price;
	int weight;
};

int func(int N, const vector<Item>& items, vector<Item>& selectedItems) {
	int itemCount = items.size();

	vector<vector<int>> dp(itemCount + 1, vector<int>(N + 1, 0));

	for (int i = 1; i <= itemCount; ++i) {
		for (int w = 1; w <= N; ++w) {
			if (items[i - 1].weight <= w) {
				dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - items[i - 1].weight] + items[i - 1].price);
			}
			else {
				dp[i][w] = dp[i - 1][w];
			}
		}
	}

	int w = N;
	for (int i = itemCount; i > 0 && w > 0; --i) {
		if (dp[i][w] != dp[i - 1][w]) {
			selectedItems.push_back(items[i - 1]);
			w = w - items[i - 1].weight;
		}
	}
	return dp[itemCount][N];
}

int main()
{
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int N;
	cout << "Максимальная вместимость рюкзака: ";
	cin >> N;
	int itemCount;
	cout << "Кол-во товаров: ";
	cin >> itemCount;

	vector<Item> items;
	for (int i = 0; i < itemCount; i++) {
		Item item;
		cout << "Название товара: ";
		cin >> item.name;
		cout << "Вес товара: ";
		cin >> item.weight;
		cout << "Цена товара: ";
		cin >> item.price;
		items.push_back(item);
	}

	vector<Item> selectedItems;
	int max = func(N, items, selectedItems);

	cout << "Макс стоимость предметов, которые можно положить в рюкзак: " << max << endl;
	cout << "Выбранные предметы: " << endl;
	for (auto item : selectedItems) {
		cout << "Название: " << item.name << ", вес: " << item.weight << ", цена: " << item.price << endl;
	}
}