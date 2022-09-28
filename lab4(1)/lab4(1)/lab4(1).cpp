// lab4(1).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool IsSimple(int candidate)
{
    for (int i = candidate - 1; i > 1; i--)
    {
        if (candidate % i == 0) return false;     
    }
    return true;
}

vector<int> GetCombinations(int multNum)
{
    vector<int> combVector;

    for (int candidate = 1111; candidate < 10000; candidate++)
    {
        int check = candidate;
        int mult = 1;

        while (check)
        {
            mult *= check % 10;
            check /= 10;
        }

        if (mult == multNum && IsSimple(candidate))
        {
            combVector.push_back(candidate);
        }

    }
    
    return combVector;
}

void Output(vector<int> resultVector)
{
    ofstream fout("output.txt");

    if (fout.is_open())
    {
        fout << resultVector.size() << " ";

        for (int i = 0; i < resultVector.size(); i++)
        {
            fout << resultVector[i] << " ";
        }
    }
    else
    {
        cout << "file does not exist.";
    }
    
    fout.close();
}


int main()
{
    vector<int> testVector;
    testVector = GetCombinations(243);
    Output(testVector);
}
