#include <iostream>
#include <vector>
using namespace std;

vector<int> Subsequence(const vector<int>& num)
{
	if (num.empty()) {
		return {};
	}

	int a = num.size();
	int length = 1;
	int index = 0;
	vector<int> sub(a, 1); //макс подпосл
	vector<int> vosst(a, -1); //восстановление пути

	for (int i = 0; i < a; i++) {
		for (int j = 0; j < i; ++j) {
			if (num[i] >= num[j] && sub[i] < sub[j] + 1) { // 5 6 12 24
				sub[i] = sub[j] + 1;
				vosst[i] = j;
			}
		}
		if (sub[i] > length) { // 5 6 7 8
			length = sub[i];
			index = i;
		}
	}

	vector<int> restore(length);
	int currIndex = index;
	for (int i = length - 1; i >= 0; --i) {
		restore[i] = num[currIndex];
		currIndex = vosst[currIndex];
	}
	return restore;
}

int main()
{
	setlocale(LC_ALL, "ru");
	int n;
	cout << "Введите кол-во элементов последовательности: ";
	cin >> n;

	vector<int> num(n);
	cout << "Введите элементы последовательности: ";
	for (int i = 0; i < n; i++) {
		cin >> num[i];
	}

	vector<int> result = Subsequence(num);
	cout << "Максимальная возрастающая подпоследовательность: ";
	for (int z : result) {
		cout << z << " ";
	}
	cout << endl;

	return 0;
}