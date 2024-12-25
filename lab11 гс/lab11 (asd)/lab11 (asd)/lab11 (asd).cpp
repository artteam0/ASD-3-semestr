#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <unordered_set>

using namespace std;

void fisherYatesShuffle(vector<int>& arr) {
    for (int i = arr.size() - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(arr[i], arr[j]);
    }
}

int main() {
    setlocale(0, "");
    srand(time(NULL));
    vector<int> zeks(100);
    vector<int> boxes(100);
    vector<int> boxesContent(100);

    for (int i = 0; i < 100; i++) {
        zeks[i] = i + 1;
        boxes[i] = i + 1;
        boxesContent[i] = -1;
    }

    unordered_set<int> unique;
    for (int i = 0; i < 100; i++) {
        int temp;
        do {
            temp = rand() % 100;
        } while (unique.find(temp) != unique.end());

        boxesContent[i] = temp;
        unique.insert(temp);
    }

    int N;
    cout << "Кол-во итераций: ";
    cin >> N;
    int success1 = 0, success2 = 0;

    for (int round = 0; round < N; round++) {
        bool allSuccess1 = true;
        bool allSuccess2 = true;

        fisherYatesShuffle(boxesContent);

        for (int j = 0; j < 100; j++) {
            bool foundRandom = false;
            for (int box = 0; box < 50; box++) {
                int randomBox = rand() % 100;
                if (boxesContent[randomBox] == j) {
                    foundRandom = true;
                    break;
                }
            }

            if (!foundRandom) {
                allSuccess1 = false;
            }

            int boxIndex = j;
            bool foundFollow = false;
            for (int box = 0; box < 50; box++) {
                boxIndex = boxesContent[boxIndex];
                if (boxIndex == j) {
                    foundFollow = true;
                    break;
                }
            }
            if (!foundFollow) {
                allSuccess2 = false;
            }
        }

        if (allSuccess1) success1++;
        if (allSuccess2) success2++;
    }

    cout << "\nСравнение:\n";
    cout << "Алгоритм случайного выбора: " << success1 << "\n";
    cout << "Алгоритм выбора номера в коробке: " << success2 << "\n";

    return 0;
}