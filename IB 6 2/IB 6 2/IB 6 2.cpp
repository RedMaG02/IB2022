// IB 6 2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>

using namespace std;


bool CheckSystem(vector<vector<bool>> a, vector<int> ls, vector<int> lo)
{
	// w = true r = false
	for (int i = 0; i < ls.size(); i++)
	{
		for (int j = 0; j < lo.size(); j++)
		{
			if (!((ls[i] > lo[j] && a[i][j]) || (ls[i] <= lo[j] && !(a[i][j]))))
			{
				return false;
			}
		}
	}
	return true;
}

bool GetVectorsForSystem(const vector<vector<bool>>& a, vector<int>& ls, vector<int>& lo)
{
	ls.clear();
	lo.clear();

	for (int i = 0; i < a.size(); i++)
	{
		int cnt_s = 1;

		for (int j = 0; j < a[i].size(); j++)
		{
			if (a[i][j])
			{
				cnt_s++;
			}
		}

		ls.push_back(cnt_s);
	}

	for (int i = 0; i < a[0].size(); i++)
	{
		int min = 1;

		for (int j = 0; j < a.size(); j++)
		{
			if (!a[j][i] && ls[j] > min)
			{
				min = ls[j];
			}
		}
		lo.push_back(min);
	}

	return CheckSystem(a, ls, lo);
}

void CreateSystem(vector<vector<bool>>& a, vector<int>& ls, vector<int>& lo)
{

	for (int i = 0; i < ls.size(); i++)
	{
		ls[i] = rand() % 10 + 1;
	}
	for (int i = 0; i < lo.size(); i++)
	{
		lo[i] = rand() % 10 + 1;
	}
	// w = true r = false
	for (int i = 0; i < ls.size(); i++)
	{
		for (int j = 0; j < lo.size(); j++)
		{
			if (ls[i] > lo[j])
			{
				a[i][j] = true;
			}
			else
			{
				a[i][j] = false;
			}
		}
	}
}


int main()
{
	vector<vector<bool>> matrixA;
	int n, m;
	cin >> n >> m;
	matrixA.resize(n);
	for (int i = 0; i < n; i++)
	{
		matrixA[i].resize(m);
	}
	vector<int> ls;
	ls.resize(n);
	vector<int> lo;
	lo.resize(m);
	CreateSystem(matrixA, ls, lo);
	for (int i = 0; i < ls.size(); i++)
	{
		cout << ls[i] << " ";
	}

	cout << endl;

	for (int i = 0; i < lo.size(); i++)
	{
		cout << lo[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < ls.size(); i++)
	{
		for (int j = 0; j < lo.size(); j++)
		{
			if (matrixA[i][j])
			{
				cout << "W";
			}
			else
			{
				cout << "R";
			}
		}
		cout << endl;
	}
	if (CheckSystem(matrixA, ls, lo))
	{
		cout << "SYSTEM SECURE" << endl;
	}
	else
	{
		cout << "SYSTEM UNSECURED" << endl;
	}
	if (GetVectorsForSystem(matrixA, ls, lo))
	{
		cout << "SECURE SYSTEM EXISTS VECTORS: " << endl;

		for (int i = 0; i < ls.size(); i++)
		{
			cout << ls[i] << " ";
		}

		cout << endl;

		for (int i = 0; i < lo.size(); i++)
		{
			cout << lo[i] << " ";
		}
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
