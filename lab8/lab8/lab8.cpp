// lab8.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <fstream>
#include <regex>

using namespace std;

class CompactHRU
{
    map <pair<int, int>, set<char>> _system;
    vector<int> _deletedSubjects;
    int _n;
    int _m;

public:

    CompactHRU()
    {
        _n = 0;
        _m = 0;
    }

    CompactHRU(int n, int m)
    {
        _n = n;
        _m = m;
    }

    void AddEnter(int i, int j, char p)
    {
        if (find(_deletedSubjects.begin(), _deletedSubjects.end(), i) == _deletedSubjects.end())
        {
            pair<int, int> pair = make_pair(i, j);
            _system[pair].insert(p);
        }
    }

    void DeleteEnter(int i, int j, char p)
    {
        if (find(_deletedSubjects.begin(), _deletedSubjects.end(), i) == _deletedSubjects.end())
        {
            pair<int, int> pair = make_pair(i, j);
            _system[pair].erase(p);
            
            if (_system[pair].size() == 0)
            {
                _system.erase(pair);
            }
        }
    }

    string AddSubject(string name)
    {
        string registrationInf;

        if (_deletedSubjects.size() != 0)
        {
            registrationInf = "Subject " + name + " registrated as " + to_string(_deletedSubjects[_deletedSubjects.size() - 1]);
            _deletedSubjects.pop_back();
        }
        else
        {
            registrationInf = "Subject " + name + " registrated as " + to_string(_n);
            _n++;
        }

        return registrationInf;
    }

    void DeleteSubject(int index)
    {
        if (find(_deletedSubjects.begin(), _deletedSubjects.end(), index) == _deletedSubjects.end())
        {
            vector<map<pair<int, int>, set<char>>::iterator> toDelete;

            for (auto iter = _system.begin(); iter != _system.end(); iter++)
            {
                if (iter->first.first == index)
                {
                    toDelete.push_back(iter);
                }
            }

            for (int i = 0; i < toDelete.size(); i++)
            {
                _system.erase(toDelete[i]);
            }

            _deletedSubjects.push_back(index);
        }
    }

    double GetMatrixFullness()
    {
        return ((_system.size() / (float)(_n * _m)) * 100);
    }

    vector<int> GetSubjectsList(int index)
    {
        vector<int> subjectsList;

        for (auto iter = _system.begin(); iter != _system.end(); iter++)
        {
            if (iter->first.second == index)
            {
                subjectsList.push_back(iter->first.first);
            }
        }

        return subjectsList;
    }

};


vector<string> split(const string& input, const string& regex)
{

    // passing -1 as the submatch index parameter performs splitting
    std::regex re(regex);
    std::sregex_token_iterator
        first{ input.begin(), input.end(), re, -1 },
        last;
    return { first, last };

}


int main()
{
    CompactHRU system;
    string systemInputPath = "in1.txt";
    map <string, int> commandList = { {"ADDS",1},{"DELS",2},{"GETPERC",3},{"GETLIST",4},{"ENTER",5},{"DELENTER",6} };

    ifstream input(systemInputPath);

    if (input.is_open())
    {

        int n;
        int m;
        string nn;
        string mm;

        getline(input, nn);
        getline(input, mm);

        n = stoi(nn);
        m = stoi(mm);

        system = CompactHRU(n, m);

        for (int i = 0; i < n; i++)
        {
            string tempString;
            getline(input, tempString);
            vector<string> tempVecString = split(tempString, ";");


            for (int j = 0; j < m; j++)
            {
                vector<string> tempVecSet = split(tempVecString[j], " ");

                for (int c = 0; c < tempVecSet.size(); c++)
                {
                    if (tempVecSet[c] != "")
                    {
                        system.AddEnter(i, j, tempVecSet[c][0]);
                    }
                }
            }
        }

        input.close();
    }

    string tempString = "";

    while (tempString != "EXIT")
    {
        getline(cin, tempString);
        vector<string> tempVecString = split(tempString, " ");

        // commands
        // 1 -  ADDS name
        // 2 -  DELS i
        // 3 -  GETPERC
        // 4 -  GETLIST j
        // 5 -  ENTER i j p
        // 6 -  DELENTER i j p 


        switch (commandList[tempVecString[0]])
        {
        case 1:
            cout << system.AddSubject(tempVecString[1])<<endl;
            break;
        case 2:
            system.DeleteSubject(atoi(tempVecString[1].c_str()));
            break;
        case 3:
            cout << "matrix fullness : " << system.GetMatrixFullness() << "%" << endl;
            break;
        case 4:
            system.GetSubjectsList(atoi(tempVecString[1].c_str())); // перегрузить оператор >> для вектора
            break;
        case 5:
            system.AddEnter(atoi(tempVecString[1].c_str()), atoi(tempVecString[2].c_str()), tempVecString[3][0]);
            break;
        case 6:
            system.DeleteEnter(atoi(tempVecString[1].c_str()), atoi(tempVecString[2].c_str()), tempVecString[3][0]);
            break;
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
