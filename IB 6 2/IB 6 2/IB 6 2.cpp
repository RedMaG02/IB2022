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
		int cnt_o = 1;

		for (int j = 0; j < a.size(); j++)
		{
			if (!a[j][i])
			{
				cnt_o++;
			}
		}
		lo.push_back(cnt_o);
	}

	return CheckSystem(a, ls, lo);
}

int main()
{
    std::cout << "Hello World!\n";
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
