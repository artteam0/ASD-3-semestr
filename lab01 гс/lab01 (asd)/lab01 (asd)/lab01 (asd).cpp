#include <iostream>
#include "chrono"
using namespace std;

int num = 0;

void Hanoi(int ringNum, int from, int to)
{
	if (ringNum == 1) 
	{
		num += 1;
		cout << "Переместить диск " << ringNum << " с " << from << " на " << to << " стержень" << endl;
	}
	else
	{
		num += 1;

		int temp = 6 - from - to;

		Hanoi(ringNum - 1, from, temp);
		cout << "Переместить диск " << ringNum << " с " << from << " на " << to << " стержень" << endl;
		Hanoi(ringNum - 1, temp, to);
	}
}

int main()
{
	setlocale(LC_ALL, "ru");
	int start_pole, end_pole, planeNum;

	cout << "Номер первого столбика: ";
	cin >> start_pole;
	if (start_pole == 0 || start_pole > 3)
	{
		cout << "erRor." << endl;
		return 0;
	}

	cout << "Номер конечного столбика: ";
	cin >> end_pole;
	if (end_pole == 0 || end_pole > 3)
	{
		cout << "erRor." << endl;
		return 0;
	}

	cout << "Количество дисков: ";
	cin >> planeNum;
	if (planeNum == 0)
	{
		cout << "Количество дисков не может быть равным нулю." << endl;
		exit(7);
	}

	float a = clock();
	Hanoi(planeNum, start_pole, end_pole);
	float b = clock();

	cout << "Количество ходов: " << num << endl;
	cout << "Время выполнения алгоритма: " << (b - a) / 1000 << endl;

	return 0;
}