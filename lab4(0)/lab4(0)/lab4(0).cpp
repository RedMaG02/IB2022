#include<iostream>
#include<fstream>
#include<list>
#include<vector>

using namespace std;

class CombinationsK2 
{
	vector<int> elements;
	vector<int> current;
	int n;

public: CombinationsK2(const vector<int>& l) 
	{
		elements = l;

		current.push_back(0);
		current.push_back(1);

		n = elements.size();
	}

public: bool Last() 
	{
		if (current[0] == n - 1 && current[1] == n)
			return true;
		else
			return false;
	}

public: vector<int> Current()
{
	vector<int> values(2);
	values[0] = elements[current[0]];
	values[1] = elements[current[1]];
	return values;
};

public: void Next()
	{
		current[1]++;
		if (current[1] < n)
		{

		}
		else 
		{
			current[0]++;
			current[1] = current[0] + 1;
		}
	}
};


vector<int> DeleteElements(const vector<int>& reduct, const vector<int>& sub) 
{
	vector<int> res;

	for (int i = 0; i < reduct.size(); i++) 
	{
		bool flag = true;

		for (int j = 0; j < sub.size(); j++)
		{
			if (reduct[i] == sub[j])
			{
				flag = false;
				break;
			}
		}
		if (flag)
		{
			res.push_back(reduct[i]);
		}
	}

	return res;
}

int main() 
{
	vector<int> elements = { 0, 1, 2, 3, 4, 5, 6, 7 };
	CombinationsK2 positionFor2(elements);

	ofstream fout("output.txt");
	if (fout.is_open())
	{
		while (!positionFor2.Last())
		{
			vector<int> pos2 = positionFor2.Current();
			vector<int> deletedVector = DeleteElements(elements, pos2);
			CombinationsK2 positionFor5(deletedVector);

			while (!positionFor5.Last())
			{
				vector<int> pos5 = positionFor5.Current();
				vector<int> pos7 = DeleteElements(deletedVector, pos5);
				vector<int> comb(8);

				for (int i = 0; i < pos2.size(); i++)
				{
					comb[pos2[i]] = 2;
				}
				for (int i = 0; i < pos5.size(); i++)
				{
					comb[pos5[i]] = 5;
				}
				for (int i = 0; i < pos7.size(); i++)
				{
					comb[pos7[i]] = 7;
				}

				for (int i = 0; i < comb.size(); i++)
				{
					fout << comb[i];
				}
				fout << endl;

				positionFor5.Next();
			}
			positionFor2.Next();
		}
		fout.close();
	}
}